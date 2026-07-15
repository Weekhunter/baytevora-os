# Baytevora OS ISO Generation (BIG) — Milestone H

This directory contains the build infrastructure for creating the first
bootable Baytevora OS installation image (ISO) for Version 0.1 Alpha.

## Directory Layout

```
baytevora-os-main/iso/
├── boot/
│   └── grub/
│       └── grub.cfg          # GRUB2 bootloader configuration
├── EFI/
│   └── BOOT/
│       └── BOOTX64.EFI       # UEFI bootloader placeholder
├── filesystem/
│   ├── rootfs/               # Staging root filesystem
│   └── squashfs/             # Compressed root filesystem output
├── packages/                 # Component staging (reserved for future split packaging)
├── scripts/
│   ├── build_iso.sh          # Main ISO build orchestrator
│   ├── clean_iso.sh          # Remove build artifacts
│   ├── validate_iso.sh       # Validate generated ISO and staging tree
│   ├── prepare_filesystem.sh # Create rootfs directory skeleton
│   ├── generate_manifest.sh  # Create version and build manifests
│   └── live-init             # Live environment init script
├── output/
│   ├── Baytevora-OS-0.1-Alpha.iso
│   ├── Baytevora-OS-0.1-Alpha.iso.sha256
│   ├── build-info.json
│   └── version-manifest.json
├── docs/
│   └── README.md             # This file
├── include/big/              # C++ build system class headers
├── src/                      # C++ build system class implementations
├── config/
│   ├── build-config.yaml     # Build parameters
│   └── iso-config.json       # ISO metadata
└── CMakeLists.txt            # Optional Qt-based ISO generator tool
```

## Boot Flow

```
UEFI Firmware
      ↓
EFI/BOOT/BOOTX64.EFI (GRUB)
      ↓
GRUB reads boot/grub/grub.cfg
      ↓
Linux Kernel (boot/vmlinuz)
      ↓
initramfs (boot/initramfs.img)
      ↓
Live init script mounts squashfs rootfs
      ↓
Live BOS Environment starts
      ↓
Baytevora OS Installer launches
      ↓
Installation completes
      ↓
Reboot
      ↓
Installed BOS boots
      ↓
First Boot Wizard (Milestone F)
      ↓
Desktop session
```

For the Alpha release the kernel, initramfs, and UEFI bootloader are
placeholders. A production build supplies real binaries via
`config/build-config.yaml` or by installing `xorriso` and `grub-mkrescue` on
the build host so the scripts can create a true bootable ISO.

## Build Process

Run the build from the `iso/scripts` directory:

```bash
cd baytevora-os-main/iso/scripts
./build_iso.sh
```

`build_iso.sh` performs the following steps:

1. Loads `config/iso-config.json` and `config/build-config.yaml`.
2. Creates the root filesystem skeleton.
3. Copies the desktop shell, installer, and branding assets into
   `filesystem/rootfs/opt/baytevora/`.
4. Generates `boot/grub/grub.cfg`.
5. Places the kernel, initramfs, and UEFI bootloader files.
6. Creates a compressed root filesystem (squashfs if available, otherwise tar).
7. Assembles the ISO image with `xorriso` or `grub-mkrescue`; falls back to a
   packaged staging archive if neither tool is available.
8. Generates `version-manifest.json` and `build-info.json`.
9. Computes the SHA256 checksum.

The output artifacts are written to `iso/output/`.

## Filesystem Layout Inside the ISO

```
/
├── boot/
│   ├── grub/
│   │   └── grub.cfg
│   ├── vmlinuz
│   └── initramfs.img
├── EFI/
│   └── BOOT/
│       └── BOOTX64.EFI
├── filesystem/
│   └── squashfs/
│       └── rootfs.squashfs (or rootfs.tar.gz placeholder)
└── (top-level packaging tree when using fallback archive)
```

The live root filesystem contains:

- `/opt/baytevora/desktop-shell`
- `/opt/baytevora/installer`
- `/opt/baytevora/branding`
- `/opt/baytevora/iso/scripts/live-init`
- `/opt/baytevora/services` (reserved)
- `/opt/baytevora/applications` (reserved)

## Live Environment

Only the services required by the installer are auto-started in the live
environment:

- `StorageManager` is linked into the installer and detects available disks.
- `BrandingManager` is linked into the installer and provides branding assets.

The desktop shell, printing framework, application framework, and standalone
applications are present but are **not** started automatically; they become
available after the installer completes and the target system reboots.

## Validation

Run `validate_iso.sh` after building:

```bash
./scripts/validate_iso.sh
```

It checks:

- ISO output file exists.
- SHA256 checksum is present and matches.
- `version-manifest.json` and `build-info.json` exist.
- `boot/grub/grub.cfg`, `EFI/BOOT/BOOTX64.EFI`, and the compressed filesystem
  are present in the staging tree or ISO.
- Installer, branding, and desktop shell packages are present in `rootfs`.
- QEMU availability is reported (manual smoke boot test required when running
  in a sandbox without virtualization tooling).

## Clean Build Artifacts

```bash
./scripts/clean_iso.sh
```

This removes `filesystem/rootfs`, `filesystem/squashfs`, `boot/*`,
`EFI/BOOT/BOOTX64.EFI`, and `output/*` while preserving source,
configuration, and scripts.

## C++ Build Tool

An optional Qt-based orchestrator is provided in `include/big/` and `src/`.
Build it with CMake when Qt 6 is available:

```bash
cd baytevora-os-main/iso
mkdir build && cd build
cmake ..
make
./Baytevora_ISO_Generator
```

The shell scripts are the primary build interface for the Alpha release.

## Virtual Machine Testing

Verified compatibility is documented for **QEMU**. Example command:

```bash
qemu-system-x86_64 -cdrom output/Baytevora-OS-0.1-Alpha.iso \
    -boot d -m 4096 -enable-kvm
```

Future validation hooks include VirtualBox, VMware, and GNOME Boxes; these
are not exercised in the Alpha build.

## Future Hooks

The architecture is ready for extension, but these features are **not**
implemented in Milestone H:

- Secure Boot and signed images.
- Legacy BIOS boot support.
- Recovery ISO and recovery boot entry.
- OEM ISO customization.
- Enterprise deployment ISO.
- Minimal ISO variant.
- Network installer / offline installer modes.
- Additional hypervisor validation (VirtualBox, VMware, GNOME Boxes).

## Constraints

- No BOS application was redesigned.
- No new applications were added.
- `BrandingManager` was not modified.
- The installer UI was not modified.
- The build system is packaging-only and preserves all prior milestone
  functionality.

## Milestone H2 — BLDF Integration

Starting with Milestone H2, the ISO build calls the Baytevora Linux Distribution Foundation scripts in `baytevora-os-main/foundation/`. This produces a Debian Stable-based live rootfs, system session, display manager auto-login, application registrations, and system services before ISO assembly. See `baytevora-os-main/foundation/docs/README.md` for full details.

