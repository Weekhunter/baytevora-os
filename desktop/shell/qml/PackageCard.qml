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

    signal packageSelected(string packageId)

    width: parent ? parent.width : 200
    height: content.height + 32
    color: ThemeManager.surfaceSecondaryColor
    radius: DesignTokens.radiusMedium
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        id: content

        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space8

        Row {
            width: parent.width
            spacing: SpacingManager.space12

            Text {
                text: root.packageData ? root.packageData.name : ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.title
                font.family: TypographyManager.fontFamily
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
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.packageData ? root.packageData.description : ""
            width: parent.width
            wrapMode: Text.WordWrap
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Row {
            spacing: SpacingManager.space12

            Text {
                text: root.packageData && packageManager
                      ? packageManager.typeName(root.packageData.packageType)
                      : ""
                color: ThemeManager.accentColor
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }

            Text {
                text: root.packageData ? root.packageData.category : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }

            Text {
                text: root.packageData ? root.packageData.size : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }

        Row {
            spacing: SpacingManager.space8

            Rectangle {
                width: depsLabel.width + 16
                height: 28
                radius: DesignTokens.radiusSmall
                color: ThemeManager.surfaceColor
                border.color: ThemeManager.borderColor
                border.width: 1

                Text {
                    id: depsLabel

                    anchors.centerIn: parent
                    text: "Dependencies"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.packageData) {
                            root.packageSelected(root.packageData.packageId);
                        }
                    }
                }
            }

            Rectangle {
                visible: root.packageData && root.packageData.installed
                width: uninstallLabel.width + 16
                height: 28
                radius: DesignTokens.radiusSmall
                color: ThemeManager.errorColor

                Text {
                    id: uninstallLabel

                    anchors.centerIn: parent
                    text: "Uninstall"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
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
                radius: DesignTokens.radiusSmall
                color: ThemeManager.successColor

                Text {
                    id: installLabel

                    anchors.centerIn: parent
                    text: "Install"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
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
                radius: DesignTokens.radiusSmall
                color: ThemeManager.warningColor

                Text {
                    id: disableLabel

                    anchors.centerIn: parent
                    text: "Disable"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
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
                radius: DesignTokens.radiusSmall
                color: ThemeManager.successColor

                Text {
                    id: enableLabel

                    anchors.centerIn: parent
                    text: "Enable"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
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
