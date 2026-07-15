import QtQuick

/**
 * @brief Browser address bar using the Baytevora Design Language.
 */
Rectangle {
    id: root

    property string currentUrl: ""

    signal navigateRequested(string url)

    height: 36
    width: parent ? parent.width : 400
    color: ThemeManager.surfaceSecondaryColor
    radius: DesignTokens.radiusMedium
    border.color: ThemeManager.borderColor
    border.width: 1

    TextInput {
        id: input

        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        verticalAlignment: TextInput.AlignVCenter
        text: root.currentUrl
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        selectByMouse: true
        clip: true

        Keys.onReturnPressed: root.navigateRequested(input.text)
        Keys.onEnterPressed: root.navigateRequested(input.text)
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        onClicked: input.forceActiveFocus()
    }
}
