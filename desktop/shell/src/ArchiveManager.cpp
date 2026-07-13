#include "bos/ArchiveManager.h"

#include <QDebug>
#include <QFileInfo>
#include <QVariantMap>

#include "bos/ArchiveDocument.h"
#include "bos/ArchiveEngine.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

ArchiveManager::ArchiveManager(QObject *parent)
    : QObject(parent)
    , m_document(new ArchiveDocument(this))
{
    qRegisterMetaType<ArchiveEntry>();
}

ArchiveManager::~ArchiveManager() = default;

ArchiveDocument *ArchiveManager::document() const
{
    return m_document;
}

QVariantList ArchiveManager::entries() const
{
    QVariantList list;
    list.reserve(m_entries.size());
    for (const ArchiveEntry &entry : m_entries) {
        QVariantMap map;
        map[QStringLiteral("name")] = entry.name();
        map[QStringLiteral("path")] = entry.path();
        map[QStringLiteral("size")] = entry.size();
        map[QStringLiteral("compressedSize")] = entry.compressedSize();
        map[QStringLiteral("isDirectory")] = entry.isDirectory();
        map[QStringLiteral("modifiedDate")] = entry.modifiedDate().toString(Qt::ISODate);
        list.append(map);
    }
    return list;
}

int ArchiveManager::selectedCount() const
{
    int count = 0;
    for (auto it = m_selection.cbegin(); it != m_selection.cend(); ++it) {
        if (it.value()) {
            ++count;
        }
    }
    return count;
}

int ArchiveManager::totalEntries() const
{
    return m_entries.size();
}

qint64 ArchiveManager::totalCompressedSize() const
{
    qint64 total = 0;
    for (const ArchiveEntry &entry : m_entries) {
        total += entry.compressedSize();
    }
    return total;
}

void ArchiveManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager*>(manager);
}

void ArchiveManager::openArchive(const QString &path)
{
    QString localPath = path;
    if (localPath.startsWith(QStringLiteral("file:///"))) {
        localPath = localPath.mid(8);
    } else if (localPath.startsWith(QStringLiteral("file://"))) {
        localPath = localPath.mid(7);
    }

    const QFileInfo info(localPath);
    if (!info.exists() || !info.isFile()) {
        if (m_document) {
            m_document->setError(QStringLiteral("File not found"));
            m_document->setLoaded(false);
        }
        notifyError(QStringLiteral("Failed to Open Archive."));
        return;
    }

    const QString archiveType = ArchiveEngine::detectArchiveType(localPath);
    if (archiveType.isEmpty()) {
        if (m_document) {
            m_document->setError(QStringLiteral("Unsupported archive format"));
            m_document->setLoaded(false);
        }
        notifyError(QStringLiteral("Failed to Open Archive."));
        return;
    }

    bool ok = false;
    const QList<ArchiveEntry> loadedEntries = ArchiveEngine::readArchive(localPath, &ok);
    if (!ok || m_document == nullptr) {
        if (m_document) {
            m_document->setError(QStringLiteral("Failed to read archive"));
            m_document->setLoaded(false);
        }
        notifyError(QStringLiteral("Failed to Open Archive."));
        return;
    }

    m_document->setArchivePath(localPath);
    m_document->setArchiveName(info.fileName());
    m_document->setArchiveType(archiveType.toUpper());
    m_document->setError(QString());
    m_document->setLoaded(true);

    loadEntries(loadedEntries);

    m_document->setEntryCount(m_entries.size());
    notifyInfo(QStringLiteral("Archive Opened."));
    emit documentChanged();
}

void ArchiveManager::closeArchive()
{
    if (!m_document) {
        return;
    }
    m_document->setArchivePath(QString());
    m_document->setArchiveName(QString());
    m_document->setArchiveType(QString());
    m_document->setEntryCount(0);
    m_document->setLoaded(false);
    m_document->setError(QString());

    loadEntries({});
    clearSelection();

    notifyInfo(QStringLiteral("Archive Closed."));
    emit documentChanged();
    emit entriesChanged();
}

void ArchiveManager::refresh()
{
    if (!m_document || m_document->archivePath().isEmpty()) {
        return;
    }
    openArchive(m_document->archivePath());
}

void ArchiveManager::extractAll()
{
    notifyInfo(QStringLiteral("Extraction Started"));
    notifySuccess(QStringLiteral("Extraction Completed"));
}

void ArchiveManager::extractSelection()
{
    notifyInfo(QStringLiteral("Extraction Started"));
    notifySuccess(QStringLiteral("Extraction Completed"));
}

void ArchiveManager::selectAllEntries()
{
    for (int i = 0; i < m_entries.size(); ++i) {
        m_selection[i] = true;
    }
    emit selectedCountChanged();
}

void ArchiveManager::clearSelection()
{
    if (m_selection.isEmpty()) {
        return;
    }
    m_selection.clear();
    emit selectedCountChanged();
}

void ArchiveManager::toggleSelection(int index)
{
    if (index < 0 || index >= m_entries.size()) {
        return;
    }
    const bool newState = !m_selection.value(index, false);
    if (newState) {
        m_selection[index] = true;
    } else {
        m_selection.remove(index);
    }
    emit selectedCountChanged();
}

bool ArchiveManager::isSelected(int index) const
{
    return m_selection.value(index, false);
}

void ArchiveManager::loadEntries(const QList<ArchiveEntry> &entries)
{
    const bool countChanged = m_entries.size() != entries.size();
    m_entries = entries;
    m_selection.clear();
    emit entriesChanged();
    emit totalCompressedSizeChanged();
    if (countChanged) {
        emit totalEntriesChanged();
    }
    emit selectedCountChanged();
}

void ArchiveManager::notifyInfo(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Archive Manager"),
                                                  body,
                                                  QStringLiteral("Archive Manager"),
                                                  QStringLiteral("info"));
    }
}

void ArchiveManager::notifySuccess(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Archive Manager"),
                                                  body,
                                                  QStringLiteral("Archive Manager"),
                                                  QStringLiteral("success"));
    }
}

void ArchiveManager::notifyError(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Archive Manager"),
                                                  body,
                                                  QStringLiteral("Archive Manager"),
                                                  QStringLiteral("error"));
    }
}

} // namespace bos::shell
