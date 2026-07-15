Baytevora OS (BOS)

Baytevora OS (BOS) is a next-generation Linux-based operating system developed by Baytevora Labs.

Our mission is to build a secure, AI-first, privacy-focused operating system designed for businesses, professionals, developers, and creators.

BOS is not intended to be just another Linux distribution. It is being designed as a complete ecosystem that combines modern desktop computing, artificial intelligence, enterprise management, cloud services, and strong security into a unified platform.

Vision

To build the world's most secure, intelligent, and trusted operating system for businesses and professionals.

Core Principles
Security by Design
AI-First Experience
Privacy by Default
Modern and Intuitive User Interface
High Performance
Enterprise-Ready Architecture
Open and Extensible Platform
Planned Components
BOS Desktop
BOS AI Assistant
BOS Software Center
BOS File Manager
BOS Settings
BOS Cloud Services
BOS Enterprise Management
BOS Identity
BOS Backup
BOS Developer Platform
Technology Direction

The project is planned as a Linux-based operating system with its own desktop environment, applications, and ecosystem.

The implementation will evolve as the project progresses and architectural decisions are finalized.

Project Structure
docs/            Project documentation
architecture/    System architecture
design/          UI/UX designs
desktop/         Desktop environment
apps/            Built-in applications
ai/              AI assistant and services
cloud/           Cloud platform
installer/       Installation system
assets/          Logos, icons, wallpapers
scripts/         Build and automation scripts
Roadmap
Project Vision
System Architecture
User Interface Design
Desktop Environment
Core Applications
AI Integration
Cloud Platform
Enterprise Features
Beta Release
Stable Release
Status

Current Stage: Planning & Architecture

The project is currently focused on defining the vision, architecture, and technical specifications before implementation begins.

License

The license will be determined before the first public release.

Milestone D — Baytevora PDF Studio Foundation

Overview

Sprint D extends the existing Baytevora PDF Viewer (Sprint 32) into Baytevora PDF Studio (BPS), a native PDF viewing, annotation, and printing application for the BDE. The existing PDF Viewer architecture is preserved and extended rather than rewritten.

Architecture

- PdfStudioDocument — metadata holder, including title, author, subject, keywords, creator, producer, creation date, and modification date.
- PdfStudioManager — per-window state owner: document, current page, zoom, current tool, and undo/redo.
- PdfAnnotation — local annotation object (page, type, rect, color, contents, author, date, selected).
- PdfAnnotationManager — owns annotations, add/move/resize/delete/undo/redo, exposed to QML.
- PdfEditorTools — tool palette enum registered for QML consumption.
- PdfStudioApplication — window creation, pending-file queue for File Manager integration.
- PdfStudioWindow / PdfStudioToolbar / PdfDocumentPanel / tabs / PdfStudioStatusBar / PdfAnnotationOverlay — QML UI layer.

Class Ownership

- ApplicationManager owns the single PdfStudioApplication instance.
- PdfStudioApplication requests windows from WindowManager.
- Each PDF Studio window owns a PdfStudioManager (created in QML).
- PdfStudioManager owns one PdfStudioDocument and one PdfAnnotationManager.
- PdfAnnotationManager owns PdfAnnotation objects and provides the local annotation layer.

Lifecycle

1. User launches "Baytevora PDF Studio" or opens a `.pdf` from File Manager.
2. ApplicationManager calls `PdfStudioApplication::open()` or `openFile(path)`.
3. A BDE window is registered with the title "Baytevora PDF Studio".
4. WindowFrame loads `PdfStudioWindow.qml`, which creates a fresh `PdfStudioManager`.
5. The QML scene reads any pending path and calls `studioManager.openDocument(path)`.
6. `PdfStudioManager` initializes the document and reads PDF metadata via `QPdfDocument`.
7. Annotations are created, moved, resized, deleted, undone, or redone through `PdfAnnotationManager`.

Core Features

- Open PDF via File Manager or Open dialog.
- Page navigation (first, previous, next, last, go to page, shortcuts).
- Zoom in/out/reset, fit to width, fit to page.
- Thumbnail sidebar, multiple windows, keyboard shortcuts.
- Annotation toolbar tools: Selection, Hand, Text, Highlight, Underline, Strikeout, Rectangle, Ellipse, Arrow, Line, Freehand Pen, Sticky Note, Stamp Placeholder, Signature Placeholder.
- Add, move, resize, delete, undo, redo annotations.
- Document panel tabs: Properties, Metadata, Bookmarks, Outline, Annotation List.
- Status bar: zoom, current page / total pages, annotation count, document status.
- Print integration via the existing `printManager.printDocument(filePath)` hook.

BDL v2 Compliance

- All colors and spacing come from ThemeManager, SpacingManager, and DesignTokens.
- No hardcoded hex literals or direct platform color names.
- Components follow the established BDE atomic design and manager patterns.

Extension Points

The architecture intentionally leaves clean hooks for future work without requiring rewrites:

- OCR: add an `OcrProcessor` helper and a new toolbar tool.
- Digital Signatures: extend `PdfAnnotation` with certificate data and a signature pipeline.
- PDF Merge/Split/Page Extraction: add `PdfStudioDocument::mergeWith` and page-range operations.
- Encryption / Password Protection: integrate `QPdfDocument` password handling and encryption flags.
- Form Editing: add form-field annotations and an `AcroFormManager`.
- AI Assistant / Cloud Collaboration: keep these out of scope per the local-only milestone rule; data layer can be added later behind the existing manager facade.

Validation

- CMakeLists.txt references all new source/header/QML files and removes replaced PDF Viewer files.
- ApplicationManager maps application name "Baytevora PDF Studio" to window loading and File Manager PDF opening.
- WindowFrame maps "Baytevora PDF Studio" to `PdfStudioWindow.qml`.
- All QML uses BDL v2 tokens only.
- No leftover references to `PdfViewerApplication`, `PdfViewerManager`, or `PdfDocument`.

Milestone E — Baytevora Identity Integration (BII)

Overview

Milestone E wires the completed Baytevora Branding Repository v1.0 into the BOS desktop shell so every system surface, application icon, and About dialog presents a single, professional Baytevora identity. No logos, colors, or typography were redesigned; existing assets are consumed as-is.

Branding Architecture

- Baytevora Branding Repository v1.0 lives at `/workspace/app-cwh12h2q3ri9/tasks/Branding/` and contains 242 assets across 20 product families plus a starter icon set.
- `BrandingManager` (`include/bos/BrandingManager.h`, `src/BrandingManager.cpp`) is the single source of truth for all branding lookups.
- The default branding directory is compiled into the shell via `BAYTEVORA_BRANDING_DIR` and can be overridden at runtime with the `BAYTEVORA_BRANDING_DIR` environment variable.
- All image paths are resolved through `BrandingManager`; no QML or C++ code hardcodes asset paths.

BrandingManager Responsibilities

- Company and product names (`companyName`, `osName`, `osVersion`, `fullVersionLabel`, `poweredBy`).
- Product symbol / logo resolution by application name (`applicationSymbolUrl`, `applicationLogoUrl`, `applicationFaviconUrl`).
- Generic icon resolution (`iconUrl`).
- Wallpaper registration (`wallpaperUrl`, `availableWallpapers`).
- Future expansion: add a new product folder and update `BrandingManager` mapping.

Integration Flow

1. `Application::registerQmlTypes()` registers `BrandingManager` as a QML singleton (`BOS.Shell.BrandingManager`).
2. `Application::loadInterface()` resolves the default wallpaper through `BrandingManager::wallpaperUrl()` instead of a hardcoded path.
3. System QML screens use `BrandingManager` for the OS symbol, version label, and company name:
   - `LoginScreen`, `LockScreen`, `LauncherHeader`, `SettingsPage` About, `WindowFrame`, `TaskbarButton`, `RunningApps`, `LauncherButton`, `DesktopIcon`, `ApplicationCard`, `PowerMenuItem`.
4. Native application windows receive their official symbol via `WindowFrame` (which uses `applicationSymbolUrl(applicationName)`), and the launcher/taskbar use the same symbol lookup.
5. New branded screens are available as QML components:
   - `BootScreen`, `SplashScreen`, `ShutdownScreen`, `RestartScreen`, `InstallerScreen`, `AboutBosScreen`, `SystemInformationScreen`.
6. `ApplicationManager::registerPlaceholderApplications()` now stores official product names in `iconName` so the BrandingManager can resolve the correct symbol.
7. The default wallpaper is generated as `assets/wallpapers/default.jpg` and registered through `BrandingManager`.

Asset Locations

- Branding repository: `/workspace/app-cwh12h2q3ri9/tasks/Branding/`
- Default wallpaper: `/workspace/app-cwh12h2q3ri9/baytevora-os-main/desktop/shell/assets/wallpapers/default.jpg`
- Branding manager source: `baytevora-os-main/desktop/shell/src/BrandingManager.cpp`
- Branding manager header: `baytevora-os-main/desktop/shell/include/bos/BrandingManager.h`

Future Branding Workflow

1. Add new product assets under `tasks/Branding/XX_Product_Name/` following the existing file naming convention.
2. Add the folder and display name to `BrandingManager`’s constructor mapping.
3. Register the application name in `ApplicationManager` with the same product name as its `iconName`.
4. New wallpapers are automatically discovered by `BrandingManager::availableWallpapers()` when placed in the branding repository’s `assets/wallpapers/` directory.

Validation

- CMakeLists.txt includes `BrandingManager.h/.cpp` and the new QML screen files.
- Application icons resolve against the 20 product symbol folders.
- The default wallpaper is set through `BrandingManager`.
- No duplicate or broken asset references were introduced.

Developed By

Baytevora Labs

Motto: Secure by Design. Intelligent by Nature.
