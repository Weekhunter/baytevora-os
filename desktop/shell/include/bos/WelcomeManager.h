#pragma once

#include <QObject>

namespace bos::shell {

class SettingsPersistence;

/**
 * @brief Tracks whether the Welcome Center should be shown after login.
 *
 * WelcomeManager reads the persisted first-boot configuration and exposes the
 * first-login state and hide-on-next-startup flag to QML. It emits a signal
 * when the shell should open the Welcome Center window.
 */
class WelcomeManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isFirstLogin READ isFirstLogin NOTIFY isFirstLoginChanged)
    Q_PROPERTY(bool welcomeCenterVisible READ welcomeCenterVisible WRITE setWelcomeCenterVisible NOTIFY welcomeCenterVisibleChanged)
    Q_PROPERTY(bool hideOnNextStartup READ hideOnNextStartup WRITE setHideOnNextStartup NOTIFY hideOnNextStartupChanged)

public:
    explicit WelcomeManager(SettingsPersistence *persistence, QObject *parent = nullptr);

    bool isFirstLogin() const;
    bool welcomeCenterVisible() const;
    bool hideOnNextStartup() const;

public slots:
    void setWelcomeCenterVisible(bool visible);
    void setHideOnNextStartup(bool hide);
    void setIsFirstLogin(bool firstLogin);

    Q_INVOKABLE void requestOpenWelcomeCenter();
    Q_INVOKABLE void closeWelcomeCenter();
    Q_INVOKABLE void markFirstLoginHandled();
    Q_INVOKABLE bool shouldOpenOnLogin() const;

    bool save();

signals:
    void isFirstLoginChanged();
    void welcomeCenterVisibleChanged();
    void hideOnNextStartupChanged();
    void openWelcomeCenterRequested();
    void closeWelcomeCenterRequested();

private:
    void load();

    SettingsPersistence *m_persistence = nullptr;
    bool m_isFirstLogin = true;
    bool m_welcomeCenterVisible = false;
    bool m_hideOnNextStartup = false;
};

} // namespace bos::shell
