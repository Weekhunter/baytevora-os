import QtQuick

/**
 * @brief Placeholder component for desktop selection handling.
 *
 * This component is intentionally empty in Sprint 16. Future sprints will use
 * it to render selection rectangles, multi-selection boxes, and related
 * interactions. It is kept as a stable integration point for the desktop
 * surface.
 */
Item {
    id: root

    /** Currently selected desktop item id; -1 means no selection. */
    property int selectedItemId: -1
}
