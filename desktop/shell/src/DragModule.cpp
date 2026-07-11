#include "bos/DragModule.h"

#include <QDebug>

#include "bos/DragManager.h"

namespace bos::shell {

DragModule::DragModule()
{
}

DragModule::~DragModule() = default;

QString DragModule::name() const
{
    return QStringLiteral("Drag");
}

void DragModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_dragManager = std::make_unique<DragManager>();
}

void DragModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void DragModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_dragManager.reset();
}

DragManager *DragModule::dragManager() const
{
    return m_dragManager.get();
}

} // namespace bos::shell
