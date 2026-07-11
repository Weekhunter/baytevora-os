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
    Q_INVOKABLE int registerWindow(const QString &title,
                                  int width,
                                  int height,
                                  int x,
                                  int y,
                                  const QString &applicationName = QString());

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

    /**
     * @brief Creates a demonstration application window with the given title.
     *
     * The window is centered on the primary screen, registered with the
     * manager, and set as the active window. Sprint 10 uses this method so
     * ApplicationManager can request windows without manipulating them directly.
     * @return The new window ID, or -1 if creation failed.
     */
    Q_INVOKABLE int createApplicationWindow(const QString &title);

    /**
     * @brief Sets the window state to Minimized.
     */
    void minimizeWindow(int id);

    /**
     * @brief Sets the window state to Maximized and fills the desktop area.
     */
    void maximizeWindow(int id);

    /**
     * @brief Restores the window to its Normal state and previous geometry.
     */
    void restoreWindow(int id);

    /**
     * @brief Sets the window state to Closed and removes it from the manager.
     */
    void closeWindow(int id);

    /**
     * @brief Handles a taskbar button click for the given window.
     *
     * Restores the window if it is minimized, focuses it if it is inactive,
     * and does nothing if it is already active. This keeps taskbar interaction
     * logic in C++.
     */
    void taskbarButtonClicked(int id);

signals:
    void windowsChanged();
    void activeWindowIdChanged();

    /**
     * @brief Emitted when a window has been closed and removed.
     */
    void windowClosed(int id);

private:
    QVariantMap windowToMap(const Window &window) const;
    Window *findWindowObject(int id) const;
    void pickNewActiveWindow();
    QString stateToString(WindowState state) const;

    int m_nextId = 1;
    int m_activeWindowId = -1;
    std::vector<std::unique_ptr<Window>> m_windows;
};

} // namespace bos::shell
