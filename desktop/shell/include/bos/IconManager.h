#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Exposes BOS icon size constants.
 *
 * IconManager defines the standard icon sizes used throughout the interface.
 * Icon packs are not implemented in this sprint; only the size vocabulary is
 * provided.
 */
class IconManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int small READ small CONSTANT)
    Q_PROPERTY(int medium READ medium CONSTANT)
    Q_PROPERTY(int normal READ normal CONSTANT)
    Q_PROPERTY(int large READ large CONSTANT)
    Q_PROPERTY(int extraLarge READ extraLarge CONSTANT)

public:
    explicit IconManager(QObject *parent = nullptr);
    ~IconManager() override;

    int small() const;
    int medium() const;
    int normal() const;
    int large() const;
    int extraLarge() const;
};

} // namespace bos::shell
