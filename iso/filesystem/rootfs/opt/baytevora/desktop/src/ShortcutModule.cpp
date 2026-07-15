#include "bos/ShortcutModule.h"

#include <QDebug>
#include <QWidget>

#include "bos/ShortcutManager.h"

namespace bos::shell {

ShortcutModule::ShortcutModule()
{
}

ShortcutModule::~ShortcutModule() = default;

QString ShortcutModule::name() const
{
    return QStringLiteral("Shortcut");
}

void ShortcutModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");

    m_shortcutHost = std::make_unique<QWidget>();
    m_shortcutHost->setObjectName(QStringLiteral("BOS_ShortcutHost"));
    m_shortcutHost->setWindowFlags(Qt::Tool);
    m_shortcutHost->hide();

    m_shortcutManager = std::make_unique<ShortcutManager>(m_shortcutHost.get());
}

void ShortcutModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void ShortcutModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_shortcutManager.reset();
    m_shortcutHost.reset();
}

ShortcutManager *ShortcutModule::shortcutManager() const
{
    return m_shortcutManager.get();
}

} // namespace bos::shell
