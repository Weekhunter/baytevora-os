import QtQuick

/**
 * @brief Main view of the native Print Manager application.
 *
 * PrintManagerWindow fills the content area of a WindowFrame and arranges
 * the toolbar, printer list, printer details, print queue, and status bar.
 * Each Print Manager window owns its own PrintManager so printer state stays
 * isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    property var selectedPrinter: null

    function findPrinter(printerName) {
        if (!printManager || !printerName) {
            return null;
        }
        return printManager.printers.find(function (printer) {
            return printer.printerName === printerName;
        });
    }

    PrintManager {
        id: printManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                printManager.setNotificationManager(notificationManager);
            }
            printManager.refreshPrinters();
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        PrintToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            printManager: printManager
            selectedPrinterName: printerList.selectedPrinterName
            selectedJobId: printQueue.selectedJobId
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - detailsPanel.height - statusBar.height
            spacing: 0

            PrinterList {
                id: printerList

                width: 220
                height: parent.height
                printManager: printManager

                onPrinterSelected: function (printerName) {
                    root.selectedPrinter = root.findPrinter(printerName);
                }
            }

            PrintQueue {
                id: printQueue

                width: parent.width - printerList.width
                height: parent.height
                printManager: printManager
            }
        }

        PrinterDetails {
            id: detailsPanel

            width: parent.width
            height: 180
            printer: root.selectedPrinter
        }

        PrintStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            printManager: printManager
        }
    }

    Connections {
        target: printManager

        function onPrintersChanged() {
            root.selectedPrinter = root.findPrinter(printerList.selectedPrinterName);
        }
    }
}
