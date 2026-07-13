#include "bos/TextEditorManager.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "bos/NotificationManager.h"
#include "bos/TextDocument.h"

namespace bos::shell {

TextEditorManager::TextEditorManager(QObject *parent)
    : QObject(parent)
    , m_document(new TextDocument(this))
{
}

TextEditorManager::~TextEditorManager() = default;

TextDocument *TextEditorManager::document() const
{
    return m_document;
}

QString TextEditorManager::content() const
{
    return m_content;
}

int TextEditorManager::cursorLine() const
{
    return m_cursorLine;
}

int TextEditorManager::cursorColumn() const
{
    return m_cursorColumn;
}

void TextEditorManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager*>(manager);
}

void TextEditorManager::setContent(const QString &content)
{
    if (m_content == content) {
        return;
    }
    m_content = content;
    if (m_document) {
        m_document->setModified(true);
    }
    updateStatistics();
    emit contentChanged();
    emit modifiedChanged();
}

void TextEditorManager::setModified(bool modified)
{
    if (m_document) {
        m_document->setModified(modified);
    }
    emit modifiedChanged();
}

void TextEditorManager::updateStatistics()
{
    if (!m_document) {
        return;
    }

    int chars = m_content.size();
    int lines = m_content.isEmpty() ? 1 : m_content.count('\n') + 1;

    m_document->setCharacterCount(chars);
    m_document->setLineCount(lines);
}

void TextEditorManager::setCursorInfo(int line, int column)
{
    if (m_cursorLine == line && m_cursorColumn == column) {
        return;
    }
    m_cursorLine = qMax(1, line);
    m_cursorColumn = qMax(1, column);
    emit cursorInfoChanged();
}

void TextEditorManager::newDocument()
{
    resetDocument();
    if (m_document) {
        m_document->setFileName(QStringLiteral("Untitled"));
        m_document->setLoaded(true);
    }
    emit contentChanged();
    emit documentChanged();
}

void TextEditorManager::openDocument(const QString &path)
{
    QString localPath = path;
    if (localPath.startsWith(QStringLiteral("file:///"))) {
        localPath = localPath.mid(8);
    } else if (localPath.startsWith(QStringLiteral("file://"))) {
        localPath = localPath.mid(7);
    }

    if (!isSupportedExtension(localPath)) {
        notifyError(QStringLiteral("Unsupported file type."));
        return;
    }

    QFile file(localPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << QStringLiteral("[BDE] TextEditorManager: failed to open") << localPath;
        notifyError(QStringLiteral("Failed to Open File."));
        return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    m_content = stream.readAll();
    file.close();

    applyPath(localPath);
    if (m_document) {
        m_document->setLoaded(true);
        m_document->setModified(false);
    }
    updateStatistics();

    notifyInfo(QStringLiteral("File Opened."));
    emit contentChanged();
    emit documentChanged();
    emit modifiedChanged();
}

void TextEditorManager::saveDocument()
{
    if (!m_document || m_document->filePath().isEmpty()) {
        notifyError(QStringLiteral("Failed to Save File."));
        return;
    }
    saveDocumentAs(m_document->filePath());
}

void TextEditorManager::saveDocumentAs(const QString &path)
{
    QString localPath = path;
    if (localPath.startsWith(QStringLiteral("file:///"))) {
        localPath = localPath.mid(8);
    } else if (localPath.startsWith(QStringLiteral("file://"))) {
        localPath = localPath.mid(7);
    }

    QFile file(localPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << QStringLiteral("[BDE] TextEditorManager: failed to save") << localPath;
        notifyError(QStringLiteral("Failed to Save File."));
        return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    stream << m_content;
    file.close();

    applyPath(localPath);
    if (m_document) {
        m_document->setModified(false);
    }

    notifySuccess(QStringLiteral("File Saved."));
    emit modifiedChanged();
}

void TextEditorManager::closeDocument()
{
    resetDocument();
    notifyInfo(QStringLiteral("File Closed."));
    emit contentChanged();
    emit documentChanged();
    emit modifiedChanged();
}

void TextEditorManager::undo()
{
    emit undoRequested();
}

void TextEditorManager::redo()
{
    emit redoRequested();
}

void TextEditorManager::cut()
{
    emit cutRequested();
}

void TextEditorManager::copy()
{
    emit copyRequested();
}

void TextEditorManager::paste()
{
    emit pasteRequested();
}

void TextEditorManager::selectAll()
{
    emit selectAllRequested();
}

void TextEditorManager::notifyInfo(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Text Editor"),
                                                  body,
                                                  QStringLiteral("Text Editor"),
                                                  QStringLiteral("info"));
    }
}

void TextEditorManager::notifySuccess(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Text Editor"),
                                                  body,
                                                  QStringLiteral("Text Editor"),
                                                  QStringLiteral("info"));
    }
}

void TextEditorManager::notifyError(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Text Editor"),
                                                  body,
                                                  QStringLiteral("Text Editor"),
                                                  QStringLiteral("error"));
    }
}

void TextEditorManager::resetDocument()
{
    m_content.clear();
    if (m_document) {
        m_document->setFilePath(QString());
        m_document->setFileName(QString());
        m_document->setLoaded(false);
        m_document->setModified(false);
        m_document->setLineCount(1);
        m_document->setCharacterCount(0);
    }
}

void TextEditorManager::applyPath(const QString &path)
{
    if (!m_document) {
        return;
    }
    m_document->setFilePath(path);
    m_document->setFileName(QFileInfo(path).fileName());
}

bool TextEditorManager::isSupportedExtension(const QString &path)
{
    const QString suffix = QFileInfo(path).suffix().toLower();
    static const QStringList kSupported = {
        QStringLiteral("txt"),
        QStringLiteral("log"),
        QStringLiteral("md"),
        QStringLiteral("json"),
        QStringLiteral("xml"),
        QStringLiteral("ini"),
        QStringLiteral("cfg")
    };
    return kSupported.contains(suffix);
}

} // namespace bos::shell
