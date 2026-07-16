#!/usr/bin/env bash
# configure_grub.sh — create GRUB configuration, GRUB EFI image and GRUB BIOS
# core image for the Baytevora OS ISO.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

ISO_DIR="${ISO_DIR:-}"
VOLUME_LABEL="${VOLUME_LABEL:-Baytevora OS}"
BOOT_TIMEOUT="${BOOT_TIMEOUT:-5}"

log_info() { echo "[INFO]  $*"; }
log_warn() { echo "[WARN]  $*"; }
log_error() { echo "[ERROR] $*" >&2; }

check_tool() { command -v "$1" >/dev/null 2>&1; }

if [[ -z "${ISO_DIR}" ]]; then
    log_error "ISO_DIR environment variable is not set"
    exit 1
fi

BOOT_DIR="${ISO_DIR}/boot"
GRUB_DIR="${BOOT_DIR}/grub"
EFI_DIR="${ISO_DIR}/EFI/BOOT"

mkdir -p "${GRUB_DIR}" "${EFI_DIR}"

log_info "Writing GRUB configuration..."
cat > "${GRUB_DIR}/grub.cfg" <<EOF
set timeout=${BOOT_TIMEOUT}
set default=0
set gfxpayload=keep

menuentry "${VOLUME_LABEL}" {
    linux /boot/vmlinuz boot=live quiet splash
    initrd /boot/initramfs.img
}

menuentry "${VOLUME_LABEL} (failsafe)" {
    linux /boot/vmlinuz boot=live noapic noapm nodma nomce nolapic nomodeset nosmp vga=normal
    initrd /boot/initramfs.img
}
EOF

# Standard GRUB modules needed for ISO boot.
GRUB_MODULES="part_gpt part_msdos fat iso9660 linux normal boot all_video configfile loopback chain efi_gop efi_uga gfxterm gettext"

# --- EFI boot image ---
if check_tool grub-mkstandalone; then
    log_info "Building GRUB EFI boot image..."
    grub-mkstandalone -O x86_64-efi \
        --modules="${GRUB_MODULES}" \
        -o "${EFI_DIR}/BOOTX64.EFI" \
        "boot/grub/grub.cfg=${GRUB_DIR}/grub.cfg"
else
    log_error "grub-mkstandalone not found. Install grub-common."
    exit 1
fi

# --- BIOS boot image ---
if check_tool grub-mkimage && [[ -f /usr/lib/grub/i386-pc/boot.img ]]; then
    log_info "Building GRUB BIOS core image..."
    grub-mkimage -O i386-pc \
        --prefix=/boot/grub \
        --modules="${GRUB_MODULES} biosdisk" \
        -c "${GRUB_DIR}/grub.cfg" \
        -o "${GRUB_DIR}/core.img"
    cat /usr/lib/grub/i386-pc/boot.img "${GRUB_DIR}/core.img" > "${GRUB_DIR}/bios.img"
    rm -f "${GRUB_DIR}/core.img"
else
    log_warn "grub-mkimage or /usr/lib/grub/i386-pc/boot.img missing; BIOS-only boot will not work."
    # Leave a marker so that assemble_iso.sh can decide to build an EFI-only ISO.
    : > "${GRUB_DIR}/bios.img.missing"
fi

log_info "GRUB configured at ${GRUB_DIR} and ${EFI_DIR}."
