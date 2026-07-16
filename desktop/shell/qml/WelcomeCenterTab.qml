import QtQuick
import BOS.Shell

/**
 * @brief Simple content tab for the Welcome Center.
 */
Column {
    id: root

    property string title: ""
    property string body: ""

    spacing: 16
    width: parent ? parent.width : 400

    Text {
        text: root.title
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.headline
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Text {
        text: root.body
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        wrapMode: Text.Wrap
        width: parent.width
    }
}
