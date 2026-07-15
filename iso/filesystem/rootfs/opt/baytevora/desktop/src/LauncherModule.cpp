#include "bos/LauncherModule.h"

#include <QDebug>

namespace bos::shell {

LauncherModule::LauncherModule(QObject *parent)
    : QObject(parent)
{
}

LauncherModule::~LauncherModule() = default;

QString LauncherModule::name() const
{
    return QStringLiteral("Launcher");
}

void LauncherModule::initialize()
{
    qDebug() << QStringLiteral("[BDE] Launcher initialized");
}

void LauncherModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("started");
}

void LauncherModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("shutting down");
}

bool LauncherModule::visible() const
{
    return m_visible;
}

void LauncherModule::openLauncher()
{
    setVisible(true);
}

void LauncherModule::closeLauncher()
{
    setVisible(false);
}

void LauncherModule::toggleLauncher()
{
    setVisible(!m_visible);
}

void LauncherModule::requestLaunch(const QString &appName)
{
    qDebug() << QStringLiteral("[BDE] Launch request:") << appName;
}

void LauncherModule::setVisible(bool visible)
{
    if (visible == m_visible) {
        return;
    }

    m_visible = visible;
    qDebug() << QStringLiteral("[BDE] Launcher") << (m_visible ? QStringLiteral("opened") : QStringLiteral("closed"));
    emit visibleChanged();
}

} // namespace bos::shell
