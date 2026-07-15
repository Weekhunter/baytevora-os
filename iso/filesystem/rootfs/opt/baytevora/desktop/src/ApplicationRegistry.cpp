#include "bos/ApplicationRegistry.h"

#include <algorithm>

namespace bos::shell {

ApplicationRegistry::ApplicationRegistry() = default;

ApplicationRegistry::~ApplicationRegistry() = default;

void ApplicationRegistry::registerApplication(const ApplicationInfo &info)
{
    m_applications.push_back(info);
}

void ApplicationRegistry::unregisterApplication(const QString &id)
{
    m_applications.erase(
        std::remove_if(
            m_applications.begin(),
            m_applications.end(),
            [&id](const ApplicationInfo &info) { return info.id() == id; }),
        m_applications.end());
}

const ApplicationInfo *ApplicationRegistry::findById(const QString &id) const
{
    for (const auto &info : m_applications) {
        if (info.id() == id) {
            return &info;
        }
    }
    return nullptr;
}

const ApplicationInfo *ApplicationRegistry::findByName(const QString &name) const
{
    for (const auto &info : m_applications) {
        if (info.name() == name) {
            return &info;
        }
    }
    return nullptr;
}

std::vector<ApplicationInfo> ApplicationRegistry::applications() const
{
    return m_applications;
}

} // namespace bos::shell
