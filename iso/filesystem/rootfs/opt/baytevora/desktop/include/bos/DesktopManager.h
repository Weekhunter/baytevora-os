#pragma once

#include <memory>

#include <QObject>

#include "bos/DesktopModel.h"

namespace bos::shell {

class DesktopItem;

/**
 * @brief Owns the desktop icon model and exposes it to QML.
 *
 * DesktopManager is the single entry point for desktop icon state. It creates
 * and registers the default placeholder icons, exposes the QAbstractListModel,
 * and provides selection and activation entry points. File operations,
 * drag-and-drop, and context menus are intentionally left for future sprints.
 */
class DesktopManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(DesktopModel *model READ model CONSTANT)

public:
    explicit DesktopManager(QObject *parent = nullptr);
    ~DesktopManager() override;

    DesktopModel *model() const;

    Q_INVOKABLE void registerItem(const QString &name, const QString &icon,
                                  const QString &type, int x, int y);
    Q_INVOKABLE void selectItem(int itemId);
    Q_INVOKABLE void activateItem(int itemId);

    void loadDefaults();

signals:
    void itemSelected(int itemId);
    void itemActivated(int itemId);

private:
    std::unique_ptr<DesktopModel> m_model;
    int m_nextId = 1;
};

} // namespace bos::shell
