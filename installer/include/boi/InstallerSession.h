#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

namespace boi {

class InstallationSummary;

/**
 * @brief Holds the user's choices and wizard navigation state.
 *
 * InstallerSession is exposed to QML as a context object. It validates the
 * current page and decides whether the user may move forward or backward.
 */
class InstallerSession : public QObject {
    Q_OBJECT

    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged FINAL)
    Q_PROPERTY(int totalPages READ totalPages CONSTANT FINAL)
    Q_PROPERTY(bool canGoNext READ canGoNext NOTIFY canGoNextChanged FINAL)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged FINAL)
    Q_PROPERTY(QString pageTitle READ pageTitle NOTIFY pageTitleChanged FINAL)

    Q_PROPERTY(QString selectedLanguage READ selectedLanguage WRITE setSelectedLanguage NOTIFY selectedLanguageChanged FINAL)
    Q_PROPERTY(QString selectedKeyboard READ selectedKeyboard WRITE setSelectedKeyboard NOTIFY selectedKeyboardChanged FINAL)
    Q_PROPERTY(bool licenseAccepted READ licenseAccepted WRITE setLicenseAccepted NOTIFY licenseAcceptedChanged FINAL)
    Q_PROPERTY(QString installationType READ installationType WRITE setInstallationType NOTIFY installationTypeChanged FINAL)
    Q_PROPERTY(QString selectedDiskId READ selectedDiskId WRITE setSelectedDiskId NOTIFY selectedDiskIdChanged FINAL)

    Q_PROPERTY(QStringList languages READ languages CONSTANT FINAL)
    Q_PROPERTY(QStringList keyboards READ keyboards CONSTANT FINAL)
    Q_PROPERTY(QStringList installationTypes READ installationTypes CONSTANT FINAL)

public:
    explicit InstallerSession(QObject *parent = nullptr);

    int currentPage() const;
    void setCurrentPage(int page);

    int totalPages() const { return 9; }

    bool canGoNext() const;
    bool canGoBack() const;

    QString pageTitle() const;

    QString selectedLanguage() const;
    void setSelectedLanguage(const QString &value);

    QString selectedKeyboard() const;
    void setSelectedKeyboard(const QString &value);

    bool licenseAccepted() const;
    void setLicenseAccepted(bool value);

    QString installationType() const;
    void setInstallationType(const QString &value);

    QString selectedDiskId() const;
    void setSelectedDiskId(const QString &value);

    QStringList languages() const { return m_languages; }
    QStringList keyboards() const { return m_keyboards; }
    QStringList installationTypes() const { return m_installationTypes; }

    Q_INVOKABLE bool validateCurrentPage(QString *errorMessage = nullptr) const;
    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void previousPage();
    Q_INVOKABLE void reset();

    InstallationSummary *buildSummary() const;

signals:
    void currentPageChanged();
    void canGoNextChanged();
    void canGoBackChanged();
    void pageTitleChanged();
    void selectedLanguageChanged();
    void selectedKeyboardChanged();
    void licenseAcceptedChanged();
    void installationTypeChanged();
    void selectedDiskIdChanged();

private:
    int m_currentPage = 0;

    QString m_selectedLanguage = QStringLiteral("English");
    QString m_selectedKeyboard = QStringLiteral("US");
    bool m_licenseAccepted = false;
    QString m_installationType = QStringLiteral("Install Baytevora OS");
    QString m_selectedDiskId;

    const QStringList m_languages = {
        QStringLiteral("English"),
        QStringLiteral("Spanish"),
        QStringLiteral("French"),
        QStringLiteral("German"),
        QStringLiteral("Portuguese"),
        QStringLiteral("Russian"),
        QStringLiteral("Japanese"),
        QStringLiteral("Simplified Chinese")
    };

    const QStringList m_keyboards = {
        QStringLiteral("US"),
        QStringLiteral("UK"),
        QStringLiteral("German"),
        QStringLiteral("French"),
        QStringLiteral("Spanish"),
        QStringLiteral("Portuguese"),
        QStringLiteral("Russian"),
        QStringLiteral("Japanese"),
        QStringLiteral("Simplified Chinese")
    };

    const QStringList m_installationTypes = {
        QStringLiteral("Install Baytevora OS"),
        QStringLiteral("Replace Existing System"),
        QStringLiteral("Manual Partitioning")
    };
};

} // namespace boi
