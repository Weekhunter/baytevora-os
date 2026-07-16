import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import BOS.Shell

/**
 * @brief Baytevora OS Welcome Center window.
 *
 * WelcomeCenterWindow opens after the first login and provides onboarding
 * resources. It can be hidden on future startups via the footer checkbox.
 */
Window {
    id: root

    visible: true
    width: 960
    height: 640
    minimumWidth: 720
    minimumHeight: 480
    title: "Welcome Center"
    color: ThemeManager.backgroundColor

    property int currentTab: 0

    onClosing: welcomeManager.closeWelcomeCenter()

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: AdaptiveLayoutManager.toolbarHeight
            color: ThemeManager.surfaceColor

            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager.space16
                spacing: SpacingManager.space12

                Image {
                    width: 28
                    height: 34
                    source: BrandingManager.applicationSymbolUrl("Baytevora OS")
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: 56
                    sourceSize.height: 68
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Welcome Center"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.title
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }
            }
        }

        // Body
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            // Sidebar
            Rectangle {
                Layout.preferredWidth: 200
                Layout.fillHeight: true
                color: ThemeManager.surfaceSecondaryColor

                ListView {
                    id: tabList

                    anchors.fill: parent
                    anchors.margins: SpacingManager.space8
                    model: [
                        "Welcome",
                        "What's New",
                        "Getting Started",
                        "Installed Applications",
                        "Documentation",
                        "Keyboard Shortcuts",
                        "Community",
                        "About Baytevora"
                    ]
                    currentIndex: root.currentTab
                    onCurrentIndexChanged: root.currentTab = currentIndex

                    delegate: Rectangle {
                        width: tabList.width
                        height: 44
                        radius: DesignTokens.radiusSmall
                        color: tabList.currentIndex === index
                               ? ThemeManager.highlightColor
                               : (tabMouse.containsMouse ? ThemeManager.surfaceColor : "transparent")

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: SpacingManager.space12
                            text: modelData
                            color: tabList.currentIndex === index
                                   ? ThemeManager.backgroundColor
                                   : ThemeManager.textPrimary
                            font.pixelSize: TypographyManager.body
                            font.family: TypographyManager.fontFamily
                        }

                        MouseArea {
                            id: tabMouse

                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: tabList.currentIndex = index
                        }
                    }
                }
            }

            // Tab content
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: ThemeManager.backgroundColor

                StackLayout {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space24
                    currentIndex: root.currentTab

                    WelcomeCenterTab {
                        title: "Welcome"
                        body: "Welcome to Baytevora OS. This center helps you get started with your new desktop environment."
                    }

                    WelcomeCenterTab {
                        title: "What's New"
                        body: "Baytevora OS v0.1 Alpha introduces the desktop shell, native applications, and the Branding Identity system."
                    }

                    WelcomeCenterTab {
                        title: "Getting Started"
                        body: "Open the Launcher to browse applications, manage windows with the taskbar, and customize your desktop in Settings."
                    }

                    WelcomeCenterTab {
                        title: "Installed Applications"
                        body: "Your Baytevora installation includes File Manager, Browser, PDF Studio, Notes, Text Editor, Calculator, Media Player, System Monitor, and more."
                    }

                    WelcomeCenterTab {
                        title: "Documentation"
                        body: "Visit the Baytevora documentation portal for user guides, administrator references, and developer documentation."
                    }

                    WelcomeCenterTab {
                        title: "Keyboard Shortcuts"
                        body: "Super — Open Launcher\nSuper + D — Show Desktop\nAlt + Tab — Switch Windows\nCtrl + Alt + T — Terminal"
                    }

                    WelcomeCenterTab {
                        title: "Community"
                        body: "Community forums and support channels will be available in a future update."
                    }

                    WelcomeCenterTab {
                        title: "About Baytevora"
                        body: BrandingManager.osName + "\n" + BrandingManager.osVersion + "\n" + BrandingManager.companyName + "\n" + BrandingManager.poweredBy
                    }
                }
            }
        }

        // Footer
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 64
            color: ThemeManager.surfaceColor

            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager.space16
                spacing: SpacingManager.space12

                Rectangle {
                    width: 20
                    height: 20
                    radius: 4
                    color: welcomeManager.hideOnNextStartup ? ThemeManager.highlightColor : ThemeManager.surfaceSecondaryColor
                    border.color: ThemeManager.borderColor
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: welcomeManager.hideOnNextStartup ? "\u2713" : ""
                        color: ThemeManager.backgroundColor
                        font.pixelSize: 12
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: welcomeManager.hideOnNextStartup = !welcomeManager.hideOnNextStartup
                    }
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Hide on next startup"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }
            }

            WizardButton {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: SpacingManager.space16
                text: "Close"
                onClicked: {
                    welcomeManager.closeWelcomeCenter();
                    root.close();
                }
            }
        }
    }
}
