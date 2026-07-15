#pragma once

#include <QObject>
#include <QStringList>
#include <QTimer>

namespace bos::shell {
class StorageManager;
}

namespace boi {

class InstallationTarget;

/**
 * @brief Drives the Baytevora OS installation workflow.
 *
 * For the Alpha release the engine performs safe placeholder operations while
 * reporting realistic progress. The class structure is production-ready for a
 * future real partitioning and copy engine.
 */
class InstallerManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int currentStep READ currentStep NOTIFY currentStepChanged FINAL)
    Q_PROPERTY(int totalSteps READ totalSteps CONSTANT FINAL)
    Q_PROPERTY(int installationProgress READ installationProgress NOTIFY installationProgressChanged FINAL)
    Q_PROPERTY(QString currentStepDescription READ currentStepDescription NOTIFY currentStepDescriptionChanged FINAL)
    Q_PROPERTY(QString estimatedTimeRemaining READ estimatedTimeRemaining NOTIFY estimatedTimeRemainingChanged FINAL)
    Q_PROPERTY(QString installationStatus READ installationStatus NOTIFY installationStatusChanged FINAL)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged FINAL)
    Q_PROPERTY(QStringList logs READ logs NOTIFY logsChanged FINAL)

public:
    explicit InstallerManager(bos::shell::StorageManager *storageManager, QObject *parent = nullptr);
    ~InstallerManager() override;

    int currentStep() const;
    int totalSteps() const { return static_cast<int>(m_stepDescriptions.size()); }
    int installationProgress() const;
    QString currentStepDescription() const;
    QString estimatedTimeRemaining() const;
    QString installationStatus() const;
    QString errorMessage() const;
    QStringList logs() const;

    Q_INVOKABLE QString validateDisk(const QString &diskId) const;
    Q_INVOKABLE bool isDiskSuitable(const QString &diskId) const;

    Q_INVOKABLE void startInstallation(InstallationTarget *target);
    Q_INVOKABLE void cancelInstallation();
    Q_INVOKABLE void resetInstallation();

    Q_INVOKABLE QString getInstallationLogs() const;

    void log(const QString &message);

signals:
    void currentStepChanged();
    void installationProgressChanged();
    void currentStepDescriptionChanged();
    void estimatedTimeRemainingChanged();
    void installationStatusChanged();
    void errorMessageChanged();
    void logsChanged();
    void installationCompleted();
    void installationFailed(const QString &reason);

private:
    void setCurrentStep(int step);
    void setInstallationProgress(int progress);
    void setCurrentStepDescription(const QString &description);
    void setEstimatedTimeRemaining(const QString &value);
    void setInstallationStatus(const QString &status);
    void setErrorMessage(const QString &message);
    void runCurrentStep();

    bos::shell::StorageManager *m_storageManager = nullptr;

    int m_currentStep = -1;
    int m_installationProgress = 0;
    QString m_currentStepDescription;
    QString m_estimatedTimeRemaining = QStringLiteral("Calculating...");
    QString m_installationStatus = QStringLiteral("idle");
    QString m_errorMessage;
    QStringList m_logs;

    InstallationTarget *m_activeTarget = nullptr;
    QTimer *m_stepTimer = nullptr;

    const QStringList m_stepDescriptions = {
        QStringLiteral("Preparing installation..."),
        QStringLiteral("Copying system files..."),
        QStringLiteral("Installing applications..."),
        QStringLiteral("Configuring bootloader..."),
        QStringLiteral("Creating configuration..."),
        QStringLiteral("Finalizing installation...")
    };
};

} // namespace boi
