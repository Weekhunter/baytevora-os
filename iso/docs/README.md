# Baytevora OS ISO Generation (BIG) — Milestone I

This directory contains the build infrastructure for creating the first
**real, bootable** Baytevora OS installation image (ISO) for Version 0.1 Alpha.
Starting with Milestone I the build uses a real Debian rootfs, a real Linux
kernel, a real initramfs, real GRUB images, a real SquashFS filesystem and
`xorriso` to produce a hybrid UEFI/BIOS ISO.

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

For the Alpha release the kernel, initramfs, and UEFI bootloader are **real**
Debian binaries generated automatically by the build scripts. No manual
`build-config.yaml` paths or placeholder files are required on a properly
configured Debian build host.

## Build Process

Run the build from the `iso/scripts` directory:

```bash
cd baytevora-os-main/iso/scripts
./build_iso.sh
```

`build_iso.sh` performs the following steps:

1. Loads `config/iso-config.json` and `config/build-config.yaml`.
2. Verifies that required real-ISO tools are installed (`debootstrap`, `chroot`,
   `mksquashfs`, `xorriso`, `grub-mkstandalone`).
3. Creates the root filesystem skeleton.
4. Runs the BLDF foundation scripts to build the Debian rootfs, configure the
   filesystem, install Baytevora components, configure the display manager,
   register applications, and enable services.
5. Installs the real Linux kernel, `initramfs-tools` and `live-boot` inside the
   chroot.
6. Generates the initramfs and copies `vmlinuz` + `initramfs.img` into `iso/boot/`.
7. Builds the GRUB EFI image (`EFI/BOOT/BOOTX64.EFI`) and the GRUB BIOS core
   image, and writes `boot/grub/grub.cfg`.
8. Creates a compressed SquashFS root filesystem at `iso/live/filesystem.squashfs`.
9. Assembles the hybrid bootable ISO image with `xorriso`.
10. Generates `version-manifest.json` and `build-info.json`.
11. Computes the SHA256 checksum.

The output artifacts are written to `iso/output/`.

## Filesystem Layout Inside the ISO

```
/
├── boot/
│   ├── grub/
│   │   ├── grub.cfg
│   │   └── bios.img
│   ├── vmlinuz
│   └── initramfs.img
├── EFI/
│   └── BOOT/
│       └── BOOTX64.EFI
└── live/
    └── filesystem.squashfs
```

The live root filesystem contains:

- `/opt/baytevora/desktop` — Baytevora Desktop Shell
- `/opt/baytevora/installer` — Baytevora OS Installer (BOI)
- `/usr/share/baytevora/branding` — Branding assets
- `/opt/baytevora/iso/scripts/live-init` — Reference live-init script
- `/opt/baytevora/services` — Storage, printing and application framework services
- `/usr/share/applications/baytevora-*.desktop` — Registered applications

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

- ISO output file exists and is a true ISO 9660 image.
- ISO size is reasonable for a real bootable image (>100 MB).
- SHA256 checksum is present and matches.
- `version-manifest.json` and `build-info.json` exist.
- `boot/grub/grub.cfg`, `boot/vmlinuz`, `boot/initramfs.img`,
  `EFI/BOOT/BOOTX64.EFI`, and `live/filesystem.squashfs` are present in the ISO.
- `boot/vmlinuz` and `boot/initramfs.img` are real binary files, not text
  placeholders.
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

### VirtualBox

1. Create a new VM: **Linux → Debian (64-bit)**.
2. Attach `iso/output/Baytevora-OS-0.1-Alpha.iso` to the optical drive.
3. In **System → Motherboard**, enable **EFI** for UEFI boot, or leave it
   disabled for legacy BIOS boot.
4. Start the VM. You should see:
   - GRUB menu → **Baytevora OS 0.1 Alpha**
   - Linux kernel boot messages
   - initramfs mounts `live/filesystem.squashfs`
   - systemd starts
   - SDDM auto-logs in the `live` user
   - Baytevora desktop session starts

### QEMU

```bash
qemu-system-x86_64 -cdrom output/Baytevora-OS-0.1-Alpha.iso \
    -boot d -m 4096 -enable-kvm
```

For UEFI firmware in QEMU, install `ovmf` and add `-bios /usr/share/ovmf/OVMF.fd`.

## Future Hooks

The architecture is ready for extension, but these features are **not**
implemented in Milestone I:

- Secure Boot and signed images.
- Recovery ISO and recovery boot entry.
- OEM ISO customization.
- Enterprise deployment ISO.
- Minimal ISO variant.
- Network installer / offline installer modes.
- Additional hypervisor validation (VMware, GNOME Boxes, Hyper-V).

## Constraints

- No BOS application was redesigned.
- No new applications were added.
- `BrandingManager` was not modified.
- The installer UI was not modified.
- Only the ISO build pipeline was changed; all prior milestone functionality is
  preserved.

## Milestones

### Milestone H2 — BLDF Integration

Starting with Milestone H2, the ISO build calls the Baytevora Linux Distribution Foundation scripts in `baytevora-os-main/foundation/`. This produces a Debian Stable-based live rootfs, system session, display manager auto-login, application registrations, and system services before ISO assembly.

### Milestone I — First Real Bootable ISO

Milestone I replaces placeholder kernel, initramfs, GRUB images, SquashFS and ISO assembly with real Debian tooling. The result is a hybrid UEFI/BIOS ISO that boots in VirtualBox, mounts the SquashFS live rootfs, starts systemd, reaches SDDM and launches the Baytevora desktop session.

