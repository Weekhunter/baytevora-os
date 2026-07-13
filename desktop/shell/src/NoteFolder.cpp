#include "bos/NoteFolder.h"

namespace bos::shell {

NoteFolder::NoteFolder()
    : NoteFolder(-1, QString())
{
}

NoteFolder::NoteFolder(int folderId, const QString &name)
    : m_folderId(folderId)
    , m_name(name)
{
}

int NoteFolder::folderId() const { return m_folderId; }
QString NoteFolder::name() const { return m_name; }

void NoteFolder::setName(const QString &name)
{
    m_name = name;
}

} // namespace bos::shell
