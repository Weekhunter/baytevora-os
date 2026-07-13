#include "bos/CalculatorApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

CalculatorApplication::CalculatorApplication(QObject *parent)
    : QObject(parent)
{
}

CalculatorApplication::~CalculatorApplication() = default;

void CalculatorApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void CalculatorApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int CalculatorApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] CalculatorApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 320;
    constexpr int height = 480;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Calculator"),
        width,
        height,
        x,
        y,
        QStringLiteral("Calculator"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Calculator window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Calculator"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Calculator"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
