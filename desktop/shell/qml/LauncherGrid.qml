import QtQuick
import BOS.Shell

/**
 * @brief Grid of registered applications for the launcher.
 *
 * LauncherGrid displays applications exposed by ApplicationManager and
 * delegates clicks to ApplicationManager.launchApplication().
 */
Grid {
    id: root

    columns: 3
    spacing: 12
    width: parent ? parent.width : 320

    Repeater {
        model: applicationManager ? applicationManager.applications : []

        delegate: LauncherButton {
            iconName: modelData.iconName
            iconSource: BrandingManager.applicationSymbolUrl(modelData.name)
            appName: modelData.name
            onClicked: {
                if (applicationManager) {
                    applicationManager.launchApplication(modelData.name)
                }
            }
        }
    }
}
