#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class RecentFile;
class NotificationManager;

/**
 * @brief Maintains the File Manager recent files list with local JSON persistence.
 */
class RecentFileManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList recentFiles READ recentFiles NOTIFY recentFilesChanged FINAL)

public:
    explicit RecentFileManager(QObject *parent = nullptr);
    ~RecentFileManager() override;

    QVariantList recentFiles() const;

    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE void addRecentFile(const QString &path);
    Q_INVOKABLE void clearRecentFiles();

private:
    void load();
    void save();
    int generateRecentId();
    void emitNotification(const QString &title, const QString &message);
    QString storageDirectory() const;
    QString storageFilePath() const;

    QList<RecentFile*> m_recentFiles;
    NotificationManager *m_notificationManager = nullptr;
    int m_nextRecentId = 1;
};

} // namespace bos::shell
