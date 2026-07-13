#include "bos/TextEditorApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

TextEditorApplication::TextEditorApplication(QObject *parent)
    : QObject(parent)
{
}

TextEditorApplication::~TextEditorApplication() = default;

void TextEditorApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void TextEditorApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int TextEditorApplication::open()
{
    return openInternal(QString());
}

int TextEditorApplication::openDocument(const QString &path)
{
    return openInternal(path);
}

int TextEditorApplication::openInternal(const QString &initialPath)
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] TextEditorApplication: WindowManager not available");
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
        QStringLiteral("Text Editor"),
        width,
        height,
        x,
        y,
        QStringLiteral("Text Editor"));

    m_windowManager->setActiveWindow(windowId);

    Q_UNUSED(initialPath)

    qDebug() << QStringLiteral("[BDE] Text Editor window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Text Editor"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Text Editor"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
