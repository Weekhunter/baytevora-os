#include "boi/InstallerManager.h"
#include "boi/InstallationTarget.h"

#include "bos/StorageDevice.h"
#include "bos/StorageManager.h"

#include <QVariant>

namespace boi {

namespace {
constexpr qint64 MinimumCapacityBytes = 20LL * 1024LL * 1024LL * 1024LL;

static int progressForStep(int step)
{
    // Map each step to its approximate completion percentage.
    static const int table[] = { 0, 15, 40, 65, 80, 95, 100 };
    return table[qBound(0, step, 6)];
}
} // namespace

InstallerManager::InstallerManager(bos::shell::StorageManager *storageManager, QObject *parent)
    : QObject(parent)
    , m_storageManager(storageManager)
    , m_stepTimer(new QTimer(this))
{
    m_stepTimer->setSingleShot(true);
    connect(m_stepTimer, &QTimer::timeout, this, &InstallerManager::runCurrentStep);
}

InstallerManager::~InstallerManager() = default;

int InstallerManager::currentStep() const { return m_currentStep; }
int InstallerManager::installationProgress() const { return m_installationProgress; }
QString InstallerManager::currentStepDescription() const { return m_currentStepDescription; }
QString InstallerManager::estimatedTimeRemaining() const { return m_estimatedTimeRemaining; }
QString InstallerManager::installationStatus() const { return m_installationStatus; }
QString InstallerManager::errorMessage() const { return m_errorMessage; }
QStringList InstallerManager::logs() const { return m_logs; }

QString InstallerManager::validateDisk(const QString &diskId) const
{
    if (!m_storageManager || diskId.isEmpty()) {
        return QStringLiteral("No storage device selected.");
    }

    const QVariantList devices = m_storageManager->devices();
    for (const QVariant &deviceVariant : devices) {
        auto *device = qobject_cast<bos::shell::StorageDevice*>(deviceVariant.value<QObject*>());
        if (!device) continue;
        if (device->deviceName() != diskId && device->displayName() != diskId) continue;

        if (device->capacity() < MinimumCapacityBytes) {
            return QStringLiteral("Disk must have at least 20 GB of capacity.");
        }
        if (device->removable()) {
            return QStringLiteral("Removable disks are not recommended as installation targets.");
        }
        return QString();
    }
    return QStringLiteral("Selected disk was not found.");
}

bool InstallerManager::isDiskSuitable(const QString &diskId) const
{
    return validateDisk(diskId).isEmpty();
}

void InstallerManager::startInstallation(InstallationTarget *target)
{
    if (!target) {
        setErrorMessage(QStringLiteral("No installation target provided."));
        emit installationFailed(m_errorMessage);
        return;
    }

    if (!validateDisk(target->diskId()).isEmpty()) {
        setErrorMessage(validateDisk(target->diskId()));
        emit installationFailed(m_errorMessage);
        return;
    }

    m_activeTarget = target;
    m_logs.clear();
    emit logsChanged();

    setErrorMessage(QString());
    setInstallationStatus(QStringLiteral("installing"));
    setEstimatedTimeRemaining(QStringLiteral("Calculating..."));

    m_currentStep = -1;
    setInstallationProgress(0);
    log(QStringLiteral("Installation started on %1").arg(target->diskId()));

    setCurrentStep(0);
}

void InstallerManager::cancelInstallation()
{
    if (m_installationStatus != QStringLiteral("installing")) return;

    m_stepTimer->stop();
    setInstallationStatus(QStringLiteral("cancelled"));
    log(QStringLiteral("Installation cancelled by user."));
}

void InstallerManager::resetInstallation()
{
    m_stepTimer->stop();
    m_currentStep = -1;
    setInstallationProgress(0);
    setCurrentStepDescription(QString());
    setEstimatedTimeRemaining(QStringLiteral("Calculating..."));
    setInstallationStatus(QStringLiteral("idle"));
    setErrorMessage(QString());
    m_activeTarget = nullptr;
}

QString InstallerManager::getInstallationLogs() const
{
    return m_logs.join(QStringLiteral("\n"));
}

void InstallerManager::log(const QString &message)
{
    m_logs.append(message);
    emit logsChanged();
}

void InstallerManager::setCurrentStep(int step)
{
    if (m_currentStep == step) return;
    m_currentStep = step;
    emit currentStepChanged();
    setInstallationProgress(progressForStep(step));
    setCurrentStepDescription(m_stepDescriptions.value(step));

    if (step >= 0 && step < totalSteps()) {
        m_stepTimer->start(900);
    } else if (step >= totalSteps()) {
        setInstallationStatus(QStringLiteral("completed"));
        setEstimatedTimeRemaining(QStringLiteral("Done"));
        log(QStringLiteral("Installation completed successfully."));
        emit installationCompleted();
    }
}

void InstallerManager::setInstallationProgress(int progress)
{
    if (m_installationProgress == progress) return;
    m_installationProgress = qBound(0, progress, 100);
    emit installationProgressChanged();
}

void InstallerManager::setCurrentStepDescription(const QString &description)
{
    if (m_currentStepDescription == description) return;
    m_currentStepDescription = description;
    emit currentStepDescriptionChanged();
}

void InstallerManager::setEstimatedTimeRemaining(const QString &value)
{
    if (m_estimatedTimeRemaining == value) return;
    m_estimatedTimeRemaining = value;
    emit estimatedTimeRemainingChanged();
}

void InstallerManager::setInstallationStatus(const QString &status)
{
    if (m_installationStatus == status) return;
    m_installationStatus = status;
    emit installationStatusChanged();
}

void InstallerManager::setErrorMessage(const QString &message)
{
    if (m_errorMessage == message) return;
    m_errorMessage = message;
    emit errorMessageChanged();
}

void InstallerManager::runCurrentStep()
{
    if (m_currentStep < 0 || m_currentStep >= totalSteps()) return;

    // Alpha: each step is a safe placeholder. A future real engine will replace
    // these blocks with partition, copy, and bootloader operations.
    log(QStringLiteral("Step %1/%2: %3")
            .arg(m_currentStep + 1)
            .arg(totalSteps())
            .arg(m_currentStepDescription));

    setEstimatedTimeRemaining(QStringLiteral("%1 step(s) remaining").arg(totalSteps() - m_currentStep));

    setCurrentStep(m_currentStep + 1);
}

} // namespace boi
