#pragma once

#include <QString>

namespace bos::shell {

/**
 * @brief Performs arithmetic evaluation for the Calculator application.
 *
 * CalculatorEngine sanitizes expression strings, evaluates them with standard
 * decimal arithmetic, and detects malformed expressions and divide-by-zero.
 * It is stateless and can be reused across multiple CalculatorManager
 * instances.
 */
class CalculatorEngine {
public:
    CalculatorEngine() = default;
    ~CalculatorEngine() = default;

    /**
     * @brief Evaluates the given expression and returns a formatted result.
     * @param expression The calculator expression using BDL operators.
     * @param ok Set to true on success, false on error.
     * @return Formatted numeric result, or an empty string on error.
     */
    QString evaluate(const QString &expression, bool *ok = nullptr) const;

    /**
     * @brief Returns true if the expression is syntactically valid.
     */
    bool isValid(const QString &expression) const;

    /**
     * @brief Formats a numeric value for display.
     */
    static QString formatNumber(double value);

private:
    QString sanitize(const QString &expression) const;
};

} // namespace bos::shell
