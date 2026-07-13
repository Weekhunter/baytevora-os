import QtQuick

/**
 * @brief Main window content for the Baytevora Package Manager Phase 2.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.surfaceColor

    property int currentSection: 0
    property string selectedPackageId: ""

    Column {
        anchors.fill: parent
        spacing: 0

        PackageToolbar {
            id: toolbar

            currentSection: root.currentSection
            onSectionSelected: (section) => root.currentSection = section
        }

        Rectangle {
            width: parent.width
            height: parent.height - toolbar.height - statusBar.height
            color: ThemeManager.surfaceColor

            Loader {
                anchors.fill: parent
                anchors.margins: SpacingManager.space24
                sourceComponent: {
                    switch (root.currentSection) {
                    case 0:
                        return packagesPageComponent;
                    case 1:
                        return repositoryManagerComponent;
                    case 2:
                        return transactionViewerComponent;
                    case 3:
                        return dependencyViewerComponent;
                    default:
                        return packagesPageComponent;
                    }
                }
            }
        }

        PackageStatusBar {
            id: statusBar

            packageCount: packageManager ? packageManager.packageCount : 0
            installedCount: packageManager ? packageManager.installedPackages.length : 0
            availableCount: packageManager ? packageManager.availablePackages.length : 0
        }
    }

    Component {
        id: packagesPageComponent

        PackagesPage {
            onPackageSelected: (packageId) => root.selectedPackageId = packageId
        }
    }

    Component {
        id: repositoryManagerComponent

        RepositoryManager {}
    }

    Component {
        id: transactionViewerComponent

        TransactionViewer {}
    }

    Component {
        id: dependencyViewerComponent

        DependencyViewer {
            selectedPackageId: root.selectedPackageId
        }
    }
}
