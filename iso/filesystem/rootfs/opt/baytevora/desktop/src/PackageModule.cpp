#include "bos/PackageModule.h"

#include <QDebug>

#include "bos/PackageManager.h"

namespace bos::shell {

PackageModule::PackageModule() = default;
PackageModule::~PackageModule() = default;

QString PackageModule::name() const
{
    return QStringLiteral("Package");
}

void PackageModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_packageManager = std::make_unique<PackageManager>();
}

void PackageModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void PackageModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_packageManager.reset();
}

PackageManager *PackageModule::packageManager() const
{
    return m_packageManager.get();
}

} // namespace bos::shell
