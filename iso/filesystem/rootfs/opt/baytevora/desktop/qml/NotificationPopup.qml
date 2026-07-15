import QtQuick

/**
 * @brief Single notification card displayed inside the notification center.
 *
 * NotificationPopup shows the title, message, source application, and timestamp.
 * It contains a close button and uses a solid background color based on severity.
 * No animations, shadows, or transparency are used.
 */
Rectangle {
    id: root

    property int notificationId: -1
    property string notificationTitle: ""
    property string message: ""
    property string sourceApplication: ""
    property string timestamp: ""
    property string severity: "info"

    signal dismissed()

    width: 340
    height: contentColumn.height + (SpacingManager.space24)
    color: {
        switch (severity) {
        case "success":
            return ThemeManager.successColor;
        case "warning":
            return ThemeManager.warningColor;
        case "error":
            return ThemeManager.errorColor;
        default:
            return ThemeManager.primaryColor;
        }
    }
    radius: DesignTokens.radiusMedium

    Column {
        id: contentColumn

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: SpacingManager.space12
        }
        spacing: SpacingManager.space8

        Row {
            width: parent.width
            spacing: SpacingManager.space8

            Text {
                width: parent.width - closeButton.width - parent.spacing
                text: root.notificationTitle
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.title
                font.weight: Font.DemiBold
                font.family: TypographyManager.fontFamily
                wrapMode: Text.Wrap
            }

            Text {
                id: closeButton

                width: 20
                text: "\u00D7"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.heading
                horizontalAlignment: Text.AlignRight

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.dismissed()
                }
            }
        }

        Text {
            width: parent.width
            text: root.message
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
        }

        Row {
            width: parent.width
            spacing: SpacingManager.space8

            Text {
                text: root.sourceApplication
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }

            Text {
                text: root.timestamp
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }
    }
}
