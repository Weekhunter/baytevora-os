#!/usr/bin/env bash
set -euo pipefail

# Baytevora OS ISO Build Script (Milestone H)

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
SQUASHFS_DIR="${FS_DIR}/squashfs"

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

generate_grub_config() {
    log_info "Generating GRUB configuration..."
    mkdir -p "${BOOT_DIR}/grub"
    cat > "${BOOT_DIR}/grub/grub.cfg" <<EOF
set timeout=${BOOT_TIMEOUT}
set default=0
set gfxpayload=keep

menuentry "${VOLUME_LABEL}" {
    linux /boot/vmlinuz quiet splash root=/dev/ram0 init=/opt/baytevora/iso/scripts/live-init
    initrd /boot/initramfs.img
}

# Future hooks:
# menuentry "Boot existing OS" { ... }
# menuentry "Recovery mode" { ... }
# menuentry "Legacy BIOS" { ... }
EOF
    log_info "  -> ${BOOT_DIR}/grub/grub.cfg"
}

create_boot_images() {
    log_info "Preparing boot images..."
    mkdir -p "${BOOT_DIR}"
    mkdir -p "${EFI_DIR}"

    if check_tool vmlinuz_path; then
        : # placeholder; real path is set in build-config.yaml
    fi

    if [[ -f "${ISO_DIR}/../desktop/shell/build/Baytevora_OS_Shell" ]]; then
        log_info "  -> Using built shell binary as kernel placeholder is not appropriate"
    fi

    # Placeholder kernel and initramfs.
    echo "# Placeholder kernel - replace with real vmlinuz" > "${BOOT_DIR}/vmlinuz"
    echo "# Placeholder initramfs - replace with real initramfs" > "${BOOT_DIR}/initramfs.img"

    # Placeholder UEFI bootloader. Real build uses grub-mkimage or signed shim.
    echo "# Placeholder UEFI bootloader - replace with BOOTX64.EFI" > "${EFI_DIR}/BOOTX64.EFI"

    log_info "  -> Boot images prepared (placeholders)"
}

create_squashfs() {
    log_info "Creating compressed root filesystem..."
    mkdir -p "${SQUASHFS_DIR}"
    if check_tool mksquashfs; then
        mksquashfs "${ROOTFS_DIR}" "${SQUASHFS_DIR}/rootfs.squashfs" -noappend -comp xz
        log_info "  -> Squashfs image created"
    else
        tar -czf "${SQUASHFS_DIR}/rootfs.tar.gz" -C "${ROOTFS_DIR}" .
        log_warn "  -> mksquashfs not found; created ${SQUASHFS_DIR}/rootfs.tar.gz as placeholder"
    fi
}

assemble_iso() {
    log_info "Assembling ISO image..."
    mkdir -p "${OUTPUT_DIR}"

    if check_tool xorriso; then
        xorriso -as mkisofs \
            -iso-level 3 \
            -o "${ISO_PATH}" \
            -V "${VOLUME_LABEL}" \
            -J -R \
            -eltorito-boot boot/grub/grub.img \
            -no-emul-boot -boot-load-size 4 -boot-info-table \
            -eltorito-alt-boot -e EFI/BOOT/BOOTX64.EFI \
            -no-emul-boot -isohybrid-gpt-basdat \
            "${ISO_DIR}"
        log_info "  -> Bootable ISO created with xorriso"
    elif check_tool grub-mkrescue; then
        grub-mkrescue -o "${ISO_PATH}" "${ISO_DIR}"
        log_info "  -> Bootable ISO created with grub-mkrescue"
    else
        log_warn "  -> No ISO creation tool found (xorriso/grub-mkrescue); packaging staging tree into ${ISO_PATH}"
        tar -czf "${ISO_PATH}" --exclude='./output' --exclude='./filesystem/rootfs' --exclude='./filesystem/squashfs' -C "${ISO_DIR}" .
    fi
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
    log_info "Starting Baytevora OS ISO build"
    log_info "ISO directory: ${ISO_DIR}"

    load_config
    prepare_filesystem
    build_foundation
    generate_grub_config
    create_boot_images
    create_squashfs
    assemble_iso
    generate_manifests
    generate_checksum

    log_info "Build complete: ${ISO_PATH}"
}

main "$@"
