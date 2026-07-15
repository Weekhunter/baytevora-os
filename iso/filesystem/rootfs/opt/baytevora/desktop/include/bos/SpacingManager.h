#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Exposes the BOS spacing scale.
 *
 * SpacingManager provides the 4 px grid spacing values as read-only
 * properties. QML should use these tokens for margins, padding, and gaps.
 */
class SpacingManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int space4 READ space4 CONSTANT)
    Q_PROPERTY(int space8 READ space8 CONSTANT)
    Q_PROPERTY(int space12 READ space12 CONSTANT)
    Q_PROPERTY(int space16 READ space16 CONSTANT)
    Q_PROPERTY(int space20 READ space20 CONSTANT)
    Q_PROPERTY(int space24 READ space24 CONSTANT)
    Q_PROPERTY(int space32 READ space32 CONSTANT)
    Q_PROPERTY(int space40 READ space40 CONSTANT)
    Q_PROPERTY(int space48 READ space48 CONSTANT)
    Q_PROPERTY(int space64 READ space64 CONSTANT)

public:
    explicit SpacingManager(QObject *parent = nullptr);
    ~SpacingManager() override;

    int space4() const;
    int space8() const;
    int space12() const;
    int space16() const;
    int space20() const;
    int space24() const;
    int space32() const;
    int space40() const;
    int space48() const;
    int space64() const;
};

} // namespace bos::shell
