#pragma once

#include <QObject>
#include <QString>

#include "bos/CalculatorEngine.h"

namespace bos::shell {

class ClipboardManager;
class NotificationManager;

/**
 * @brief Manages calculator state and exposes it to QML.
 *
 * Each Calculator window owns an independent CalculatorManager. The manager
 * builds the current expression, evaluates it through CalculatorEngine, and
 * integrates with the clipboard and notification services.
 */
class CalculatorManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString currentExpression READ currentExpression NOTIFY currentExpressionChanged FINAL)
    Q_PROPERTY(QString currentResult READ currentResult NOTIFY currentResultChanged FINAL)

public:
    explicit CalculatorManager(QObject *parent = nullptr);
    ~CalculatorManager() override;

    QString currentExpression() const;
    QString currentResult() const;

    Q_INVOKABLE void setClipboardManager(QObject *manager);
    Q_INVOKABLE void setNotificationManager(QObject *manager);

    Q_INVOKABLE void appendDigit(const QString &digit);
    Q_INVOKABLE void appendOperator(const QString &op);
    Q_INVOKABLE void appendDecimalPoint();
    Q_INVOKABLE void toggleSign();
    Q_INVOKABLE void percentage();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void clearEntry();
    Q_INVOKABLE void backspace();
    Q_INVOKABLE void calculate();
    Q_INVOKABLE void copyResult();

signals:
    void currentExpressionChanged();
    void currentResultChanged();

private:
    void setExpression(const QString &expression);
    void setResult(const QString &result);
    void notifyError(const QString &message);
    void notifyInfo(const QString &message);

    bool isUnaryContext() const;

    CalculatorEngine m_engine;
    QString m_expression;
    QString m_result = QStringLiteral("0");
    bool m_expectingNewOperand = false;
    ClipboardManager *m_clipboardManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
