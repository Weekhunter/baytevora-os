#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single browser bookmark.
 */
class BrowserBookmark : public QObject {
    Q_OBJECT

    Q_PROPERTY(int bookmarkId READ bookmarkId NOTIFY bookmarkIdChanged FINAL)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged FINAL)
    Q_PROPERTY(QString folder READ folder NOTIFY folderChanged FINAL)
    Q_PROPERTY(QDateTime createdAt READ createdAt NOTIFY createdAtChanged FINAL)
    Q_PROPERTY(QDateTime lastVisited READ lastVisited NOTIFY lastVisitedChanged FINAL)

public:
    explicit BrowserBookmark(int bookmarkId, QObject *parent = nullptr);
    ~BrowserBookmark() override;

    int bookmarkId() const;
    QString title() const;
    QString url() const;
    QString folder() const;
    QDateTime createdAt() const;
    QDateTime lastVisited() const;

    void setTitle(const QString &title);
    void setUrl(const QString &url);
    void setFolder(const QString &folder);
    void setCreatedAt(const QDateTime &createdAt);
    void setLastVisited(const QDateTime &lastVisited);

signals:
    void bookmarkIdChanged();
    void titleChanged();
    void urlChanged();
    void folderChanged();
    void createdAtChanged();
    void lastVisitedChanged();

private:
    int m_bookmarkId = -1;
    QString m_title;
    QString m_url;
    QString m_folder;
    QDateTime m_createdAt;
    QDateTime m_lastVisited;
};

} // namespace bos::shell
