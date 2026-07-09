#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <memory>
#include <vector>

#include "bos/DesktopModule.h"

namespace bos::shell {

class Window;

/**
 * @brief Manages desktop windows for the Baytevora Desktop Environment.
 *
 * WindowManager is both a DesktopModule (so it is owned and driven by
 * ModuleManager) and a QObject (so it can expose window state to QML).
 *
 * In Sprint 5 it only registers, removes, and enumerates windows. A single
 * demonstration window is created automatically when the session starts.
 */
class WindowManager : public QObject, public DesktopModule {
    Q_OBJECT

    /**
     * @brief List of active windows exposed to QML.
     */
    Q_PROPERTY(QVariantList windows READ windows NOTIFY windowsChanged)

    /**
     * @brief ID of the currently active window exposed to QML.
     */
    Q_PROPERTY(int activeWindowId READ activeWindowId NOTIFY activeWindowIdChanged)

public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager() override;

    // DesktopModule interface
    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    /**
     * @brief Creates and registers a new window with a unique ID.
     * @return The assigned window ID.
     */
    Q_INVOKABLE int registerWindow(const QString &title, int width, int height, int x, int y);

    /**
     * @brief Removes the window with the given ID.
     */
    Q_INVOKABLE void unregisterWindow(int id);

    /**
     * @return A list of all currently registered windows as QVariantMap items.
     */
    QVariantList windows() const;

    /**
     * @brief Finds a window by ID.
     * @return A QVariantMap with the window data, or an empty map if not found.
     */
    Q_INVOKABLE QVariantMap findWindow(int id) const;

    /**
     * @brief Returns the currently active window as a QVariantMap.
     * @return Window data, or an empty map if no window is active.
     */
    Q_INVOKABLE QVariantMap activeWindow() const;

    /**
     * @return The ID of the currently active window, or -1 if none is active.
     */
    int activeWindowId() const;

public slots:
    /**
     * @brief Sets the window with the given ID as the active window.
     *
     * The previously active window becomes inactive, and the active window is
     * brought to the front. If the ID does not correspond to a registered
     * window, the request is ignored and a warning is logged.
     */
    void setActiveWindow(int id);

signals:
    void windowsChanged();
    void activeWindowIdChanged();

private:
    QVariantMap windowToMap(const Window &window) const;
    Window *findWindowObject(int id) const;

    int m_nextId = 1;
    int m_activeWindowId = -1;
    std::vector<std::unique_ptr<Window>> m_windows;
};

} // namespace bos::shell
