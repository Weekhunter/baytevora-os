#!/usr/bin/env bash
# install_kernel.sh — install a real Linux kernel, initramfs-tools and live-boot
# into the Baytevora root filesystem. Must run after prepare_debian_base.sh.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

ENV_TARGET_ROOT="${TARGET_ROOT:-}"
TARGET_ROOT="${FOUNDATION_DIR}/rootfs"

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
log_warn() { echo "[WARN]  $*"; }
log_error() { echo "[ERROR] $*" >&2; }

if [[ ! -d "${TARGET_ROOT}/bin" ]]; then
    log_error "Root filesystem not found at ${TARGET_ROOT}"
    exit 1
fi

mount_pseudo() {
    mkdir -p "${TARGET_ROOT}/dev" "${TARGET_ROOT}/proc" "${TARGET_ROOT}/sys" "${TARGET_ROOT}/run"
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

log_info "Installing kernel, initramfs-tools, live-boot and firmware..."
chroot "${TARGET_ROOT}" apt-get update
chroot "${TARGET_ROOT}" apt-get install -y --no-install-recommends \
    linux-image-amd64 \
    initramfs-tools \
    live-boot \
    live-config \
    firmware-linux-free \
    firmware-linux \
    firmware-misc-nonfree

# Ensure the live initramfs can mount ISO, SquashFS and overlay.
mkdir -p "${TARGET_ROOT}/etc/initramfs-tools"
cat > "${TARGET_ROOT}/etc/initramfs-tools/modules" <<'EOF'
squashfs
overlay
loop
isofs
sr_mod
cdrom
sd_mod
ext4
EOF

log_info "Kernel installed. Available images:"
ls -l "${TARGET_ROOT}/boot"/vmlinuz-* "${TARGET_ROOT}/boot"/initrd.img-* 2>/dev/null || true
