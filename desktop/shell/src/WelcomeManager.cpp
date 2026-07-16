#include "bos/WelcomeManager.h"

#include "bos/SettingsPersistence.h"

namespace bos::shell {

namespace {

constexpr char kFirstBootCompletedKey[] = "firstBootCompleted";
constexpr char kWelcomeCenterHiddenKey[] = "welcomeCenterHidden";

} // namespace

WelcomeManager::WelcomeManager(SettingsPersistence *persistence, QObject *parent)
    : QObject(parent)
    , m_persistence(persistence)
{
    load();
}

bool WelcomeManager::isFirstLogin() const { return m_isFirstLogin; }
bool WelcomeManager::welcomeCenterVisible() const { return m_welcomeCenterVisible; }
bool WelcomeManager::hideOnNextStartup() const { return m_hideOnNextStartup; }

void WelcomeManager::setWelcomeCenterVisible(bool visible)
{
    if (m_welcomeCenterVisible == visible) {
        return;
    }
    m_welcomeCenterVisible = visible;
    emit welcomeCenterVisibleChanged();
}

void WelcomeManager::setHideOnNextStartup(bool hide)
{
    if (m_hideOnNextStartup == hide) {
        return;
    }
    m_hideOnNextStartup = hide;
    emit hideOnNextStartupChanged();
    save();
}

void WelcomeManager::requestOpenWelcomeCenter()
{
    if (m_hideOnNextStartup) {
        return;
    }
    setWelcomeCenterVisible(true);
    emit openWelcomeCenterRequested();
}

void WelcomeManager::closeWelcomeCenter()
{
    setWelcomeCenterVisible(false);
    emit closeWelcomeCenterRequested();
}

void WelcomeManager::setIsFirstLogin(bool firstLogin)
{
    if (m_isFirstLogin == firstLogin) {
        return;
    }
    m_isFirstLogin = firstLogin;
    emit isFirstLoginChanged();
}

void WelcomeManager::markFirstLoginHandled()
{
    if (m_isFirstLogin) {
        m_isFirstLogin = false;
        emit isFirstLoginChanged();
    }
}

bool WelcomeManager::shouldOpenOnLogin() const
{
    return m_isFirstLogin && !m_hideOnNextStartup;
}

bool WelcomeManager::save()
{
    if (!m_persistence) {
        return false;
    }
    QVariantMap settings = m_persistence->load();
    settings[QStringLiteral(kWelcomeCenterHiddenKey)] = m_hideOnNextStartup;
    return m_persistence->save(settings);
}

void WelcomeManager::load()
{
    if (!m_persistence) {
        m_isFirstLogin = true;
        m_hideOnNextStartup = false;
        return;
    }

    const QVariantMap settings = m_persistence->load();
    const bool firstBootCompleted = settings.value(QStringLiteral(kFirstBootCompletedKey)).toBool();
    m_isFirstLogin = firstBootCompleted; // first login only after first boot is complete
    m_hideOnNextStartup = settings.value(QStringLiteral(kWelcomeCenterHiddenKey)).toBool();
}

} // namespace bos::shell
