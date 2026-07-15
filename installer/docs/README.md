# Baytevora OS Installer (BOI) — Milestone G

The Baytevora OS Installer is a standalone native application that guides the
user through installing Baytevora OS. It is built with Qt 6 / Qt Quick (QML) and
C++17 and lives under `baytevora-os-main/installer`.

## Architecture

```
installer/
├── include/boi/        # C++ headers
│   ├── InstallerApplication.h
│   ├── InstallerManager.h
│   ├── InstallerSession.h
│   ├── InstallationSummary.h
│   └── InstallationTarget.h
├── src/                # C++ implementation
├── qml/                # QML UI components
├── data/               # Bundled data (license text)
└── docs/               # Documentation
```

## Core Classes

### InstallerApplication
- Owns the Qt application object, QML engine, design-system singletons, and
  installer services.
- Registers the `BOI.Installer` QML module.
- Exposes `installerSession`, `installerManager`, and BDL v2 managers as
  context properties.
- Loads `InstallerWindow.qml` and runs the event loop.

### InstallerSession
- Holds the user's selections (language, keyboard, license acceptance,
  installation type, selected disk).
- Tracks the current wizard page and exposes `canGoNext` / `canGoBack`.
- Validates the current page before navigation.

### InstallerManager
- Drives the installation workflow.
- Validates disk selection against capacity and removable-media rules.
- Runs a staged installation process and reports progress via QML-bound
  properties.
- Supports cancellation and logging.
- For Alpha, each stage is a safe placeholder; the structure is ready for a
  future real partitioning/copy engine.

### InstallationTarget
- Value object describing the selected disk (name, model, filesystem,
  capacity, removable flag, validity).

### InstallationSummary
- Read-only data holder used by the review/summary page.

## Installation Lifecycle

1. **Startup** — `InstallerApplication` initializes design managers, storage
   manager, session, and manager. The disk list is refreshed immediately.
2. **Welcome / Language / Keyboard** — User selections are stored in
   `InstallerSession`.
3. **License** — The user must accept the bundled license text.
4. **Installation Type** — Only "Install Baytevora OS" is functional; the
   remaining options are disabled placeholders.
5. **Disk Selection** — Available disks come from the existing
   `StorageManager`. `InstallerManager.validateDisk()` enforces the minimum
   capacity and removable-media rules.
6. **Summary** — The user reviews choices and clicks **Install**.
7. **Installation Progress** — `InstallerManager.startInstallation()` runs the
   staged placeholder engine. Progress, status, and logs are displayed live.
8. **Completion** — On success, the installer shows **Restart Now** and
   **Restart Later**. System restart integration is a future hook.

## Integration with Existing Code

- **BrandingManager** (`desktop/shell/src/BrandingManager.cpp`) is reused for
  logos, OS name, and version strings.
- **StorageManager** (`desktop/shell/src/StorageManager.cpp`) is reused for
  disk detection.
- **BDL v2 managers** (`ThemeManager`, `TypographyManager`, `SpacingManager`,
  `DesignTokens`, `IconManager`, `AdaptiveLayoutManager`) are reused so the
  installer matches the desktop shell visually.

All reused sources are compiled into the installer target from the desktop
shell tree; no duplication is required.

## Ownership

- `InstallerApplication` owns all long-lived C++ objects.
- `InstallerSession` and `InstallerManager` are context properties; the engine
  does not take ownership of them.
- `InstallationTarget` instances are created from QML and may be owned by
  QML; the manager does not retain them after the installation finishes.

## Future Extension Points

- **Real installation engine**: Replace the placeholder steps in
  `InstallerManager::runCurrentStep()` with partition, format, copy, and
  bootloader operations.
- **Advanced partitioning**: Add a partition editor behind the
  "Manual Partitioning" installation type.
- **Dual boot**: Extend disk validation and bootloader configuration to
  coexist with other operating systems.
- **Encrypted installation / LVM / Btrfs snapshots**: Add new installation
  types and corresponding backend hooks.
- **Recovery mode / OEM / enterprise deployment**: Add boot flags or command
  line switches that change `InstallerSession` defaults and flow.
- **Network installation**: Replace local staging with a network source.

## Validation

Run `python3 tasks/validate_milestone_g.py` from the project root to verify
that the expected files, CMake entries, class methods, and QML components are
present.

## Notes

- The installer does **not** modify real disks in the Alpha release.
- No online activation, cloud accounts, or telemetry are implemented.
- Backward compatibility with Sprint 50 / Milestone F is maintained; the
  installer is a separate executable and does not change the desktop shell.
