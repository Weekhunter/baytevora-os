import QtQuick
import QtQuick.Window
import BOS.Shell

/**
 * @brief Baytevora OS first-boot setup wizard.
 *
 * FirstBootWizard is a full-screen window that guides the user through initial
 * system configuration. The current page is driven by FirstBootManager; the
 * footer adapts its primary action to each page.
 */
Window {
    id: root

    visible: true
    flags: Qt.FramelessWindowHint
    visibility: Window.FullScreen
    color: ThemeManager.backgroundColor

    Wallpaper {
        anchors.fill: parent
        source: BrandingManager.wallpaperUrl("default")
        fallbackColor: ThemeManager.backgroundColor
    }

    Rectangle {
        anchors.fill: parent
        color: "#990F172A"
    }

    Column {
        anchors.fill: parent
        spacing: 0

        // Header
        Rectangle {
            id: header

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            color: "transparent"

            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager.space24
                spacing: SpacingManager.space12

                Image {
                    width: 32
                    height: 38
                    source: BrandingManager.applicationSymbolUrl("Baytevora OS")
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: 64
                    sourceSize.height: 76
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Welcome to Baytevora OS"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.title
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: SpacingManager.space24
                text: "Step " + (firstBootManager.currentPage + 1) + " of " + firstBootManager.totalPages
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }
        }

        // Page content
        Rectangle {
            width: parent.width
            height: parent.height - header.height - footer.height
            color: "transparent"

            Loader {
                id: pageLoader

                anchors.fill: parent
                source: wizardPages[firstBootManager.currentPage]
            }
        }

        // Footer
        Rectangle {
            id: footer

            width: parent.width
            height: 80
            color: "transparent"

            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: SpacingManager.space32
                spacing: SpacingManager.space16

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: firstBootManager.errorMessage
                    color: ThemeManager.errorColor
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    visible: firstBootManager.errorMessage.length > 0
                }

                WizardButton {
                    id: backButton

                    text: "Back"
                    visible: firstBootManager.canGoBack && firstBootManager.currentPage < 10
                    enabled: firstBootManager.canGoBack
                    onClicked: firstBootManager.previousPage()
                }

                WizardButton {
                    id: nextButton

                    text: {
                        if (firstBootManager.currentPage === 9) return "Start Setup";
                        if (firstBootManager.currentPage === 11) return "Start Using BOS";
                        return "Next";
                    }
                    primary: true
                    visible: firstBootManager.currentPage < 10 || firstBootManager.currentPage === 11
                    enabled: firstBootManager.currentPage !== 10
                    onClicked: {
                        if (firstBootManager.currentPage === 9) {
                            firstBootManager.startSetup();
                        } else if (firstBootManager.currentPage === 11) {
                            firstBootManager.completeSetup();
                        } else {
                            firstBootManager.nextPage();
                        }
                    }
                }
            }
        }
    }

    property var wizardPages: [
        "WizardWelcomePage.qml",
        "WizardRegionPage.qml",
        "WizardLanguagePage.qml",
        "WizardKeyboardPage.qml",
        "WizardTimezonePage.qml",
        "WizardDateTimePage.qml",
        "WizardPrivacyPage.qml",
        "WizardUserAccountPage.qml",
        "WizardComputerNamePage.qml",
        "WizardSummaryPage.qml",
        "WizardSetupProgressPage.qml",
        "WizardFinishPage.qml"
    ]
}
