#include "bos/DesktopManager.h"

#include <QDebug>

#include "bos/DesktopItem.h"

namespace bos::shell {

DesktopManager::DesktopManager(QObject *parent)
    : QObject(parent)
    , m_model(std::make_unique<DesktopModel>())
{
}

DesktopManager::~DesktopManager() = default;

DesktopModel *DesktopManager::model() const
{
    return m_model.get();
}

void DesktopManager::registerItem(const QString &name, const QString &icon,
                                  const QString &type, int x, int y)
{
    const int id = m_nextId++;
    auto *item = new DesktopItem(id, name, icon, type, x, y, m_model.get());
    m_model->addItem(item);

    qDebug() << QStringLiteral("[BDE] Desktop item registered:") << name;
}

void DesktopManager::selectItem(int itemId)
{
    const int rows = m_model->rowCount();
    for (int i = 0; i < rows; ++i) {
        DesktopItem *item = m_model->itemAt(i);
        if (!item) {
            continue;
        }
        item->setSelected(item->itemId() == itemId);
    }

    qDebug() << QStringLiteral("[BDE] Desktop item selected:") << itemId;
    emit itemSelected(itemId);
}

void DesktopManager::activateItem(int itemId)
{
    qDebug() << QStringLiteral("[BDE] Desktop item activated:") << itemId;
    emit itemActivated(itemId);
}

void DesktopManager::loadDefaults()
{
    qDebug() << QStringLiteral("[BDE] Desktop initialized");

    constexpr int startX = 24;
    constexpr int startY = 24;
    constexpr int stepY = 88;

    registerItem(QStringLiteral("Home"), QStringLiteral("home"),
                 QStringLiteral("folder"), startX, startY);
    registerItem(QStringLiteral("Documents"), QStringLiteral("documents"),
                 QStringLiteral("folder"), startX, startY + stepY);
    registerItem(QStringLiteral("Downloads"), QStringLiteral("downloads"),
                 QStringLiteral("folder"), startX, startY + 2 * stepY);
    registerItem(QStringLiteral("Computer"), QStringLiteral("computer"),
                 QStringLiteral("system"), startX, startY + 3 * stepY);
    registerItem(QStringLiteral("Trash"), QStringLiteral("trash"),
                 QStringLiteral("system"), startX, startY + 4 * stepY);
    registerItem(QStringLiteral("Settings"), QStringLiteral("settings"),
                 QStringLiteral("application"), startX, startY + 5 * stepY);
}

} // namespace bos::shell
