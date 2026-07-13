import QtQuick
import QtQuick.Layouts

/**
 * @brief Keypad layout for the Calculator application.
 *
 * CalculatorKeypad arranges digit, operator, and function buttons in a
 * standard desktop calculator grid.
 */
GridLayout {
    id: root

    property var calculatorManager: null

    columns: 4
    columnSpacing: SpacingManager.space8
    rowSpacing: SpacingManager.space8

    CalculatorButton {
        label: "C"
        role: "function"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.clear()
    }

    CalculatorButton {
        label: "CE"
        role: "function"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.clearEntry()
    }

    CalculatorButton {
        label: "⌫"
        role: "function"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.backspace()
    }

    CalculatorButton {
        label: "÷"
        role: "operator"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendOperator("÷")
    }

    CalculatorButton {
        label: "7"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("7")
    }

    CalculatorButton {
        label: "8"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("8")
    }

    CalculatorButton {
        label: "9"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("9")
    }

    CalculatorButton {
        label: "×"
        role: "operator"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendOperator("×")
    }

    CalculatorButton {
        label: "4"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("4")
    }

    CalculatorButton {
        label: "5"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("5")
    }

    CalculatorButton {
        label: "6"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("6")
    }

    CalculatorButton {
        label: "−"
        role: "operator"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendOperator("−")
    }

    CalculatorButton {
        label: "1"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("1")
    }

    CalculatorButton {
        label: "2"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("2")
    }

    CalculatorButton {
        label: "3"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("3")
    }

    CalculatorButton {
        label: "+"
        role: "operator"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendOperator("+")
    }

    CalculatorButton {
        label: "±"
        role: "function"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.toggleSign()
    }

    CalculatorButton {
        label: "0"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDigit("0")
    }

    CalculatorButton {
        label: "."
        role: "function"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.appendDecimalPoint()
    }

    CalculatorButton {
        label: "="
        role: "operator"
        Layout.fillWidth: true
        Layout.fillHeight: true
        onClicked: root.calculatorManager.calculate()
    }
}
