#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Describes where a shortcut is active.
 *
 * Global shortcuts are active whenever the application has focus.
 * Application shortcuts are tied to the active application scope.
 * Window shortcuts are active only when the focused window matches.
 *
 * Sprint 18 primarily uses the Global/Application scopes through the
 * Qt::ApplicationShortcut context so that the hidden shortcut host receives
 * key events from every window of the desktop shell.
 */
Q_NAMESPACE

enum class ShortcutContext {
    Global = 0,
    Application,
    Window
};

Q_ENUM_NS(ShortcutContext)

} // namespace bos::shell
