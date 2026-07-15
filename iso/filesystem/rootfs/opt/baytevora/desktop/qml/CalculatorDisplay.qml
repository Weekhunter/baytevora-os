import QtQuick
import QtQuick.Layouts

/**
 * @brief Display area for the Calculator application.
 *
 * CalculatorDisplay shows the current expression and the computed result.
 */
Rectangle {
    id: root

    property alias expression: expressionLabel.text
    property alias result: resultLabel.text

    color: ThemeManager.surfaceColor

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: AdaptiveLayoutManager.contentPadding
        spacing: SpacingManager.space4

        Text {
            id: expressionLabel

            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            id: resultLabel

            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.heading
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
            elide: Text.ElideRight
        }
    }
}
