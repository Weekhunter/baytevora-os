#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

#include "bos/ShortcutContext.h"

class QWidget;

namespace bos::shell {

class Shortcut;

/**
 * @brief Central manager for all keyboard shortcuts in the desktop environment.
 *
 * ShortcutManager registers, unregisters, enables, and disables shortcuts using
 * Qt's QShortcut API. It detects duplicate registrations and exposes the list of
 * registered shortcuts to QML. When a shortcut is activated, the manager emits
 * shortcutActivated(id) so applications can react.
 */
class ShortcutManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList registeredShortcuts READ registeredShortcuts NOTIFY registeredShortcutsChanged)

public:
    explicit ShortcutManager(QWidget *shortcutParent, QObject *parent = nullptr);
    ~ShortcutManager() override;

    Q_INVOKABLE int registerShortcut(const QString &name, const QString &keySequence,
                                     ShortcutContext context,
                                     const QString &description = QString());
    Q_INVOKABLE bool removeShortcut(int id);
    Q_INVOKABLE bool enableShortcut(int id);
    Q_INVOKABLE bool disableShortcut(int id);
    Q_INVOKABLE bool isRegistered(const QString &keySequence, ShortcutContext context) const;
    Q_INVOKABLE QVariantList registeredShortcuts() const;

signals:
    void shortcutActivated(int id);
    void shortcutRegistered(int id);
    void shortcutRemoved(int id);
    void registeredShortcutsChanged();

private:
    Shortcut *findShortcut(int id) const;

    QWidget *m_shortcutParent = nullptr;
    QList<Shortcut *> m_shortcuts;
    int m_nextId = 1;
};

} // namespace bos::shell
