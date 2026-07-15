#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single browser page state.
 *
 * BrowserPage stores the current URL, page title, and loading state. It is
 * owned by a BrowserManager and exposed to QML through the manager's
 * properties.
 */
class BrowserPage : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString currentUrl READ currentUrl WRITE setCurrentUrl NOTIFY currentUrlChanged FINAL)
    Q_PROPERTY(QString pageTitle READ pageTitle NOTIFY pageTitleChanged FINAL)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged FINAL)

public:
    explicit BrowserPage(QObject *parent = nullptr);
    ~BrowserPage() override;

    QString currentUrl() const;
    void setCurrentUrl(const QString &url);

    QString pageTitle() const;
    void setPageTitle(const QString &title);

    bool loading() const;
    void setLoading(bool loading);

signals:
    void currentUrlChanged();
    void pageTitleChanged();
    void loadingChanged();

private:
    QString m_currentUrl;
    QString m_pageTitle;
    bool m_loading = false;
};

} // namespace bos::shell
