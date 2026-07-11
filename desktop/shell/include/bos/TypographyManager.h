#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Exposes the BOS typography scale and font family.
 *
 * TypographyManager provides the type scale as read-only integer properties.
 * QML must use these values instead of hardcoding font sizes.
 */
class TypographyManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString fontFamily READ fontFamily CONSTANT)
    Q_PROPERTY(int display READ displaySize CONSTANT)
    Q_PROPERTY(int heading READ heading CONSTANT)
    Q_PROPERTY(int title READ title CONSTANT)
    Q_PROPERTY(int subtitle READ subtitle CONSTANT)
    Q_PROPERTY(int body READ body CONSTANT)
    Q_PROPERTY(int caption READ caption CONSTANT)
    Q_PROPERTY(int small READ small CONSTANT)

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
};

} // namespace bos::shell
