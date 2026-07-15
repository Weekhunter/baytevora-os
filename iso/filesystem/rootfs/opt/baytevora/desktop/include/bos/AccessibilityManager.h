#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Placeholder accessibility settings manager for BDL v2.
 *
 * AccessibilityManager exposes the core accessibility toggles that future
 * sprints will consume. No visual changes are implemented in this sprint.
 */
class AccessibilityManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool largeTextEnabled READ largeTextEnabled NOTIFY largeTextEnabledChanged FINAL)
    Q_PROPERTY(bool highContrastEnabled READ highContrastEnabled NOTIFY highContrastEnabledChanged FINAL)
    Q_PROPERTY(bool reducedMotionEnabled READ reducedMotionEnabled NOTIFY reducedMotionEnabledChanged FINAL)

public:
    explicit AccessibilityManager(QObject *parent = nullptr);
    ~AccessibilityManager() override;

    bool largeTextEnabled() const;
    bool highContrastEnabled() const;
    bool reducedMotionEnabled() const;

public slots:
    void setLargeTextEnabled(bool enabled);
    void setHighContrastEnabled(bool enabled);
    void setReducedMotionEnabled(bool enabled);

signals:
    void largeTextEnabledChanged();
    void highContrastEnabledChanged();
    void reducedMotionEnabledChanged();
};

} // namespace bos::shell
