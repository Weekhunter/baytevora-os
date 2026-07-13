#include "bos/NoteSearchManager.h"

#include "bos/Note.h"

namespace bos::shell {

NoteSearchManager::NoteSearchManager(QObject *parent)
    : QObject(parent)
{
}

NoteSearchManager::~NoteSearchManager() = default;

QVariantList NoteSearchManager::search(const QList<Note> &notes,
                                       const QString &query,
                                       const QString &folder,
                                       bool favoritesOnly) const
{
    QVariantList results;
    results.reserve(notes.size());

    for (const Note &note : notes) {
        if (!matches(note, query, folder, favoritesOnly)) {
            continue;
        }

        QVariantMap map;
        map.insert(QStringLiteral("noteId"), note.noteId());
        map.insert(QStringLiteral("title"), note.title());
        map.insert(QStringLiteral("content"), note.content());
        map.insert(QStringLiteral("folder"), note.folder());
        map.insert(QStringLiteral("createdAt"), note.createdAt().toString(QStringLiteral("yyyy-MM-dd hh:mm")));
        map.insert(QStringLiteral("updatedAt"), note.updatedAt().toString(QStringLiteral("yyyy-MM-dd hh:mm")));
        map.insert(QStringLiteral("pinned"), note.pinned());
        map.insert(QStringLiteral("favorite"), note.favorite());
        results.append(map);
    }

    return results;
}

bool NoteSearchManager::matches(const Note &note, const QString &query,
                                const QString &folder, bool favoritesOnly)
{
    if (favoritesOnly && !note.favorite()) {
        return false;
    }

    if (!folder.isEmpty() && note.folder() != folder) {
        return false;
    }

    if (query.isEmpty()) {
        return true;
    }

    const QString lowerQuery = query.toLower();
    if (note.title().toLower().contains(lowerQuery)) {
        return true;
    }

    if (note.content().toLower().contains(lowerQuery)) {
        return true;
    }

    return false;
}

} // namespace bos::shell
