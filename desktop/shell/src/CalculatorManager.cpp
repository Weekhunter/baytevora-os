#include "bos/CalculatorManager.h"

#include <QDebug>

#include "bos/ClipboardManager.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

CalculatorManager::CalculatorManager(QObject *parent)
    : QObject(parent)
{
}

CalculatorManager::~CalculatorManager() = default;

QString CalculatorManager::currentExpression() const
{
    return m_expression.isEmpty() ? QStringLiteral("0") : m_expression;
}

QString CalculatorManager::currentResult() const
{
    return m_result;
}

void CalculatorManager::setClipboardManager(QObject *manager)
{
    m_clipboardManager = qobject_cast<ClipboardManager*>(manager);
}

void CalculatorManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager*>(manager);
}

void CalculatorManager::appendDigit(const QString &digit)
{
    if (digit.isEmpty()) {
        return;
    }

    if (m_expectingNewOperand || m_expression == QStringLiteral("0")
        || m_expression == QStringLiteral("Error")) {
        m_expectingNewOperand = false;
        setExpression(digit);
    } else {
        setExpression(m_expression + digit);
    }
}

void CalculatorManager::appendOperator(const QString &op)
{
    if (op.isEmpty()) {
        return;
    }

    // Recover from an error state or start a new chained operation after a
    // completed calculation.
    if (m_expectingNewOperand || m_expression == QStringLiteral("Error")) {
        m_expectingNewOperand = false;
        if (m_result != QStringLiteral("Error")) {
            setExpression(m_result + op);
        } else {
            setExpression(QStringLiteral("0") + op);
        }
        return;
    }

    // Start a new expression from the previous result when the input area is
    // empty and a valid result exists.
    if (m_expression.isEmpty() && m_result != QStringLiteral("Error")) {
        setExpression(m_result + op);
        return;
    }

    if (m_expression.isEmpty()) {
        setExpression(QStringLiteral("0") + op);
        return;
    }

    const QChar last = m_expression.back();
    const bool lastIsOperator = last == QLatin1Char('+') || last == QLatin1Char('\u2212')
                                || last == QLatin1Char('\u00d7') || last == QLatin1Char('\u00f7')
                                || last == QLatin1Char('*') || last == QLatin1Char('/')
                                || last == QLatin1Char('-');

    if (lastIsOperator) {
        // Replace the trailing operator rather than stacking operators.
        QString updated = m_expression;
        updated.chop(1);
        setExpression(updated + op);
    } else {
        setExpression(m_expression + op);
    }
}

void CalculatorManager::appendDecimalPoint()
{
    if (m_expectingNewOperand || m_expression == QStringLiteral("Error")) {
        m_expectingNewOperand = false;
        setExpression(QStringLiteral("0."));
        return;
    }

    if (m_expression.isEmpty()) {
        setExpression(QStringLiteral("0."));
        return;
    }

    const QChar last = m_expression.back();
    if (last == QLatin1Char('.')) {
        return;
    }

    // Find the start of the last operand and check whether it already
    // contains a decimal point.
    int i = m_expression.length() - 1;
    while (i >= 0) {
        const QChar c = m_expression.at(i);
        if (c == QLatin1Char('.')) {
            return;
        }
        if (c == QLatin1Char('+') || c == QLatin1Char('\u2212')
            || c == QLatin1Char('\u00d7') || c == QLatin1Char('\u00f7')
            || c == QLatin1Char('*') || c == QLatin1Char('/')
            || c == QLatin1Char('-')) {
            break;
        }
        --i;
    }

    setExpression(m_expression + QLatin1Char('.'));
}

void CalculatorManager::toggleSign()
{
    m_expectingNewOperand = false;

    if (m_expression.isEmpty() || m_expression == QStringLiteral("Error")) {
        if (m_result != QStringLiteral("Error")) {
            bool ok = false;
            const double value = m_result.toDouble(&ok);
            if (ok) {
                setExpression(CalculatorEngine::formatNumber(-value));
                return;
            }
        }
        setExpression(QStringLiteral("-0"));
        return;
    }

    // If the expression is a single number, negate it directly.
    bool ok = false;
    const double direct = m_expression.toDouble(&ok);
    if (ok && !m_expression.contains(QLatin1Char('+')) && !m_expression.contains(QLatin1Char('\u2212'))
        && !m_expression.contains(QLatin1Char('\u00d7')) && !m_expression.contains(QLatin1Char('\u00f7'))
        && !m_expression.contains(QLatin1Char('*')) && !m_expression.contains(QLatin1Char('/'))) {
        setExpression(CalculatorEngine::formatNumber(-direct));
        return;
    }

    // For expressions, evaluate first, then negate.
    const QString evaluated = m_engine.evaluate(m_expression, &ok);
    if (ok) {
        bool valueOk = false;
        const double value = evaluated.toDouble(&valueOk);
        if (valueOk) {
            setExpression(CalculatorEngine::formatNumber(-value));
            return;
        }
    }

    setExpression(QStringLiteral("-") + m_expression);
}

void CalculatorManager::percentage()
{
    m_expectingNewOperand = false;

    const QString source = (m_expression.isEmpty() || m_expression == QStringLiteral("Error"))
                           ? m_result : m_expression;
    if (source.isEmpty() || source == QStringLiteral("Error")) {
        setExpression(QStringLiteral("0"));
        calculate();
        return;
    }

    bool ok = false;
    const QString evaluated = m_engine.evaluate(source, &ok);
    if (ok) {
        bool valueOk = false;
        const double value = evaluated.toDouble(&valueOk);
        if (valueOk) {
            setExpression(CalculatorEngine::formatNumber(value / 100.0));
            calculate();
            return;
        }
    }

    setExpression(QStringLiteral("(") + source + QStringLiteral(")/100"));
    calculate();
}

void CalculatorManager::clear()
{
    m_expectingNewOperand = false;
    setExpression(QStringLiteral("0"));
    setResult(QStringLiteral("0"));
}

void CalculatorManager::clearEntry()
{
    m_expectingNewOperand = false;
    setExpression(QStringLiteral("0"));
}

void CalculatorManager::backspace()
{
    m_expectingNewOperand = false;

    if (m_expression.isEmpty() || m_expression == QStringLiteral("Error")) {
        setExpression(QStringLiteral("0"));
        return;
    }

    QString updated = m_expression;
    updated.chop(1);
    if (updated.isEmpty() || updated == QLatin1String("-")) {
        updated = QStringLiteral("0");
    }
    setExpression(updated);
}

void CalculatorManager::calculate()
{
    if (m_expression.isEmpty() || m_expression == QStringLiteral("Error")) {
        setResult(QStringLiteral("0"));
        m_expectingNewOperand = false;
        return;
    }

    bool ok = false;
    const QString result = m_engine.evaluate(m_expression, &ok);

    if (!ok) {
        m_expectingNewOperand = false;
        setResult(QStringLiteral("Error"));
        notifyError(QStringLiteral("Calculation Error"));
        return;
    }

    m_expectingNewOperand = true;
    setResult(result);
    setExpression(result);
}

void CalculatorManager::copyResult()
{
    if (m_result.isEmpty() || m_result == QStringLiteral("Error")) {
        return;
    }

    if (m_clipboardManager) {
        m_clipboardManager->copyText(m_result);
        notifyInfo(QStringLiteral("Result copied."));
    } else {
        qWarning() << QStringLiteral("[BDE] CalculatorManager: ClipboardManager not available");
    }
}

void CalculatorManager::setExpression(const QString &expression)
{
    if (m_expression == expression) {
        return;
    }
    m_expression = expression;
    emit currentExpressionChanged();
}

void CalculatorManager::setResult(const QString &result)
{
    if (m_result == result) {
        return;
    }
    m_result = result;
    emit currentResultChanged();
}

void CalculatorManager::notifyError(const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(
            QStringLiteral("Calculator"), message, QStringLiteral("Calculator"), QStringLiteral("error"));
    }
}

void CalculatorManager::notifyInfo(const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(
            QStringLiteral("Calculator"), message, QStringLiteral("Calculator"), QStringLiteral("info"));
    }
}

bool CalculatorManager::isUnaryContext() const
{
    if (m_expression.isEmpty()) {
        return true;
    }
    const QChar last = m_expression.back();
    return last == QLatin1Char('+') || last == QLatin1Char('\u2212')
           || last == QLatin1Char('\u00d7') || last == QLatin1Char('\u00f7')
           || last == QLatin1Char('*') || last == QLatin1Char('/')
           || last == QLatin1Char('-');
}

} // namespace bos::shell
