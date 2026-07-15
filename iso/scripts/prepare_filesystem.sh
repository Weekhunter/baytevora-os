#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ISO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
ROOTFS_DIR="${ISO_DIR}/filesystem/rootfs"

log_info() { echo "[INFO]  $*"; }

log_info "Creating root filesystem directories..."

mkdir -p "${ROOTFS_DIR}"/{bin,lib,lib64,usr,etc,var,home,opt,srv,tmp,run,root,boot,sysroot}
mkdir -p "${ROOTFS_DIR}/usr"/{bin,lib,share,local}
mkdir -p "${ROOTFS_DIR}/etc"/{init.d,default,sysconfig}
mkdir -p "${ROOTFS_DIR}/var"/{log,tmp,run}

# Placeholder compatibility symlinks.
ln -sf /run "${ROOTFS_DIR}/var/run" 2>/dev/null || true
ln -sf /run/lock "${ROOTFS_DIR}/var/lock" 2>/dev/null || true

# Minimal init compatibility marker.
: > "${ROOTFS_DIR}/etc/baytevora-release"
echo "Baytevora OS 0.1 Alpha" > "${ROOTFS_DIR}/etc/baytevora-release"

log_info "Root filesystem prepared at ${ROOTFS_DIR}"
