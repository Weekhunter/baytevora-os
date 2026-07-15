# Baytevora Branding Repository v1.0

Official brand asset repository for the Baytevora ecosystem.

## Design Philosophy

- Minimal Tech
- Enterprise & Premium
- Modern & Timeless
- Flat Design with refined gradients
- Clean Geometry

## Brand Hierarchy

- **Master Brand**: `01_Baytevora_Labs` — the approved Baytevora Labs identity.
- **Product Brands**: `02_BOS` … `20_Welcome_Center` — each inherits the same
  B-symbol geometry and uses only a unique accent color.

## Color Palette

| Product | Accent | Highlight |
|---------|--------|-----------|
| Baytevora Labs | `#0E81FD` | `#4BD7FF` |
| BOS | `#2563EB` | `#60A5FA` |
| Browser | `#06B6D4` | `#67E8F9` |
| PDF Studio | `#8B5CF6` | `#C4B5FD` |
| Media Studio | `#D946EF` | `#F0ABFC` |
| Store | `#22C55E` | `#86EFAC` |
| Settings | `#6B7280` | `#D1D5DB` |
| File Manager | `#F59E0B` | `#FCD34D` |
| Notes | `#EAB308` | `#FDE047` |
| Calculator | `#14B8A6` | `#5EEAD4` |
| Image Viewer | `#EC4899` | `#F9A8D4` |
| Archive Manager | `#F97316` | `#FDBA74` |
| Text Editor | `#6366F1` | `#A5B4FC` |
| Media Player | `#A855F7` | `#D8B4FE` |
| System Monitor | `#EF4444` | `#FCA5A5` |
| Task Manager | `#3B82F6` | `#93C5FD` |
| Network Manager | `#0EA5E9` | `#7DD3FC` |
| Storage Manager | `#10B981` | `#6EE7B7` |
| Print Manager | `#64748B` | `#CBD5E1` |
| Welcome Center | `#F43F5E` | `#FDA4AF` |

### Neutral System

- Ink: `#111827`
- Dark: `#0B0F19`
- Surface: `#F3F4F6`
- Silver: `#E5E7EB`
- Light: `#FFFFFF`

## Typography Recommendations

- **Primary**: Inter, SF Pro, or Segoe UI
- **Fallback**: system-ui, -apple-system, BlinkMacSystemFont, sans-serif
- **Weights**: 700 for wordmarks, 500/400 for body

## Logo Usage

1. Use the **Default** logo on light/white backgrounds.
2. Use the **Dark** logo on dark backgrounds.
3. Use the **Monochrome** logo in single-color contexts (print, embossing).
4. Maintain clear space around the symbol equal to at least the symbol's stem width.
5. Do not stretch, rotate, distort, or recolor the symbol outside the approved palette.

## File Naming

Each product folder contains:

- `logo.svg` — default horizontal lockup
- `logo-dark.svg` — dark-background lockup
- `logo-light.svg` — light-background lockup
- `logo-monochrome.svg` — single-color lockup
- `symbol.svg` — standalone B symbol
- `favicon.svg` — favicon-ready symbol
- `logo-1024.png` — high-resolution raster
- `logo-512.png` — standard raster
- `preview.png` — product preview card

Master folder additionally contains `logo-256.png`, `logo-128.png`, and
`usage-sheet.png`.

## Icon Language

The `Icons/` directory contains the starter icon language. All icons share:

- 2 px stroke width
- Rounded caps and joins
- 24 × 24 viewBox
- Geometric, single-weight construction

## Future Expansion

When adding new Baytevora products:

1. Choose a new accent color that does not conflict with existing products.
2. Re-use the B-symbol geometry from `01_Baytevora_Labs/symbol.svg`.
3. Create the same file set in a new `XX_Product_Name/` folder.
4. Update the color table in this README.

## License

These assets are proprietary to Baytevora Labs and intended for Baytevora OS
and Baytevora product use.
