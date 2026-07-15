# BDL Motion

## Status

Motion is documented-only in BDL v1. No animations are implemented this sprint. The values below define the timing vocabulary that future sprints will use.

## Timing Standards

| Token | Duration | Usage |
|-------|----------|-------|
| Fast | 120 ms | Micro-interactions: hover states, focus rings, button presses |
| Normal | 180 ms | Standard transitions: panel visibility, color changes |
| Slow | 250 ms | Larger state changes: window open/close, launcher toggle |

## Easing

| Token | Curve | Usage |
|-------|-------|-------|
| Standard | ease-in-out | General purpose transitions |
| Enter | ease-out | Elements appearing on screen |
| Exit | ease-in | Elements leaving the screen |

## Animation Philosophy

- Motion should be functional, not decorative.
- Animations must not block input or hide content.
- Avoid transparency-based fades for state changes when possible.
- Future motion work must respect the accessibility requirement to reduce or disable motion for users who request it.
