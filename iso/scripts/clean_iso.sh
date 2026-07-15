#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ISO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

log_info() { echo "[INFO]  $*"; }

log_info "Cleaning ISO build artifacts..."

rm -rf "${ISO_DIR}/filesystem/rootfs"
rm -rf "${ISO_DIR}/filesystem/squashfs"
rm -rf "${ISO_DIR}/boot/vmlinuz"
rm -rf "${ISO_DIR}/boot/initramfs.img"
rm -rf "${ISO_DIR}/EFI/BOOT/BOOTX64.EFI"
rm -rf "${ISO_DIR}/output"

log_info "Clean complete. Source, configuration, and scripts are preserved."
