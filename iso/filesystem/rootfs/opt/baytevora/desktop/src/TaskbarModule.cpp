#include "bos/TaskbarModule.h"

#include <QDebug>

namespace bos::shell {

TaskbarModule::TaskbarModule() = default;
TaskbarModule::~TaskbarModule() = default;

QString TaskbarModule::name() const
{
    return QStringLiteral("Taskbar");
}

void TaskbarModule::initialize()
{
    qDebug() << QStringLiteral("[BDE] Taskbar initialized");
}

void TaskbarModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("started");
}

void TaskbarModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("shutting down");
}

} // namespace bos::shell
