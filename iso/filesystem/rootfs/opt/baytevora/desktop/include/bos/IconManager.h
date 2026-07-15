#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Exposes BOS icon size constants.
 *
 * IconManager defines the adaptive standard icon sizes used throughout the
 * interface. Sizes are scaled by the BDL adaptive icon scale.
 */
class IconManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int small READ small NOTIFY smallChanged FINAL)
    Q_PROPERTY(int medium READ medium NOTIFY mediumChanged FINAL)
    Q_PROPERTY(int normal READ normal NOTIFY normalChanged FINAL)
    Q_PROPERTY(int large READ large NOTIFY largeChanged FINAL)
    Q_PROPERTY(int extraLarge READ extraLarge NOTIFY extraLargeChanged FINAL)

public:
    explicit IconManager(QObject *parent = nullptr);
    ~IconManager() override;

    int small() const;
    int medium() const;
    int normal() const;
    int large() const;
    int extraLarge() const;

    void setScaleFactor(double scaleFactor);

signals:
    void smallChanged();
    void mediumChanged();
    void normalChanged();
    void largeChanged();
    void extraLargeChanged();

private:
    int scaled(int baseSize) const;

    double m_scaleFactor = 1.0;
};

} // namespace bos::shell
