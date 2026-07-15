#include "bos/SpacingManager.h"

namespace bos::shell {

SpacingManager::SpacingManager(QObject *parent)
    : QObject(parent)
{
}

SpacingManager::~SpacingManager() = default;

int SpacingManager::space4() const { return 4; }
int SpacingManager::space8() const { return 8; }
int SpacingManager::space12() const { return 12; }
int SpacingManager::space16() const { return 16; }
int SpacingManager::space20() const { return 20; }
int SpacingManager::space24() const { return 24; }
int SpacingManager::space32() const { return 32; }
int SpacingManager::space40() const { return 40; }
int SpacingManager::space48() const { return 48; }
int SpacingManager::space64() const { return 64; }

} // namespace bos::shell
