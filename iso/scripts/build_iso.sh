#!/usr/bin/env bash
set -euo pipefail

# Baytevora OS ISO Build Script (Milestone I)
# Produces a real, bootable UEFI/BIOS hybrid ISO using debootstrap,
# a real Debian kernel/initramfs, GRUB, SquashFS and xorriso.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ISO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
SOURCE_ROOT="$(cd "${ISO_DIR}/.." && pwd)"
PROJECT_ROOT="$(cd "${SOURCE_ROOT}/.." && pwd)"

CONFIG_DIR="${ISO_DIR}/config"
OUTPUT_DIR="${ISO_DIR}/output"
BOOT_DIR="${ISO_DIR}/boot"
EFI_DIR="${ISO_DIR}/EFI/BOOT"
FS_DIR="${ISO_DIR}/filesystem"
ROOTFS_DIR="${FS_DIR}/rootfs"
LIVE_DIR="${ISO_DIR}/live"

ISO_NAME="Baytevora-OS-0.1-Alpha.iso"
ISO_PATH="${OUTPUT_DIR}/${ISO_NAME}"

log_info() { echo "[INFO]  $*"; }
log_warn() { echo "[WARN]  $*"; }
log_error() { echo "[ERROR] $*" >&2; }

check_tool() { command -v "$1" >/dev/null 2>&1; }

load_config() {
    log_info "Loading configuration..."
    if [[ ! -f "${CONFIG_DIR}/iso-config.json" ]]; then
        log_error "Missing ${CONFIG_DIR}/iso-config.json"
        exit 1
    fi
    if [[ ! -f "${CONFIG_DIR}/build-config.yaml" ]]; then
        log_error "Missing ${CONFIG_DIR}/build-config.yaml"
        exit 1
    fi

    VOLUME_LABEL="$(python3 -c 'import json,sys; print(json.load(open("'"${CONFIG_DIR}/iso-config.json"'")).get("volumeLabel",""))')"
    BOOT_TIMEOUT="$(python3 -c 'import json,sys; print(json.load(open("'"${CONFIG_DIR}/iso-config.json"'")).get("bootTimeout","5"))')"

    if [[ -z "${VOLUME_LABEL}" ]]; then
        log_error "Could not read volume label from iso-config.json"
        exit 1
    fi

    log_info "Volume label: ${VOLUME_LABEL}"
}

check_prerequisites() {
    local missing=""
    for tool in debootstrap chroot mksquashfs xorriso grub-mkstandalone; do
        if ! check_tool "${tool}"; then
            missing="${missing} ${tool}"
        fi
    done
    if [[ -n "${missing}" ]]; then
        log_error "This build requires real Linux ISO tooling that is not available in this environment."
        log_error "Missing tools:${missing}"
        log_error "Please run this script on a Debian build host with the packages listed in foundation/debian-base/packages.list installed."
        exit 1
    fi
}

prepare_filesystem() {
    log_info "Preparing staging filesystem skeleton..."
    bash "${SCRIPT_DIR}/prepare_filesystem.sh"
}

build_foundation() {
    log_info "Building Debian-based Baytevora OS foundation (BLDF)..."

    export TARGET_ROOT="${ROOTFS_DIR}"
    export SOURCE_ROOT="${SOURCE_ROOT}"

    bash "${SOURCE_ROOT}/foundation/scripts/prepare_debian_base.sh"
    bash "${SOURCE_ROOT}/foundation/scripts/configure_filesystem.sh"
    bash "${SOURCE_ROOT}/foundation/scripts/install_baytevora_components.sh"
    bash "${SOURCE_ROOT}/foundation/scripts/configure_display_manager.sh"
    bash "${SOURCE_ROOT}/foundation/scripts/register_applications.sh"
    bash "${SOURCE_ROOT}/foundation/scripts/configure_services.sh"

    # Installer autostart for the live user.
    mkdir -p "${ROOTFS_DIR}/home/live/.config/autostart"
    cat > "${ROOTFS_DIR}/home/live/.config/autostart/baytevora-installer.desktop" <<EOF
[Desktop Entry]
Name=Baytevora Installer
Comment=Install Baytevora OS
Exec=/usr/bin/baytevora-installer
Type=Application
Terminal=false
X-GNOME-Autostart-enabled=true
EOF

    # Keep the ISO-level live-init script inside the rootfs for reference.
    rm -rf "${ROOTFS_DIR}/opt/baytevora/iso"
    mkdir -p "${ROOTFS_DIR}/opt/baytevora/iso/scripts"
    cp -a "${ISO_DIR}/scripts/live-init" "${ROOTFS_DIR}/opt/baytevora/iso/scripts/live-init"
    chmod +x "${ROOTFS_DIR}/opt/baytevora/iso/scripts/live-init"

    log_info "  -> Foundation integrated"
}

install_kernel() {
    log_info "Installing real Linux kernel and live-boot packages..."
    export TARGET_ROOT="${ROOTFS_DIR}"
    bash "${SOURCE_ROOT}/foundation/scripts/install_kernel.sh"
}

generate_initramfs() {
    log_info "Generating initramfs..."
    export TARGET_ROOT="${ROOTFS_DIR}"
    export ISO_BOOT_DIR="${BOOT_DIR}"
    bash "${SOURCE_ROOT}/foundation/scripts/generate_initramfs.sh"
}

configure_grub() {
    log_info "Configuring GRUB EFI/BIOS bootloader..."
    export ISO_DIR VOLUME_LABEL BOOT_TIMEOUT
    bash "${SOURCE_ROOT}/foundation/scripts/configure_grub.sh"
}

create_squashfs() {
    log_info "Creating compressed SquashFS root filesystem..."
    export TARGET_ROOT="${ROOTFS_DIR}"
    export ISO_DIR
    bash "${SOURCE_ROOT}/foundation/scripts/generate_squashfs.sh"
}

assemble_iso() {
    log_info "Assembling bootable ISO image with xorriso..."
    export ISO_DIR ISO_PATH VOLUME_LABEL
    bash "${SOURCE_ROOT}/foundation/scripts/assemble_iso.sh"
}

generate_manifests() {
    log_info "Generating manifests..."
    bash "${SCRIPT_DIR}/generate_manifest.sh" "${VOLUME_LABEL}"
}

generate_checksum() {
    log_info "Generating SHA256 checksum..."
    if [[ -f "${ISO_PATH}" ]]; then
        (cd "${OUTPUT_DIR}" && sha256sum "${ISO_NAME}" > "${ISO_NAME}.sha256")
        log_info "  -> ${OUTPUT_DIR}/${ISO_NAME}.sha256"
    else
        log_warn "  -> ISO file not found, skipping checksum"
    fi
}

main() {
    log_info "Starting Baytevora OS ISO build (Milestone I)"
    log_info "ISO directory: ${ISO_DIR}"

    load_config
    check_prerequisites
    prepare_filesystem
    build_foundation
    install_kernel
    generate_initramfs
    configure_grub
    create_squashfs
    assemble_iso
    generate_manifests
    generate_checksum

    log_info "Build complete: ${ISO_PATH}"
}

main "$@"
