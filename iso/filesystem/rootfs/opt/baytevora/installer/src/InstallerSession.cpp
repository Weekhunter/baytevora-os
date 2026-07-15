#include "boi/InstallerSession.h"
#include "boi/InstallationSummary.h"

namespace boi {

InstallerSession::InstallerSession(QObject *parent)
    : QObject(parent)
{
}

int InstallerSession::currentPage() const { return m_currentPage; }
void InstallerSession::setCurrentPage(int page)
{
    if (page < 0 || page >= totalPages() || m_currentPage == page) return;
    m_currentPage = page;
    emit currentPageChanged();
    emit canGoNextChanged();
    emit canGoBackChanged();
    emit pageTitleChanged();
}

bool InstallerSession::canGoNext() const
{
    if (m_currentPage >= totalPages() - 1) return false;
    return validateCurrentPage(nullptr);
}

bool InstallerSession::canGoBack() const
{
    return m_currentPage > 0 && m_currentPage < 7;
}

QString InstallerSession::pageTitle() const
{
    static const QStringList titles = {
        QStringLiteral("Welcome"),
        QStringLiteral("Language"),
        QStringLiteral("Keyboard"),
        QStringLiteral("License Agreement"),
        QStringLiteral("Installation Type"),
        QStringLiteral("Disk Selection"),
        QStringLiteral("Summary"),
        QStringLiteral("Installing"),
        QStringLiteral("Complete")
    };
    return titles.value(m_currentPage);
}

QString InstallerSession::selectedLanguage() const { return m_selectedLanguage; }
void InstallerSession::setSelectedLanguage(const QString &value)
{
    if (m_selectedLanguage == value) return;
    m_selectedLanguage = value;
    emit selectedLanguageChanged();
    emit canGoNextChanged();
}

QString InstallerSession::selectedKeyboard() const { return m_selectedKeyboard; }
void InstallerSession::setSelectedKeyboard(const QString &value)
{
    if (m_selectedKeyboard == value) return;
    m_selectedKeyboard = value;
    emit selectedKeyboardChanged();
    emit canGoNextChanged();
}

bool InstallerSession::licenseAccepted() const { return m_licenseAccepted; }
void InstallerSession::setLicenseAccepted(bool value)
{
    if (m_licenseAccepted == value) return;
    m_licenseAccepted = value;
    emit licenseAcceptedChanged();
    emit canGoNextChanged();
}

QString InstallerSession::installationType() const { return m_installationType; }
void InstallerSession::setInstallationType(const QString &value)
{
    if (m_installationType == value) return;
    m_installationType = value;
    emit installationTypeChanged();
    emit canGoNextChanged();
}

QString InstallerSession::selectedDiskId() const { return m_selectedDiskId; }
void InstallerSession::setSelectedDiskId(const QString &value)
{
    if (m_selectedDiskId == value) return;
    m_selectedDiskId = value;
    emit selectedDiskIdChanged();
    emit canGoNextChanged();
}

bool InstallerSession::validateCurrentPage(QString *errorMessage) const
{
    switch (m_currentPage) {
    case 0:
        return true;
    case 1:
        if (m_selectedLanguage.isEmpty()) {
            if (errorMessage) *errorMessage = QStringLiteral("Please select a language.");
            return false;
        }
        return true;
    case 2:
        if (m_selectedKeyboard.isEmpty()) {
            if (errorMessage) *errorMessage = QStringLiteral("Please select a keyboard layout.");
            return false;
        }
        return true;
    case 3:
        if (!m_licenseAccepted) {
            if (errorMessage) *errorMessage = QStringLiteral("You must accept the license agreement to continue.");
            return false;
        }
        return true;
    case 4:
        if (m_installationType.isEmpty()) {
            if (errorMessage) *errorMessage = QStringLiteral("Please select an installation type.");
            return false;
        }
        return true;
    case 5:
        if (m_selectedDiskId.isEmpty()) {
            if (errorMessage) *errorMessage = QStringLiteral("Please select a target disk.");
            return false;
        }
        return true;
    case 6:
    case 7:
    case 8:
        return true;
    }
    return true;
}

void InstallerSession::nextPage()
{
    if (m_currentPage < totalPages() - 1) {
        setCurrentPage(m_currentPage + 1);
    }
}

void InstallerSession::previousPage()
{
    if (m_currentPage > 0) {
        setCurrentPage(m_currentPage - 1);
    }
}

void InstallerSession::reset()
{
    m_selectedLanguage = QStringLiteral("English");
    m_selectedKeyboard = QStringLiteral("US");
    m_licenseAccepted = false;
    m_installationType = QStringLiteral("Install Baytevora OS");
    m_selectedDiskId.clear();
    setCurrentPage(0);
}

InstallationSummary *InstallerSession::buildSummary() const
{
    auto *summary = new InstallationSummary(const_cast<InstallerSession*>(this));
    summary->setTargetDisk(m_selectedDiskId);
    summary->setInstallationType(m_installationType);
    summary->setLanguage(m_selectedLanguage);
    summary->setKeyboard(m_selectedKeyboard);
    summary->setRequiredSpace(QStringLiteral("20 GB"));
    summary->setDiskCapacity(QStringLiteral("Unknown"));
    return summary;
}

} // namespace boi
