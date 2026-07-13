import QtQuick
import QtQuick.Layouts
import BOS.Shell

/**
 * @brief Main view of the native Calculator application.
 *
 * CalculatorWindow fills the content area of a WindowFrame and owns an
 * independent CalculatorManager. It displays the current expression and result,
 * a calculator keypad, and a status bar. Keyboard shortcuts are bound to the
 * calculator actions.
 */
Rectangle {
    id: root

    color: ThemeManager.windowBackground

    CalculatorManager {
        id: calculatorManager

        Component.onCompleted: {
            if (clipboardManager) {
                setClipboardManager(clipboardManager);
            }
            if (notificationManager) {
                setNotificationManager(notificationManager);
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        CalculatorDisplay {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.28
            expression: calculatorManager.currentExpression
            result: calculatorManager.currentResult
        }

        CalculatorKeypad {
            Layout.fillWidth: true
            Layout.fillHeight: true
            calculatorManager: calculatorManager
        }

        CalculatorStatusBar {
            Layout.fillWidth: true
            Layout.preferredHeight: AdaptiveLayoutManager.titleBarHeight
        }
    }

    // Keyboard shortcuts for calculator input.
    Shortcut {
        sequences: ["0"]
        onActivated: calculatorManager.appendDigit("0")
    }
    Shortcut {
        sequences: ["1"]
        onActivated: calculatorManager.appendDigit("1")
    }
    Shortcut {
        sequences: ["2"]
        onActivated: calculatorManager.appendDigit("2")
    }
    Shortcut {
        sequences: ["3"]
        onActivated: calculatorManager.appendDigit("3")
    }
    Shortcut {
        sequences: ["4"]
        onActivated: calculatorManager.appendDigit("4")
    }
    Shortcut {
        sequences: ["5"]
        onActivated: calculatorManager.appendDigit("5")
    }
    Shortcut {
        sequences: ["6"]
        onActivated: calculatorManager.appendDigit("6")
    }
    Shortcut {
        sequences: ["7"]
        onActivated: calculatorManager.appendDigit("7")
    }
    Shortcut {
        sequences: ["8"]
        onActivated: calculatorManager.appendDigit("8")
    }
    Shortcut {
        sequences: ["9"]
        onActivated: calculatorManager.appendDigit("9")
    }
    Shortcut {
        sequences: ["+", "Shift+="]
        onActivated: calculatorManager.appendOperator("+")
    }
    Shortcut {
        sequences: ["-"]
        onActivated: calculatorManager.appendOperator("−")
    }
    Shortcut {
        sequences: ["*", "Shift+8"]
        onActivated: calculatorManager.appendOperator("×")
    }
    Shortcut {
        sequences: ["/"]
        onActivated: calculatorManager.appendOperator("÷")
    }
    Shortcut {
        sequences: ["Enter", "Return", "="]
        onActivated: calculatorManager.calculate()
    }
    Shortcut {
        sequences: ["Backspace"]
        onActivated: calculatorManager.backspace()
    }
    Shortcut {
        sequences: ["Escape"]
        onActivated: calculatorManager.clear()
    }
    Shortcut {
        sequences: ["."]
        onActivated: calculatorManager.appendDecimalPoint()
    }
    Shortcut {
        sequences: ["%", "Shift+5"]
        onActivated: calculatorManager.percentage()
    }
    Shortcut {
        sequences: ["Ctrl+C"]
        onActivated: calculatorManager.copyResult()
    }
}
