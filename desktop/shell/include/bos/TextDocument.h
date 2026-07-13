#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents the document currently loaded in the Text Editor.
 */
class TextDocument : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged FINAL)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged FINAL)
    Q_PROPERTY(bool modified READ modified NOTIFY modifiedChanged FINAL)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(int lineCount READ lineCount NOTIFY lineCountChanged FINAL)
    Q_PROPERTY(int characterCount READ characterCount NOTIFY characterCountChanged FINAL)

public:
    explicit TextDocument(QObject *parent = nullptr);

    QString filePath() const;
    QString fileName() const;
    bool modified() const;
    bool loaded() const;
    int lineCount() const;
    int characterCount() const;

    void setFilePath(const QString &path);
    void setFileName(const QString &name);
    void setModified(bool modified);
    void setLoaded(bool loaded);
    void setLineCount(int count);
    void setCharacterCount(int count);

signals:
    void filePathChanged();
    void fileNameChanged();
    void modifiedChanged();
    void loadedChanged();
    void lineCountChanged();
    void characterCountChanged();

private:
    QString m_filePath;
    QString m_fileName;
    bool m_modified = false;
    bool m_loaded = false;
    int m_lineCount = 0;
    int m_characterCount = 0;
};

} // namespace bos::shell
