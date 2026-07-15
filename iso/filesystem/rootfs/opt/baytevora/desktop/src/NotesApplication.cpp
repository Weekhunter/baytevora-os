#include "bos/NotesApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

NotesApplication::NotesApplication(QObject *parent)
    : QObject(parent)
{
}

NotesApplication::~NotesApplication() = default;

void NotesApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void NotesApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int NotesApplication::open()
{
    return doOpen();
}

int NotesApplication::openFile(const QString &filePath)
{
    if (!filePath.isEmpty()) {
        m_pendingOpenFiles.append(filePath);
        emit pendingOpenFilesChanged();
    }
    return doOpen();
}

QStringList NotesApplication::pendingOpenFiles() const
{
    return m_pendingOpenFiles;
}

QString NotesApplication::takePendingOpenFile()
{
    if (m_pendingOpenFiles.isEmpty()) {
        return QString();
    }
    const QString path = m_pendingOpenFiles.takeFirst();
    emit pendingOpenFilesChanged();
    return path;
}

int NotesApplication::doOpen()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] NotesApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 800;
    constexpr int height = 560;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Notes"),
        width,
        height,
        x,
        y,
        QStringLiteral("Notes"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Notes window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Notes"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Notes"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
