# Baytevora Linux Distribution Foundation (BLDF) — Milestone H2

BLDF is the Linux distribution foundation that turns Baytevora OS from a standalone Qt/QML desktop project into a complete Debian Stable-based operating system. It is intentionally built **underneath** the existing Baytevora desktop, installer, applications, and branding without rewriting them.

## Table of Contents

1. [Architecture](#architecture)
2. [Directory Layout](#directory-layout)
3. [Boot Process](#boot-process)
4. [Root Filesystem](#root-filesystem)
5. [Package Layout](#package-layout)
6. [Desktop Session](#desktop-session)
7. [Application Registration](#application-registration)
8. [Service Architecture](#service-architecture)
9. [ISO Composition](#iso-composition)
10. [Building](#building)
11. [Validation](#validation)
12. [Future Roadmap](#future-roadmap)

## Architecture

```text
Baytevora Applications
        ↓
Baytevora Desktop
        ↓
Baytevora Frameworks
        ↓
       Qt 6
        ↓
Debian User Space
        ↓
    systemd
        ↓
  Linux Kernel
        ↓
    Hardware
```

- **Base distribution:** Debian Stable
- **Init system:** systemd
- **Display stack:** Wayland preferred, X11 compatibility fallback
- **Display manager:** SDDM (GDM alternative configuration included)
- **Session:** `Baytevora.desktop`
- **Package integration:** read-only dpkg status parsing in Alpha, APT hook for future releases

## Directory Layout

```text
foundation/
├── debian-base/            # Debian sources, package list, APT preferences
├── filesystem/             # Static rootfs files (fstab, session, .desktop entries, …)
├── services/               # systemd units and service configuration
├── display-manager/        # SDDM/GDM configuration
├── scripts/                # Shell scripts used by both C++ and ISO build
├── include/bldf/           # C++ class headers
├── src/                    # C++ class implementations
├── config/                 # foundation-config.yaml
├── docs/                   # This documentation
├── CMakeLists.txt          # C++ project
└── rootfs/                 # Build-time staging root filesystem
```

## Boot Process

1. UEFI firmware loads GRUB.
2. GRUB loads the Linux kernel and initramfs.
3. `live-init` mounts the ISO, then mounts the squashfs rootfs.
4. `switch_root` transfers control to `/sbin/init` (systemd).
5. systemd starts NetworkManager, PipeWire, CUPS, udisks2, polkit, and Baytevora services.
6. SDDM auto-logs in the `live` user and launches `Baytevora.desktop`.
7. The Baytevora Desktop starts and, in the live environment, autostarts the Installer.
8. After installation and reboot, the installed system starts systemd, the display manager, first-boot wizard, and then the desktop.

## Root Filesystem

The following standard Linux directories are created in the staging rootfs:

`/bin`, `/boot`, `/dev`, `/etc`, `/home`, `/lib`, `/lib64`, `/media`, `/mnt`, `/opt`, `/proc`, `/root`, `/run`, `/sbin`, `/srv`, `/sys`, `/tmp`, `/usr`, `/var`

## Package Layout

- `debian-base/packages.list` lists required Debian Stable packages.
- `debian-base/sources.list` configures official Debian repositories.
- `debian-base/apt-preferences` pins Debian Stable with priority 900.
- At build time, if `debootstrap` is available, a real Debian base is installed; otherwise a placeholder environment with dpkg status and stub binaries is generated.

## Desktop Session

- `/usr/share/xsessions/Baytevora.desktop` registers the Baytevora session.
- `/usr/bin/baytevora-session` sets Wayland/X11 environment variables and launches the desktop shell.
- SDDM is configured to auto-login `live` and run `Baytevora.desktop`.
- A GDM fallback configuration is also provided.

## Application Registration

Desktop entry files are installed under `/usr/share/applications/` for:

- PDF Studio
- Browser
- Store
- Settings
- Welcome Center

MIME type `application/x-baytevora` is registered in `/usr/share/mime/packages/baytevora.xml`.

## Service Architecture

systemd unit files in `/etc/systemd/system/`:

- `baytevora-storage.service`
- `baytevora-printing.service`
- `baytevora-application.service`

Configuration files:

- `/etc/NetworkManager/NetworkManager.conf`
- `/etc/pipewire/pipewire.conf`
- `/etc/cups/cupsd.conf`

All services are enabled for the `multi-user.target`.

## ISO Composition

The Milestone H ISO build is extended to include BLDF:

1. `prepare_filesystem.sh` creates the rootfs skeleton.
2. `build_foundation` runs the BLDF shell scripts.
3. GRUB configuration points the kernel to `live-init`.
4. Boot images (kernel, initramfs, UEFI bootloader) are staged.
5. The rootfs is compressed to squashfs (or tar.gz fallback).
6. `xorriso`, `grub-mkrescue`, or a tar fallback assembles the final ISO.
7. Manifests and SHA256 checksums are generated.

## Building

Run the foundation scripts individually:

```bash
cd /workspace/app-cwh12h2q3ri9/baytevora-os-main/foundation/scripts
export TARGET_ROOT=/tmp/bos-rootfs
./prepare_debian_base.sh
./configure_filesystem.sh
./install_baytevora_components.sh
./configure_display_manager.sh
./register_applications.sh
./configure_services.sh
./validate_foundation.sh
```

Or build the full ISO:

```bash
cd /workspace/app-cwh12h2q3ri9/baytevora-os-main/iso/scripts
./build_iso.sh
./validate_iso.sh
```

## Validation

- `validate_foundation.sh` checks the staged rootfs structure, configuration files, component installation, session registration, applications, services, and live user.
- `iso/scripts/validate_iso.sh` checks the generated ISO artifacts.
- In a real environment, the ISO is booted in QEMU/VMware to verify live boot, desktop launch, installer flow, installation, first-boot wizard, and shutdown/restart.

## Future Roadmap

- **Secure Boot:** signed shim + GRUB + kernel + modules
- **Automatic updates:** unattended-upgrades integration
- **Native BOS repositories:** custom APT repository and `.deb` packages for Baytevora components
- **Enterprise edition:** domain join, group policy, VPN
- **ARM64:** build rootfs and ISO for `aarch64`
- **Recovery mode:** GRUB rescue entry with repair tools
- **OEM deployment:** pre-installation customization tools
