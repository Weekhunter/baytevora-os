#pragma once

#include <QObject>

namespace bos::shell {

class ThemeManager;

/**
 * @brief Provides adaptive layout metrics for the BDL v2 design system.
 *
 * AdaptiveLayoutManager exposes window padding, content padding, section
 * spacing, control spacing, toolbar height, taskbar height, sidebar width,
 * and title bar height. Values are computed from the primary screen
 * geometry and the BDL adaptive scale factor.
 */
class AdaptiveLayoutManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int windowPadding READ windowPadding NOTIFY metricsChanged FINAL)
    Q_PROPERTY(int contentPadding READ contentPadding NOTIFY metricsChanged FINAL)
    Q_PROPERTY(int sectionSpacing READ sectionSpacing NOTIFY metricsChanged FINAL)
    Q_PROPERTY(int controlSpacing READ controlSpacing NOTIFY metricsChanged FINAL)
    Q_PROPERTY(int toolbarHeight READ toolbarHeight NOTIFY metricsChanged FINAL)
    Q_PROPERTY(int taskbarHeight READ taskbarHeight NOTIFY metricsChanged FINAL)
    Q_PROPERTY(int sidebarWidth READ sidebarWidth NOTIFY metricsChanged FINAL)
    Q_PROPERTY(int titleBarHeight READ titleBarHeight NOTIFY metricsChanged FINAL)

public:
    explicit AdaptiveLayoutManager(QObject *parent = nullptr);
    ~AdaptiveLayoutManager() override;

    int windowPadding() const;
    int contentPadding() const;
    int sectionSpacing() const;
    int controlSpacing() const;
    int toolbarHeight() const;
    int taskbarHeight() const;
    int sidebarWidth() const;
    int titleBarHeight() const;

    void setScaleFactor(double scaleFactor);

public slots:
    void recalculate();

signals:
    void metricsChanged();

private:
    int scaled(int baseSize) const;

    double m_scaleFactor = 1.0;
};

} // namespace bos::shell
