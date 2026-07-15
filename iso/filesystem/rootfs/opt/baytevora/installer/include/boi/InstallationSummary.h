#pragma once

#include <QObject>
#include <QString>

namespace boi {

/**
 * @brief Read-only data holder for the installation review screen.
 */
class InstallationSummary : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString targetDisk READ targetDisk NOTIFY targetDiskChanged FINAL)
    Q_PROPERTY(QString diskCapacity READ diskCapacity NOTIFY diskCapacityChanged FINAL)
    Q_PROPERTY(QString requiredSpace READ requiredSpace NOTIFY requiredSpaceChanged FINAL)
    Q_PROPERTY(QString installationType READ installationType NOTIFY installationTypeChanged FINAL)
    Q_PROPERTY(QString language READ language NOTIFY languageChanged FINAL)
    Q_PROPERTY(QString keyboard READ keyboard NOTIFY keyboardChanged FINAL)

public:
    explicit InstallationSummary(QObject *parent = nullptr);

    QString targetDisk() const;
    void setTargetDisk(const QString &value);

    QString diskCapacity() const;
    void setDiskCapacity(const QString &value);

    QString requiredSpace() const;
    void setRequiredSpace(const QString &value);

    QString installationType() const;
    void setInstallationType(const QString &value);

    QString language() const;
    void setLanguage(const QString &value);

    QString keyboard() const;
    void setKeyboard(const QString &value);

signals:
    void targetDiskChanged();
    void diskCapacityChanged();
    void requiredSpaceChanged();
    void installationTypeChanged();
    void languageChanged();
    void keyboardChanged();

private:
    QString m_targetDisk;
    QString m_diskCapacity;
    QString m_requiredSpace;
    QString m_installationType;
    QString m_language;
    QString m_keyboard;
};

} // namespace boi
