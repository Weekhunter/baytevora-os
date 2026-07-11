import QtQuick

/**
 * @brief A single desktop icon.
 *
 * Displays a placeholder icon and the item name. Single click selects the
 * item; double click activates it and logs the activation. Visual state uses
 * BDL tokens for colors, typography, and spacing.
 */
Rectangle {
    id: root

    property int itemId: 0
    property string displayName: ""
    property string iconName: ""
    property string itemType: ""
    property bool selected: false

    width: 64
    height: 80
    color: root.selected
        ? (ThemeManager ? ThemeManager.primaryColor : "#2563EB")
        : "transparent"
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    opacity: ThemeManager ? 1.0 : 1.0

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager ? SpacingManager.space4 : 4
        spacing: SpacingManager ? SpacingManager.space4 : 4

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: IconManager ? IconManager.large : 32
            height: width
            color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
            radius: DesignTokens ? DesignTokens.radiusSmall : 6

            Text {
                anchors.centerIn: parent
                text: root.displayName.length > 0 ? root.displayName.charAt(0).toUpperCase() : "?"
                color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                font.pixelSize: TypographyManager ? TypographyManager.title : 18
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            text: root.displayName
            color: root.selected
                ? (ThemeManager ? ThemeManager.textPrimary : "#F8FAFC")
                : (ThemeManager ? ThemeManager.textPrimary : "#F8FAFC")
            font.pixelSize: TypographyManager ? TypographyManager.caption : 12
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            elide: Text.ElideRight
            maximumLineCount: 2
        }
    }

    Timer {
        id: singleClickTimer

        interval: 200
        onTriggered: {
            if (desktopManager) {
                desktopManager.selectItem(root.itemId);
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            singleClickTimer.start();
        }
        onDoubleClicked: {
            singleClickTimer.stop();
            if (desktopManager) {
                desktopManager.activateItem(root.itemId);
            }
        }
    }
}
