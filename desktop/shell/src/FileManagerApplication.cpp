#include "bos/FileManagerApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

FileManagerApplication::FileManagerApplication(QObject *parent)
    : QObject(parent)
{
}

FileManagerApplication::~FileManagerApplication() = default;

void FileManagerApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void FileManagerApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int FileManagerApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] FileManagerApplication: WindowManager not available");
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
        QStringLiteral("File Manager"),
        width,
        height,
        x,
        y,
        QStringLiteral("File Manager"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] File Manager window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("File Manager"),
                                                   QStringLiteral("Ready."),
                                                   QStringLiteral("File Manager"),
                                                   QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
