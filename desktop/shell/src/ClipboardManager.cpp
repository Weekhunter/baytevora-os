#include "bos/ClipboardManager.h"

#include <QClipboard>
#include <QDebug>
#include <QGuiApplication>

#include "bos/ClipboardItem.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

ClipboardManager::ClipboardManager(QClipboard *clipboard, QObject *parent)
    : QObject(parent)
    , m_clipboard(clipboard)
{
    if (m_clipboard) {
        connect(m_clipboard, &QClipboard::dataChanged,
                this, &ClipboardManager::onClipboardChanged);
    }

    qDebug() << QStringLiteral("[BDE] Clipboard initialized");
}

ClipboardManager::~ClipboardManager() = default;

bool ClipboardManager::hasContent() const
{
    return m_currentItem && !m_currentItem->text().isEmpty();
}

QString ClipboardManager::text() const
{
    return m_currentItem ? m_currentItem->text() : QString();
}

QString ClipboardManager::type() const
{
    return m_currentItem ? m_currentItem->type() : QStringLiteral("text/plain");
}

QDateTime ClipboardManager::timestamp() const
{
    return m_currentItem ? m_currentItem->timestamp() : QDateTime();
}

void ClipboardManager::copyText(const QString &text)
{
    if (!m_clipboard) {
        return;
    }

    m_clipboard->setText(text);
    updateCurrentItem(text);

    qDebug() << QStringLiteral("[BDE] Clipboard updated");
}

QString ClipboardManager::pasteText() const
{
    if (!m_clipboard) {
        return QString();
    }

    return m_clipboard->text();
}

void ClipboardManager::clearClipboard()
{
    if (!m_clipboard) {
        return;
    }

    m_clipboard->clear();
    updateCurrentItem(QString());

    if (m_notificationManager) {
        m_notificationManager->createNotification(
            QStringLiteral("Clipboard"),
            QStringLiteral("Clipboard cleared"),
            QStringLiteral("System"),
            QStringLiteral("info"));
    }

    qDebug() << QStringLiteral("[BDE] Clipboard cleared");
}

void ClipboardManager::setNotificationManager(NotificationManager *manager)
{
    m_notificationManager = manager;
}

void ClipboardManager::onClipboardChanged()
{
    if (!m_clipboard) {
        return;
    }

    const QString newText = m_clipboard->text();
    updateCurrentItem(newText);
}

void ClipboardManager::updateCurrentItem(const QString &text)
{
    const QString trimmed = text.trimmed();
    const bool nowHasContent = !trimmed.isEmpty();

    const bool hadContent = hasContent();
    const QString oldText = hadContent ? m_currentItem->text() : QString();

    if (nowHasContent) {
        m_currentItem = std::make_unique<ClipboardItem>(m_nextId++, trimmed,
                                                        QStringLiteral("text/plain"),
                                                        QDateTime::currentDateTime(),
                                                        this);
    } else {
        m_currentItem.reset();
    }

    if (hadContent != nowHasContent || oldText != trimmed) {
        emitStateChanged();
    }
}

void ClipboardManager::emitStateChanged()
{
    emit stateChanged();
    emit clipboardChanged();
}

} // namespace bos::shell
