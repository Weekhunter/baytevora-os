#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class Note;

/**
 * @brief Provides fast local search over the notes collection.
 *
 * NoteSearchManager supports title search, content search, folder filtering,
 * and favorite filtering. It is invoked on demand from QML and performs no
 * background indexing.
 */
class NoteSearchManager : public QObject {
    Q_OBJECT

public:
    explicit NoteSearchManager(QObject *parent = nullptr);
    ~NoteSearchManager() override;

    Q_INVOKABLE QVariantList search(const QList<Note> &notes,
                                     const QString &query,
                                     const QString &folder = QString(),
                                     bool favoritesOnly = false) const;

    static bool matches(const Note &note, const QString &query,
                        const QString &folder, bool favoritesOnly);
};

} // namespace bos::shell
