#include "bos/NotesManager.h"

#include <algorithm>

#include <QDateTime>
#include <QVariantMap>

#include "bos/Note.h"
#include "bos/NoteFolder.h"
#include "bos/NotesStorageManager.h"
#include "bos/NoteSearchManager.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

NotesManager::NotesManager(QObject *parent)
    : QObject(parent)
    , m_storageManager(new NotesStorageManager(this))
    , m_searchManager(new NoteSearchManager(this))
{
    load();
    ensureDefaultFolders();

    if (m_notes.isEmpty()) {
        createNote();
    } else {
        selectNote(0);
    }
}

NotesManager::~NotesManager() = default;

QVariantList NotesManager::notes() const
{
    return m_noteModel;
}

QVariantList NotesManager::folders() const
{
    return m_folderModel;
}

int NotesManager::noteCount() const
{
    return m_notes.size();
}

int NotesManager::folderCount() const
{
    return m_folders.size();
}

int NotesManager::activeNoteIndex() const
{
    return m_activeIndex;
}

int NotesManager::activeNoteId() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->noteId() : -1;
}

QString NotesManager::activeNoteTitle() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->title() : QString();
}

QString NotesManager::activeNoteContent() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->content() : QString();
}

QString NotesManager::activeNoteFolder() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->folder() : QString();
}

QString NotesManager::activeNoteUpdatedAt() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->updatedAt().toString(QStringLiteral("yyyy-MM-dd hh:mm")) : QString();
}

bool NotesManager::activeNotePinned() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->pinned() : false;
}

bool NotesManager::activeNoteFavorite() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->favorite() : false;
}

void NotesManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager *>(manager);
}

void NotesManager::selectNote(int index)
{
    if (index < 0 || index >= m_notes.size() || m_activeIndex == index) {
        return;
    }
    m_activeIndex = index;
    emit activeNoteChanged();
}

void NotesManager::selectNoteById(int noteId)
{
    const int index = noteIndexById(noteId);
    if (index >= 0) {
        selectNote(index);
    }
}

void NotesManager::createNote()
{
    const int index = m_notes.size();
    m_notes.append(Note(generateNoteId(), QStringLiteral("New Note")));
    rebuildModel();
    selectNote(index);
    persist();
}

void NotesManager::newNote()
{
    createNote();
}

void NotesManager::save()
{
    persist();
    emitNotification(QStringLiteral("Note Saved"),
                    QStringLiteral("%1 saved").arg(activeNoteTitle()));
}

void NotesManager::saveAs(const QString &title)
{
    if (title.isEmpty()) {
        return;
    }
    Note *note = noteAt(m_activeIndex);
    if (!note) {
        return;
    }
    note->setTitle(title);
    rebuildModel();
    persist();
    emit activeNoteChanged();
    emitNotification(QStringLiteral("Note Saved"),
                    QStringLiteral("%1 saved").arg(title));
}

void NotesManager::renameActiveNote(const QString &title)
{
    saveAs(title);
}

void NotesManager::duplicateActiveNote()
{
    const Note *source = noteAt(m_activeIndex);
    if (!source) {
        return;
    }

    Note duplicate(generateNoteId(), source->title() + QStringLiteral(" Copy"));
    duplicate.setContent(source->content());
    duplicate.setFolder(source->folder());
    duplicate.setPinned(source->pinned());
    duplicate.setFavorite(source->favorite());

    m_notes.append(duplicate);
    rebuildModel();
    selectNote(m_notes.size() - 1);
    persist();
}

void NotesManager::deleteNote(int index)
{
    if (index < 0 || index >= m_notes.size()) {
        return;
    }

    const QString title = m_notes.at(index).title();
    m_notes.removeAt(index);

    if (m_activeIndex >= m_notes.size()) {
        m_activeIndex = m_notes.size() - 1;
    }

    rebuildModel();
    emit activeNoteChanged();
    emit noteCountChanged();
    persist();

    emitNotification(QStringLiteral("Note Deleted"),
                    QStringLiteral("%1 deleted").arg(title));
}

void NotesManager::deleteActiveNote()
{
    deleteNote(m_activeIndex);
}

void NotesManager::moveActiveNoteToFolder(const QString &folder)
{
    Note *note = noteAt(m_activeIndex);
    if (!note) {
        return;
    }
    note->setFolder(folder);
    rebuildModel();
    emit activeNoteChanged();
    persist();
}

void NotesManager::pinActiveNote()
{
    Note *note = noteAt(m_activeIndex);
    if (!note) {
        return;
    }
    note->setPinned(true);
    rebuildModel();
    emit activeNoteChanged();
    persist();
}

void NotesManager::favoriteActiveNote()
{
    Note *note = noteAt(m_activeIndex);
    if (!note) {
        return;
    }
    note->setFavorite(true);
    rebuildModel();
    emit activeNoteChanged();
    persist();
}

void NotesManager::togglePinActiveNote()
{
    Note *note = noteAt(m_activeIndex);
    if (!note) {
        return;
    }
    note->setPinned(!note->pinned());
    rebuildModel();
    emit activeNoteChanged();
    persist();
}

void NotesManager::toggleFavoriteActiveNote()
{
    Note *note = noteAt(m_activeIndex);
    if (!note) {
        return;
    }
    note->setFavorite(!note->favorite());
    rebuildModel();
    emit activeNoteChanged();
    persist();
}

void NotesManager::createFolder(const QString &name)
{
    if (name.isEmpty()) {
        return;
    }
    m_folders.append(NoteFolder(generateFolderId(), name));
    rebuildFolderModel();
    persist();
    emitNotification(QStringLiteral("Folder Created"),
                    QStringLiteral("%1 created").arg(name));
}

void NotesManager::renameFolder(int folderId, const QString &name)
{
    NoteFolder *folder = folderAt(folderIndexById(folderId));
    if (!folder || name.isEmpty()) {
        return;
    }
    folder->setName(name);
    rebuildFolderModel();
    persist();
}

void NotesManager::deleteFolder(int folderId)
{
    const int index = folderIndexById(folderId);
    if (index < 0) {
        return;
    }

    const QString name = m_folders.at(index).name();
    m_folders.removeAt(index);

    for (Note &note : m_notes) {
        if (note.folder() == name) {
            note.setFolder(QStringLiteral("Notes"));
        }
    }

    rebuildFolderModel();
    rebuildModel();
    persist();
    emitNotification(QStringLiteral("Folder Deleted"),
                    QStringLiteral("%1 deleted").arg(name));
}

QVariantList NotesManager::searchNotes(const QString &query, const QString &folder, bool favoritesOnly) const
{
    return m_searchManager->search(m_notes, query, folder, favoritesOnly);
}

bool NotesManager::exportActiveNote(const QString &filePath)
{
    const Note *note = noteAt(m_activeIndex);
    if (!note) {
        return false;
    }
    return m_storageManager->exportNoteToFile(*note, filePath);
}

bool NotesManager::importNote(const QString &filePath)
{
    Note note;
    if (!m_storageManager->importNoteFromFile(filePath, note)) {
        return false;
    }
    note = Note(generateNoteId(), note.title());
    m_notes.append(note);
    rebuildModel();
    selectNote(m_notes.size() - 1);
    persist();
    return true;
}

void NotesManager::setActiveNoteTitle(const QString &title)
{
    Note *note = noteAt(m_activeIndex);
    if (!note || note->title() == title) {
        return;
    }
    note->setTitle(title);
    rebuildModel();
    emit activeNoteChanged();
    autoSave();
}

void NotesManager::setActiveNoteContent(const QString &content)
{
    Note *note = noteAt(m_activeIndex);
    if (!note || note->content() == content) {
        return;
    }
    note->setContent(content);
    emit activeNoteChanged();
    autoSave();
}

void NotesManager::setActiveNoteFolder(const QString &folder)
{
    Note *note = noteAt(m_activeIndex);
    if (!note || note->folder() == folder) {
        return;
    }
    note->setFolder(folder);
    rebuildModel();
    emit activeNoteChanged();
    autoSave();
}

void NotesManager::setActiveNotePinned(bool pinned)
{
    Note *note = noteAt(m_activeIndex);
    if (!note || note->pinned() == pinned) {
        return;
    }
    note->setPinned(pinned);
    rebuildModel();
    emit activeNoteChanged();
    autoSave();
}

void NotesManager::setActiveNoteFavorite(bool favorite)
{
    Note *note = noteAt(m_activeIndex);
    if (!note || note->favorite() == favorite) {
        return;
    }
    note->setFavorite(favorite);
    rebuildModel();
    emit activeNoteChanged();
    autoSave();
}

int NotesManager::characterCount() const
{
    const Note *note = noteAt(m_activeIndex);
    return note ? note->content().length() : 0;
}

int NotesManager::wordCount() const
{
    const Note *note = noteAt(m_activeIndex);
    if (!note) {
        return 0;
    }
    const QString simplified = note->content().simplified();
    return simplified.isEmpty() ? 0 : simplified.split(QLatin1Char(' ')).size();
}

void NotesManager::load()
{
    m_storageManager->load(m_notes, m_folders, m_nextNoteId, m_nextFolderId);
    rebuildModel();
    rebuildFolderModel();
    emit notesChanged();
    emit foldersChanged();
    emit noteCountChanged();
    emit folderCountChanged();
}

void NotesManager::persist()
{
    m_storageManager->save(m_notes, m_folders);
}

void NotesManager::autoSave()
{
    persist();
}

void NotesManager::rebuildModel()
{
    m_noteModel.clear();
    m_noteModel.reserve(m_notes.size());

    // Pinned notes appear first, then by updated time descending.
    QList<int> indices;
    indices.reserve(m_notes.size());
    for (int i = 0; i < m_notes.size(); ++i) {
        indices.append(i);
    }

    std::sort(indices.begin(), indices.end(), [this](int a, int b) {
        const Note &na = m_notes.at(a);
        const Note &nb = m_notes.at(b);
        if (na.pinned() != nb.pinned()) {
            return na.pinned() > nb.pinned();
        }
        return na.updatedAt() > nb.updatedAt();
    });

    for (int index : qAsConst(indices)) {
        const Note &note = m_notes.at(index);
        QVariantMap map;
        map[QStringLiteral("noteId")] = note.noteId();
        map[QStringLiteral("title")] = note.title();
        map[QStringLiteral("content")] = note.content();
        map[QStringLiteral("folder")] = note.folder();
        map[QStringLiteral("createdAt")] = note.createdAt().toString(QStringLiteral("yyyy-MM-dd hh:mm"));
        map[QStringLiteral("updatedAt")] = note.updatedAt().toString(QStringLiteral("yyyy-MM-dd hh:mm"));
        map[QStringLiteral("pinned")] = note.pinned();
        map[QStringLiteral("favorite")] = note.favorite();
        map[QStringLiteral("index")] = index;
        m_noteModel.append(map);
    }

    emit notesChanged();
}

void NotesManager::rebuildFolderModel()
{
    m_folderModel.clear();
    m_folderModel.reserve(m_folders.size());

    for (const NoteFolder &folder : qAsConst(m_folders)) {
        QVariantMap map;
        map[QStringLiteral("folderId")] = folder.folderId();
        map[QStringLiteral("name")] = folder.name();
        map[QStringLiteral("noteCount")] = [this, &folder]() {
            int count = 0;
            for (const Note &note : m_notes) {
                if (note.folder() == folder.name()) {
                    ++count;
                }
            }
            return count;
        }();
        m_folderModel.append(map);
    }

    emit foldersChanged();
}

Note *NotesManager::noteAt(int index)
{
    if (index < 0 || index >= m_notes.size()) {
        return nullptr;
    }
    return &m_notes[index];
}

const Note *NotesManager::noteAt(int index) const
{
    if (index < 0 || index >= m_notes.size()) {
        return nullptr;
    }
    return &m_notes[index];
}

NoteFolder *NotesManager::folderAt(int index)
{
    if (index < 0 || index >= m_folders.size()) {
        return nullptr;
    }
    return &m_folders[index];
}

int NotesManager::noteIndexById(int noteId) const
{
    for (int i = 0; i < m_notes.size(); ++i) {
        if (m_notes.at(i).noteId() == noteId) {
            return i;
        }
    }
    return -1;
}

int NotesManager::folderIndexById(int folderId) const
{
    for (int i = 0; i < m_folders.size(); ++i) {
        if (m_folders.at(i).folderId() == folderId) {
            return i;
        }
    }
    return -1;
}

void NotesManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("Notes"),
                                              QStringLiteral("info"));
}

void NotesManager::ensureDefaultFolders()
{
    bool hasNotes = false;
    bool hasFavorites = false;
    for (const NoteFolder &folder : qAsConst(m_folders)) {
        if (folder.name() == QStringLiteral("Notes")) {
            hasNotes = true;
        } else if (folder.name() == QStringLiteral("Favorites")) {
            hasFavorites = true;
        }
    }

    if (!hasNotes) {
        m_folders.append(NoteFolder(generateFolderId(), QStringLiteral("Notes")));
    }
    if (!hasFavorites) {
        m_folders.append(NoteFolder(generateFolderId(), QStringLiteral("Favorites")));
    }

    if (!hasNotes || !hasFavorites) {
        rebuildFolderModel();
    }
}

int NotesManager::generateNoteId()
{
    return m_nextNoteId++;
}

int NotesManager::generateFolderId()
{
    return m_nextFolderId++;
}

} // namespace bos::shell
