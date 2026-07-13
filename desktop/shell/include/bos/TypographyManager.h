#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Exposes the BOS typography scale and font family.
 *
 * TypographyManager provides the adaptive type scale as read-only integer
 * properties. Font sizes are scaled by the BDL adaptive text scale and
 * emit change notifications so QML bindings update automatically.
 */
class TypographyManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString fontFamily READ fontFamily CONSTANT)
    Q_PROPERTY(int display READ displaySize NOTIFY displayChanged FINAL)
    Q_PROPERTY(int heading READ heading NOTIFY headingChanged FINAL)
    Q_PROPERTY(int title READ title NOTIFY titleChanged FINAL)
    Q_PROPERTY(int subtitle READ subtitle NOTIFY subtitleChanged FINAL)
    Q_PROPERTY(int body READ body NOTIFY bodyChanged FINAL)
    Q_PROPERTY(int caption READ caption NOTIFY captionChanged FINAL)
    Q_PROPERTY(int small READ small NOTIFY smallChanged FINAL)

public:
    explicit TypographyManager(QObject *parent = nullptr);
    ~TypographyManager() override;

    QString fontFamily() const;
    int displaySize() const;
    int heading() const;
    int title() const;
    int subtitle() const;
    int body() const;
    int caption() const;
    int small() const;

public slots:
    void setScaleFactor(double scaleFactor);

signals:
    void displayChanged();
    void headingChanged();
    void titleChanged();
    void subtitleChanged();
    void bodyChanged();
    void captionChanged();
    void smallChanged();

private:
    int scaled(int baseSize) const;

    double m_scaleFactor = 1.0;
};

} // namespace bos::shell
