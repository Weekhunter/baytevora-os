#pragma once

#include <QObject>
#include <QProcess>
#include <QStringList>

namespace big {

class BuildConfiguration;
class ISOConfiguration;
class BuildLogger;
class ImageManifest;

/**
 * @brief Orchestrates the Baytevora OS ISO build process.
 */
class ISOBuilder : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString buildStatus READ buildStatus NOTIFY buildStatusChanged FINAL)
    Q_PROPERTY(int buildProgress READ buildProgress NOTIFY buildProgressChanged FINAL)
    Q_PROPERTY(QString currentStep READ currentStep NOTIFY currentStepChanged FINAL)
    Q_PROPERTY(QString outputPath READ outputPath NOTIFY outputPathChanged FINAL)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged FINAL)

public:
    explicit ISOBuilder(QObject *parent = nullptr);

    QString buildStatus() const;
    int buildProgress() const;
    QString currentStep() const;
    QString outputPath() const;
    QString errorMessage() const;

    Q_INVOKABLE void startBuild(BuildConfiguration *buildConfig, ISOConfiguration *isoConfig);
    Q_INVOKABLE void cancelBuild();
    Q_INVOKABLE bool validateOutput(const QString &isoPath) const;
    Q_INVOKABLE QString getBuildLogs() const;

signals:
    void buildStatusChanged();
    void buildProgressChanged();
    void currentStepChanged();
    void outputPathChanged();
    void errorMessageChanged();
    void buildCompleted(const QString &isoPath);
    void buildFailed(const QString &reason);

private:
    void setBuildStatus(const QString &status);
    void setBuildProgress(int progress);
    void setCurrentStep(const QString &step);
    void setErrorMessage(const QString &message);
    void setOutputPath(const QString &path);
    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

    bool prepareFilesystem(const BuildConfiguration *config);
    bool copyPackages(const BuildConfiguration *config);
    bool generateGrubConfig(const BuildConfiguration *config, const ISOConfiguration *isoConfig);
    bool createBootImages(const BuildConfiguration *config, const ISOConfiguration *isoConfig);
    bool createSquashfs(const BuildConfiguration *config);
    bool assembleIso(const BuildConfiguration *config, const ISOConfiguration *isoConfig);
    bool generateManifests(const BuildConfiguration *config, const ISOConfiguration *isoConfig);
    bool generateChecksum(const QString &isoPath);

    QString m_buildStatus = QStringLiteral("idle");
    int m_buildProgress = 0;
    QString m_currentStep;
    QString m_outputPath;
    QString m_errorMessage;
    bool m_cancelled = false;

    BuildLogger *m_logger = nullptr;
    ImageManifest *m_manifest = nullptr;
};

} // namespace big
