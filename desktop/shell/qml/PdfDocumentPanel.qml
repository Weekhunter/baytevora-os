import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

/**
 * @brief Document panel for Baytevora PDF Studio.
 *
 * Provides a tabbed view of Properties, Metadata, Bookmarks, Outline, and
 * Annotation List. The panel is owned by PdfStudioWindow and binds to a
 * PdfStudioManager instance.
 */
Rectangle {
    id: root

    property var studioManager: null
    property int panelWidth: 260

    width: panelWidth
    height: parent ? parent.height : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "Document"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }
        }

        TabBar {
            id: tabBar

            width: parent.width
            height: 36
            contentHeight: 36

            background: Rectangle {
                color: ThemeManager.surfaceColor
                border.color: ThemeManager.borderColor
                border.width: 1
            }

            TabButton {
                text: "Properties"
                width: implicitWidth
                font.pixelSize: TypographyManager.small
                font.family: TypographyManager.fontFamily
            }
            TabButton {
                text: "Metadata"
                width: implicitWidth
                font.pixelSize: TypographyManager.small
                font.family: TypographyManager.fontFamily
            }
            TabButton {
                text: "Bookmarks"
                width: implicitWidth
                font.pixelSize: TypographyManager.small
                font.family: TypographyManager.fontFamily
            }
            TabButton {
                text: "Outline"
                width: implicitWidth
                font.pixelSize: TypographyManager.small
                font.family: TypographyManager.fontFamily
            }
            TabButton {
                text: "Annotations"
                width: implicitWidth
                font.pixelSize: TypographyManager.small
                font.family: TypographyManager.fontFamily
            }
        }

        StackLayout {
            width: parent.width
            height: parent.height - tabBar.height
            currentIndex: tabBar.currentIndex

            PdfPropertiesTab {
                studioManager: root.studioManager
            }
            PdfMetadataTab {
                studioManager: root.studioManager
            }
            PdfBookmarksTab {
                studioManager: root.studioManager
            }
            PdfOutlineTab {
                studioManager: root.studioManager
            }
            PdfAnnotationListTab {
                studioManager: root.studioManager
            }
        }
    }
}
