#include "bos/CalculatorEngine.h"

#include <QJSEngine>
#include <QJSValue>
#include <QtMath>

namespace bos::shell {

QString CalculatorEngine::evaluate(const QString &expression, bool *ok) const
{
    if (ok) {
        *ok = false;
    }

    const QString sanitized = sanitize(expression);
    if (sanitized.isEmpty()) {
        return QString();
    }

    QJSEngine engine;
    const QJSValue result = engine.evaluate(sanitized);

    if (result.isError() || result.isUndefined() || result.isNull()) {
        return QString();
    }

    const double value = result.toNumber();
    if (qIsInf(value) || qIsNaN(value)) {
        return QString();
    }

    if (ok) {
        *ok = true;
    }
    return formatNumber(value);
}

bool CalculatorEngine::isValid(const QString &expression) const
{
    bool ok = false;
    evaluate(expression, &ok);
    return ok;
}

QString CalculatorEngine::formatNumber(double value)
{
    if (qIsNaN(value)) {
        return QStringLiteral("Error");
    }

    if (qIsInf(value)) {
        return QStringLiteral("Error");
    }

    const double rounded = qRound(value);
    if (qFuzzyCompare(value, rounded)) {
        return QString::number(static_cast<qlonglong>(rounded));
    }

    QString text = QString::number(value, 'g', 12);
    // Drop a trailing decimal point left by the formatter.
    if (text.endsWith(QLatin1Char('.'))) {
        text.chop(1);
    }
    return text;
}

QString CalculatorEngine::sanitize(const QString &expression) const
{
    QString sanitized = expression;

    // Replace display operators with JavaScript operators.
    sanitized.replace(QChar(0x2212), QLatin1Char('-')); // −
    sanitized.replace(QLatin1String("×"), QLatin1String("*"));
    sanitized.replace(QLatin1String("÷"), QLatin1String("/"));

    // Trim trailing operators so "5+" does not produce a syntax error.
    while (!sanitized.isEmpty()) {
        const QChar last = sanitized.back();
        if (last == QLatin1Char('+') || last == QLatin1Char('-')
            || last == QLatin1Char('*') || last == QLatin1Char('/')) {
            sanitized.chop(1);
        } else {
            break;
        }
    }

    // Empty or only operators is treated as a zero-value input.
    if (sanitized.isEmpty()) {
        return QStringLiteral("0");
    }

    return sanitized;
}

} // namespace bos::shell
