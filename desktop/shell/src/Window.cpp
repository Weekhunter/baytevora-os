#include "bos/Window.h"

namespace bos::shell {

Window::Window(int id,
               const QString &title,
               int width,
               int height,
               int x,
               int y,
               const QString &applicationName,
               bool visible)
    : m_id(id)
    , m_title(title)
    , m_width(width)
    , m_height(height)
    , m_x(x)
    , m_y(y)
    , m_applicationName(applicationName)
    , m_visible(visible)
    , m_active(false)
    , m_state(WindowState::Normal)
    , m_normalX(x)
    , m_normalY(y)
    , m_normalWidth(width)
    , m_normalHeight(height)
{
}

int Window::id() const { return m_id; }
QString Window::title() const { return m_title; }
int Window::width() const { return m_width; }
int Window::height() const { return m_height; }
int Window::x() const { return m_x; }
int Window::y() const { return m_y; }
QString Window::applicationName() const { return m_applicationName; }
bool Window::isVisible() const { return m_visible; }
bool Window::isActive() const { return m_active; }
WindowState Window::state() const { return m_state; }

int Window::normalX() const { return m_normalX; }
int Window::normalY() const { return m_normalY; }
int Window::normalWidth() const { return m_normalWidth; }
int Window::normalHeight() const { return m_normalHeight; }

void Window::setTitle(const QString &title) { m_title = title; }
void Window::setWidth(int width) { m_width = width; }
void Window::setHeight(int height) { m_height = height; }
void Window::setX(int x) { m_x = x; }
void Window::setY(int y) { m_y = y; }
void Window::setApplicationName(const QString &applicationName) { m_applicationName = applicationName; }
void Window::setVisible(bool visible) { m_visible = visible; }
void Window::setActive(bool active) { m_active = active; }
void Window::setState(WindowState state) { m_state = state; }

void Window::saveNormalGeometry()
{
    m_normalX = m_x;
    m_normalY = m_y;
    m_normalWidth = m_width;
    m_normalHeight = m_height;
}

void Window::restoreNormalGeometry()
{
    m_x = m_normalX;
    m_y = m_normalY;
    m_width = m_normalWidth;
    m_height = m_normalHeight;
}

} // namespace bos::shell
