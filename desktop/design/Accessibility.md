# BDL Accessibility

## Contrast

- Body text must meet WCAG AA: at least 4.5:1 against its background.
- Large text (18 px and above, or 14 px bold) and UI components must meet at least 3:1.
- `TextDisabled` is reserved for inactive controls only and must not carry meaningful state by color alone.

## Focus Visibility

- Focus rings use `Primary` (`#2563EB`) at 2 px thickness.
- Focus indicators must be visible against both `Surface` and `Background`.
- Every focusable element must show a focus indicator.

## Touch Targets

- Minimum tappable area is 48 × 48 px for touch interfaces.
- For mouse-driven desktop elements, aim for at least 32 × 32 px.
- Touch targets may be larger than their visual icons.

## Text Scaling

- Layouts must tolerate text sizes up to 200% of the base scale without clipping controls or hiding actions.
- Avoid fixed-height containers for text when possible.

## High DPI

- All measurements are in device-independent pixels (dp) where Qt handles scaling.
- Icon and spacing tokens scale with the device pixel ratio automatically through Qt.
- Do not assume a fixed 96 DPI; test at 1×, 1.5×, and 2× scaling factors.

## Motion

- Respect the system setting for reduced motion.
- When motion is implemented, provide a static fallback path.
- Avoid flashing, strobing, or rapid motion.
