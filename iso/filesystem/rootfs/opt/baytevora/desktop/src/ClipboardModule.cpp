#include "bos/ClipboardModule.h"

#include <QClipboard>
#include <QDebug>
#include <QGuiApplication>

#include "bos/ClipboardManager.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

ClipboardModule::ClipboardModule()
{
}

ClipboardModule::~ClipboardModule() = default;

QString ClipboardModule::name() const
{
    return QStringLiteral("Clipboard");
}

void ClipboardModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");

    QClipboard *clipboard = QGuiApplication::clipboard();
    m_clipboardManager = std::make_unique<ClipboardManager>(clipboard);
}

void ClipboardModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void ClipboardModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_clipboardManager.reset();
}

ClipboardManager *ClipboardModule::clipboardManager() const
{
    return m_clipboardManager.get();
}

void ClipboardModule::setNotificationManager(NotificationManager *manager)
{
    if (m_clipboardManager) {
        m_clipboardManager->setNotificationManager(manager);
    }
}

} // namespace bos::shell
