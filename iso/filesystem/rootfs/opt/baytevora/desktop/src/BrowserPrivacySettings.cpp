#include "bos/BrowserPrivacySettings.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "bos/BrowserHistoryManager.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

BrowserPrivacySettings::BrowserPrivacySettings(QObject *parent)
    : QObject(parent)
{
    load();
}

BrowserPrivacySettings::~BrowserPrivacySettings() = default;

bool BrowserPrivacySettings::doNotTrackEnabled() const { return m_doNotTrackEnabled; }
bool BrowserPrivacySettings::blockThirdPartyCookies() const { return m_blockThirdPartyCookies; }
bool BrowserPrivacySettings::clearHistoryOnExit() const { return m_clearHistoryOnExit; }
bool BrowserPrivacySettings::clearCookiesOnExit() const { return m_clearCookiesOnExit; }
bool BrowserPrivacySettings::sendReferrer() const { return m_sendReferrer; }
bool BrowserPrivacySettings::javascriptEnabled() const { return m_javascriptEnabled; }
bool BrowserPrivacySettings::popupsBlocked() const { return m_popupsBlocked; }

void BrowserPrivacySettings::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

void BrowserPrivacySettings::setDoNotTrackEnabled(bool enabled)
{
    if (m_doNotTrackEnabled == enabled) {
        return;
    }
    m_doNotTrackEnabled = enabled;
    emit doNotTrackEnabledChanged();
    emit privacySettingsUpdated();
    emitNotification(QStringLiteral("Privacy Settings Updated"),
                   QStringLiteral("Do Not Track set to %1").arg(enabled ? "On" : "Off"));
    save();
}

void BrowserPrivacySettings::setBlockThirdPartyCookies(bool enabled)
{
    if (m_blockThirdPartyCookies == enabled) {
        return;
    }
    m_blockThirdPartyCookies = enabled;
    emit blockThirdPartyCookiesChanged();
    emit privacySettingsUpdated();
    emitNotification(QStringLiteral("Privacy Settings Updated"),
                   QStringLiteral("Third-party cookie blocking set to %1").arg(enabled ? "On" : "Off"));
    save();
}

void BrowserPrivacySettings::setClearHistoryOnExit(bool enabled)
{
    if (m_clearHistoryOnExit == enabled) {
        return;
    }
    m_clearHistoryOnExit = enabled;
    emit clearHistoryOnExitChanged();
    emit privacySettingsUpdated();
    emitNotification(QStringLiteral("Privacy Settings Updated"),
                   QStringLiteral("Clear history on exit set to %1").arg(enabled ? "On" : "Off"));
    save();
}

void BrowserPrivacySettings::setClearCookiesOnExit(bool enabled)
{
    if (m_clearCookiesOnExit == enabled) {
        return;
    }
    m_clearCookiesOnExit = enabled;
    emit clearCookiesOnExitChanged();
    emit privacySettingsUpdated();
    emitNotification(QStringLiteral("Privacy Settings Updated"),
                   QStringLiteral("Clear cookies on exit set to %1").arg(enabled ? "On" : "Off"));
    save();
}

void BrowserPrivacySettings::setSendReferrer(bool enabled)
{
    if (m_sendReferrer == enabled) {
        return;
    }
    m_sendReferrer = enabled;
    emit sendReferrerChanged();
    emit privacySettingsUpdated();
    emitNotification(QStringLiteral("Privacy Settings Updated"),
                   QStringLiteral("Send referrer set to %1").arg(enabled ? "On" : "Off"));
    save();
}

void BrowserPrivacySettings::setJavascriptEnabled(bool enabled)
{
    if (m_javascriptEnabled == enabled) {
        return;
    }
    m_javascriptEnabled = enabled;
    emit javascriptEnabledChanged();
    emit privacySettingsUpdated();
    emitNotification(QStringLiteral("Privacy Settings Updated"),
                   QStringLiteral("JavaScript set to %1").arg(enabled ? "On" : "Off"));
    save();
}

void BrowserPrivacySettings::setPopupsBlocked(bool enabled)
{
    if (m_popupsBlocked == enabled) {
        return;
    }
    m_popupsBlocked = enabled;
    emit popupsBlockedChanged();
    emit privacySettingsUpdated();
    emitNotification(QStringLiteral("Privacy Settings Updated"),
                   QStringLiteral("Popup blocking set to %1").arg(enabled ? "On" : "Off"));
    save();
}

void BrowserPrivacySettings::applyExitPolicy(BrowserHistoryManager *historyManager)
{
    if (!historyManager) {
        return;
    }
    if (m_clearHistoryOnExit) {
        historyManager->clearHistory();
    }
    if (m_clearCookiesOnExit) {
        // Placeholder-safe: cookie clearing is reserved for a future sprint
        // that integrates with the WebEngine profile cookie store.
    }
}

void BrowserPrivacySettings::load()
{
    const QString path = storageFilePath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    const QByteArray data = file.readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        return;
    }

    const QJsonObject obj = doc.object();
    m_doNotTrackEnabled = obj.value(QStringLiteral("doNotTrackEnabled")).toBool(false);
    m_blockThirdPartyCookies = obj.value(QStringLiteral("blockThirdPartyCookies")).toBool(false);
    m_clearHistoryOnExit = obj.value(QStringLiteral("clearHistoryOnExit")).toBool(false);
    m_clearCookiesOnExit = obj.value(QStringLiteral("clearCookiesOnExit")).toBool(false);
    m_sendReferrer = obj.value(QStringLiteral("sendReferrer")).toBool(true);
    m_javascriptEnabled = obj.value(QStringLiteral("javascriptEnabled")).toBool(true);
    m_popupsBlocked = obj.value(QStringLiteral("popupsBlocked")).toBool(true);
}

void BrowserPrivacySettings::save()
{
    QJsonObject obj;
    obj.insert(QStringLiteral("doNotTrackEnabled"), m_doNotTrackEnabled);
    obj.insert(QStringLiteral("blockThirdPartyCookies"), m_blockThirdPartyCookies);
    obj.insert(QStringLiteral("clearHistoryOnExit"), m_clearHistoryOnExit);
    obj.insert(QStringLiteral("clearCookiesOnExit"), m_clearCookiesOnExit);
    obj.insert(QStringLiteral("sendReferrer"), m_sendReferrer);
    obj.insert(QStringLiteral("javascriptEnabled"), m_javascriptEnabled);
    obj.insert(QStringLiteral("popupsBlocked"), m_popupsBlocked);

    const QString path = storageFilePath();
    QDir dir(storageDirectory());
    if (!dir.exists()) {
        dir.mkpath(QStringLiteral("."));
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
}

void BrowserPrivacySettings::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("Browser"),
                                              QStringLiteral("info"));
}

QString BrowserPrivacySettings::storageDirectory() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + QStringLiteral("/.baytevora");
    }
    return path + QStringLiteral("/browser");
}

QString BrowserPrivacySettings::storageFilePath() const
{
    return storageDirectory() + QStringLiteral("/privacy.json");
}

} // namespace bos::shell
