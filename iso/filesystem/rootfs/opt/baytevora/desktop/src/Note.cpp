#include "bos/Note.h"

namespace bos::shell {

Note::Note()
    : Note(-1, QString())
{
}

Note::Note(int noteId, const QString &title)
    : m_noteId(noteId)
    , m_title(title)
    , m_folder(QStringLiteral("Notes"))
    , m_createdAt(QDateTime::currentDateTime())
    , m_updatedAt(m_createdAt)
{
}

int Note::noteId() const { return m_noteId; }
QString Note::title() const { return m_title; }
QString Note::content() const { return m_content; }
QString Note::folder() const { return m_folder; }
QDateTime Note::createdAt() const { return m_createdAt; }
QDateTime Note::updatedAt() const { return m_updatedAt; }
bool Note::pinned() const { return m_pinned; }
bool Note::favorite() const { return m_favorite; }

void Note::setTitle(const QString &title)
{
    m_title = title;
    touch();
}

void Note::setContent(const QString &content)
{
    m_content = content;
    touch();
}

void Note::setFolder(const QString &folder)
{
    m_folder = folder;
    touch();
}

void Note::setPinned(bool pinned)
{
    m_pinned = pinned;
    touch();
}

void Note::setFavorite(bool favorite)
{
    m_favorite = favorite;
    touch();
}

void Note::touch()
{
    m_updatedAt = QDateTime::currentDateTime();
}

} // namespace bos::shell
