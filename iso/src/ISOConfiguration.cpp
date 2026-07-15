#include "big/ISOConfiguration.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace big {

ISOConfiguration::ISOConfiguration(QObject *parent)
    : QObject(parent)
{
}

QString ISOConfiguration::volumeLabel() const { return m_volumeLabel; }
void ISOConfiguration::setVolumeLabel(const QString &value)
{
    if (m_volumeLabel == value) return;
    m_volumeLabel = value;
    emit volumeLabelChanged();
}

QString ISOConfiguration::publisher() const { return m_publisher; }
void ISOConfiguration::setPublisher(const QString &value)
{
    if (m_publisher == value) return;
    m_publisher = value;
    emit publisherChanged();
}

QString ISOConfiguration::applicationID() const { return m_applicationID; }
void ISOConfiguration::setApplicationID(const QString &value)
{
    if (m_applicationID == value) return;
    m_applicationID = value;
    emit applicationIDChanged();
}

QString ISOConfiguration::bootMode() const { return m_bootMode; }
void ISOConfiguration::setBootMode(const QString &value)
{
    if (m_bootMode == value) return;
    m_bootMode = value;
    emit bootModeChanged();
}

int ISOConfiguration::bootTimeout() const { return m_bootTimeout; }
void ISOConfiguration::setBootTimeout(int value)
{
    if (m_bootTimeout == value) return;
    m_bootTimeout = value;
    emit bootTimeoutChanged();
}

bool ISOConfiguration::loadFromFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return false;

    const QJsonObject obj = doc.object();
    setVolumeLabel(obj.value(QStringLiteral("volumeLabel")).toString());
    setPublisher(obj.value(QStringLiteral("publisher")).toString());
    setApplicationID(obj.value(QStringLiteral("applicationID")).toString());
    setBootMode(obj.value(QStringLiteral("bootMode")).toString());
    setBootTimeout(obj.value(QStringLiteral("bootTimeout")).toInt());
    return true;
}

bool ISOConfiguration::validate() const
{
    if (m_volumeLabel.isEmpty() || m_publisher.isEmpty() || m_applicationID.isEmpty()) return false;
    if (m_bootMode != QStringLiteral("UEFI")) return false; // Alpha scope.
    return true;
}

QVariantMap ISOConfiguration::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("volumeLabel")] = m_volumeLabel;
    map[QStringLiteral("publisher")] = m_publisher;
    map[QStringLiteral("applicationID")] = m_applicationID;
    map[QStringLiteral("bootMode")] = m_bootMode;
    map[QStringLiteral("bootTimeout")] = m_bootTimeout;
    return map;
}

} // namespace big
