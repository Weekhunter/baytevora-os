import QtQuick
import BOS.Shell

/**
 * @brief Baytevora OS System Information screen.
 *
 * SystemInformationScreen surfaces the branding header plus read-only
 * system details from SettingsManager, mirroring the Settings "System" page in a
 * standalone branded view.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    property var infoManager: settingsManager

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 48
        width: Math.min(parent.width - 64, 640)
        spacing: 32

        // Branded header
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 16

            Image {
                width: 64
                height: 77
                source: BrandingManager.applicationSymbolUrl("Baytevora OS")
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 128
                sourceSize.height: 154
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 4

                Text {
                    text: BrandingManager.osName
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.title
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    text: BrandingManager.fullVersionLabel
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }
            }
        }

        // Info rows
        Rectangle {
            width: parent.width
            height: infoColumn.height + 32
            radius: DesignTokens.radiusXLarge
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Column {
                id: infoColumn

                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                InfoRow {
                    width: parent.width
                    label: "BOS Version"
                    value: root.infoManager ? root.infoManager.bosVersion : "—"
                }

                InfoRow {
                    width: parent.width
                    label: "Qt Version"
                    value: root.infoManager ? root.infoManager.qtVersion : "—"
                }

                InfoRow {
                    width: parent.width
                    label: "Architecture"
                    value: root.infoManager ? root.infoManager.architecture : "—"
                }

                InfoRow {
                    width: parent.width
                    label: "Session Uptime"
                    value: root.infoManager ? root.infoManager.uptime : "—"
                }

                InfoRow {
                    width: parent.width
                    label: "Current User"
                    value: loginManager && loginManager.selectedUser
                           ? loginManager.selectedUser.displayName
                           : "—"
                }

                InfoRow {
                    width: parent.width
                    label: "Branding Source"
                    value: BrandingManager.companyName
                }
            }
        }
    }
}
