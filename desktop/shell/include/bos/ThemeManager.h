#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Provides the BOS color palette to QML.
 *
 * ThemeManager exposes read-only properties for all semantic and surface
 * colors defined by BDL v1. Future theme engine work will replace these
 * values without changing QML.
 */
class ThemeManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString primaryColor READ primaryColor CONSTANT)
    Q_PROPERTY(QString accentColor READ accentColor CONSTANT)
    Q_PROPERTY(QString backgroundColor READ backgroundColor CONSTANT)
    Q_PROPERTY(QString surfaceColor READ surfaceColor CONSTANT)
    Q_PROPERTY(QString surfaceSecondaryColor READ surfaceSecondaryColor CONSTANT)
    Q_PROPERTY(QString borderColor READ borderColor CONSTANT)
    Q_PROPERTY(QString textPrimary READ textPrimary CONSTANT)
    Q_PROPERTY(QString textSecondary READ textSecondary CONSTANT)
    Q_PROPERTY(QString textDisabled READ textDisabled CONSTANT)
    Q_PROPERTY(QString successColor READ successColor CONSTANT)
    Q_PROPERTY(QString warningColor READ warningColor CONSTANT)
    Q_PROPERTY(QString errorColor READ errorColor CONSTANT)
    Q_PROPERTY(QString highlightColor READ highlightColor CONSTANT)
    Q_PROPERTY(QString selectionColor READ selectionColor CONSTANT)
    Q_PROPERTY(QString windowBackground READ windowBackground CONSTANT)
    Q_PROPERTY(QString taskbarBackground READ taskbarBackground CONSTANT)
    Q_PROPERTY(QString launcherBackground READ launcherBackground CONSTANT)
    Q_PROPERTY(QString notificationBackground READ notificationBackground CONSTANT)

public:
    explicit ThemeManager(QObject *parent = nullptr);
    ~ThemeManager() override;

    QString primaryColor() const;
    QString accentColor() const;
    QString backgroundColor() const;
    QString surfaceColor() const;
    QString surfaceSecondaryColor() const;
    QString borderColor() const;
    QString textPrimary() const;
    QString textSecondary() const;
    QString textDisabled() const;
    QString successColor() const;
    QString warningColor() const;
    QString errorColor() const;
    QString highlightColor() const;
    QString selectionColor() const;
    QString windowBackground() const;
    QString taskbarBackground() const;
    QString launcherBackground() const;
    QString notificationBackground() const;
};

} // namespace bos::shell
