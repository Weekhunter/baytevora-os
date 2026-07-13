#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single browser history entry.
 */
class BrowserHistoryEntry : public QObject {
    Q_OBJECT

    Q_PROPERTY(int historyId READ historyId NOTIFY historyIdChanged FINAL)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged FINAL)
    Q_PROPERTY(QDateTime visitTime READ visitTime NOTIFY visitTimeChanged FINAL)
    Q_PROPERTY(int visitCount READ visitCount NOTIFY visitCountChanged FINAL)

public:
    explicit BrowserHistoryEntry(int historyId, QObject *parent = nullptr);
    ~BrowserHistoryEntry() override;

    int historyId() const;
    QString title() const;
    QString url() const;
    QDateTime visitTime() const;
    int visitCount() const;

    void setTitle(const QString &title);
    void setUrl(const QString &url);
    void setVisitTime(const QDateTime &visitTime);
    void setVisitCount(int visitCount);

    void incrementVisitCount();

signals:
    void historyIdChanged();
    void titleChanged();
    void urlChanged();
    void visitTimeChanged();
    void visitCountChanged();

private:
    int m_historyId = -1;
    QString m_title;
    QString m_url;
    QDateTime m_visitTime;
    int m_visitCount = 1;
};

} // namespace bos::shell
