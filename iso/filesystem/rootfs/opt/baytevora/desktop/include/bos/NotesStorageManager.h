#pragma once

#include <QList>
#include <QObject>
#include <QString>

namespace bos::shell {

class Note;
class NoteFolder;

/**
 * @brief Persists notes and folders to local JSON files.
 *
 * NotesStorageManager owns the storage lifecycle: load at startup, save on
 * demand, auto-save individual notes, and delete stale files. No database is
 * used for the Alpha release.
 */
class NotesStorageManager : public QObject {
    Q_OBJECT

public:
    explicit NotesStorageManager(QObject *parent = nullptr);
    ~NotesStorageManager() override;

    bool load(QList<Note> &notes, QList<NoteFolder> &folders, int &nextNoteId, int &nextFolderId);
    bool save(const QList<Note> &notes, const QList<NoteFolder> &folders);
    bool saveNote(const Note &note);
    bool deleteNote(int noteId);
    bool exportNoteToFile(const Note &note, const QString &filePath);
    bool importNoteFromFile(const QString &filePath, Note &note);

    QString notesDirectory() const;
    QString storageFilePath() const;

private:
    void ensureDirectory() const;
};

} // namespace bos::shell
