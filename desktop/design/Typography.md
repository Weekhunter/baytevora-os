# BDL Typography

## Font Family

BOS uses a single default system font family to keep the interface lightweight and predictable.

| Token | Value |
|-------|-------|
| FontFamily | `"Inter, sans-serif"` |

If `Inter` is unavailable, the system falls back to a generic sans-serif font. Qt resolves the comma-separated list when used in QML.

## Type Scale

All font sizes are exposed by `TypographyManager`. No QML component may hardcode a font size after this sprint.

| Token | Size | Usage |
|-------|------|-------|
| Display | 32 px | Large hero text, empty-state headlines |
| Heading | 24 px | Page titles, section headers |
| Title | 18 px | Card titles, dialog titles |
| Subtitle | 16 px | Subheadings, emphasized body |
| Body | 14 px | Default body text, labels, descriptions |
| Caption | 12 px | Timestamps, metadata, helper text |
| Small | 10 px | Badges, minimal annotations |

## Guidelines

- Use a maximum of three weights inside a single component.
- Default body text is `Body` (14 px).
- Keep line-height at 1.5× for multi-line body text.
- Headings use 1.2–1.3× line-height.
- Never use a font size smaller than `Small` (10 px).
