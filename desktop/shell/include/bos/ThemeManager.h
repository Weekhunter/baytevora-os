#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Provides the BOS color palette to QML.
 *
 * ThemeManager exposes read-only properties for all semantic and surface
 * colors defined by BDL v2. It also provides adaptive read-only metrics
 * computed from the primary screen geometry and device pixel ratio.
 * Future theme engine work will replace color values without changing QML.
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

    Q_PROPERTY(bool compactMode READ compactMode NOTIFY metricsChanged)
    Q_PROPERTY(bool touchMode READ touchMode NOTIFY metricsChanged)
    Q_PROPERTY(bool highDpi READ highDpi NOTIFY metricsChanged)
    Q_PROPERTY(double scaleFactor READ scaleFactor NOTIFY metricsChanged)
    Q_PROPERTY(double iconScale READ iconScale NOTIFY metricsChanged)
    Q_PROPERTY(double textScale READ textScale NOTIFY metricsChanged)

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

    bool compactMode() const;
    bool touchMode() const;
    bool highDpi() const;
    double scaleFactor() const;
    double iconScale() const;
    double textScale() const;

public slots:
    void recalculateMetrics();

signals:
    void metricsChanged();

private:
    void updateMetrics();

    bool m_compactMode = false;
    bool m_touchMode = false;
    bool m_highDpi = false;
    double m_scaleFactor = 1.0;
    double m_iconScale = 1.0;
    double m_textScale = 1.0;
};

} // namespace bos::shell
