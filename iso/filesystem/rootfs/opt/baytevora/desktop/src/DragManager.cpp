#include "bos/DragManager.h"

#include <QDebug>

#include "bos/NotificationManager.h"

namespace bos::shell {

DragManager::DragManager(QObject *parent)
    : QObject(parent)
{
    qDebug() << QStringLiteral("[BDE] DragManager initialized");
    notify(QStringLiteral("Drag & Drop"), QStringLiteral("Framework initialized"));
}

DragManager::~DragManager() = default;

void DragManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
    notify(QStringLiteral("Drag & Drop"), QStringLiteral("Framework initialized"));
}

bool DragManager::active() const
{
    return m_operation.isActive();
}

QVariantMap DragManager::currentOperation() const
{
    return m_operation.toMap();
}

int DragManager::currentDragType() const
{
    return static_cast<int>(m_operation.data.type);
}

QString DragManager::currentSource() const
{
    return m_operation.source;
}

QString DragManager::currentTarget() const
{
    return m_operation.target;
}

QPoint DragManager::currentPosition() const
{
    return m_operation.position;
}

void DragManager::beginDrag(int type, const QString &source, const QString &value)
{
    if (active()) {
        cancelDrag();
    }

    m_operation = DragOperation();
    m_operation.state = DragOperationState::Started;
    m_operation.source = source;
    m_operation.data.type = static_cast<DragType::Value>(type);
    m_operation.data.value = value;
    m_operation.position = QPoint(0, 0);

    qDebug() << QStringLiteral("[BDE] Desktop drag started");

    emit operationChanged();
    emit stateChanged();
    emit dragStarted();
}

void DragManager::updatePosition(int x, int y)
{
    if (!active()) {
        return;
    }

    m_operation.position = QPoint(x, y);
    if (m_operation.state == DragOperationState::Started) {
        m_operation.state = DragOperationState::Dragging;
        emit stateChanged();
    }
    emit positionChanged();
}

void DragManager::setTarget(const QString &target)
{
    if (!active()) {
        return;
    }

    if (m_operation.target != target) {
        m_operation.target = target;
        emit operationChanged();
    }
}

void DragManager::clearTarget()
{
    if (!active()) {
        return;
    }

    if (!m_operation.target.isEmpty()) {
        m_operation.target.clear();
        emit operationChanged();
    }
}

void DragManager::completeDrop(const QString &target)
{
    if (!active()) {
        return;
    }

    if (!target.isEmpty()) {
        m_operation.target = target;
    }

    setState(DragOperationState::Dropped);
    qDebug() << QStringLiteral("[BDE] Desktop drag completed");
    notify(QStringLiteral("Drag & Drop"), QStringLiteral("Drag completed"));
    emit dragCompleted();
}

void DragManager::cancelDrag()
{
    if (!active()) {
        return;
    }

    setState(DragOperationState::Cancelled);
    qDebug() << QStringLiteral("[BDE] Desktop drag cancelled");
    notify(QStringLiteral("Drag & Drop"), QStringLiteral("Drag cancelled"));
    emit dragCancelled();
}

void DragManager::setState(DragOperationState::Value state)
{
    m_operation.state = state;
    emit operationChanged();
    emit stateChanged();
}

void DragManager::notify(const QString &title, const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(title, message,
                                                   QStringLiteral("Drag & Drop"),
                                                   QStringLiteral("info"));
    }
}

} // namespace bos::shell
