import QtQuick

/**
 * @brief Privacy settings toggles for the browser.
 */
Rectangle {
    id: root

    property var privacySettings: null

    color: ThemeManager.backgroundColor

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space12

        PrivacyToggle {
            label: "Do Not Track"
            checked: root.privacySettings ? root.privacySettings.doNotTrackEnabled : false
            onToggled: (checked) => {
                if (root.privacySettings) {
                    root.privacySettings.setDoNotTrackEnabled(checked);
                }
            }
        }

        PrivacyToggle {
            label: "Block Third-Party Cookies"
            checked: root.privacySettings ? root.privacySettings.blockThirdPartyCookies : false
            onToggled: (checked) => {
                if (root.privacySettings) {
                    root.privacySettings.setBlockThirdPartyCookies(checked);
                }
            }
        }

        PrivacyToggle {
            label: "Clear History on Exit"
            checked: root.privacySettings ? root.privacySettings.clearHistoryOnExit : false
            onToggled: (checked) => {
                if (root.privacySettings) {
                    root.privacySettings.setClearHistoryOnExit(checked);
                }
            }
        }

        PrivacyToggle {
            label: "Clear Cookies on Exit"
            checked: root.privacySettings ? root.privacySettings.clearCookiesOnExit : false
            onToggled: (checked) => {
                if (root.privacySettings) {
                    root.privacySettings.setClearCookiesOnExit(checked);
                }
            }
        }

        PrivacyToggle {
            label: "Send Referrer"
            checked: root.privacySettings ? root.privacySettings.sendReferrer : true
            onToggled: (checked) => {
                if (root.privacySettings) {
                    root.privacySettings.setSendReferrer(checked);
                }
            }
        }

        PrivacyToggle {
            label: "Enable JavaScript"
            checked: root.privacySettings ? root.privacySettings.javascriptEnabled : true
            onToggled: (checked) => {
                if (root.privacySettings) {
                    root.privacySettings.setJavascriptEnabled(checked);
                }
            }
        }

        PrivacyToggle {
            label: "Block Popups"
            checked: root.privacySettings ? root.privacySettings.popupsBlocked : true
            onToggled: (checked) => {
                if (root.privacySettings) {
                    root.privacySettings.setPopupsBlocked(checked);
                }
            }
        }
    }
}
