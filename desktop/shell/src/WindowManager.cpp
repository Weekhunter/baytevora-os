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
        { QStringLiteral("isActive"), window.id() == m_activeWindowId }
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

} // namespace bos::shell
