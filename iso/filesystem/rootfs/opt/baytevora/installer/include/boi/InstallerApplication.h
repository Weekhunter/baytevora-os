#pragma once

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <memory>

namespace bos::shell {
class BrandingManager;
class StorageManager;
class ThemeManager;
class TypographyManager;
class SpacingManager;
class DesignTokens;
class IconManager;
class AdaptiveLayoutManager;
} // namespace bos::shell

namespace boi {
class InstallerManager;
class InstallerSession;
}

namespace boi {

/**
 * @brief Top-level controller for the Baytevora OS Installer application.
 *
 * InstallerApplication owns the Qt application object, the QML engine, the
 * installer services, and the design-system singletons reused from BOS.Shell.
 */
class InstallerApplication : public QObject {
    Q_OBJECT

public:
    explicit InstallerApplication(QGuiApplication &app, QObject *parent = nullptr);
    ~InstallerApplication() override;

    int run();

private:
    void registerQmlTypes();
    void exposeContextObjects();

    QGuiApplication &m_app;
    std::unique_ptr<QQmlApplicationEngine> m_engine;

    bos::shell::BrandingManager *m_brandingManager = nullptr;
    bos::shell::StorageManager *m_storageManager = nullptr;
    bos::shell::ThemeManager *m_themeManager = nullptr;
    bos::shell::TypographyManager *m_typographyManager = nullptr;
    bos::shell::SpacingManager *m_spacingManager = nullptr;
    bos::shell::DesignTokens *m_designTokens = nullptr;
    bos::shell::IconManager *m_iconManager = nullptr;
    bos::shell::AdaptiveLayoutManager *m_adaptiveLayoutManager = nullptr;

    InstallerSession *m_session = nullptr;
    InstallerManager *m_manager = nullptr;
};

} // namespace boi
