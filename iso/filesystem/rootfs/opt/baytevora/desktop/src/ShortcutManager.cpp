#include "bos/ShortcutManager.h"

#include <QDebug>
#include <QKeySequence>
#include <QVariantMap>
#include <QWidget>

#include "bos/Shortcut.h"

namespace bos::shell {

ShortcutManager::ShortcutManager(QWidget *shortcutParent, QObject *parent)
    : QObject(parent)
    , m_shortcutParent(shortcutParent)
{
    qDebug() << QStringLiteral("[BDE] Shortcut manager initialized");
}

ShortcutManager::~ShortcutManager()
{
    qDeleteAll(m_shortcuts);
    m_shortcuts.clear();
}

int ShortcutManager::registerShortcut(const QString &name, const QString &keySequence,
                                       ShortcutContext context, const QString &description)
{
    if (name.isEmpty() || keySequence.isEmpty()) {
        return -1;
    }

    QKeySequence sequence(keySequence);
    if (sequence.isEmpty()) {
        qDebug() << QStringLiteral("[BDE] Invalid shortcut sequence: ") << keySequence;
        return -1;
    }

    if (isRegistered(keySequence, context)) {
        qDebug() << QStringLiteral("[BDE] Duplicate shortcut rejected: ") << keySequence;
        return -1;
    }

    Shortcut *shortcut = new Shortcut(m_nextId, name, sequence, context, description,
                                      m_shortcutParent, this);
    connect(shortcut, &Shortcut::triggered,
            this, [this](int id) {
                emit shortcutActivated(id);
                qDebug() << QStringLiteral("[BDE] Shortcut activated: ") << id;
            });

    m_shortcuts.append(shortcut);
    const int id = m_nextId++;

    emit shortcutRegistered(id);
    emit registeredShortcutsChanged();

    qDebug() << QStringLiteral("[BDE] Shortcut registered: ") << name;
    return id;
}

bool ShortcutManager::removeShortcut(int id)
{
    Shortcut *shortcut = findShortcut(id);
    if (!shortcut) {
        return false;
    }

    m_shortcuts.removeOne(shortcut);
    delete shortcut;

    emit shortcutRemoved(id);
    emit registeredShortcutsChanged();

    qDebug() << QStringLiteral("[BDE] Shortcut removed");
    return true;
}

bool ShortcutManager::enableShortcut(int id)
{
    Shortcut *shortcut = findShortcut(id);
    if (!shortcut) {
        return false;
    }
    shortcut->setEnabled(true);
    return true;
}

bool ShortcutManager::disableShortcut(int id)
{
    Shortcut *shortcut = findShortcut(id);
    if (!shortcut) {
        return false;
    }
    shortcut->setEnabled(false);
    return true;
}

bool ShortcutManager::isRegistered(const QString &keySequence, ShortcutContext context) const
{
    const QKeySequence sequence(keySequence);
    for (const Shortcut *shortcut : m_shortcuts) {
        if (shortcut->context() == context && shortcut->keySequence() == sequence.toString(QKeySequence::PortableText)) {
            return true;
        }
    }
    return false;
}

QVariantList ShortcutManager::registeredShortcuts() const
{
    QVariantList result;
    for (const Shortcut *shortcut : m_shortcuts) {
        QVariantMap map;
        map[QStringLiteral("id")] = shortcut->id();
        map[QStringLiteral("name")] = shortcut->name();
        map[QStringLiteral("keySequence")] = shortcut->keySequence();
        map[QStringLiteral("context")] = static_cast<int>(shortcut->context());
        map[QStringLiteral("enabled")] = shortcut->enabled();
        map[QStringLiteral("description")] = shortcut->description();
        result.append(map);
    }
    return result;
}

Shortcut *ShortcutManager::findShortcut(int id) const
{
    for (Shortcut *shortcut : m_shortcuts) {
        if (shortcut->id() == id) {
            return shortcut;
        }
    }
    return nullptr;
}

} // namespace bos::shell
