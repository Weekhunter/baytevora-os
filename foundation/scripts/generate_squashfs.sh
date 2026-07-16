#!/usr/bin/env bash
# generate_squashfs.sh — compress the live root filesystem into SquashFS.
set -euo pipefail

log_info() { echo "[INFO]  $*"; }
log_error() { echo "[ERROR] $*" >&2; }

check_tool() { command -v "$1" >/dev/null 2>&1; }

if [[ -z "${TARGET_ROOT:-}" ]]; then
    log_error "TARGET_ROOT environment variable is not set"
    exit 1
fi

if [[ -z "${ISO_DIR:-}" ]]; then
    log_error "ISO_DIR environment variable is not set"
    exit 1
fi

LIVE_DIR="${ISO_DIR}/live"
SQUASHFS_IMAGE="${LIVE_DIR}/filesystem.squashfs"

mkdir -p "${LIVE_DIR}"

if ! check_tool mksquashfs; then
    log_error "mksquashfs not found. Install squashfs-tools."
    exit 1
fi

log_info "Generating SquashFS image from ${TARGET_ROOT}..."
mksquashfs "${TARGET_ROOT}" "${SQUASHFS_IMAGE}" \
    -noappend \
    -comp xz \
    -e boot proc sys dev tmp run mnt media lost+found var/cache/apt var/lib/apt/lists

log_info "SquashFS image created at ${SQUASHFS_IMAGE}:"
ls -lh "${SQUASHFS_IMAGE}"
