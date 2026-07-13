#include "bos/PrintApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

PrintApplication::PrintApplication(QObject *parent)
    : QObject(parent)
{
}

PrintApplication::~PrintApplication() = default;

void PrintApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void PrintApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int PrintApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] PrintApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 900;
    constexpr int height = 620;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Print Manager"),
        width,
        height,
        x,
        y,
        QStringLiteral("Print Manager"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Print Manager window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Printing"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Print Manager"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
