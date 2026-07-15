#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ISO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
OUTPUT_DIR="${ISO_DIR}/output"
ISO_NAME="Baytevora-OS-0.1-Alpha.iso"
ISO_PATH="${OUTPUT_DIR}/${ISO_NAME}"

PASS=0
FAIL=0

log_pass() { echo "[PASS]  $*"; PASS=$((PASS + 1)); }
log_fail() { echo "[FAIL]  $*" >&2; FAIL=$((FAIL + 1)); }
log_info() { echo "[INFO]  $*"; }

if [[ ! -f "${ISO_PATH}" ]]; then
    log_fail "ISO file not found: ${ISO_PATH}"
else
    log_pass "ISO file exists: ${ISO_PATH}"
fi

if [[ -f "${ISO_PATH}.sha256" ]]; then
    log_pass "Checksum file exists"
    if (cd "${OUTPUT_DIR}" && sha256sum -c "${ISO_NAME}.sha256" >/dev/null 2>&1); then
        log_pass "SHA256 checksum matches"
    else
        log_fail "SHA256 checksum mismatch"
    fi
else
    log_fail "Checksum file missing"
fi

if [[ -f "${OUTPUT_DIR}/version-manifest.json" ]]; then
    log_pass "version-manifest.json exists"
else
    log_fail "version-manifest.json missing"
fi

if [[ -f "${OUTPUT_DIR}/build-info.json" ]]; then
    log_pass "build-info.json exists"
else
    log_fail "build-info.json missing"
fi

# Inspect the generated archive/ISO contents.
if command -v isoinfo >/dev/null 2>&1 && file "${ISO_PATH}" | grep -qi iso; then
    if isoinfo -i "${ISO_PATH}" -x /BOOT/GRUB/GRUB.CFG >/dev/null 2>&1; then
        log_pass "ISO contains boot/grub/grub.cfg"
    else
        log_fail "ISO missing boot/grub/grub.cfg"
    fi
    if isoinfo -i "${ISO_PATH}" -x /EFI/BOOT/BOOTX64.EFI >/dev/null 2>&1; then
        log_pass "ISO contains EFI/BOOT/BOOTX64.EFI"
    else
        log_fail "ISO missing EFI/BOOT/BOOTX64.EFI"
    fi
    if isoinfo -i "${ISO_PATH}" -x /FILESYSTEM/SQUASHFS/ROOTFS.SQUASHFS >/dev/null 2>&1 || \
       isoinfo -i "${ISO_PATH}" -x /FILESYSTEM/SQUASHFS/ROOTFS.TAR.GZ >/dev/null 2>&1; then
        log_pass "ISO contains compressed filesystem"
    else
        log_fail "ISO missing compressed filesystem"
    fi
else
    log_info "isoinfo not available or output is not a true ISO; checking staging tree instead"
    if [[ -f "${ISO_DIR}/boot/grub/grub.cfg" ]]; then
        log_pass "Staging boot/grub/grub.cfg exists"
    else
        log_fail "Staging boot/grub/grub.cfg missing"
    fi
    if [[ -f "${ISO_DIR}/EFI/BOOT/BOOTX64.EFI" ]]; then
        log_pass "Staging EFI/BOOT/BOOTX64.EFI exists"
    else
        log_fail "Staging EFI/BOOT/BOOTX64.EFI missing"
    fi
    if [[ -f "${ISO_DIR}/filesystem/squashfs/rootfs.squashfs" ]] || \
       [[ -f "${ISO_DIR}/filesystem/squashfs/rootfs.tar.gz" ]]; then
        log_pass "Staging compressed filesystem exists"
    else
        log_fail "Staging compressed filesystem missing"
    fi
fi

# Check installer and branding inside rootfs.
if [[ -d "${ISO_DIR}/filesystem/rootfs/opt/baytevora/installer" ]]; then
    log_pass "Installer package present in rootfs"
else
    log_fail "Installer package missing from rootfs"
fi

if [[ -d "${ISO_DIR}/filesystem/rootfs/usr/share/baytevora/branding" ]]; then
    log_pass "Branding assets present in rootfs"
else
    log_fail "Branding assets missing from rootfs"
fi

if [[ -d "${ISO_DIR}/filesystem/rootfs/opt/baytevora/desktop" ]]; then
    log_pass "Desktop shell present in rootfs"
else
    log_fail "Desktop shell missing from rootfs"
fi

# BLDF validation: Debian base, session, applications, services.
if [[ -f "${ISO_DIR}/filesystem/rootfs/etc/os-release" ]]; then
    log_pass "OS release file present in rootfs"
else
    log_fail "OS release file missing from rootfs"
fi

if [[ -f "${ISO_DIR}/filesystem/rootfs/usr/share/xsessions/Baytevora.desktop" ]]; then
    log_pass "Baytevora desktop session registered"
else
    log_fail "Baytevora desktop session missing"
fi

if [[ -x "${ISO_DIR}/filesystem/rootfs/usr/bin/baytevora-session" ]]; then
    log_pass "baytevora-session launcher present"
else
    log_fail "baytevora-session launcher missing"
fi

if [[ -f "${ISO_DIR}/filesystem/rootfs/usr/share/applications/baytevora-welcome.desktop" ]]; then
    log_pass "Application desktop entries present"
else
    log_fail "Application desktop entries missing"
fi

if [[ -f "${ISO_DIR}/filesystem/rootfs/etc/systemd/system/baytevora-storage.service" ]]; then
    log_pass "Baytevora service units present"
else
    log_fail "Baytevora service units missing"
fi

if grep -q "^live:" "${ISO_DIR}/filesystem/rootfs/etc/passwd" 2>/dev/null; then
    log_pass "Live user configured"
else
    log_fail "Live user not configured"
fi

# QEMU boot check is optional; qemu is not available in every build sandbox.
if command -v qemu-system-x86_64 >/dev/null 2>&1; then
    log_info "qemu-system-x86_64 found; run manual smoke boot test with:"
    log_info "  qemu-system-x86_64 -cdrom ${ISO_PATH} -boot d -m 4096"
else
    log_info "qemu-system-x86_64 not available; VM smoke test skipped"
fi

echo ""
echo "Validation complete: ${PASS} passed, ${FAIL} failed"
exit ${FAIL}
