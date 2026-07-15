#pragma once

#include <QString>

namespace bos::shell {

/**
 * @brief Possible states of a desktop window.
 */
enum class WindowState {
    Normal,
    Minimized,
    Maximized,
    Closed
};

/**
 * @brief Lightweight data model representing a desktop window.
 *
 * Window holds the basic state of a window: a unique identifier, title,
 * geometry, visibility, focus, and window state. It intentionally contains no
 * behavior beyond simple accessors so that the WindowManager owns and controls
 * the lifecycle.
 */
class Window {
public:
    Window(int id,
           const QString &title,
           int width,
           int height,
           int x,
           int y,
           const QString &applicationName = QString(),
           bool visible = true);

    int id() const;
    QString title() const;
    int width() const;
    int height() const;
    int x() const;
    int y() const;
    QString applicationName() const;
    bool isVisible() const;
    bool isActive() const;
    WindowState state() const;

    int normalX() const;
    int normalY() const;
    int normalWidth() const;
    int normalHeight() const;

    void setTitle(const QString &title);
    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setY(int y);
    void setApplicationName(const QString &applicationName);
    void setVisible(bool visible);
    void setActive(bool active);
    void setState(WindowState state);

    void saveNormalGeometry();
    void restoreNormalGeometry();

private:
    int m_id;
    QString m_title;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
    QString m_applicationName;
    bool m_visible;
    bool m_active;
    WindowState m_state;

    int m_normalX;
    int m_normalY;
    int m_normalWidth;
    int m_normalHeight;
};

} // namespace bos::shell
