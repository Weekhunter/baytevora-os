#pragma once

#include <QObject>
#include <QVariantList>

namespace bos::shell {

/**
 * @brief Provides fast local in-session file search for the File Manager.
 *
 * FileSearchManager performs on-demand filesystem traversal without any
 * background indexing service. It supports filename matching, extension
 * filtering, path filtering, current-folder search, and optional recursive
 * search.
 */
class FileSearchManager : public QObject {
    Q_OBJECT

public:
    explicit FileSearchManager(QObject *parent = nullptr);
    ~FileSearchManager() override;

    Q_INVOKABLE QVariantList search(const QString &directory, const QString &query,
                                     const QString &extensionFilter = QString(),
                                     bool recursive = false) const;
    Q_INVOKABLE QVariantList searchFileNames(const QString &directory, const QString &query,
                                             bool recursive = false) const;

private:
    void searchDirectory(QVariantList &results, const QString &directory,
                        const QString &query, const QString &extensionFilter,
                        bool recursive) const;
    bool matchesQuery(const QString &fileName, const QString &query) const;
    bool matchesExtension(const QString &fileName, const QString &extensionFilter) const;
};

} // namespace bos::shell
