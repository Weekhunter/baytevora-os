#include "bos/ApplicationLauncher.h"

#include "bos/ApplicationRegistry.h"

namespace bos::shell {

ApplicationLauncher::ApplicationLauncher(const ApplicationRegistry *registry)
    : m_registry(registry)
{
}

ApplicationLauncher::~ApplicationLauncher() = default;

bool ApplicationLauncher::canLaunch(const QString &name) const
{
    if (!m_registry) {
        m_lastError = QStringLiteral("Application registry is not available");
        return false;
    }

    if (name.isEmpty()) {
        m_lastError = QStringLiteral("Application name is empty");
        return false;
    }

    if (!m_registry->findByName(name)) {
        m_lastError = QStringLiteral("Application not found: ") + name;
        return false;
    }

    m_lastError.clear();
    return true;
}

} // namespace bos::shell
