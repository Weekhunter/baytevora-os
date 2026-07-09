#include "bos/ApplicationManager.h"

#include <QDebug>

#include "bos/ApplicationInfo.h"
#include "bos/ApplicationLauncher.h"
#include "bos/ApplicationRegistry.h"
#include "bos/WindowManager.h"

namespace bos::shell {

ApplicationManager::ApplicationManager(QObject *parent)
    : QObject(parent)
    , m_registry(std::make_unique<ApplicationRegistry>())
    , m_launcher(std::make_unique<ApplicationLauncher>(m_registry.get()))
{
}

ApplicationManager::~ApplicationManager() = default;

QString ApplicationManager::name() const
{
    return QStringLiteral("ApplicationManager");
}

void ApplicationManager::initialize()
{
    qDebug() << QStringLiteral("[BDE] ApplicationManager initialized");
    registerPlaceholderApplications();
}

void ApplicationManager::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("started");
}

void ApplicationManager::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("shutting down");
}

void ApplicationManager::setWindowManager(WindowManager *windowManager)
{
    if (m_windowManager == windowManager) {
        return;
    }

    if (m_windowManager) {
        disconnect(m_windowManager, nullptr, this, nullptr);
    }

    m_windowManager = windowManager;

    if (m_windowManager) {
        connect(m_windowManager,
                &WindowManager::windowClosed,
                this,
                &ApplicationManager::onWindowClosed);
    }
}

QVariantList ApplicationManager::applications() const
{
    QVariantList list;
    for (const auto &info : m_registry->applications()) {
        list.append(info.toMap());
    }
    return list;
}

QVariantList ApplicationManager::runningApplications() const
{
    QVariantList list;
    for (const auto &name : m_running) {
        list.append(name);
    }
    return list;
}

bool ApplicationManager::launchApplication(const QString &name)
{
    qDebug() << QStringLiteral("[BDE] Launch request:") << name;

    if (!m_launcher->canLaunch(name)) {
        qWarning() << QStringLiteral("[BDE] Launch validation failed:") << m_launcher->lastError();
        return false;
    }

    const ApplicationInfo *info = m_registry->findByName(name);
    if (!info) {
        qWarning() << QStringLiteral("[BDE] Application not found:") << name;
        return false;
    }

    if (info->singleInstance() && m_running.contains(name)) {
        qDebug() << QStringLiteral("[BDE] Launch denied:") << name << QStringLiteral("already running");
        return false;
    }

    qDebug() << QStringLiteral("[BDE] Launch approved");

    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] WindowManager not available; cannot create window for") << name;
        return false;
    }

    const int windowId = m_windowManager->createApplicationWindow(info->name());
    if (windowId < 0) {
        qWarning() << QStringLiteral("[BDE] Failed to create window for") << name;
        return false;
    }

    qDebug() << QStringLiteral("[BDE] Demo window created:") << info->name();

    m_running.insert(name);
    m_windowToApp.insert(windowId, name);
    emit runningApplicationsChanged();

    return true;
}

void ApplicationManager::registerPlaceholderApplications()
{
    struct Placeholder {
        QString id;
        QString name;
        QString description;
        QString category;
        QString iconName;
        bool singleInstance;
    };

    const std::vector<Placeholder> placeholders = {
        {QStringLiteral("file-manager"), QStringLiteral("File Manager"), QStringLiteral("Browse files"), QStringLiteral("Utilities"), QStringLiteral("FM"), false},
        {QStringLiteral("terminal"), QStringLiteral("Terminal"), QStringLiteral("Command line"), QStringLiteral("Utilities"), QStringLiteral("TR"), true},
        {QStringLiteral("settings"), QStringLiteral("Settings"), QStringLiteral("System settings"), QStringLiteral("System"), QStringLiteral("ST"), true},
        {QStringLiteral("browser"), QStringLiteral("Browser"), QStringLiteral("Web browser"), QStringLiteral("Internet"), QStringLiteral("BR"), false},
        {QStringLiteral("calculator"), QStringLiteral("Calculator"), QStringLiteral("Basic calculator"), QStringLiteral("Utilities"), QStringLiteral("CA"), true},
        {QStringLiteral("notes"), QStringLiteral("Notes"), QStringLiteral("Simple notes"), QStringLiteral("Productivity"), QStringLiteral("NO"), false}
    };

    for (const auto &placeholder : placeholders) {
        m_registry->registerApplication(ApplicationInfo(
            placeholder.id,
            placeholder.name,
            placeholder.description,
            QStringLiteral("1.0.0"),
            placeholder.category,
            placeholder.iconName,
            QStringLiteral("/usr/bin/") + placeholder.id,
            placeholder.singleInstance));

        qDebug() << QStringLiteral("[BDE] Application registered:") << placeholder.name;
    }

    emit applicationsChanged();
}

void ApplicationManager::onWindowClosed(int id)
{
    auto it = m_windowToApp.find(id);
    if (it == m_windowToApp.end()) {
        return;
    }

    const QString appName = it.value();
    m_windowToApp.erase(it);

    // Only remove from running set if no other window is open for this app.
    if (!m_windowToApp.values().contains(appName)) {
        m_running.remove(appName);
        emit runningApplicationsChanged();
    }
}

} // namespace bos::shell
