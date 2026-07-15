#include "bos/ArchiveDocument.h"

#include <QFileInfo>

namespace bos::shell {

ArchiveDocument::ArchiveDocument(QObject *parent)
    : QObject(parent)
{
}

QString ArchiveDocument::archivePath() const
{
    return m_archivePath;
}

QString ArchiveDocument::archiveName() const
{
    return m_archiveName;
}

QString ArchiveDocument::archiveType() const
{
    return m_archiveType;
}

int ArchiveDocument::entryCount() const
{
    return m_entryCount;
}

bool ArchiveDocument::loaded() const
{
    return m_loaded;
}

QString ArchiveDocument::error() const
{
    return m_error;
}

void ArchiveDocument::setArchivePath(const QString &path)
{
    if (m_archivePath == path) {
        return;
    }
    m_archivePath = path;
    emit archivePathChanged();
}

void ArchiveDocument::setArchiveName(const QString &name)
{
    if (m_archiveName == name) {
        return;
    }
    m_archiveName = name;
    emit archiveNameChanged();
}

void ArchiveDocument::setArchiveType(const QString &type)
{
    if (m_archiveType == type) {
        return;
    }
    m_archiveType = type;
    emit archiveTypeChanged();
}

void ArchiveDocument::setEntryCount(int count)
{
    if (m_entryCount == count) {
        return;
    }
    m_entryCount = count;
    emit entryCountChanged();
}

void ArchiveDocument::setLoaded(bool loaded)
{
    if (m_loaded == loaded) {
        return;
    }
    m_loaded = loaded;
    emit loadedChanged();
}

void ArchiveDocument::setError(const QString &error)
{
    if (m_error == error) {
        return;
    }
    m_error = error;
    emit errorChanged();
}

} // namespace bos::shell
