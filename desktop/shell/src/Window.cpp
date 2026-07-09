#include "bos/Window.h"

namespace bos::shell {

Window::Window(int id, const QString &title, int width, int height, int x, int y, bool visible)
    : m_id(id)
    , m_title(title)
    , m_width(width)
    , m_height(height)
    , m_x(x)
    , m_y(y)
    , m_visible(visible)
    , m_active(false)
{
}

int Window::id() const { return m_id; }
QString Window::title() const { return m_title; }
int Window::width() const { return m_width; }
int Window::height() const { return m_height; }
int Window::x() const { return m_x; }
int Window::y() const { return m_y; }
bool Window::isVisible() const { return m_visible; }
bool Window::isActive() const { return m_active; }

void Window::setTitle(const QString &title) { m_title = title; }
void Window::setWidth(int width) { m_width = width; }
void Window::setHeight(int height) { m_height = height; }
void Window::setX(int x) { m_x = x; }
void Window::setY(int y) { m_y = y; }
void Window::setVisible(bool visible) { m_visible = visible; }
void Window::setActive(bool active) { m_active = active; }

} // namespace bos::shell
