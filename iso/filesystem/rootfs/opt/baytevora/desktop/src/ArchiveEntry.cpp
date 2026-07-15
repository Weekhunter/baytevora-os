#include "bos/ArchiveEntry.h"

namespace bos::shell {

ArchiveEntry::ArchiveEntry()
{
}

QString ArchiveEntry::name() const
{
    return m_name;
}

void ArchiveEntry::setName(const QString &name)
{
    m_name = name;
}

QString ArchiveEntry::path() const
{
    return m_path;
}

void ArchiveEntry::setPath(const QString &path)
{
    m_path = path;
}

qint64 ArchiveEntry::size() const
{
    return m_size;
}

void ArchiveEntry::setSize(qint64 size)
{
    m_size = size;
}

qint64 ArchiveEntry::compressedSize() const
{
    return m_compressedSize;
}

void ArchiveEntry::setCompressedSize(qint64 compressedSize)
{
    m_compressedSize = compressedSize;
}

bool ArchiveEntry::isDirectory() const
{
    return m_isDirectory;
}

void ArchiveEntry::setIsDirectory(bool isDirectory)
{
    m_isDirectory = isDirectory;
}

QDateTime ArchiveEntry::modifiedDate() const
{
    return m_modifiedDate;
}

void ArchiveEntry::setModifiedDate(const QDateTime &modifiedDate)
{
    m_modifiedDate = modifiedDate;
}

} // namespace bos::shell
