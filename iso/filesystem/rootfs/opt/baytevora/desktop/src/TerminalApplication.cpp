#include "bos/TerminalApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

TerminalApplication::TerminalApplication(QObject *parent)
    : QObject(parent)
{
}

TerminalApplication::~TerminalApplication() = default;

void TerminalApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void TerminalApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int TerminalApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] TerminalApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 900;
    constexpr int height = 600;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Terminal"),
        width,
        height,
        x,
        y,
        QStringLiteral("Terminal"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Terminal window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Terminal"),
                                                   QStringLiteral("Ready."),
                                                   QStringLiteral("Terminal"),
                                                   QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
