# BDL Component Standards

These standards describe the visual vocabulary that all BOS components must follow. Only token references are allowed after this sprint.

## Buttons

- Background on `Surface`: `SurfaceSecondaryColor` at rest, `Border` on hover.
- Text: `TextPrimary`.
- Disabled: `TextDisabled` on `SurfaceSecondaryColor`.
- Minimum height: 32 px; touch targets 48 × 48 px when used in touch contexts.
- Radius: `DesignTokens.radiusSmall` (6 px) for standard buttons, `radiusMedium` (8 px) for prominent buttons.

## Toolbars

- Background: `ThemeManager.taskbarBackground` (Surface).
- Border: 1 px `Border` divider on the edge that separates the toolbar from content.
- Height: 40 px default; content centered vertically.
- Items use `space8`/`space12` internal spacing.

## Sidebars

- Background: `Surface`.
- Width: 200–260 px.
- Active item: `SurfaceSecondaryColor` background, `TextPrimary` label.
- Inactive item: `TextSecondary` label, transparent background.
- Radius: `radiusMedium` for active item highlight.

## Lists

- Background: transparent or `Surface`.
- Alternate rows may use `Surface` and `SurfaceSecondaryColor` for distinction, or remain uniform.
- Text: `TextPrimary` for names, `TextSecondary` for metadata.
- Selected row: `SelectionColor` background with `TextPrimary` text.

## Cards

- Background: `Surface`.
- Border: 1 px `Border`.
- Radius: `DesignTokens.radiusMedium` (8 px).
- Padding: `SpacingManager.space16`.
- No shadows, no blur, no transparency.

## Notifications

- Background: `ThemeManager.notificationBackground`.
- Success: `SuccessColor`.
- Warning: `WarningColor`.
- Error: `ErrorColor`.
- Info: `PrimaryColor`.
- Radius: `DesignTokens.radiusMedium`.
- Padding: `SpacingManager.space12`.

## Windows

- Background: `ThemeManager.windowBackground`.
- Active border: 2 px `Border`.
- Inactive border: 1 px `SurfaceSecondaryColor`.
- Title bar height: 32 px.
- Title bar active background: `Surface`.
- Title bar inactive background: `Background`.
- Title text: `TextPrimary`.

## Dialogs

- Background: `Surface`.
- Border: 1 px `Border`.
- Radius: `DesignTokens.radiusLarge` (12 px).
- Padding: `SpacingManager.space24`.
- Action buttons anchored to the bottom-right with `space12` gap.

## Context Menus (future)

- Background: `Surface`.
- Border: 1 px `Border`.
- Radius: `DesignTokens.radiusSmall`.
- Item height: 32 px minimum.
- Hover: `SurfaceSecondaryColor`.

## Application Layout

- Use `SpacingManager` tokens for all margins and gaps.
- Cards and panels use `DesignTokens.radiusMedium`.
- Avoid arbitrary widths; prefer `space` multiples or relative layouts.
- Keep the primary action count to one per section.
