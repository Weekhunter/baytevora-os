#pragma once

#include <QDate>
#include <QObject>
#include <QString>
#include <QTime>
#include <QVariantMap>

class QTimer;

namespace bos::shell {

class SettingsPersistence;
class UserManager;

/**
 * @brief Drives the Baytevora OS first-boot wizard and setup process.
 *
 * FirstBootManager owns the wizard state, validates each page, executes the
 * setup stages, and persists the resulting configuration. A single instance is
 * exposed to QML as a context property.
 */
class FirstBootManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int totalPages READ totalPages CONSTANT)
    Q_PROPERTY(bool canGoNext READ canGoNext NOTIFY canGoNextChanged)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

    Q_PROPERTY(QString region READ region WRITE setRegion NOTIFY regionChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString keyboardLayout READ keyboardLayout WRITE setKeyboardLayout NOTIFY keyboardLayoutChanged)
    Q_PROPERTY(QString timeZone READ timeZone WRITE setTimeZone NOTIFY timeZoneChanged)
    Q_PROPERTY(bool autoDateTime READ autoDateTime WRITE setAutoDateTime NOTIFY autoDateTimeChanged)
    Q_PROPERTY(QDate manualDate READ manualDate WRITE setManualDate NOTIFY manualDateChanged)
    Q_PROPERTY(QTime manualTime READ manualTime WRITE setManualTime NOTIFY manualTimeChanged)
    Q_PROPERTY(bool use24HourFormat READ use24HourFormat WRITE setUse24HourFormat NOTIFY use24HourFormatChanged)

    Q_PROPERTY(bool usageAnalytics READ usageAnalytics WRITE setUsageAnalytics NOTIFY usageAnalyticsChanged)
    Q_PROPERTY(bool crashReports READ crashReports WRITE setCrashReports NOTIFY crashReportsChanged)
    Q_PROPERTY(bool personalization READ personalization WRITE setPersonalization NOTIFY personalizationChanged)
    Q_PROPERTY(bool locationServices READ locationServices WRITE setLocationServices NOTIFY locationServicesChanged)

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString userLogin READ userLogin WRITE setUserLogin NOTIFY userLoginChanged)
    Q_PROPERTY(QString userPassword READ userPassword WRITE setUserPassword NOTIFY userPasswordChanged)
    Q_PROPERTY(QString userConfirmPassword READ userConfirmPassword WRITE setUserConfirmPassword NOTIFY userConfirmPasswordChanged)
    Q_PROPERTY(QString userAvatar READ userAvatar WRITE setUserAvatar NOTIFY userAvatarChanged)
    Q_PROPERTY(bool isAdministrator READ isAdministrator WRITE setIsAdministrator NOTIFY isAdministratorChanged)

    Q_PROPERTY(QString computerName READ computerName WRITE setComputerName NOTIFY computerNameChanged)

    Q_PROPERTY(int setupProgress READ setupProgress NOTIFY setupProgressChanged)
    Q_PROPERTY(QString setupStage READ setupStage NOTIFY setupStageChanged)

public:
    explicit FirstBootManager(SettingsPersistence *persistence,
                              UserManager *userManager,
                              QObject *parent = nullptr);

    int currentPage() const;
    int totalPages() const;
    bool canGoNext() const;
    bool canGoBack() const;
    QString errorMessage() const;

    QString region() const;
    QString language() const;
    QString keyboardLayout() const;
    QString timeZone() const;
    bool autoDateTime() const;
    QDate manualDate() const;
    QTime manualTime() const;
    bool use24HourFormat() const;

    bool usageAnalytics() const;
    bool crashReports() const;
    bool personalization() const;
    bool locationServices() const;

    QString userName() const;
    QString userLogin() const;
    QString userPassword() const;
    QString userAvatar() const;
    bool isAdministrator() const;

    QString computerName() const;

    int setupProgress() const;
    QString setupStage() const;

public slots:
    void setCurrentPage(int page);
    void setRegion(const QString &region);
    void setLanguage(const QString &language);
    void setKeyboardLayout(const QString &keyboardLayout);
    void setTimeZone(const QString &timeZone);
    void setAutoDateTime(bool enabled);
    void setManualDate(const QDate &date);
    void setManualTime(const QTime &time);
    void setUse24HourFormat(bool enabled);

    void setUsageAnalytics(bool enabled);
    void setCrashReports(bool enabled);
    void setPersonalization(bool enabled);
    void setLocationServices(bool enabled);

    void setUserName(const QString &name);
    void setUserLogin(const QString &login);
    void setUserPassword(const QString &password);
    void setUserConfirmPassword(const QString &password);
    void setUserAvatar(const QString &avatar);
    void setIsAdministrator(bool enabled);

    void setComputerName(const QString &name);

    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void previousPage();
    Q_INVOKABLE void goToPage(int page);
    Q_INVOKABLE bool validateCurrentPage();
    Q_INVOKABLE void startSetup();
    Q_INVOKABLE void completeSetup();
    Q_INVOKABLE QString passwordStrength(const QString &password) const;

    QVariantMap buildSettings() const;

signals:
    void currentPageChanged();
    void canGoNextChanged();
    void canGoBackChanged();
    void errorMessageChanged();

    void regionChanged();
    void languageChanged();
    void keyboardLayoutChanged();
    void timeZoneChanged();
    void autoDateTimeChanged();
    void manualDateChanged();
    void manualTimeChanged();
    void use24HourFormatChanged();

    void usageAnalyticsChanged();
    void crashReportsChanged();
    void personalizationChanged();
    void locationServicesChanged();

    void userNameChanged();
    void userLoginChanged();
    void userPasswordChanged();
    void userConfirmPasswordChanged();
    void userAvatarChanged();
    void isAdministratorChanged();

    void computerNameChanged();

    void setupProgressChanged();
    void setupStageChanged();
    void setupCompleted();
    void setupFailed(const QString &reason);

private:
    void setErrorMessage(const QString &message);
    bool validatePage(int page) const;
    QString passwordStrengthLabel(const QString &password) const;

    void runSetupStage();

    static constexpr int kTotalPages = 12;

    SettingsPersistence *m_persistence = nullptr;
    UserManager *m_userManager = nullptr;

    int m_currentPage = 0;
    QString m_errorMessage;

    QString m_region;
    QString m_language = QStringLiteral("English");
    QString m_keyboardLayout = QStringLiteral("US");
    QString m_timeZone;
    bool m_autoDateTime = true;
    QDate m_manualDate;
    QTime m_manualTime;
    bool m_use24HourFormat = false;

    bool m_usageAnalytics = false;
    bool m_crashReports = false;
    bool m_personalization = false;
    bool m_locationServices = false;

    QString m_userName;
    QString m_userLogin;
    QString m_userPassword;
    QString m_userConfirmPassword;
    QString m_userAvatar;
    bool m_isAdministrator = true;

    QString m_computerName = QStringLiteral("BAYTEVORA-PC");

    int m_setupProgress = 0;
    QString m_setupStage;
    int m_setupStageIndex = -1;
    QStringList m_setupStages;
    QTimer *m_setupTimer = nullptr;
};

} // namespace bos::shell
