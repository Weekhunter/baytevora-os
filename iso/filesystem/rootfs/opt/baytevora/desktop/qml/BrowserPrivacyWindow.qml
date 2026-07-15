import QtQuick
import QtQuick.Layouts

/**
 * @brief In-window privacy overlay for the browser.
 */
Rectangle {
    id: root

    property var browserManager: null
    property bool visible: false

    anchors.fill: parent
    color: ThemeManager.backgroundColor
    visible: root.visible
    z: 100

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: header

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            color: ThemeManager.surfaceColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space8
                spacing: SpacingManager.space8

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Privacy"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.Medium
                }

                Item {
                    width: parent.width - permissionsTab.width - settingsTab.width - closeButton.width - parent.spacing * 4
                    height: parent.height
                }

                BrowserToolButton {
                    id: permissionsTab

                    label: "Permissions"
                    anchors.verticalCenter: parent.verticalCenter
                    opacity: contentStack.currentIndex === 0 ? 1.0 : 0.6
                    onClicked: contentStack.currentIndex = 0
                }

                BrowserToolButton {
                    id: settingsTab

                    label: "Settings"
                    anchors.verticalCenter: parent.verticalCenter
                    opacity: contentStack.currentIndex === 1 ? 1.0 : 0.6
                    onClicked: contentStack.currentIndex = 1
                }

                BrowserToolButton {
                    id: closeButton

                    label: "Close"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: root.visible = false
                }
            }
        }

        StackLayout {
            id: contentStack

            width: parent.width
            height: parent.height - header.height
            currentIndex: 0

            BrowserPermissionList {
                permissionManager: root.browserManager ? root.browserManager.permissionManager : null
            }

            BrowserPrivacySettingsPage {
                privacySettings: root.browserManager ? root.browserManager.privacySettings : null
            }
        }
    }
}
