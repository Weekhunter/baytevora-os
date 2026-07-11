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
    height: contentColumn.height + (SpacingManager ? SpacingManager.space24 : 24)
    color: {
        switch (severity) {
        case "success":
            return ThemeManager ? ThemeManager.successColor : "#166534";
        case "warning":
            return ThemeManager ? ThemeManager.warningColor : "#92400e";
        case "error":
            return ThemeManager ? ThemeManager.errorColor : "#991b1b";
        default:
            return ThemeManager ? ThemeManager.primaryColor : "#1e3a8a";
        }
    }
    radius: DesignTokens ? DesignTokens.radiusMedium : 8

    Column {
        id: contentColumn

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: SpacingManager ? SpacingManager.space12 : 12
        }
        spacing: SpacingManager ? SpacingManager.space8 : 8

        Row {
            width: parent.width
            spacing: SpacingManager ? SpacingManager.space8 : 8

            Text {
                width: parent.width - closeButton.width - parent.spacing
                text: root.notificationTitle
                color: ThemeManager ? ThemeManager.textPrimary : "#ffffff"
                font.pixelSize: TypographyManager ? TypographyManager.title : 15
                font.weight: Font.DemiBold
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                wrapMode: Text.Wrap
            }

            Text {
                id: closeButton

                width: 20
                text: "\u00D7"
                color: ThemeManager ? ThemeManager.textPrimary : "#ffffff"
                font.pixelSize: TypographyManager ? TypographyManager.heading : 20
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
            color: ThemeManager ? ThemeManager.textSecondary : "#e2e8f0"
            font.pixelSize: TypographyManager ? TypographyManager.body : 13
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            wrapMode: Text.Wrap
        }

        Row {
            width: parent.width
            spacing: SpacingManager ? SpacingManager.space8 : 8

            Text {
                text: root.sourceApplication
                color: ThemeManager ? ThemeManager.textSecondary : "#bfdbfe"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            }

            Text {
                text: root.timestamp
                color: ThemeManager ? ThemeManager.textSecondary : "#bfdbfe"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            }
        }
    }
}
