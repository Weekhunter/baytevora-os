import QtQuick

/**
 * @brief Search bar for the File Manager.
 *
 * Emits searchRequested with query, extension filter, and recursive flag.
 */
Rectangle {
    id: root

    property var fileSystemModel: null

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal searchRequested(string query, string extensionFilter, bool recursive)

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        TextField {
            id: queryField

            width: parent.width * 0.45 - parent.spacing * 2
            height: parent.height
            placeholderText: "Search files..."
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            background: Rectangle {
                color: ThemeManager.backgroundColor
                radius: DesignTokens.radiusSmall
            }
        }

        TextField {
            id: extensionField

            width: parent.width * 0.2 - parent.spacing
            height: parent.height
            placeholderText: "Extension"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            background: Rectangle {
                color: ThemeManager.backgroundColor
                radius: DesignTokens.radiusSmall
            }
        }

        CheckBox {
            id: recursiveBox

            text: "Recursive"
            anchors.verticalCenter: parent.verticalCenter
            checked: false
        }

        BrowserToolButton {
            label: "Search"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                root.searchRequested(queryField.text, extensionField.text, recursiveBox.checked);
            }
        }

        BrowserToolButton {
            label: "Clear"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                queryField.text = "";
                extensionField.text = "";
                recursiveBox.checked = false;
                root.searchRequested("", "", false);
            }
        }
    }
}
