import QtQuick

/**
 * @brief Annotation list tab for the PDF Studio document panel.
 *
 * Lists the local annotations for the current document and lets the user
 * select or delete them.
 */
Rectangle {
    id: root

    property var studioManager: null

    width: parent ? parent.width : 260
    height: parent ? parent.height : 400
    color: ThemeManager.surfaceColor

    ListView {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space4
        clip: true

        model: root.studioManager ? root.studioManager.annotationManager.annotations : []

        delegate: Rectangle {
            width: ListView.view.width
            height: 44
            color: modelData.selected ? ThemeManager.primaryColor : ThemeManager.surfaceSecondaryColor
            radius: DesignTokens.radiusSmall
            border.color: ThemeManager.borderColor
            border.width: 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space8
                spacing: SpacingManager.space8

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * 0.2
                    text: modelData.type
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.small
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * 0.2
                    text: "p. " + (modelData.pageNumber + 1)
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.small
                    font.family: TypographyManager.fontFamily
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * 0.55
                    text: modelData.contents || "No text"
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.small
                    font.family: TypographyManager.fontFamily
                    elide: Text.ElideRight
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.studioManager && root.studioManager.annotationManager) {
                        root.studioManager.annotationManager.selectAnnotation(modelData.id);
                    }
                }
            }
        }
    }
}
