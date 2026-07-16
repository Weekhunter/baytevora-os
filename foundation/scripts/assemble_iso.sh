#!/usr/bin/env bash
# assemble_iso.sh — create a hybrid UEFI/BIOS bootable ISO from the staging tree.
set -euo pipefail

log_info() { echo "[INFO]  $*"; }
log_warn() { echo "[WARN]  $*"; }
log_error() { echo "[ERROR] $*" >&2; }

check_tool() { command -v "$1" >/dev/null 2>&1; }

if [[ -z "${ISO_DIR:-}" ]]; then
    log_error "ISO_DIR environment variable is not set"
    exit 1
fi

if [[ -z "${ISO_PATH:-}" ]]; then
    log_error "ISO_PATH environment variable is not set"
    exit 1
fi

if [[ -z "${VOLUME_LABEL:-}" ]]; then
    log_error "VOLUME_LABEL environment variable is not set"
    exit 1
fi

if ! check_tool xorriso; then
    log_error "xorriso not found. Install xorriso."
    exit 1
fi

mkdir -p "$(dirname "${ISO_PATH}")"

if [[ -f "${ISO_DIR}/boot/grub/bios.img" ]]; then
    log_info "Building hybrid UEFI+BIOS ISO with xorriso..."
    xorriso -as mkisofs \
        -iso-level 3 \
        -full-iso9660-filenames \
        -joliet -joliet-long -rational-rock \
        -V "${VOLUME_LABEL}" \
        -A "Baytevora-OS-Installer" \
        -P "Baytevora Project" \
        -b boot/grub/bios.img \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --eltorito-alt-boot \
        -e EFI/BOOT/BOOTX64.EFI \
        -no-emul-boot -isohybrid-gpt-basdat \
        -o "${ISO_PATH}" \
        "${ISO_DIR}"
else
    log_warn "No BIOS boot image; building EFI-only ISO."
    xorriso -as mkisofs \
        -iso-level 3 \
        -full-iso9660-filenames \
        -joliet -joliet-long -rational-rock \
        -V "${VOLUME_LABEL}" \
        -A "Baytevora-OS-Installer" \
        -P "Baytevora Project" \
        -e EFI/BOOT/BOOTX64.EFI \
        -no-emul-boot -isohybrid-gpt-basdat \
        -o "${ISO_PATH}" \
        "${ISO_DIR}"
fi

log_info "Bootable ISO created at ${ISO_PATH}:"
ls -lh "${ISO_PATH}"
