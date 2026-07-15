import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import BOI.Installer

Window {
    id: root
    visible: true
    width: 960
    height: 640
    minimumWidth: 800
    minimumHeight: 540
    title: "Baytevora OS Installer"
    color: ThemeManager.backgroundColor

    property var pageComponents: [
        "WelcomePage.qml",
        "LanguagePage.qml",
        "KeyboardPage.qml",
        "LicensePage.qml",
        "InstallationTypePage.qml",
        "DiskSelectionPage.qml",
        "PartitionSummaryPage.qml",
        "InstallationProgressPage.qml",
        "CompletionPage.qml"
    ]

    function goNext() {
        if (!installerSession.canGoNext && installerSession.currentPage !== 6) return;

        if (installerSession.currentPage === 6) {
            startInstallation();
            return;
        }

        installerSession.nextPage();
    }

    function startInstallation() {
        var target = Qt.createQmlObject(
            'import BOI.Installer; InstallationTarget { }',
            root
        );
        target.diskId = installerSession.selectedDiskId;
        target.diskName = installerSession.selectedDiskId;
        installerManager.installationCompleted.connect(function() {
            installerSession.nextPage();
        });
        installerManager.installationFailed.connect(function(reason) {
            console.warn("Installation failed:", reason);
        });
        installerManager.startInstallation(target);
        installerSession.nextPage();
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        InstallerToolbar {
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            InstallerSidebar {
                id: sidebar
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: ThemeManager.backgroundColor

                StackLayout {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space32
                    currentIndex: installerSession.currentPage

                    Repeater {
                        model: root.pageComponents

                        Loader {
                            source: modelData
                        }
                    }
                }
            }
        }

        InstallerStatusBar {
            Layout.fillWidth: true
            onBackClicked: installerSession.previousPage()
            onNextClicked: root.goNext()
            onCancelClicked: {
                if (installerSession.currentPage === 7) {
                    installerManager.cancelInstallation();
                }
                Qt.quit();
            }
        }
    }
}
