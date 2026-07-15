#include "bldf/ApplicationRegistrar.h"
#include "bldf/ComponentInstaller.h"
#include "bldf/DebianBaseBuilder.h"
#include "bldf/DisplayManagerConfigurator.h"
#include "bldf/FilesystemConfigurator.h"
#include "bldf/ServiceConfigurator.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QObject>
#include <QDebug>

class FoundationRunner : public QObject {
    Q_OBJECT
public:
    explicit FoundationRunner(QObject *parent = nullptr) : QObject(parent) {}

    void start(const QString &configPath)
    {
        bldf::DebianBaseBuilder builder;
        bldf::FilesystemConfigurator fs;
        bldf::ComponentInstaller installer;
        bldf::DisplayManagerConfigurator dm;
        bldf::ApplicationRegistrar registrar;
        bldf::ServiceConfigurator services;

        connect(&builder, &bldf::DebianBaseBuilder::logInfo, this, [](const QString &m) { qInfo().noquote() << m; });
        connect(&builder, &bldf::DebianBaseBuilder::logWarning, this, [](const QString &m) { qWarning().noquote() << m; });
        connect(&builder, &bldf::DebianBaseBuilder::logError, this, [](const QString &m) { qCritical().noquote() << m; });

        QString targetRoot = QDir::currentPath() + QStringLiteral("/rootfs");
        QString sourceRoot = QFileInfo(QDir::currentPath()).dir().absolutePath();

        if (!configPath.isEmpty() && QFile::exists(configPath)) {
            // Minimal YAML parsing is done in the shell scripts; C++ defaults to current paths.
        }

        builder.setTargetRoot(targetRoot);
        fs.setTargetRoot(targetRoot);
        installer.setTargetRoot(targetRoot);
        installer.setSourceRoot(sourceRoot);
        dm.setTargetRoot(targetRoot);
        registrar.setTargetRoot(targetRoot);
        services.setTargetRoot(targetRoot);

        if (!builder.buildBase()) {
            QCoreApplication::exit(1);
            return;
        }
        if (!fs.configureAll()) {
            QCoreApplication::exit(1);
            return;
        }
        if (!installer.installAll()) {
            QCoreApplication::exit(1);
            return;
        }
        if (!dm.configureAll()) {
            QCoreApplication::exit(1);
            return;
        }
        if (!registrar.registerAll()) {
            QCoreApplication::exit(1);
            return;
        }
        if (!services.configureAll()) {
            QCoreApplication::exit(1);
            return;
        }

        qInfo().noquote() << "Baytevora foundation prepared at" << targetRoot;
        QCoreApplication::exit(0);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("Baytevora Foundation Builder"));

    const QString configPath = argc > 1 ? QString::fromUtf8(argv[1]) : QString();
    FoundationRunner runner;
    QTimer::singleShot(0, &runner, [configPath, &runner]() { runner.start(configPath); });

    return QCoreApplication::exec();
}
