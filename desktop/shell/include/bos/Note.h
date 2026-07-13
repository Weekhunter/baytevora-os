#pragma once

#include <QDateTime>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single note in the Baytevora Notes application.
 *
 * Note stores an integer identifier, title, content, folder, creation time,
 * update time, pinned flag, and favorite flag. It is used by NotesManager and
 * persisted by NotesStorageManager.
 */
class Note {
public:
    Note();
    explicit Note(int noteId, const QString &title = QString());

    int noteId() const;
    QString title() const;
    QString content() const;
    QString folder() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    bool pinned() const;
    bool favorite() const;

    void setTitle(const QString &title);
    void setContent(const QString &content);
    void setFolder(const QString &folder);
    void setPinned(bool pinned);
    void setFavorite(bool favorite);
    void touch();

private:
    int m_noteId = -1;
    QString m_title;
    QString m_content;
    QString m_folder;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
    bool m_pinned = false;
    bool m_favorite = false;
};

} // namespace bos::shell
