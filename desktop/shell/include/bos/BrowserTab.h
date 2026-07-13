#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents the state of a single browser tab.
 */
class BrowserTab : public QObject {
    Q_OBJECT

    Q_PROPERTY(int tabId READ tabId NOTIFY tabIdChanged FINAL)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged FINAL)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged FINAL)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged FINAL)
    Q_PROPERTY(bool canGoForward READ canGoForward NOTIFY canGoForwardChanged FINAL)

public:
    explicit BrowserTab(int tabId, QObject *parent = nullptr);
    ~BrowserTab() override;

    int tabId() const;
    QString title() const;
    QString url() const;
    bool loading() const;
    bool canGoBack() const;
    bool canGoForward() const;

    void setTitle(const QString &title);
    void setUrl(const QString &url);
    void setLoading(bool loading);
    void setCanGoBack(bool canGoBack);
    void setCanGoForward(bool canGoForward);

signals:
    void tabIdChanged();
    void titleChanged();
    void urlChanged();
    void loadingChanged();
    void canGoBackChanged();
    void canGoForwardChanged();

private:
    int m_tabId = -1;
    QString m_title;
    QString m_url;
    bool m_loading = false;
    bool m_canGoBack = false;
    bool m_canGoForward = false;
};

} // namespace bos::shell
