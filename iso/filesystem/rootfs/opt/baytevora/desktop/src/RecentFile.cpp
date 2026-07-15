#include "bos/RecentFile.h"

namespace bos::shell {

RecentFile::RecentFile(int recentId, QObject *parent)
    : QObject(parent)
    , m_recentId(recentId)
{
}

RecentFile::~RecentFile() = default;

int RecentFile::recentId() const { return m_recentId; }
QString RecentFile::fileName() const { return m_fileName; }
QString RecentFile::path() const { return m_path; }
QString RecentFile::fileType() const { return m_fileType; }
QDateTime RecentFile::lastOpened() const { return m_lastOpened; }

void RecentFile::setFileName(const QString &fileName)
{
    if (m_fileName == fileName) {
        return;
    }
    m_fileName = fileName;
    emit fileNameChanged();
}

void RecentFile::setPath(const QString &path)
{
    if (m_path == path) {
        return;
    }
    m_path = path;
    emit pathChanged();
}

void RecentFile::setFileType(const QString &fileType)
{
    if (m_fileType == fileType) {
        return;
    }
    m_fileType = fileType;
    emit fileTypeChanged();
}

void RecentFile::setLastOpened(const QDateTime &lastOpened)
{
    if (m_lastOpened == lastOpened) {
        return;
    }
    m_lastOpened = lastOpened;
    emit lastOpenedChanged();
}

} // namespace bos::shell
