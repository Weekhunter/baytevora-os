import QtQuick
import QtQuick.Layouts
import BOI.Installer

Rectangle {
    id: root
    height: 64
    color: ThemeManager.surfaceColor

    signal backClicked
    signal nextClicked
    signal cancelClicked

    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: 1
        color: ThemeManager.borderColor
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space24
        anchors.rightMargin: SpacingManager.space24
        spacing: SpacingManager.space12

        InstallerButton {
            text: "Cancel"
            destructive: true
            onClicked: root.cancelClicked()
        }

        Item { Layout.fillWidth: true }

        InstallerButton {
            text: "Back"
            visible: installerSession.canGoBack
            enabled: visible
            onClicked: root.backClicked()
        }

        InstallerButton {
            text: installerSession.currentPage === 6 ? "Install" : "Next"
            primary: true
            visible: installerSession.currentPage < 7
            enabled: installerSession.canGoNext
            onClicked: root.nextClicked()
        }
    }
}
