#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class BrowserHistoryEntry;
class NotificationManager;

/**
 * @brief Manages browsing history for a browser session.
 *
 * History entries are persisted to a local JSON file under the application's
 * writable data location. Visits are recorded automatically when the active
 * tab navigates to a non-error, non-internal page.
 */
class BrowserHistoryManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList history READ history NOTIFY historyChanged FINAL)
    Q_PROPERTY(QVariantList recentHistory READ recentHistory NOTIFY historyChanged FINAL)

public:
    explicit BrowserHistoryManager(QObject *parent = nullptr);
    ~BrowserHistoryManager() override;

    QVariantList history() const;
    QVariantList recentHistory() const;

    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE void recordVisit(const QString &title, const QString &url);
    Q_INVOKABLE void clearHistory();
    Q_INVOKABLE bool removeHistoryEntry(int historyId);
    Q_INVOKABLE QVariantList searchHistory(const QString &query) const;

private:
    void load();
    void save();
    QString storageDirectory() const;
    QString storageFilePath() const;
    int generateHistoryId();
    BrowserHistoryEntry *findEntry(const QString &url) const;
    BrowserHistoryEntry *findEntryById(int historyId) const;
    void emitNotification(const QString &title, const QString &message);
    bool shouldRecord(const QString &url) const;

    QList<BrowserHistoryEntry*> m_history;
    NotificationManager *m_notificationManager = nullptr;
    int m_nextHistoryId = 1;
};

} // namespace bos::shell
