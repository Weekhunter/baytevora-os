import QtQuick

/**
 * @brief Breadcrumb navigation bar for the File Manager.
 *
 * Displays the current path as clickable segments. Clicking a segment
 * navigates the FileSystemModel to that folder.
 */
Rectangle {
    id: root

    property var fileSystemModel: null

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    ListView {
        id: breadcrumbList

        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        orientation: ListView.Horizontal
        spacing: 0
        clip: true

        model: {
            if (!root.fileSystemModel || !root.fileSystemModel.path) {
                return [];
            }
            const clean = root.fileSystemModel.path.replace(/\\/g, "/");
            const parts = clean.split("/").filter(Boolean);
            const segments = [];
            let cumulative = "";
            for (let i = 0; i < parts.length; ++i) {
                cumulative += "/" + parts[i];
                segments.push({ name: parts[i], path: cumulative });
            }
            return segments;
        }

        delegate: Row {
            height: breadcrumbList.height
            spacing: 0

            Text {
                height: parent.height
                text: modelData.name
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.fileSystemModel) {
                            root.fileSystemModel.path = modelData.path;
                        }
                    }
                }
            }

            Text {
                height: parent.height
                text: "/"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                verticalAlignment: Text.AlignVCenter
                visible: index < breadcrumbList.count - 1
            }
        }
    }
}
