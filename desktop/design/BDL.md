# Baytevora Design Language (BDL)

## Purpose

The Baytevora Design Language (BDL) is the official visual and interaction standard for every Baytevora OS (BOS) component and application. It exists as a shared source of truth so that future applications, dialogs, notifications, and shell chrome remain consistent without each team redefining colors, spacing, typography, or motion.

This sprint establishes the **design foundation only**. No existing application is redesigned. Existing QML receives a small, safe token pass where hardcoded constants are replaced by values exposed from C++ managers.

## Design Principles

- **Minimal surface.** Only the tokens required for the current shell and applications are defined.
- **C++ authority.** Business logic for tokens lives in C++ managers. QML consumes values, it does not own them.
- **Forward compatible.** A future theme engine can replace the values held by `ThemeManager` without touching QML.
- **No forbidden features.** BDL v1 does not include dark/light switching, animations, blur, transparency, custom themes, or dynamic colors.

## Design System Files

| File | Purpose |
|------|---------|
| `BDL.md` | This overview and architecture guide |
| `Colors.md` | BOS color palette and semantic color usage |
| `Typography.md` | Type scale, font family, and usage |
| `Spacing.md` | Spacing tokens and application |
| `Motion.md` | Timing and easing standards (documentation only) |
| `Icons.md` | Icon size constants |
| `Accessibility.md` | Contrast, focus, touch targets, and scaling rules |
| `Components.md` | Component standards for buttons, toolbars, windows, etc. |

## Architecture

```
Application
        |
        +-- ThemeManager         (colors)
        +-- DesignTokens         (radius, base tokens)
        +-- TypographyManager    (font sizes and family)
        +-- SpacingManager       (spacing scale)
        +-- IconManager          (icon size constants)
        |
        +-- exposed to QML as context properties
                |
                v
        QML components reference ThemeManager.backgroundColor,
        SpacingManager.space16, DesignTokens.radiusMedium, etc.
```

## How to Use

From QML, reference the managers directly because they are exposed as context properties:

```qml
Rectangle {
    color: ThemeManager.backgroundColor
    radius: DesignTokens.radiusMedium
    anchors.margins: SpacingManager.space16
}

Text {
    color: ThemeManager.textPrimary
    font.pixelSize: TypographyManager.body
    font.family: TypographyManager.fontFamily
}
```

New applications **must not** hardcode colors, font sizes, spacing, or radius values after this sprint.

## Version

- **BDL Version:** 1.0
- **BOS Version:** 0.15.0
