#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single plain-text clipboard entry.
 *
 * ClipboardItem holds the metadata for one clipboard item. Sprint 17 supports
 * only plain UTF-8 text; images, files, and rich content are intentionally not
 * implemented.
 */
class ClipboardItem : public QObject {
    Q_OBJECT

    Q_PROPERTY(int itemId READ itemId CONSTANT)
    Q_PROPERTY(QString text READ text CONSTANT)
    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(QDateTime timestamp READ timestamp CONSTANT)

public:
    explicit ClipboardItem(int itemId, const QString &text, const QString &type,
                           const QDateTime &timestamp, QObject *parent = nullptr);
    ~ClipboardItem() override;

    int itemId() const;
    QString text() const;
    QString type() const;
    QDateTime timestamp() const;

private:
    int m_itemId;
    QString m_text;
    QString m_type;
    QDateTime m_timestamp;
};

} // namespace bos::shell
