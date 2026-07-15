#include "bos/ArchiveEngine.h"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include <zlib.h>

namespace bos::shell {

namespace {

constexpr quint32 ZIP_EOCD_SIGNATURE = 0x06054b50;
constexpr quint32 ZIP_CENTRAL_DIR_SIGNATURE = 0x02014b50;

quint16 readUInt16LE(const QByteArray &data, int offset)
{
    if (offset + 2 > data.size()) {
        return 0;
    }
    return static_cast<quint8>(data.at(offset))
           | (static_cast<quint8>(data.at(offset + 1)) << 8);
}

quint32 readUInt32LE(const QByteArray &data, int offset)
{
    if (offset + 4 > data.size()) {
        return 0;
    }
    return static_cast<quint8>(data.at(offset))
           | (static_cast<quint8>(data.at(offset + 1)) << 8)
           | (static_cast<quint8>(data.at(offset + 2)) << 16)
           | (static_cast<quint8>(data.at(offset + 3)) << 24);
}

QDateTime zipDateTime(quint16 dosDate, quint16 dosTime)
{
    const int year = ((dosDate >> 9) & 0x7F) + 1980;
    const int month = (dosDate >> 5) & 0x0F;
    const int day = dosDate & 0x1F;
    const int hour = (dosTime >> 11) & 0x1F;
    const int minute = (dosTime >> 5) & 0x3F;
    const int second = (dosTime & 0x1F) * 2;
    return QDateTime(QDate(year, qMax(1, month), qMax(1, day)),
                     QTime(hour, minute, second),
                     Qt::UTC);
}

qint64 parseOctal(const QByteArray &data, int offset, int length)
{
    QByteArray bytes = data.mid(offset, length).trimmed();
    // Remove trailing null and space characters.
    int end = 0;
    for (end = 0; end < bytes.size(); ++end) {
        const char c = bytes.at(end);
        if (c == '\0' || c == ' ') {
            break;
        }
    }
    bytes = bytes.left(end);
    bool ok = false;
    const qint64 value = bytes.toLongLong(&ok, 8);
    return ok ? value : 0;
}

QByteArray tarFileName(const QByteArray &header)
{
    QByteArray name = header.mid(0, 100);
    QByteArray prefix = header.mid(345, 155);
    int nameLen = name.indexOf('\0');
    if (nameLen >= 0) {
        name = name.left(nameLen);
    }
    int prefixLen = prefix.indexOf('\0');
    if (prefixLen >= 0) {
        prefix = prefix.left(prefixLen);
    }
    if (!prefix.isEmpty()) {
        return prefix + '/' + name;
    }
    return name;
}

bool isTarBlockZero(const QByteArray &block)
{
    for (char c : block) {
        if (c != '\0') {
            return false;
        }
    }
    return true;
}

QList<ArchiveEntry> parseTar(const QByteArray &data, bool *ok)
{
    QList<ArchiveEntry> entries;
    int offset = 0;
    while (offset + 512 <= data.size()) {
        const QByteArray header = data.mid(offset, 512);
        offset += 512;
        if (isTarBlockZero(header)) {
            // Two consecutive zero blocks mark the end of the archive.
            if (offset + 512 <= data.size() && isTarBlockZero(data.mid(offset, 512))) {
                break;
            }
            continue;
        }

        const QByteArray rawName = tarFileName(header);
        const qint64 size = parseOctal(header, 124, 12);
        const qint64 mtime = parseOctal(header, 136, 12);
        const char typeFlag = header.size() > 156 ? header.at(156) : '\0';

        ArchiveEntry entry;
        entry.setPath(QString::fromLocal8Bit(rawName));
        entry.setName(QString::fromLocal8Bit(QFileInfo(entry.path()).fileName().toUtf8()));
        entry.setSize(size);
        entry.setCompressedSize(size);
        entry.setModifiedDate(QDateTime::fromSecsSinceEpoch(mtime, Qt::UTC));
        entry.setIsDirectory(typeFlag == '5' || rawName.endsWith('/'));
        entries.append(entry);

        const qint64 blocks = (size + 511) / 512;
        offset += static_cast<int>(blocks * 512);
    }
    if (ok) {
        *ok = true;
    }
    return entries;
}

QByteArray gunzip(const QByteArray &input, bool *ok)
{
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

    // 16 + MAX_WBITS enables gzip decoding.
    int ret = inflateInit2(&strm, 16 + MAX_WBITS);
    if (ret != Z_OK) {
        if (ok) {
            *ok = false;
        }
        return QByteArray();
    }

    QByteArray output;
    constexpr int chunkSize = 65536;
    QByteArray buffer(chunkSize, Qt::Initialization::Uninitialized);

    strm.avail_in = static_cast<uInt>(input.size());
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(input.data()));

    do {
        strm.avail_out = chunkSize;
        strm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        ret = inflate(&strm, Z_NO_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            inflateEnd(&strm);
            if (ok) {
                *ok = false;
            }
            return QByteArray();
        }
        const int have = chunkSize - static_cast<int>(strm.avail_out);
        output.append(buffer.data(), have);
    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
    if (ok) {
        *ok = true;
    }
    return output;
}

QList<ArchiveEntry> readZipArchive(const QString &path, bool *ok)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if (ok) {
            *ok = false;
        }
        return {};
    }
    const QByteArray data = file.readAll();
    file.close();

    if (data.size() < 22) {
        if (ok) {
            *ok = false;
        }
        return {};
    }

    // Locate the End of Central Directory record.
    int eocdOffset = -1;
    constexpr int maxComment = 65535;
    const int searchStart = qMax(0, data.size() - static_cast<int>(maxComment) - 22);
    for (int i = data.size() - 22; i >= searchStart; --i) {
        if (readUInt32LE(data, i) == ZIP_EOCD_SIGNATURE) {
            eocdOffset = i;
            break;
        }
    }
    if (eocdOffset < 0) {
        if (ok) {
            *ok = false;
        }
        return {};
    }

    const quint16 totalEntries = readUInt16LE(data, eocdOffset + 8);
    const quint32 centralDirOffset = readUInt32LE(data, eocdOffset + 16);

    QList<ArchiveEntry> entries;
    int offset = static_cast<int>(centralDirOffset);
    for (quint16 i = 0; i < totalEntries; ++i) {
        if (offset + 46 > data.size()) {
            break;
        }
        if (readUInt32LE(data, offset) != ZIP_CENTRAL_DIR_SIGNATURE) {
            break;
        }

        const quint16 fileNameLength = readUInt16LE(data, offset + 28);
        const quint16 extraLength = readUInt16LE(data, offset + 30);
        const quint16 commentLength = readUInt16LE(data, offset + 32);
        const quint32 compressedSize = readUInt32LE(data, offset + 20);
        const quint32 uncompressedSize = readUInt32LE(data, offset + 24);
        const quint16 lastModTime = readUInt16LE(data, offset + 12);
        const quint16 lastModDate = readUInt16LE(data, offset + 14);
        const quint32 externalAttrs = readUInt32LE(data, offset + 38);

        const int nameOffset = offset + 46;
        QByteArray rawName = data.mid(nameOffset, fileNameLength);
        const QString entryPath = QString::fromUtf8(rawName);

        ArchiveEntry entry;
        entry.setPath(entryPath);
        entry.setName(QFileInfo(entryPath).fileName());
        entry.setSize(static_cast<qint64>(uncompressedSize));
        entry.setCompressedSize(static_cast<qint64>(compressedSize));
        entry.setModifiedDate(zipDateTime(lastModDate, lastModTime));
        const bool isDirByName = entryPath.endsWith('/');
        const bool isDirByAttr = (externalAttrs & 0x10) != 0;
        entry.setIsDirectory(isDirByName || isDirByAttr);
        entries.append(entry);

        offset += 46 + fileNameLength + extraLength + commentLength;
    }
    if (ok) {
        *ok = true;
    }
    return entries;
}

QList<ArchiveEntry> readTarArchive(const QString &path, bool *ok)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if (ok) {
            *ok = false;
        }
        return {};
    }
    QByteArray data = file.readAll();
    file.close();
    return parseTar(data, ok);
}

QList<ArchiveEntry> readTarGzArchive(const QString &path, bool *ok)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if (ok) {
            *ok = false;
        }
        return {};
    }
    const QByteArray compressed = file.readAll();
    file.close();

    bool decompressedOk = false;
    const QByteArray decompressed = gunzip(compressed, &decompressedOk);
    if (!decompressedOk) {
        if (ok) {
            *ok = false;
        }
        return {};
    }
    return parseTar(decompressed, ok);
}

} // anonymous namespace

QString ArchiveEngine::detectArchiveType(const QString &path)
{
    const QFileInfo info(path);
    const QString suffix = info.suffix().toLower();
    const QString completeSuffix = info.completeSuffix().toLower();

    if (suffix == QStringLiteral("zip")) {
        return QStringLiteral("zip");
    }
    if (completeSuffix == QStringLiteral("tar.gz") || completeSuffix == QStringLiteral("tgz")) {
        return QStringLiteral("tar.gz");
    }
    if (suffix == QStringLiteral("tar")) {
        return QStringLiteral("tar");
    }
    return QString();
}

QList<ArchiveEntry> ArchiveEngine::readArchive(const QString &path, bool *ok)
{
    const QString type = detectArchiveType(path);
    if (type == QStringLiteral("zip")) {
        return readZipArchive(path, ok);
    }
    if (type == QStringLiteral("tar")) {
        return readTarArchive(path, ok);
    }
    if (type == QStringLiteral("tar.gz")) {
        return readTarGzArchive(path, ok);
    }
    if (ok) {
        *ok = false;
    }
    return {};
}

} // namespace bos::shell
