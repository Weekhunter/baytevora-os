#include "bos/BrowserModule.h"

#include <QDebug>

#include "bos/BrowserManager.h"

namespace bos::shell {

BrowserModule::BrowserModule() = default;
BrowserModule::~BrowserModule() = default;

QString BrowserModule::name() const
{
    return QStringLiteral("Browser");
}

void BrowserModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_browserManager = std::make_unique<BrowserManager>();
}

void BrowserModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void BrowserModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_browserManager.reset();
}

BrowserManager *BrowserModule::browserManager() const
{
    return m_browserManager.get();
}

} // namespace bos::shell
