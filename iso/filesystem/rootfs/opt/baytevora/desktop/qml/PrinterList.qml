import QtQuick

/**
 * @brief List of printers for the Print Manager.
 */
Rectangle {
    id: root

    property var printManager: null
    property string selectedPrinterName: ""

    width: 220
    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal printerSelected(string printerName)

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            width: parent.width
            height: AdaptiveLayoutManager.listHeaderHeight
            color: ThemeManager.surfaceColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Text {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                text: "Printers"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
                verticalAlignment: Text.AlignVCenter
            }
        }

        ListView {
            id: listView

            width: parent.width
            height: parent.height - header.height
            model: root.printManager ? root.printManager.printers : []
            clip: true

            delegate: PrinterDelegate {
                width: listView.width
                printer: modelData
                selected: modelData && modelData.printerName === root.selectedPrinterName

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (modelData) {
                            root.selectedPrinterName = modelData.printerName;
                            root.printerSelected(modelData.printerName);
                        }
                    }
                }
            }
        }
    }
}
