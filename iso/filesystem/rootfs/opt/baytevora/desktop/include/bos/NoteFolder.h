#pragma once

#include <QString>

namespace bos::shell {

/**
 * @brief Represents a folder used to organize notes.
 */
class NoteFolder {
public:
    NoteFolder();
    explicit NoteFolder(int folderId, const QString &name);

    int folderId() const;
    QString name() const;

    void setName(const QString &name);

private:
    int m_folderId = -1;
    QString m_name;
};

} // namespace bos::shell
