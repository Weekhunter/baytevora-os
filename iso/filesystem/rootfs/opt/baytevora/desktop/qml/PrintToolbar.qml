import QtQuick

/**
 * @brief Print Manager toolbar with printer and job actions.
 */
Rectangle {
    id: root

    property var printManager: null
    property string selectedPrinterName: ""
    property int selectedJobId: -1

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        PrintToolButton {
            label: "Refresh Printers"
            onClicked: {
                if (root.printManager) {
                    root.printManager.refreshPrinters();
                }
            }
        }

        PrintToolButton {
            label: "Refresh Queue"
            onClicked: {
                if (root.printManager) {
                    root.printManager.refreshJobs();
                }
            }
        }

        PrintToolButton {
            label: "Set Default"
            onClicked: {
                if (root.printManager && root.selectedPrinterName.length > 0) {
                    root.printManager.setDefaultPrinter(root.selectedPrinterName);
                }
            }
        }

        PrintToolButton {
            label: "Cancel Job"
            onClicked: {
                if (root.printManager && root.selectedJobId >= 0) {
                    root.printManager.cancelJob(root.selectedJobId);
                }
            }
        }
    }
}
