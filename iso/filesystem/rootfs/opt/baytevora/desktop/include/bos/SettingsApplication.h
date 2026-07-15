#pragma once

#include <QObject>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Settings application for Baytevora OS.
 *
 * SettingsApplication requests a managed window from WindowManager and emits a
 * startup notification. All page content and configuration logic is provided by
 * SettingsManager and displayed by QML.
 */
class SettingsApplication : public QObject {
    Q_OBJECT

public:
    explicit SettingsApplication(QObject *parent = nullptr);
    ~SettingsApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();

    /**
     * @brief Opens the Settings window and requests the given page.
     *
     * The requested page is exposed through the pendingPage property so the
     * QML Settings window can set currentPage on startup.
     */
    Q_INVOKABLE int openPage(const QString &pageId);

    /**
     * @brief The page requested by the last openPage() call.
     *
     * The QML Settings window reads and clears this property on completion.
     */
    Q_PROPERTY(QString pendingPage READ pendingPage WRITE setPendingPage NOTIFY pendingPageChanged)

    QString pendingPage() const;
    void setPendingPage(const QString &pageId);

signals:
    void pendingPageChanged();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QString m_pendingPage;
};

} // namespace bos::shell
