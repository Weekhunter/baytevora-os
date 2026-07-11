import QtQuick

/**
 * @brief BDL-styled search bar for the Baytevora Store.
 */
Rectangle {
    id: root

    property string text: input.text

    signal searchAccepted()

    height: 40
    width: parent ? parent.width : 400
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
    border.width: 1

    TextInput {
        id: input

        anchors.fill: parent
        anchors.margins: SpacingManager ? SpacingManager.space12 : 12
        verticalAlignment: TextInput.AlignVCenter
        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
        font.pixelSize: TypographyManager ? TypographyManager.body : 14
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        clip: true

        Keys.onReturnPressed: root.searchAccepted()
        Keys.onEnterPressed: root.searchAccepted()
    }

    Text {
        visible: input.text.length === 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: SpacingManager ? SpacingManager.space12 : 12
        text: "Search apps..."
        color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
        font.pixelSize: TypographyManager ? TypographyManager.body : 14
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
    }
}
