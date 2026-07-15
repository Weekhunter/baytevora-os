#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class Note;
class NoteFolder;
class NotesStorageManager;
class NoteSearchManager;
class NotificationManager;

/**
 * @brief Manages a collection of notes and folders for one Notes window.
 *
 * NotesManager exposes the note list and folder list to QML, tracks the active
 * note, persists changes through NotesStorageManager, and provides operations
 * for create, save, rename, duplicate, delete, move, pin, favorite, and search.
 */
class NotesManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList notes READ notes NOTIFY notesChanged FINAL)
    Q_PROPERTY(QVariantList folders READ folders NOTIFY foldersChanged FINAL)
    Q_PROPERTY(int noteCount READ noteCount NOTIFY noteCountChanged FINAL)
    Q_PROPERTY(int folderCount READ folderCount NOTIFY folderCountChanged FINAL)

    Q_PROPERTY(int activeNoteIndex READ activeNoteIndex NOTIFY activeNoteChanged FINAL)
    Q_PROPERTY(int activeNoteId READ activeNoteId NOTIFY activeNoteChanged FINAL)
    Q_PROPERTY(QString activeNoteTitle READ activeNoteTitle NOTIFY activeNoteChanged FINAL)
    Q_PROPERTY(QString activeNoteContent READ activeNoteContent WRITE setActiveNoteContent NOTIFY activeNoteChanged FINAL)
    Q_PROPERTY(QString activeNoteFolder READ activeNoteFolder WRITE setActiveNoteFolder NOTIFY activeNoteChanged FINAL)
    Q_PROPERTY(QString activeNoteUpdatedAt READ activeNoteUpdatedAt NOTIFY activeNoteChanged FINAL)
    Q_PROPERTY(bool activeNotePinned READ activeNotePinned WRITE setActiveNotePinned NOTIFY activeNoteChanged FINAL)
    Q_PROPERTY(bool activeNoteFavorite READ activeNoteFavorite WRITE setActiveNoteFavorite NOTIFY activeNoteChanged FINAL)

public:
    explicit NotesManager(QObject *parent = nullptr);
    ~NotesManager() override;

    QVariantList notes() const;
    QVariantList folders() const;
    int noteCount() const;
    int folderCount() const;
    int activeNoteIndex() const;

    int activeNoteId() const;
    QString activeNoteTitle() const;
    QString activeNoteContent() const;
    QString activeNoteFolder() const;
    QString activeNoteUpdatedAt() const;
    bool activeNotePinned() const;
    bool activeNoteFavorite() const;

    Q_INVOKABLE void setNotificationManager(QObject *manager);

    Q_INVOKABLE void selectNote(int index);
    Q_INVOKABLE void selectNoteById(int noteId);
    Q_INVOKABLE void createNote();
    Q_INVOKABLE void newNote(); // Alias for createNote.
    Q_INVOKABLE void save();
    Q_INVOKABLE void saveAs(const QString &title);
    Q_INVOKABLE void renameActiveNote(const QString &title);
    Q_INVOKABLE void duplicateActiveNote();
    Q_INVOKABLE void deleteNote(int index);
    Q_INVOKABLE void deleteActiveNote();
    Q_INVOKABLE void moveActiveNoteToFolder(const QString &folder);
    Q_INVOKABLE void pinActiveNote();
    Q_INVOKABLE void favoriteActiveNote();
    Q_INVOKABLE void togglePinActiveNote();
    Q_INVOKABLE void toggleFavoriteActiveNote();

    Q_INVOKABLE void createFolder(const QString &name);
    Q_INVOKABLE void renameFolder(int folderId, const QString &name);
    Q_INVOKABLE void deleteFolder(int folderId);

    Q_INVOKABLE QVariantList searchNotes(const QString &query, const QString &folder = QString(), bool favoritesOnly = false) const;

    Q_INVOKABLE bool exportActiveNote(const QString &filePath);
    Q_INVOKABLE bool importNote(const QString &filePath);

    Q_INVOKABLE void setActiveNoteTitle(const QString &title);
    Q_INVOKABLE void setActiveNoteContent(const QString &content);
    Q_INVOKABLE void setActiveNoteFolder(const QString &folder);
    Q_INVOKABLE void setActiveNotePinned(bool pinned);
    Q_INVOKABLE void setActiveNoteFavorite(bool favorite);

    Q_INVOKABLE int characterCount() const;
    Q_INVOKABLE int wordCount() const;

signals:
    void notesChanged();
    void foldersChanged();
    void noteCountChanged();
    void folderCountChanged();
    void activeNoteChanged();
    void searchResultsChanged();

private:
    void load();
    void persist();
    void autoSave();
    void rebuildModel();
    void rebuildFolderModel();
    Note *noteAt(int index);
    const Note *noteAt(int index) const;
    NoteFolder *folderAt(int index);
    int noteIndexById(int noteId) const;
    int folderIndexById(int folderId) const;
    void emitNotification(const QString &title, const QString &message);
    void ensureDefaultFolders();
    int generateNoteId();
    int generateFolderId();

    QList<Note> m_notes;
    QList<NoteFolder> m_folders;
    QVariantList m_noteModel;
    QVariantList m_folderModel;
    int m_activeIndex = -1;
    int m_nextNoteId = 1;
    int m_nextFolderId = 1;

    NotesStorageManager *m_storageManager = nullptr;
    NoteSearchManager *m_searchManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
