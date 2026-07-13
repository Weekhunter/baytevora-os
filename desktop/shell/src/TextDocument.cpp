#include "bos/TextDocument.h"

namespace bos::shell {

TextDocument::TextDocument(QObject *parent)
    : QObject(parent)
{
}

QString TextDocument::filePath() const
{
    return m_filePath;
}

QString TextDocument::fileName() const
{
    return m_fileName;
}

bool TextDocument::modified() const
{
    return m_modified;
}

bool TextDocument::loaded() const
{
    return m_loaded;
}

int TextDocument::lineCount() const
{
    return m_lineCount;
}

int TextDocument::characterCount() const
{
    return m_characterCount;
}

void TextDocument::setFilePath(const QString &path)
{
    if (m_filePath == path) {
        return;
    }
    m_filePath = path;
    emit filePathChanged();
}

void TextDocument::setFileName(const QString &name)
{
    if (m_fileName == name) {
        return;
    }
    m_fileName = name;
    emit fileNameChanged();
}

void TextDocument::setModified(bool modified)
{
    if (m_modified == modified) {
        return;
    }
    m_modified = modified;
    emit modifiedChanged();
}

void TextDocument::setLoaded(bool loaded)
{
    if (m_loaded == loaded) {
        return;
    }
    m_loaded = loaded;
    emit loadedChanged();
}

void TextDocument::setLineCount(int count)
{
    if (m_lineCount == count) {
        return;
    }
    m_lineCount = count;
    emit lineCountChanged();
}

void TextDocument::setCharacterCount(int count)
{
    if (m_characterCount == count) {
        return;
    }
    m_characterCount = count;
    emit characterCountChanged();
}

} // namespace bos::shell
