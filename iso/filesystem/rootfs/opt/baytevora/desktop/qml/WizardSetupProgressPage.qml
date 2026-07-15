import QtQuick
import BOS.Shell

/**
 * @brief First-boot wizard setup progress page.
 *
 * Displays the current setup stage and a progress bar. The page has no user
 * interaction; progress is driven by FirstBootManager.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 24
        width: Math.min(parent.width * 0.8, 480)

        Text {
            text: "Setting up Baytevora OS"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 8
            radius: 4
            color: ThemeManager.surfaceSecondaryColor

            Rectangle {
                width: parent.width * (firstBootManager.setupProgress / 100.0)
                height: parent.height
                radius: parent.radius
                color: ThemeManager.highlightColor
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: firstBootManager.setupStage
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
