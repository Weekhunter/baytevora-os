import QtQuick

/**
 * @brief Card displaying a single Baytevora package.
 *
 * PackageCard consumes the BDL token managers and shows the package name,
 * version, description, developer, category, type, size, and state. Action
 * buttons let the user request placeholder install, uninstall, enable, or
 * disable operations.
 */
Rectangle {
    id: root

    property var packageData: null

    width: parent ? parent.width : 200
    height: content.height + 32
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
    border.width: 1

    Column {
        id: content

        anchors.fill: parent
        anchors.margins: SpacingManager ? SpacingManager.space16 : 16
        spacing: SpacingManager ? SpacingManager.space8 : 8

        Row {
            width: parent.width
            spacing: SpacingManager ? SpacingManager.space12 : 12

            Text {
                text: root.packageData ? root.packageData.name : ""
                color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                font.pixelSize: TypographyManager ? TypographyManager.title : 18
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.DemiBold
            }

            PackageStatus {
                packageState: root.packageData ? root.packageData.state : 0
            }

            Item {
                height: 1
                width: parent.width - parent.children[0].width - parent.children[1].width - 24
            }
        }

        Text {
            text: root.packageData ? root.packageData.version : ""
            color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
            font.pixelSize: TypographyManager ? TypographyManager.body : 14
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }

        Text {
            text: root.packageData ? root.packageData.description : ""
            width: parent.width
            wrapMode: Text.WordWrap
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.body : 14
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }

        Row {
            spacing: SpacingManager ? SpacingManager.space12 : 12

            Text {
                text: root.packageData && packageManager
                      ? packageManager.typeName(root.packageData.packageType)
                      : ""
                color: ThemeManager ? ThemeManager.accentColor : "#38bdf8"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.DemiBold
            }

            Text {
                text: root.packageData ? root.packageData.category : ""
                color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            }

            Text {
                text: root.packageData ? root.packageData.size : ""
                color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            }
        }

        Row {
            spacing: SpacingManager ? SpacingManager.space8 : 8

            Rectangle {
                visible: root.packageData && root.packageData.installed
                width: uninstallLabel.width + 16
                height: 28
                radius: DesignTokens ? DesignTokens.radiusSmall : 4
                color: ThemeManager ? ThemeManager.errorColor : "#ef4444"

                Text {
                    id: uninstallLabel

                    anchors.centerIn: parent
                    text: "Uninstall"
                    color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                    font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (packageManager && root.packageData) {
                            packageManager.uninstallPackage(root.packageData.packageId);
                        }
                    }
                }
            }

            Rectangle {
                visible: root.packageData && !root.packageData.installed
                width: installLabel.width + 16
                height: 28
                radius: DesignTokens ? DesignTokens.radiusSmall : 4
                color: ThemeManager ? ThemeManager.successColor : "#22c55e"

                Text {
                    id: installLabel

                    anchors.centerIn: parent
                    text: "Install"
                    color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                    font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (packageManager && root.packageData) {
                            packageManager.installPackage(root.packageData.packageId);
                        }
                    }
                }
            }

            Rectangle {
                visible: root.packageData && root.packageData.state === PackageState.Installed
                width: disableLabel.width + 16
                height: 28
                radius: DesignTokens ? DesignTokens.radiusSmall : 4
                color: ThemeManager ? ThemeManager.warningColor : "#f59e0b"

                Text {
                    id: disableLabel

                    anchors.centerIn: parent
                    text: "Disable"
                    color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                    font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (packageManager && root.packageData) {
                            packageManager.disablePackage(root.packageData.packageId);
                        }
                    }
                }
            }

            Rectangle {
                visible: root.packageData && root.packageData.state === PackageState.Disabled
                width: enableLabel.width + 16
                height: 28
                radius: DesignTokens ? DesignTokens.radiusSmall : 4
                color: ThemeManager ? ThemeManager.successColor : "#22c55e"

                Text {
                    id: enableLabel

                    anchors.centerIn: parent
                    text: "Enable"
                    color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                    font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (packageManager && root.packageData) {
                            packageManager.enablePackage(root.packageData.packageId);
                        }
                    }
                }
            }
        }
    }
}
