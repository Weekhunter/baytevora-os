#include "bos/LoginModule.h"

#include <QDebug>

#include "bos/LoginManager.h"
#include "bos/LoginState.h"

namespace bos::shell {

LoginModule::LoginModule()
{
}

LoginModule::~LoginModule() = default;

QString LoginModule::name() const
{
    return QStringLiteral("Login");
}

void LoginModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_loginManager = std::make_unique<LoginManager>();
}

void LoginModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
    // Only transition out of the boot state here; if the user is already logged
    // in, leave the manager in its current state.
    if (m_loginManager && m_loginManager->state() == static_cast<int>(LoginState::Booting)) {
        m_loginManager->cancel();
    }
}

void LoginModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_loginManager.reset();
}

LoginManager *LoginModule::loginManager() const
{
    return m_loginManager.get();
}

} // namespace bos::shell
