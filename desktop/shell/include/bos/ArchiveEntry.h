#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents one entry inside an archive document.
 *
 * ArchiveEntry is a value type holding the name, path, sizes, directory flag,
 * and modification date for a single file or folder in an archive. It is
 * registered with the Qt meta type system so it can be exposed to QML.
 */
class ArchiveEntry {
    Q_GADGET

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(qint64 size READ size WRITE setSize)
    Q_PROPERTY(qint64 compressedSize READ compressedSize WRITE setCompressedSize)
    Q_PROPERTY(bool isDirectory READ isDirectory WRITE setIsDirectory)
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate WRITE setModifiedDate)

public:
    ArchiveEntry();

    QString name() const;
    void setName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    qint64 size() const;
    void setSize(qint64 size);

    qint64 compressedSize() const;
    void setCompressedSize(qint64 compressedSize);

    bool isDirectory() const;
    void setIsDirectory(bool isDirectory);

    QDateTime modifiedDate() const;
    void setModifiedDate(const QDateTime &modifiedDate);

private:
    QString m_name;
    QString m_path;
    qint64 m_size = 0;
    qint64 m_compressedSize = 0;
    bool m_isDirectory = false;
    QDateTime m_modifiedDate;
};

} // namespace bos::shell

Q_DECLARE_METATYPE(bos::shell::ArchiveEntry)
