#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class BrowserHistoryManager;
class NotificationManager;

/**
 * @brief Holds global browser privacy settings and applies exit policies.
 *
 * Settings are persisted to a local JSON file under the application's
 * writable data location.
 */
class BrowserPrivacySettings : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool doNotTrackEnabled READ doNotTrackEnabled WRITE setDoNotTrackEnabled NOTIFY doNotTrackEnabledChanged FINAL)
    Q_PROPERTY(bool blockThirdPartyCookies READ blockThirdPartyCookies WRITE setBlockThirdPartyCookies NOTIFY blockThirdPartyCookiesChanged FINAL)
    Q_PROPERTY(bool clearHistoryOnExit READ clearHistoryOnExit WRITE setClearHistoryOnExit NOTIFY clearHistoryOnExitChanged FINAL)
    Q_PROPERTY(bool clearCookiesOnExit READ clearCookiesOnExit WRITE setClearCookiesOnExit NOTIFY clearCookiesOnExitChanged FINAL)
    Q_PROPERTY(bool sendReferrer READ sendReferrer WRITE setSendReferrer NOTIFY sendReferrerChanged FINAL)
    Q_PROPERTY(bool javascriptEnabled READ javascriptEnabled WRITE setJavascriptEnabled NOTIFY javascriptEnabledChanged FINAL)
    Q_PROPERTY(bool popupsBlocked READ popupsBlocked WRITE setPopupsBlocked NOTIFY popupsBlockedChanged FINAL)

public:
    explicit BrowserPrivacySettings(QObject *parent = nullptr);
    ~BrowserPrivacySettings() override;

    bool doNotTrackEnabled() const;
    bool blockThirdPartyCookies() const;
    bool clearHistoryOnExit() const;
    bool clearCookiesOnExit() const;
    bool sendReferrer() const;
    bool javascriptEnabled() const;
    bool popupsBlocked() const;

    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE void setDoNotTrackEnabled(bool enabled);
    Q_INVOKABLE void setBlockThirdPartyCookies(bool enabled);
    Q_INVOKABLE void setClearHistoryOnExit(bool enabled);
    Q_INVOKABLE void setClearCookiesOnExit(bool enabled);
    Q_INVOKABLE void setSendReferrer(bool enabled);
    Q_INVOKABLE void setJavascriptEnabled(bool enabled);
    Q_INVOKABLE void setPopupsBlocked(bool enabled);

    Q_INVOKABLE void applyExitPolicy(BrowserHistoryManager *historyManager);

signals:
    void doNotTrackEnabledChanged();
    void blockThirdPartyCookiesChanged();
    void clearHistoryOnExitChanged();
    void clearCookiesOnExitChanged();
    void sendReferrerChanged();
    void javascriptEnabledChanged();
    void popupsBlockedChanged();

    void privacySettingsUpdated();

private:
    void load();
    void save();
    void emitNotification(const QString &title, const QString &message);
    QString storageDirectory() const;
    QString storageFilePath() const;

    bool m_doNotTrackEnabled = false;
    bool m_blockThirdPartyCookies = false;
    bool m_clearHistoryOnExit = false;
    bool m_clearCookiesOnExit = false;
    bool m_sendReferrer = true;
    bool m_javascriptEnabled = true;
    bool m_popupsBlocked = true;

    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
