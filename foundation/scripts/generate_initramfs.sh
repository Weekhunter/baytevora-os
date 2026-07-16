#!/usr/bin/env bash
# generate_initramfs.sh — build the initramfs inside the rootfs and copy the
# kernel + initramfs images into the ISO boot directory.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

ENV_TARGET_ROOT="${TARGET_ROOT:-}"
TARGET_ROOT="${FOUNDATION_DIR}/rootfs"
ISO_BOOT_DIR="${ISO_BOOT_DIR:-}"

if [[ -f "${FOUNDATION_DIR}/config/foundation-config.yaml" ]]; then
    eval "$(python3 - <<'PY'
import yaml, os
path = os.environ.get('FOUNDATION_DIR') + '/config/foundation-config.yaml'
with open(path) as f:
    cfg = yaml.safe_load(f)
for k in ['targetRoot']:
    v = cfg.get(k, '')
    if v:
        name = k.upper().replace('ROOT', '_ROOT')
        print(f'{name}="{v}"')
PY
    )"
fi

TARGET_ROOT="${ENV_TARGET_ROOT:-$TARGET_ROOT}"

log_info() { echo "[INFO]  $*"; }
log_error() { echo "[ERROR] $*" >&2; }

if [[ -z "${ISO_BOOT_DIR}" ]]; then
    log_error "ISO_BOOT_DIR environment variable is not set"
    exit 1
fi

mkdir -p "${ISO_BOOT_DIR}"

mount_pseudo() {
    mount --bind /dev "${TARGET_ROOT}/dev"
    mount --bind /proc "${TARGET_ROOT}/proc"
    mount --bind /sys "${TARGET_ROOT}/sys"
    mount --bind /run "${TARGET_ROOT}/run"
}

unmount_pseudo() {
    umount -l "${TARGET_ROOT}/dev" 2>/dev/null || true
    umount -l "${TARGET_ROOT}/proc" 2>/dev/null || true
    umount -l "${TARGET_ROOT}/sys" 2>/dev/null || true
    umount -l "${TARGET_ROOT}/run" 2>/dev/null || true
}

trap unmount_pseudo EXIT
mount_pseudo

log_info "Generating initramfs inside rootfs..."
chroot "${TARGET_ROOT}" update-initramfs -c -k all

# Identify the newest kernel/initramfs pair.
KERNEL_IMAGE="$(ls -1 "${TARGET_ROOT}/boot"/vmlinuz-* | sort -V | tail -n 1)"
INITRAMFS_IMAGE="$(ls -1 "${TARGET_ROOT}/boot"/initrd.img-* | sort -V | tail -n 1)"

if [[ ! -f "${KERNEL_IMAGE}" || ! -f "${INITRAMFS_IMAGE}" ]]; then
    log_error "Could not find generated kernel or initramfs in ${TARGET_ROOT}/boot"
    exit 1
fi

cp "${KERNEL_IMAGE}" "${ISO_BOOT_DIR}/vmlinuz"
cp "${INITRAMFS_IMAGE}" "${ISO_BOOT_DIR}/initramfs.img"

log_info "Kernel and initramfs copied to ${ISO_BOOT_DIR}:"
ls -lh "${ISO_BOOT_DIR}/vmlinuz" "${ISO_BOOT_DIR}/initramfs.img"
