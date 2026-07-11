import QtQuick

/**
 * @brief Read-only label/value row used by the System settings page.
 */
Row {
    id: root

    property string label: ""
    property string value: ""

    spacing: 16

    Text {
        width: 140
        text: root.label
        color: "#334155"
        font.pixelSize: 14
        font.weight: Font.DemiBold
    }

    Text {
        text: root.value
        color: "#64748b"
        font.pixelSize: 14
    }
}
