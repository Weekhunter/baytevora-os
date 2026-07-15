#include "bos/ArchiveApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

ArchiveApplication::ArchiveApplication(QObject *parent)
    : QObject(parent)
{
}

ArchiveApplication::~ArchiveApplication() = default;

void ArchiveApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void ArchiveApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int ArchiveApplication::open()
{
    return openInternal(QString());
}

int ArchiveApplication::openArchive(const QString &path)
{
    return openInternal(path);
}

int ArchiveApplication::openInternal(const QString &initialPath)
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] ArchiveApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 860;
    constexpr int height = 620;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Archive Manager"),
        width,
        height,
        x,
        y,
        QStringLiteral("Archive Manager"));

    m_windowManager->setActiveWindow(windowId);

    // Future File Manager integration can pass initialPath here via QML context
    // properties or a shared payload API once WindowManager supports it.
    Q_UNUSED(initialPath)

    qDebug() << QStringLiteral("[BDE] Archive Manager window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Archive Manager"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Archive Manager"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
