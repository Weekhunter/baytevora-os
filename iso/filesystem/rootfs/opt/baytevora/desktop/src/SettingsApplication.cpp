#include "bos/SettingsApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

SettingsApplication::SettingsApplication(QObject *parent)
    : QObject(parent)
{
}

SettingsApplication::~SettingsApplication() = default;

void SettingsApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void SettingsApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

QString SettingsApplication::pendingPage() const
{
    return m_pendingPage;
}

void SettingsApplication::setPendingPage(const QString &pageId)
{
    if (m_pendingPage == pageId) {
        return;
    }
    m_pendingPage = pageId;
    emit pendingPageChanged();
}

int SettingsApplication::openPage(const QString &pageId)
{
    setPendingPage(pageId);
    qDebug() << QStringLiteral("[BDE] Settings page requested:") << pageId;
    return open();
}

int SettingsApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] SettingsApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 900;
    constexpr int height = 650;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Settings"),
        width,
        height,
        x,
        y,
        QStringLiteral("Settings"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Settings window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Settings"),
                                                   QStringLiteral("Ready."),
                                                   QStringLiteral("Settings"),
                                                   QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
