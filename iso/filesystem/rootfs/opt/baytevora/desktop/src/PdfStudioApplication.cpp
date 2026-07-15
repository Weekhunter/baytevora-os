#include "bos/PdfStudioApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/PrintApplication.h"
#include "bos/WindowManager.h"

namespace bos::shell {

PdfStudioApplication::PdfStudioApplication(QObject *parent)
    : QObject(parent)
{
}

PdfStudioApplication::~PdfStudioApplication() = default;

void PdfStudioApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void PdfStudioApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

void PdfStudioApplication::setPrintApplication(PrintApplication *printApplication)
{
    m_printApplication = printApplication;
}

int PdfStudioApplication::open()
{
    return doOpen();
}

int PdfStudioApplication::openFile(const QString &filePath)
{
    if (!filePath.isEmpty()) {
        m_pendingOpenFiles.append(filePath);
    }
    return doOpen();
}

bool PdfStudioApplication::hasPendingOpenFile() const
{
    return !m_pendingOpenFiles.isEmpty();
}

QString PdfStudioApplication::takePendingOpenFile()
{
    if (m_pendingOpenFiles.isEmpty()) {
        return QString();
    }
    return m_pendingOpenFiles.takeFirst();
}

int PdfStudioApplication::doOpen()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] PdfStudioApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 1000;
    constexpr int height = 720;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Baytevora PDF Studio"),
        width,
        height,
        x,
        y,
        QStringLiteral("Baytevora PDF Studio"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Baytevora PDF Studio window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Baytevora PDF Studio"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Baytevora PDF Studio"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
