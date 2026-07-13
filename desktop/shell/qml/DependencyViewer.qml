import QtQuick

/**
 * @brief Dependency graph viewer for the Package Manager Phase 2.
 */
Column {
    id: root

    property string selectedPackageId: ""

    width: parent ? parent.width : 600
    spacing: SpacingManager.space16

    Text {
        text: "Dependency Viewer"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Text {
        text: "Select a package"
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }

    Repeater {
        model: packageManager ? packageManager.packages : []

        delegate: Rectangle {
            width: parent.width
            height: 40
            radius: DesignTokens.radiusSmall
            color: root.selectedPackageId === modelData.packageId
                   ? (ThemeManager.accentColor)
                   : (ThemeManager.surfaceSecondaryColor)

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager.space12
                text: modelData.name + " (" + modelData.packageId + ")"
                color: root.selectedPackageId === modelData.packageId
                       ? (ThemeManager.textPrimary)
                       : (ThemeManager.textPrimary)
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.selectedPackageId = modelData.packageId
            }
        }
    }

    Text {
        visible: root.selectedPackageId.length > 0
        text: root.selectedPackageId.length > 0
              ? ("Dependencies for " + root.selectedPackageId)
              : ""
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Repeater {
        model: root.selectedPackageId.length > 0 && packageManager
               ? packageManager.dependenciesFor(root.selectedPackageId)
               : []

        delegate: Rectangle {
            width: parent.width
            height: 48
            radius: DesignTokens.radiusSmall
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Column {
                anchors.fill: parent
                anchors.margins: SpacingManager.space8
                spacing: SpacingManager.space4

                Text {
                    text: modelData.dependencyId + (modelData.optional ? " (optional)" : " (required)")
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    text: "Minimum version " + modelData.minimumVersion
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }
            }
        }
    }

    Text {
        visible: root.selectedPackageId.length > 0 && packageManager
                 && packageManager.dependenciesFor(root.selectedPackageId).length === 0
        text: "No declared dependencies."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }
}
