#pragma once

#include <QList>
#include <QString>

#include "bos/ArchiveEntry.h"

namespace bos::shell {

/**
 * @brief Lightweight archive reader for ZIP, TAR, and TAR.GZ files.
 *
 * ArchiveEngine implements a minimal, read-only parser for the supported
 * archive formats. It does not modify archives and only lists entries.
 */
class ArchiveEngine {
public:
    /**
     * @brief Detects the archive type from a file path.
     * @return "zip", "tar", "tar.gz", or an empty string.
     */
    static QString detectArchiveType(const QString &path);

    /**
     * @brief Reads the entries of the archive at @p path.
     *
     * @param path Local file path to the archive.
     * @param ok Optional pointer set to true on success and false on failure.
     * @return The list of archive entries, or an empty list on failure.
     */
    static QList<ArchiveEntry> readArchive(const QString &path, bool *ok = nullptr);

private:
    static QList<ArchiveEntry> readZip(const QString &path, bool *ok);
    static QList<ArchiveEntry> readTar(const QString &path, bool *ok);
    static QList<ArchiveEntry> readTarGz(const QString &path, bool *ok);
};

} // namespace bos::shell
