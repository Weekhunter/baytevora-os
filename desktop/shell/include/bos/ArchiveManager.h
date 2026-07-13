#pragma once

#include <QHash>
#include <QList>
#include <QObject>
#include <QVariantList>

#include "bos/ArchiveEntry.h"

namespace bos::shell {

class ArchiveDocument;
class NotificationManager;

/**
 * @brief Manages the archive document and entry selection for one Archive Manager window.
 *
 * ArchiveManager owns the current ArchiveDocument and a list of ArchiveEntry
 * objects. It exposes an entry model to QML and provides methods for opening,
 * closing, refreshing, and placeholder-extraction actions.
 */
class ArchiveManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(ArchiveDocument *document READ document NOTIFY documentChanged FINAL)
    Q_PROPERTY(QVariantList entries READ entries NOTIFY entriesChanged FINAL)
    Q_PROPERTY(int selectedCount READ selectedCount NOTIFY selectedCountChanged FINAL)
    Q_PROPERTY(int totalEntries READ totalEntries NOTIFY totalEntriesChanged FINAL)
    Q_PROPERTY(qint64 totalCompressedSize READ totalCompressedSize NOTIFY totalCompressedSizeChanged FINAL)

public:
    explicit ArchiveManager(QObject *parent = nullptr);
    ~ArchiveManager() override;

    ArchiveDocument *document() const;
    QVariantList entries() const;
    int selectedCount() const;
    int totalEntries() const;
    qint64 totalCompressedSize() const;

    Q_INVOKABLE void setNotificationManager(QObject *manager);

    Q_INVOKABLE void openArchive(const QString &path);
    Q_INVOKABLE void closeArchive();
    Q_INVOKABLE void refresh();

    Q_INVOKABLE void extractAll();
    Q_INVOKABLE void extractSelection();

    Q_INVOKABLE void selectAllEntries();
    Q_INVOKABLE void clearSelection();
    Q_INVOKABLE void toggleSelection(int index);
    Q_INVOKABLE bool isSelected(int index) const;

signals:
    void documentChanged();
    void entriesChanged();
    void selectedCountChanged();
    void totalEntriesChanged();
    void totalCompressedSizeChanged();

private:
    void loadEntries(const QList<ArchiveEntry> &entries);
    void notifyInfo(const QString &body);
    void notifySuccess(const QString &body);
    void notifyError(const QString &body);

    ArchiveDocument *m_document = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QList<ArchiveEntry> m_entries;
    QHash<int, bool> m_selection;
};

} // namespace bos::shell
