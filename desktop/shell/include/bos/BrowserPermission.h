#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single browser site permission rule.
 */
class BrowserPermission : public QObject {
    Q_OBJECT

    Q_PROPERTY(int permissionId READ permissionId NOTIFY permissionIdChanged FINAL)
    Q_PROPERTY(QString origin READ origin NOTIFY originChanged FINAL)
    Q_PROPERTY(QString permissionType READ permissionType NOTIFY permissionTypeChanged FINAL)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged FINAL)
    Q_PROPERTY(QDateTime lastModified READ lastModified NOTIFY lastModifiedChanged FINAL)

public:
    explicit BrowserPermission(int permissionId, QObject *parent = nullptr);
    ~BrowserPermission() override;

    int permissionId() const;
    QString origin() const;
    QString permissionType() const;
    QString state() const;
    QDateTime lastModified() const;

    void setOrigin(const QString &origin);
    void setPermissionType(const QString &permissionType);
    void setState(const QString &state);
    void setLastModified(const QDateTime &lastModified);

signals:
    void permissionIdChanged();
    void originChanged();
    void permissionTypeChanged();
    void stateChanged();
    void lastModifiedChanged();

private:
    int m_permissionId = -1;
    QString m_origin;
    QString m_permissionType;
    QString m_state;
    QDateTime m_lastModified;
};

} // namespace bos::shell
