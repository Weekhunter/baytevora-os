#include "boi/InstallerApplication.h"
#include "boi/InstallationSummary.h"
#include "boi/InstallationTarget.h"
#include "boi/InstallerManager.h"
#include "boi/InstallerSession.h"

#include "bos/AdaptiveLayoutManager.h"
#include "bos/BrandingManager.h"
#include "bos/DesignTokens.h"
#include "bos/IconManager.h"
#include "bos/SpacingManager.h"
#include "bos/StorageManager.h"
#include "bos/ThemeManager.h"
#include "bos/TypographyManager.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QTimer>
#include <QUrl>

namespace boi {

InstallerApplication::InstallerApplication(QGuiApplication &app, QObject *parent)
    : QObject(parent)
    , m_app(app)
    , m_engine(std::make_unique<QQmlApplicationEngine>(this))
{
    m_brandingManager = new bos::shell::BrandingManager(this);
    m_storageManager = new bos::shell::StorageManager(this);
    m_themeManager = new bos::shell::ThemeManager(this);
    m_typographyManager = new bos::shell::TypographyManager(this);
    m_spacingManager = new bos::shell::SpacingManager(this);
    m_designTokens = new bos::shell::DesignTokens(this);
    m_iconManager = new bos::shell::IconManager(this);
    m_adaptiveLayoutManager = new bos::shell::AdaptiveLayoutManager(this);

    m_session = new InstallerSession(this);
    m_manager = new InstallerManager(m_storageManager, this);
}

InstallerApplication::~InstallerApplication() = default;

void InstallerApplication::registerQmlTypes()
{
    // Installer-specific types.
    qmlRegisterType<InstallerSession>("BOI.Installer", 1, 0, "InstallerSession");
    qmlRegisterType<InstallationTarget>("BOI.Installer", 1, 0, "InstallationTarget");
    qmlRegisterType<InstallationSummary>("BOI.Installer", 1, 0, "InstallationSummary");
    qmlRegisterType<InstallerManager>("BOI.Installer", 1, 0, "InstallerManager");

    // BDL v2 design system singletons reused from BOS.Shell.
    qmlRegisterSingletonType<bos::shell::ThemeManager>(
        "BOI.Installer", 1, 0, "ThemeManager",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_themeManager; });
    qmlRegisterSingletonType<bos::shell::TypographyManager>(
        "BOI.Installer", 1, 0, "TypographyManager",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_typographyManager; });
    qmlRegisterSingletonType<bos::shell::SpacingManager>(
        "BOI.Installer", 1, 0, "SpacingManager",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_spacingManager; });
    qmlRegisterSingletonType<bos::shell::DesignTokens>(
        "BOI.Installer", 1, 0, "DesignTokens",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_designTokens; });
    qmlRegisterSingletonType<bos::shell::IconManager>(
        "BOI.Installer", 1, 0, "IconManager",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_iconManager; });
    qmlRegisterSingletonType<bos::shell::AdaptiveLayoutManager>(
        "BOI.Installer", 1, 0, "AdaptiveLayoutManager",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_adaptiveLayoutManager; });
    qmlRegisterSingletonType<bos::shell::BrandingManager>(
        "BOI.Installer", 1, 0, "BrandingManager",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_brandingManager; });
    qmlRegisterSingletonType<bos::shell::StorageManager>(
        "BOI.Installer", 1, 0, "StorageManager",
        [this](QQmlEngine *, QJSEngine *) -> QObject * { return m_storageManager; });
}

void InstallerApplication::exposeContextObjects()
{
    QQmlContext *context = m_engine->rootContext();
    context->setContextProperty(QStringLiteral("installerSession"), m_session);
    context->setContextProperty(QStringLiteral("installerManager"), m_manager);
    context->setContextProperty(QStringLiteral("brandingManager"), m_brandingManager);
    context->setContextProperty(QStringLiteral("storageManager"), m_storageManager);
    context->setContextProperty(QStringLiteral("themeManager"), m_themeManager);
    context->setContextProperty(QStringLiteral("typographyManager"), m_typographyManager);
    context->setContextProperty(QStringLiteral("spacingManager"), m_spacingManager);
    context->setContextProperty(QStringLiteral("designTokens"), m_designTokens);
    context->setContextProperty(QStringLiteral("iconManager"), m_iconManager);
    context->setContextProperty(QStringLiteral("adaptiveLayoutManager"), m_adaptiveLayoutManager);
}

int InstallerApplication::run()
{
    registerQmlTypes();
    exposeContextObjects();

    // Preload disk information so the disk selection page is populated.
    m_storageManager->refresh();
    m_storageManager->startMonitoring();

    m_engine->loadFromModule(QStringLiteral("BOI.Installer"), QStringLiteral("InstallerWindow"));

    if (m_engine->rootObjects().isEmpty()) {
        return -1;
    }

    return QCoreApplication::exec();
}

} // namespace boi
