#include "bos/Shortcut.h"

#include <QShortcut>
#include <QWidget>

namespace bos::shell {

Shortcut::Shortcut(int id, const QString &name, const QKeySequence &keySequence,
                   ShortcutContext context, const QString &description,
                   QWidget *shortcutParent, QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_name(name)
    , m_keySequence(keySequence)
    , m_context(context)
    , m_description(description)
{
    m_nativeShortcut = new QShortcut(keySequence, shortcutParent);

    Qt::ShortcutContext nativeContext = Qt::ApplicationShortcut;
    if (context == ShortcutContext::Window) {
        nativeContext = Qt::WindowShortcut;
    }
    m_nativeShortcut->setContext(nativeContext);

    connect(m_nativeShortcut, &QShortcut::activated,
            this, [this]() { emit triggered(m_id); });
}

Shortcut::~Shortcut() = default;

int Shortcut::id() const
{
    return m_id;
}

QString Shortcut::name() const
{
    return m_name;
}

QString Shortcut::keySequence() const
{
    return m_keySequence.toString(QKeySequence::PortableText);
}

ShortcutContext Shortcut::context() const
{
    return m_context;
}

bool Shortcut::enabled() const
{
    return m_enabled;
}

QString Shortcut::description() const
{
    return m_description;
}

void Shortcut::setEnabled(bool enabled)
{
    if (m_enabled == enabled) {
        return;
    }
    m_enabled = enabled;
    if (m_nativeShortcut) {
        m_nativeShortcut->setEnabled(enabled);
    }
    emit enabledChanged();
}

QShortcut *Shortcut::nativeShortcut() const
{
    return m_nativeShortcut;
}

} // namespace bos::shell
