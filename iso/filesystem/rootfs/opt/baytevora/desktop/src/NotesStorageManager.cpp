#include "bos/NotesStorageManager.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "bos/Note.h"
#include "bos/NoteFolder.h"

namespace bos::shell {

NotesStorageManager::NotesStorageManager(QObject *parent)
    : QObject(parent)
{
}

NotesStorageManager::~NotesStorageManager() = default;

bool NotesStorageManager::load(QList<Note> &notes, QList<NoteFolder> &folders,
                             int &nextNoteId, int &nextFolderId)
{
    notes.clear();
    folders.clear();
    nextNoteId = 1;
    nextFolderId = 1;

    QFile file(storageFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        // No existing data: return true with empty lists so defaults are created.
        return true;
    }

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) {
        return false;
    }

    const QJsonObject root = doc.object();
    const QJsonArray foldersArray = root.value(QStringLiteral("folders")).toArray();
    for (const QJsonValue &value : foldersArray) {
        const QJsonObject obj = value.toObject();
        const int id = obj.value(QStringLiteral("folderId")).toInt(-1);
        if (id >= nextFolderId) {
            nextFolderId = id + 1;
        }
        folders.append(NoteFolder(id, obj.value(QStringLiteral("name")).toString()));
    }

    const QJsonArray notesArray = root.value(QStringLiteral("notes")).toArray();
    for (const QJsonValue &value : notesArray) {
        const QJsonObject obj = value.toObject();
        const int id = obj.value(QStringLiteral("noteId")).toInt(-1);
        if (id >= nextNoteId) {
            nextNoteId = id + 1;
        }
        Note note(id, obj.value(QStringLiteral("title")).toString());
        note.setContent(obj.value(QStringLiteral("content")).toString());
        note.setFolder(obj.value(QStringLiteral("folder")).toString(QStringLiteral("Notes")));
        note.setPinned(obj.value(QStringLiteral("pinned")).toBool(false));
        note.setFavorite(obj.value(QStringLiteral("favorite")).toBool(false));
        notes.append(note);
    }

    return true;
}

bool NotesStorageManager::save(const QList<Note> &notes, const QList<NoteFolder> &folders)
{
    ensureDirectory();

    QJsonArray foldersArray;
    for (const NoteFolder &folder : folders) {
        QJsonObject obj;
        obj.insert(QStringLiteral("folderId"), folder.folderId());
        obj.insert(QStringLiteral("name"), folder.name());
        foldersArray.append(obj);
    }

    QJsonArray notesArray;
    for (const Note &note : notes) {
        QJsonObject obj;
        obj.insert(QStringLiteral("noteId"), note.noteId());
        obj.insert(QStringLiteral("title"), note.title());
        obj.insert(QStringLiteral("content"), note.content());
        obj.insert(QStringLiteral("folder"), note.folder());
        obj.insert(QStringLiteral("createdAt"), note.createdAt().toString(Qt::ISODate));
        obj.insert(QStringLiteral("updatedAt"), note.updatedAt().toString(Qt::ISODate));
        obj.insert(QStringLiteral("pinned"), note.pinned());
        obj.insert(QStringLiteral("favorite"), note.favorite());
        notesArray.append(obj);
    }

    QJsonObject root;
    root.insert(QStringLiteral("folders"), foldersArray);
    root.insert(QStringLiteral("notes"), notesArray);

    QFile file(storageFilePath());
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}

bool NotesStorageManager::saveNote(const Note &note)
{
    Q_UNUSED(note)
    // Sprint 46: full save is used for auto-save. Per-note delta save is
    // reserved for a future sprint.
    return true;
}

bool NotesStorageManager::deleteNote(int noteId)
{
    Q_UNUSED(noteId)
    // The full save call removes deleted notes from storage.
    return true;
}

bool NotesStorageManager::exportNoteToFile(const Note &note, const QString &filePath)
{
    QJsonObject obj;
    obj.insert(QStringLiteral("noteId"), note.noteId());
    obj.insert(QStringLiteral("title"), note.title());
    obj.insert(QStringLiteral("content"), note.content());
    obj.insert(QStringLiteral("folder"), note.folder());
    obj.insert(QStringLiteral("createdAt"), note.createdAt().toString(Qt::ISODate));
    obj.insert(QStringLiteral("updatedAt"), note.updatedAt().toString(Qt::ISODate));
    obj.insert(QStringLiteral("pinned"), note.pinned());
    obj.insert(QStringLiteral("favorite"), note.favorite());

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
    return true;
}

bool NotesStorageManager::importNoteFromFile(const QString &filePath, Note &note)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) {
        return false;
    }

    const QJsonObject obj = doc.object();
    note = Note(-1, obj.value(QStringLiteral("title")).toString());
    note.setContent(obj.value(QStringLiteral("content")).toString());
    note.setFolder(obj.value(QStringLiteral("folder")).toString(QStringLiteral("Notes")));
    note.setPinned(obj.value(QStringLiteral("pinned")).toBool(false));
    note.setFavorite(obj.value(QStringLiteral("favorite")).toBool(false));
    return true;
}

QString NotesStorageManager::notesDirectory() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + QStringLiteral("/.baytevora");
    }
    return path + QStringLiteral("/notes");
}

QString NotesStorageManager::storageFilePath() const
{
    return notesDirectory() + QStringLiteral("/notes.json");
}

void NotesStorageManager::ensureDirectory() const
{
    QDir dir(notesDirectory());
    if (!dir.exists()) {
        dir.mkpath(QStringLiteral("."));
    }
}

} // namespace bos::shell
