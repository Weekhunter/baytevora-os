#include "bos/WindowManager.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/Window.h"

namespace bos::shell {

WindowManager::WindowManager(QObject *parent)
    : QObject(parent)
{
}

WindowManager::~WindowManager() = default;

QString WindowManager::name() const
{
    return QStringLiteral("WindowManager");
}

void WindowManager::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("initialized");
}

void WindowManager::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("started");

    // Create a single demonstration window centered on the primary screen and
    // make it the active window.
    constexpr int width = 700;
    constexpr int height = 450;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int demoWindowId = registerWindow(QStringLiteral("Welcome to Baytevora OS"), width, height, x, y);
    setActiveWindow(demoWindowId);
}

void WindowManager::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("shutting down");
    m_activeWindowId = -1;
    m_windows.clear();
    emit activeWindowIdChanged();
    emit windowsChanged();
}

int WindowManager::registerWindow(const QString &title, int width, int height, int x, int y)
{
    const int id = m_nextId++;
    m_windows.push_back(std::make_unique<Window>(id, title, width, height, x, y));

    qDebug() << QStringLiteral("[BDE] Window created (ID:") << id << QStringLiteral(")");
    qDebug() << QStringLiteral("[BDE] Window registered");

    emit windowsChanged();
    return id;
}

void WindowManager::unregisterWindow(int id)
{
    auto it = std::remove_if(m_windows.begin(), m_windows.end(),
                             [id](const auto &window) { return window->id() == id; });

    if (it != m_windows.end()) {
        m_windows.erase(it, m_windows.end());
        emit windowsChanged();
    }
}

QVariantList WindowManager::windows() const
{
    QVariantList list;
    list.reserve(static_cast<int>(m_windows.size()));
    for (const auto &window : m_windows) {
        list.append(windowToMap(*window));
    }
    return list;
}

QVariantMap WindowManager::findWindow(int id) const
{
    for (const auto &window : m_windows) {
        if (window->id() == id) {
            return windowToMap(*window);
        }
    }
    return {};
}

QVariantMap WindowManager::activeWindow() const
{
    if (m_activeWindowId == -1) {
        return {};
    }
    return findWindow(m_activeWindowId);
}

int WindowManager::activeWindowId() const
{
    return m_activeWindowId;
}

int WindowManager::createApplicationWindow(const QString &title)
{
    constexpr int width = 700;
    constexpr int height = 450;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = registerWindow(title, width, height, x, y);
    setActiveWindow(windowId);
    return windowId;
}

void WindowManager::setActiveWindow(int id)
{
    if (id == m_activeWindowId) {
        return;
    }

    if (findWindow(id).isEmpty()) {
        qWarning() << QStringLiteral("[BDE] Attempted to activate unknown window ID:") << id;
        return;
    }

    if (Window *previous = findWindowObject(m_activeWindowId)) {
        previous->setActive(false);
        qDebug() << QStringLiteral("[BDE] Window") << m_activeWindowId << QStringLiteral("lost focus");
    }

    m_activeWindowId = id;
    if (Window *current = findWindowObject(m_activeWindowId)) {
        current->setActive(true);
    }

    qDebug() << QStringLiteral("[BDE] Active window:") << m_activeWindowId;
    qDebug() << QStringLiteral("[BDE] Window") << m_activeWindowId << QStringLiteral("focused");

    emit activeWindowIdChanged();
    emit windowsChanged();
}

void WindowManager::minimizeWindow(int id)
{
    Window *window = findWindowObject(id);
    if (!window) {
        qWarning() << QStringLiteral("[BDE] Attempted to minimize unknown window ID:") << id;
        return;
    }

    if (window->state() == WindowState::Minimized) {
        return;
    }

    window->saveNormalGeometry();
    window->setState(WindowState::Minimized);
    qDebug() << QStringLiteral("[BDE] Window") << id << QStringLiteral("minimized");

    if (m_activeWindowId == id) {
        pickNewActiveWindow();
    }

    emit activeWindowIdChanged();
    emit windowsChanged();
}

void WindowManager::maximizeWindow(int id)
{
    Window *window = findWindowObject(id);
    if (!window) {
        qWarning() << QStringLiteral("[BDE] Attempted to maximize unknown window ID:") << id;
        return;
    }

    if (window->state() == WindowState::Maximized) {
        return;
    }

    if (window->state() == WindowState::Normal) {
        window->saveNormalGeometry();
    }

    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        window->setX(geometry.x());
        window->setY(geometry.y());
        window->setWidth(geometry.width());
        window->setHeight(geometry.height());
    }

    window->setState(WindowState::Maximized);
    qDebug() << QStringLiteral("[BDE] Window") << id << QStringLiteral("maximized");

    emit windowsChanged();
}

void WindowManager::restoreWindow(int id)
{
    Window *window = findWindowObject(id);
    if (!window) {
        qWarning() << QStringLiteral("[BDE] Attempted to restore unknown window ID:") << id;
        return;
    }

    if (window->state() == WindowState::Normal) {
        return;
    }

    if (window->state() == WindowState::Maximized) {
        window->restoreNormalGeometry();
    }

    window->setState(WindowState::Normal);
    qDebug() << QStringLiteral("[BDE] Window") << id << QStringLiteral("restored");

    emit windowsChanged();
}

void WindowManager::closeWindow(int id)
{
    Window *window = findWindowObject(id);
    if (!window) {
        qWarning() << QStringLiteral("[BDE] Attempted to close unknown window ID:") << id;
        return;
    }

    window->setState(WindowState::Closed);
    qDebug() << QStringLiteral("[BDE] Window") << id << QStringLiteral("closed");

    const bool activeChanged = (m_activeWindowId == id);
    if (activeChanged) {
        pickNewActiveWindow();
    }

    auto it = std::remove_if(m_windows.begin(), m_windows.end(),
                             [id](const auto &w) { return w->id() == id; });
    m_windows.erase(it, m_windows.end());

    if (activeChanged) {
        emit activeWindowIdChanged();
    }
    emit windowsChanged();
    emit windowClosed(id);
}

void WindowManager::taskbarButtonClicked(int id)
{
    Window *window = findWindowObject(id);
    if (!window) {
        qWarning() << QStringLiteral("[BDE] Taskbar click on unknown window ID:") << id;
        return;
    }

    if (window->state() == WindowState::Minimized) {
        restoreWindow(id);
        qDebug() << QStringLiteral("[BDE] Window restored from taskbar");
        return;
    }

    if (id == m_activeWindowId) {
        return;
    }

    setActiveWindow(id);
}

QVariantMap WindowManager::windowToMap(const Window &window) const
{
    return QVariantMap{
        { QStringLiteral("id"), window.id() },
        { QStringLiteral("title"), window.title() },
        { QStringLiteral("width"), window.width() },
        { QStringLiteral("height"), window.height() },
        { QStringLiteral("x"), window.x() },
        { QStringLiteral("y"), window.y() },
        { QStringLiteral("visible"), window.isVisible() },
        { QStringLiteral("isActive"), window.id() == m_activeWindowId },
        { QStringLiteral("state"), stateToString(window.state()) }
    };
}

Window *WindowManager::findWindowObject(int id) const
{
    for (const auto &window : m_windows) {
        if (window->id() == id) {
            return window.get();
        }
    }
    return nullptr;
}

void WindowManager::pickNewActiveWindow()
{
    for (const auto &window : m_windows) {
        if (window->state() != WindowState::Minimized && window->state() != WindowState::Closed) {
            m_activeWindowId = window->id();
            window->setActive(true);
            qDebug() << QStringLiteral("[BDE] Active window:") << m_activeWindowId;
            return;
        }
    }

    m_activeWindowId = -1;
}

QString WindowManager::stateToString(WindowState state) const
{
    switch (state) {
    case WindowState::Normal:
        return QStringLiteral("normal");
    case WindowState::Minimized:
        return QStringLiteral("minimized");
    case WindowState::Maximized:
        return QStringLiteral("maximized");
    case WindowState::Closed:
        return QStringLiteral("closed");
    }

    return QStringLiteral("normal");
}

} // namespace bos::shell
