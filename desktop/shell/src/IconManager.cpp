#include "bos/IconManager.h"

namespace bos::shell {

IconManager::IconManager(QObject *parent)
    : QObject(parent)
{
}

IconManager::~IconManager() = default;

int IconManager::small() const { return 16; }
int IconManager::medium() const { return 20; }
int IconManager::normal() const { return 24; }
int IconManager::large() const { return 32; }
int IconManager::extraLarge() const { return 48; }

} // namespace bos::shell
