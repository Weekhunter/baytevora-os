#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class TextDocument;
class NotificationManager;

/**
 * @brief Manages document content and editing state for one Text Editor window.
 *
 * TextEditorManager owns the current TextDocument and stores the plain-text
 * content. It provides invokable document actions, editing request signals,
 * and file I/O for TXT/LOG/MD/JSON/XML/INI/CFG files encoded in UTF-8.
 */
class TextEditorManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(TextDocument *document READ document NOTIFY documentChanged FINAL)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged FINAL)
    Q_PROPERTY(int cursorLine READ cursorLine NOTIFY cursorInfoChanged FINAL)
    Q_PROPERTY(int cursorColumn READ cursorColumn NOTIFY cursorInfoChanged FINAL)

public:
    explicit TextEditorManager(QObject *parent = nullptr);
    ~TextEditorManager() override;

    TextDocument *document() const;
    QString content() const;
    int cursorLine() const;
    int cursorColumn() const;

    void setNotificationManager(QObject *manager);

    Q_INVOKABLE void setContent(const QString &content);
    Q_INVOKABLE void setModified(bool modified);
    Q_INVOKABLE void updateStatistics();
    Q_INVOKABLE void setCursorInfo(int line, int column);

    Q_INVOKABLE void newDocument();
    Q_INVOKABLE void openDocument(const QString &path);
    Q_INVOKABLE void saveDocument();
    Q_INVOKABLE void saveDocumentAs(const QString &path);
    Q_INVOKABLE void closeDocument();

    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    Q_INVOKABLE void cut();
    Q_INVOKABLE void copy();
    Q_INVOKABLE void paste();
    Q_INVOKABLE void selectAll();

signals:
    void documentChanged();
    void contentChanged();
    void modifiedChanged();
    void cursorInfoChanged();

    // Editing request signals routed to the QML TextArea.
    void undoRequested();
    void redoRequested();
    void cutRequested();
    void copyRequested();
    void pasteRequested();
    void selectAllRequested();

private:
    void notifyInfo(const QString &body);
    void notifySuccess(const QString &body);
    void notifyError(const QString &body);
    void resetDocument();
    void applyPath(const QString &path);
    static bool isSupportedExtension(const QString &path);

    TextDocument *m_document = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QString m_content;
    int m_cursorLine = 1;
    int m_cursorColumn = 1;
};

} // namespace bos::shell
