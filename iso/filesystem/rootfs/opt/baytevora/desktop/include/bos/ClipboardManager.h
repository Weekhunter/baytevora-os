#pragma once

#include <memory>

#include <QDateTime>
#include <QObject>
#include <QString>

class QClipboard;

namespace bos::shell {

class ClipboardItem;
class NotificationManager;

/**
 * @brief Central clipboard manager for the desktop environment.
 *
 * ClipboardManager wraps the native Qt QClipboard and exposes the current
 * plain-text clipboard state to QML. It supports copying text, pasting text,
 * and clearing the clipboard. It also emits a signal whenever the clipboard
 * content changes, either through this manager or externally.
 *
 * Only plain UTF-8 text is supported in Sprint 17. Images, files, history,
 * persistence, and synchronization are forbidden.
 */
class ClipboardManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool hasContent READ hasContent NOTIFY stateChanged)
    Q_PROPERTY(QString text READ text NOTIFY stateChanged)
    Q_PROPERTY(QString type READ type NOTIFY stateChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp NOTIFY stateChanged)

public:
    explicit ClipboardManager(QClipboard *clipboard, QObject *parent = nullptr);
    ~ClipboardManager() override;

    bool hasContent() const;
    QString text() const;
    QString type() const;
    QDateTime timestamp() const;

    Q_INVOKABLE void copyText(const QString &text);
    Q_INVOKABLE QString pasteText() const;
    Q_INVOKABLE void clearClipboard();

    void setNotificationManager(NotificationManager *manager);

signals:
    void stateChanged();
    void clipboardChanged();

private slots:
    void onClipboardChanged();

private:
    void updateCurrentItem(const QString &text);
    void emitStateChanged();

    QClipboard *m_clipboard = nullptr;
    std::unique_ptr<ClipboardItem> m_currentItem;
    NotificationManager *m_notificationManager = nullptr;
    int m_nextId = 1;
};

} // namespace bos::shell
