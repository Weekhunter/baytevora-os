# BDL Colors

## Base Palette

The initial BOS palette is a dark, low-saturation foundation designed for long reading sessions and clear hierarchy.

| Token | Hex | Usage |
|-------|-----|-------|
| Background | `#0F172A` | Desktop and root window backgrounds |
| Surface | `#1E293B` | Panels, cards, taskbar, and window frames |
| Surface Secondary | `#334155` | Elevated surfaces, inactive borders, secondary panels |
| Border | `#475569` | Dividers, active window borders, outlines |

## Semantic Colors

| Token | Hex | Usage |
|-------|-----|-------|
| Primary | `#2563EB` | Primary actions, selected states, focus rings |
| Accent | `#06B6D4` | Highlights, active indicators, subtle emphasis |
| Success | `#10B981` | Success states, positive feedback |
| Warning | `#F59E0B` | Warnings, cautionary feedback |
| Error | `#EF4444` | Errors, destructive actions, critical feedback |
| Highlight | `#38BDF8` | Selections, hover accents |
| Selection | `#2563EB` | Text and item selection |

## Text Colors

| Token | Hex | Usage |
|-------|-----|-------|
| Text Primary | `#F8FAFC` | Headings, primary body text, labels |
| Text Secondary | `#CBD5E1` | Secondary text, descriptions, timestamps |
| Text Disabled | `#64748B` | Disabled controls, placeholders, inactive items |

## Surface-Specific Tokens

| Token | Mapped Value | Usage |
|-------|--------------|-------|
| WindowBackground | `#1E293B` (Surface) | Managed window backgrounds |
| TaskbarBackground | `#1E293B` (Surface) | Taskbar bar |
| LauncherBackground | `#1E293B` (Surface) | Launcher panel background |
| NotificationBackground | `#1E293B` (Surface) | Notification card backgrounds |

## Guidelines

- Use semantic tokens instead of raw hex values in QML.
- Keep text on surfaces at a contrast ratio of at least 4.5:1 for body text and 3:1 for large UI elements.
- Avoid using Primary or Accent for large fills; reserve them for interactive elements and small indicators.
- Disabled controls must use `TextDisabled`.
