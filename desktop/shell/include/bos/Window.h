#pragma once

#include <QString>

namespace bos::shell {

/**
 * @brief Lightweight data model representing a desktop window.
 *
 * Window holds the basic state of a window: a unique identifier, title,
 * geometry, and visibility. It intentionally contains no behavior beyond simple
 * accessors so that the WindowManager owns and controls the lifecycle.
 */
class Window {
public:
    Window(int id, const QString &title, int width, int height, int x, int y, bool visible = true);

    int id() const;
    QString title() const;
    int width() const;
    int height() const;
    int x() const;
    int y() const;
    bool isVisible() const;
    bool isActive() const;

    void setTitle(const QString &title);
    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setY(int y);
    void setVisible(bool visible);
    void setActive(bool active);

private:
    int m_id;
    QString m_title;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
    bool m_visible;
    bool m_active;
};

} // namespace bos::shell
