import QtQuick
import BOS.Shell

/**
 * @brief List of search results for the launcher.
 *
 * SearchResults binds to searchManager.results and renders one
 * SearchResultItem per result. It exposes a resultSelected(result) signal so the
 * parent can handle activation.
 */
ListView {
    id: root

    signal resultSelected(var result)

    width: parent ? parent.width : 320
    height: parent ? parent.height : 200
    clip: true
    model: searchManager ? searchManager.results : []

    delegate: SearchResultItem {
        width: ListView.view.width
        resultTitle: modelData.title
        resultSubtitle: modelData.subtitle
        resultProvider: modelData.provider

        onActivated: {
            root.resultSelected(modelData);
        }
    }
}
