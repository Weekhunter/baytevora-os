#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Shared, non-color design tokens for BOS components.
 *
 * DesignTokens exposes values such as corner radii that are independent of
 * color theme. QML references these tokens to keep visual constants in one
 * place.
 */
class DesignTokens : public QObject {
    Q_OBJECT

    Q_PROPERTY(int radiusSmall READ radiusSmall CONSTANT)
    Q_PROPERTY(int radiusMedium READ radiusMedium CONSTANT)
    Q_PROPERTY(int radiusLarge READ radiusLarge CONSTANT)
    Q_PROPERTY(int radiusXLarge READ radiusXLarge CONSTANT)

public:
    explicit DesignTokens(QObject *parent = nullptr);
    ~DesignTokens() override;

    int radiusSmall() const;
    int radiusMedium() const;
    int radiusLarge() const;
    int radiusXLarge() const;
};

} // namespace bos::shell
