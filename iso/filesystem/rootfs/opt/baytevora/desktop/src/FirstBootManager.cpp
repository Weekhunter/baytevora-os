#include "bos/FirstBootManager.h"

#include <QRegularExpression>
#include <QTimer>

#include "bos/SettingsPersistence.h"
#include "bos/UserManager.h"

namespace bos::shell {

FirstBootManager::FirstBootManager(SettingsPersistence *persistence,
                                   UserManager *userManager,
                                   QObject *parent)
    : QObject(parent)
    , m_persistence(persistence)
    , m_userManager(userManager)
    , m_manualDate(QDate::currentDate())
    , m_manualTime(QTime::currentTime())
{
    m_setupStages = {
        QStringLiteral("Preparing desktop..."),
        QStringLiteral("Creating user..."),
        QStringLiteral("Applying settings..."),
        QStringLiteral("Configuring system..."),
        QStringLiteral("Almost ready...")
    };

    m_setupTimer = new QTimer(this);
    m_setupTimer->setSingleShot(true);
    connect(m_setupTimer, &QTimer::timeout, this, &FirstBootManager::runSetupStage);
}

int FirstBootManager::currentPage() const { return m_currentPage; }
int FirstBootManager::totalPages() const { return kTotalPages; }

void FirstBootManager::setCurrentPage(int page)
{
    if (page < 0 || page >= kTotalPages || m_currentPage == page) {
        return;
    }
    m_currentPage = page;
    setErrorMessage(QString());
    emit currentPageChanged();
    emit canGoNextChanged();
    emit canGoBackChanged();
}

bool FirstBootManager::canGoNext() const
{
    return m_currentPage < kTotalPages - 1;
}

bool FirstBootManager::canGoBack() const
{
    return m_currentPage > 0 && m_currentPage < kTotalPages - 1;
}

QString FirstBootManager::errorMessage() const { return m_errorMessage; }

void FirstBootManager::setErrorMessage(const QString &message)
{
    if (m_errorMessage == message) {
        return;
    }
    m_errorMessage = message;
    emit errorMessageChanged();
}

QString FirstBootManager::region() const { return m_region; }
void FirstBootManager::setRegion(const QString &region)
{
    if (m_region == region) return;
    m_region = region;
    emit regionChanged();
    if (m_currentPage == 1) emit canGoNextChanged();
}

QString FirstBootManager::language() const { return m_language; }
void FirstBootManager::setLanguage(const QString &language)
{
    if (m_language == language) return;
    m_language = language;
    emit languageChanged();
    if (m_currentPage == 2) emit canGoNextChanged();
}

QString FirstBootManager::keyboardLayout() const { return m_keyboardLayout; }
void FirstBootManager::setKeyboardLayout(const QString &keyboardLayout)
{
    if (m_keyboardLayout == keyboardLayout) return;
    m_keyboardLayout = keyboardLayout;
    emit keyboardLayoutChanged();
}

QString FirstBootManager::timeZone() const { return m_timeZone; }
void FirstBootManager::setTimeZone(const QString &timeZone)
{
    if (m_timeZone == timeZone) return;
    m_timeZone = timeZone;
    emit timeZoneChanged();
    if (m_currentPage == 4) emit canGoNextChanged();
}

bool FirstBootManager::autoDateTime() const { return m_autoDateTime; }
void FirstBootManager::setAutoDateTime(bool enabled)
{
    if (m_autoDateTime == enabled) return;
    m_autoDateTime = enabled;
    emit autoDateTimeChanged();
}

QDate FirstBootManager::manualDate() const { return m_manualDate; }
void FirstBootManager::setManualDate(const QDate &date)
{
    if (m_manualDate == date) return;
    m_manualDate = date;
    emit manualDateChanged();
}

QTime FirstBootManager::manualTime() const { return m_manualTime; }
void FirstBootManager::setManualTime(const QTime &time)
{
    if (m_manualTime == time) return;
    m_manualTime = time;
    emit manualTimeChanged();
}

bool FirstBootManager::use24HourFormat() const { return m_use24HourFormat; }
void FirstBootManager::setUse24HourFormat(bool enabled)
{
    if (m_use24HourFormat == enabled) return;
    m_use24HourFormat = enabled;
    emit use24HourFormatChanged();
}

bool FirstBootManager::usageAnalytics() const { return m_usageAnalytics; }
void FirstBootManager::setUsageAnalytics(bool enabled)
{
    if (m_usageAnalytics == enabled) return;
    m_usageAnalytics = enabled;
    emit usageAnalyticsChanged();
}

bool FirstBootManager::crashReports() const { return m_crashReports; }
void FirstBootManager::setCrashReports(bool enabled)
{
    if (m_crashReports == enabled) return;
    m_crashReports = enabled;
    emit crashReportsChanged();
}

bool FirstBootManager::personalization() const { return m_personalization; }
void FirstBootManager::setPersonalization(bool enabled)
{
    if (m_personalization == enabled) return;
    m_personalization = enabled;
    emit personalizationChanged();
}

bool FirstBootManager::locationServices() const { return m_locationServices; }
void FirstBootManager::setLocationServices(bool enabled)
{
    if (m_locationServices == enabled) return;
    m_locationServices = enabled;
    emit locationServicesChanged();
}

QString FirstBootManager::userName() const { return m_userName; }
void FirstBootManager::setUserName(const QString &name)
{
    if (m_userName == name) return;
    m_userName = name;
    emit userNameChanged();
    if (m_currentPage == 7) emit canGoNextChanged();
}

QString FirstBootManager::userLogin() const { return m_userLogin; }
void FirstBootManager::setUserLogin(const QString &login)
{
    if (m_userLogin == login) return;
    m_userLogin = login;
    emit userLoginChanged();
    if (m_currentPage == 7) emit canGoNextChanged();
}

QString FirstBootManager::userPassword() const { return m_userPassword; }
void FirstBootManager::setUserPassword(const QString &password)
{
    if (m_userPassword == password) return;
    m_userPassword = password;
    emit userPasswordChanged();
    if (m_currentPage == 7) emit canGoNextChanged();
}

QString FirstBootManager::userConfirmPassword() const { return m_userConfirmPassword; }
void FirstBootManager::setUserConfirmPassword(const QString &password)
{
    if (m_userConfirmPassword == password) return;
    m_userConfirmPassword = password;
    emit userConfirmPasswordChanged();
}

QString FirstBootManager::userAvatar() const { return m_userAvatar; }
void FirstBootManager::setUserAvatar(const QString &avatar)
{
    if (m_userAvatar == avatar) return;
    m_userAvatar = avatar;
    emit userAvatarChanged();
}

bool FirstBootManager::isAdministrator() const { return m_isAdministrator; }
void FirstBootManager::setIsAdministrator(bool enabled)
{
    if (m_isAdministrator == enabled) return;
    m_isAdministrator = enabled;
    emit isAdministratorChanged();
}

QString FirstBootManager::computerName() const { return m_computerName; }
void FirstBootManager::setComputerName(const QString &name)
{
    if (m_computerName == name) return;
    m_computerName = name;
    emit computerNameChanged();
    if (m_currentPage == 8) emit canGoNextChanged();
}

int FirstBootManager::setupProgress() const { return m_setupProgress; }
QString FirstBootManager::setupStage() const { return m_setupStage; }

void FirstBootManager::nextPage()
{
    if (!validateCurrentPage()) {
        return;
    }
    if (m_currentPage < kTotalPages - 1) {
        setCurrentPage(m_currentPage + 1);
    }
}

void FirstBootManager::previousPage()
{
    if (m_currentPage > 0) {
        setCurrentPage(m_currentPage - 1);
    }
}

void FirstBootManager::goToPage(int page)
{
    setCurrentPage(page);
}

bool FirstBootManager::validateCurrentPage()
{
    const bool ok = validatePage(m_currentPage);
    if (!ok && m_errorMessage.isEmpty()) {
        setErrorMessage(QStringLiteral("Please complete the required fields."));
    }
    return ok;
}

bool FirstBootManager::validatePage(int page) const
{
    switch (page) {
    case 0: // Welcome
        return true;
    case 1: // Region
        return !m_region.isEmpty();
    case 2: // Language
        return !m_language.isEmpty();
    case 3: // Keyboard
        return !m_keyboardLayout.isEmpty();
    case 4: // Time zone
        return !m_timeZone.isEmpty();
    case 5: // Date/Time
        if (!m_autoDateTime) {
            return m_manualDate.isValid() && m_manualTime.isValid();
        }
        return true;
    case 6: // Privacy
        return true;
    case 7: // User account
        if (m_userName.trimmed().isEmpty()) {
            const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Please enter the user's full name."));
            return false;
        }
        if (m_userLogin.trimmed().isEmpty()) {
            const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Please enter a username."));
            return false;
        }
        {
            static const QRegularExpression loginRe(QStringLiteral("^[a-zA-Z0-9_-]+$"));
            if (!loginRe.match(m_userLogin).hasMatch()) {
                const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Username may only contain letters, numbers, underscores, and hyphens."));
                return false;
            }
        }
        if (m_userPassword.length() < 8) {
            const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Password must be at least 8 characters."));
            return false;
        }
        {
            bool hasUpper = false, hasLower = false, hasDigit = false;
            for (const QChar &c : m_userPassword) {
                if (c.isUpper()) hasUpper = true;
                if (c.isLower()) hasLower = true;
                if (c.isDigit()) hasDigit = true;
            }
            if (!hasUpper || !hasLower || !hasDigit) {
                const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Password must contain uppercase, lowercase, and a digit."));
                return false;
            }
        }
        if (m_userPassword != m_userConfirmPassword) {
            const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Passwords do not match."));
            return false;
        }
        return true;
    case 8: // Computer name
        if (m_computerName.trimmed().isEmpty()) {
            const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Please enter a computer name."));
            return false;
        }
        {
            static const QRegularExpression nameRe(QStringLiteral("^[A-Za-z0-9-]{1,15}$"));
            if (!nameRe.match(m_computerName).hasMatch()) {
                const_cast<FirstBootManager*>(this)->setErrorMessage(QStringLiteral("Computer name must be 1-15 characters and contain only letters, numbers, and hyphens."));
                return false;
            }
        }
        return true;
    case 9:  // Summary
    case 10: // Setup progress
    case 11: // Finish
        return true;
    default:
        return true;
    }
}

QString FirstBootManager::passwordStrengthLabel(const QString &password) const
{
    if (password.length() < 6) {
        return QStringLiteral("Weak");
    }
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;
    for (const QChar &c : password) {
        if (c.isUpper()) hasUpper = true;
        if (c.isLower()) hasLower = true;
        if (c.isDigit()) hasDigit = true;
        if (!c.isLetterOrNumber()) hasSymbol = true;
    }
    const int score = (hasUpper ? 1 : 0) + (hasLower ? 1 : 0) + (hasDigit ? 1 : 0) + (hasSymbol ? 1 : 0);
    if (password.length() >= 10 && score >= 4) {
        return QStringLiteral("Strong");
    }
    if (password.length() >= 8 && score >= 3) {
        return QStringLiteral("Good");
    }
    return QStringLiteral("Weak");
}

void FirstBootManager::startSetup()
{
    m_setupStageIndex = 0;
    m_setupProgress = 0;
    m_setupStage = m_setupStages.value(0);
    emit setupProgressChanged();
    emit setupStageChanged();
    runSetupStage();
}

void FirstBootManager::runSetupStage()
{
    if (m_setupStageIndex < 0 || m_setupStageIndex >= m_setupStages.size()) {
        return;
    }

    m_setupStage = m_setupStages.at(m_setupStageIndex);
    m_setupProgress = static_cast<int>((m_setupStageIndex + 1) * 100.0 / m_setupStages.size());
    emit setupStageChanged();
    emit setupProgressChanged();

    if (m_setupStageIndex == 1) {
        if (m_userManager) {
            m_userManager->createUserFromWizard(m_userName, m_userLogin, m_userPassword,
                                                 m_isAdministrator, m_userAvatar);
        }
    }

    if (m_setupStageIndex + 1 >= m_setupStages.size()) {
        setCurrentPage(kTotalPages - 1); // Finish page
        return;
    }

    ++m_setupStageIndex;
    m_setupTimer->start(150);
}

void FirstBootManager::completeSetup()
{
    if (!m_persistence) {
        emit setupFailed(QStringLiteral("Settings persistence is not available."));
        return;
    }

    QVariantMap settings = buildSettings();
    settings[QStringLiteral("firstBootCompleted")] = true;
    settings[QStringLiteral("firstUserCreated")] = true;

    if (!m_persistence->save(settings)) {
        emit setupFailed(QStringLiteral("Failed to save first-boot configuration."));
        return;
    }

    emit setupCompleted();
}

QString FirstBootManager::passwordStrength(const QString &password) const
{
    return passwordStrengthLabel(password);
}

QVariantMap FirstBootManager::buildSettings() const
{
    QVariantMap settings;
    settings[QStringLiteral("region")] = m_region;
    settings[QStringLiteral("language")] = m_language;
    settings[QStringLiteral("keyboardLayout")] = m_keyboardLayout;
    settings[QStringLiteral("timeZone")] = m_timeZone;
    settings[QStringLiteral("autoDateTime")] = m_autoDateTime;
    settings[QStringLiteral("use24HourFormat")] = m_use24HourFormat;
    settings[QStringLiteral("usageAnalytics")] = m_usageAnalytics;
    settings[QStringLiteral("crashReports")] = m_crashReports;
    settings[QStringLiteral("personalization")] = m_personalization;
    settings[QStringLiteral("locationServices")] = m_locationServices;
    settings[QStringLiteral("computerName")] = m_computerName;
    // The first user's login credentials are intentionally not persisted here; the
    // account is created by UserManager during setup. Only the firstUserCreated
    // flag (set in completeSetup) is stored.
    return settings;
}

} // namespace bos::shell
