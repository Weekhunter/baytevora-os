import QtQuick

/**
 * @brief Repository management page for the Baytevora Package Manager Phase 2.
 */
Column {
    id: root

    width: parent ? parent.width : 600
    spacing: SpacingManager.space16

    Text {
        text: "Repositories"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Repeater {
        model: packageManager ? packageManager.repositories : []

        delegate: RepositoryDelegate {
            repoData: modelData
            onEnableRequested: (repositoryId) => {
                if (packageManager) {
                    packageManager.enableRepository(repositoryId);
                }
            }
            onDisableRequested: (repositoryId) => {
                if (packageManager) {
                    packageManager.disableRepository(repositoryId);
                }
            }
        }
    }

    Text {
        visible: packageManager && packageManager.repositories.length === 0
        text: "No repositories configured."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }
}
