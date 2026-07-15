#include "big/BuildConfiguration.h"
#include "big/ISOBuilder.h"
#include "big/ISOConfiguration.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QObject>

class BuildRunner : public QObject {
    Q_OBJECT
public:
    explicit BuildRunner(big::ISOBuilder *builder, big::BuildConfiguration *buildConfig,
                         big::ISOConfiguration *isoConfig, QObject *parent = nullptr)
        : QObject(parent)
        , m_builder(builder)
        , m_buildConfig(buildConfig)
        , m_isoConfig(isoConfig)
    {
        connect(m_builder, &big::ISOBuilder::buildCompleted, this, &BuildRunner::onCompleted);
        connect(m_builder, &big::ISOBuilder::buildFailed, this, &BuildRunner::onFailed);
    }

    void start() { m_builder->startBuild(m_buildConfig, m_isoConfig); }

private slots:
    void onCompleted(const QString &isoPath) {
        qInfo().noquote() << "Build completed:" << isoPath;
        QCoreApplication::exit(0);
    }
    void onFailed(const QString &reason) {
        qWarning().noquote() << "Build failed:" << reason;
        QCoreApplication::exit(1);
    }

private:
    big::ISOBuilder *m_builder;
    big::BuildConfiguration *m_buildConfig;
    big::ISOConfiguration *m_isoConfig;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("Baytevora ISO Generator"));

    QString isoDir = QFileInfo(QString::fromUtf8(argv[0])).absolutePath();
    if (!QFile::exists(isoDir + QStringLiteral("/config/iso-config.json"))) {
        isoDir = QDir::currentPath();
    }

    const QString buildConfigPath = isoDir + QStringLiteral("/config/build-config.yaml");
    const QString isoConfigPath = isoDir + QStringLiteral("/config/iso-config.json");

    big::BuildConfiguration buildConfig;
    big::ISOConfiguration isoConfig;

    if (!buildConfig.loadFromFile(buildConfigPath)) {
        qWarning().noquote() << "Could not load build configuration:" << buildConfigPath;
        return 1;
    }
    if (!isoConfig.loadFromFile(isoConfigPath)) {
        qWarning().noquote() << "Could not load ISO configuration:" << isoConfigPath;
        return 1;
    }

    big::ISOBuilder builder;
    BuildRunner runner(&builder, &buildConfig, &isoConfig);

    QTimer::singleShot(0, &runner, &BuildRunner::start);
    return QCoreApplication::exec();
}
