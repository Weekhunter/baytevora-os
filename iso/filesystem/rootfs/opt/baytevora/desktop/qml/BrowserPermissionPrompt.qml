import QtQuick
import QtWebEngine

/**
 * @brief Modal prompt shown when a website requests a browser permission and
 *        no saved rule exists.
 */
Rectangle {
    id: root

    property var browserManager: null
    property var targetView: null
    property var pendingFeature: 0
    property string pendingOrigin: ""
    property string pendingType: ""

    anchors.fill: parent
    color: ThemeManager.backgroundColor
    opacity: 0.96
    visible: false
    z: 200

    Column {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.8, 420)
        spacing: SpacingManager.space16

        Text {
            width: parent.width
            text: "Permission Request"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.heading
            font.family: TypographyManager.fontFamily
            font.weight: Font.Medium
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            width: parent.width
            text: root.pendingOrigin + " wants to access " + root.pendingType + "."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
        }

        Row {
            width: parent.width
            spacing: SpacingManager.space12
            justifyContent: Text.AlignHCenter // not applicable in Row; left for spacing only

            BrowserToolButton {
                label: "Block"
                onClicked: root.respond(false)
            }

            Item {
                width: parent.width - blockButton.width - allowButton.width - parent.spacing
                height: 1
            }

            BrowserToolButton {
                id: allowButton

                label: "Allow"
                onClicked: root.respond(true)
            }
        }
    }

    function show(view, feature, origin, type) {
        root.targetView = view;
        root.pendingFeature = feature;
        root.pendingOrigin = origin;
        root.pendingType = type;
        root.visible = true;
    }

    function respond(granted) {
        if (root.browserManager && root.pendingType.length > 0) {
            root.browserManager.permissionManager.setPermission(
                root.pendingOrigin, root.pendingType, granted ? "Allow" : "Block");
        }
        if (root.targetView) {
            root.targetView.grantFeaturePermission(root.pendingOrigin, root.pendingFeature, granted);
        }
        root.visible = false;
        root.targetView = null;
        root.pendingOrigin = "";
        root.pendingType = "";
    }
}
