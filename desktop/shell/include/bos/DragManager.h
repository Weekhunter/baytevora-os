#pragma once

#include <QObject>
#include <QPoint>
#include <QVariantMap>

#include "bos/DragData.h"
#include "bos/DragOperation.h"
#include "bos/DragOperationState.h"
#include "bos/DragType.h"

namespace bos::shell {

class NotificationManager;

/**
 * @brief Central controller for the Baytevora Drag & Drop Framework (BDDF).
 *
 * DragManager owns the active DragOperation, exposes it to QML, and provides
 * methods to begin, update, complete, and cancel a drag. It contains no
 * application-specific logic; applications only read the shared drag state
 * and report their own roles as source or target.
 */
class DragManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY operationChanged)
    Q_PROPERTY(QVariantMap currentOperation READ currentOperation NOTIFY operationChanged)
    Q_PROPERTY(int currentDragType READ currentDragType NOTIFY operationChanged)
    Q_PROPERTY(QString currentSource READ currentSource NOTIFY operationChanged)
    Q_PROPERTY(QString currentTarget READ currentTarget NOTIFY operationChanged)
    Q_PROPERTY(QPoint currentPosition READ currentPosition NOTIFY positionChanged)

public:
    explicit DragManager(QObject *parent = nullptr);
    ~DragManager() override;

    void setNotificationManager(NotificationManager *notificationManager);

    bool active() const;
    QVariantMap currentOperation() const;
    int currentDragType() const;
    QString currentSource() const;
    QString currentTarget() const;
    QPoint currentPosition() const;

    Q_INVOKABLE void beginDrag(int type, const QString &source, const QString &value);
    Q_INVOKABLE void updatePosition(int x, int y);
    Q_INVOKABLE void setTarget(const QString &target);
    Q_INVOKABLE void clearTarget();
    Q_INVOKABLE void completeDrop(const QString &target);
    Q_INVOKABLE void cancelDrag();

signals:
    void operationChanged();
    void positionChanged();
    void stateChanged();
    void dragStarted();
    void dragCompleted();
    void dragCancelled();

private:
    void setState(DragOperationState::Value state);
    void notify(const QString &title, const QString &message);

    DragOperation m_operation;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
