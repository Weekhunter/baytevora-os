#!/usr/bin/env bash
# validate_iso.sh — verify that the generated ISO is a real bootable image.
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

is_true_iso() {
    command -v file >/dev/null 2>&1 && file "${ISO_PATH}" | grep -qi "iso 9660"
}

iso_has() {
    local path="$1"
    if command -v isoinfo >/dev/null 2>&1 && is_true_iso; then
        isoinfo -i "${ISO_PATH}" -x "${path}" >/dev/null 2>&1
    else
        return 1
    fi
}

if [[ ! -f "${ISO_PATH}" ]]; then
    log_fail "ISO file not found: ${ISO_PATH}"
else
    log_pass "ISO file exists: ${ISO_PATH}"
fi

# A real bootable ISO should be ISO 9660 and larger than a placeholder.
if [[ -f "${ISO_PATH}" ]]; then
    ISO_SIZE="$(stat -c%s "${ISO_PATH}" 2>/dev/null || echo 0)"
    if is_true_iso; then
        log_pass "ISO is a true ISO 9660 image"
    else
        log_fail "ISO is not a true ISO 9660 image (got placeholder?)"
    fi
    if [[ "${ISO_SIZE}" -gt 104857600 ]]; then
        log_pass "ISO size looks reasonable (${ISO_SIZE} bytes)"
    else
        log_warn "ISO size is only ${ISO_SIZE} bytes; a real image should be >100 MB"
    fi
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

# Real ISO contents.
if iso_has /BOOT/GRUB/GRUB.CFG; then
    log_pass "ISO contains boot/grub/grub.cfg"
else
    log_fail "ISO missing boot/grub/grub.cfg"
fi

if iso_has /BOOT/VMLINUZ; then
    log_pass "ISO contains boot/vmlinuz"
else
    log_fail "ISO missing boot/vmlinuz"
fi

if iso_has /BOOT/INITRAMFS.IMG; then
    log_pass "ISO contains boot/initramfs.img"
else
    log_fail "ISO missing boot/initramfs.img"
fi

if iso_has /EFI/BOOT/BOOTX64.EFI; then
    log_pass "ISO contains EFI/BOOT/BOOTX64.EFI"
else
    log_fail "ISO missing EFI/BOOT/BOOTX64.EFI"
fi

if iso_has /LIVE/FILESYSTEM.SQUASHFS; then
    log_pass "ISO contains live/filesystem.squashfs"
else
    log_fail "ISO missing live/filesystem.squashfs"
fi

# Boot images must not be placeholder text files.
if [[ -f "${ISO_DIR}/boot/vmlinuz" && ! "$(file -b "${ISO_DIR}/boot/vmlinuz")" =~ ASCII ]]; then
    log_pass "boot/vmlinuz is a real kernel image"
elif [[ -f "${ISO_DIR}/boot/vmlinuz" ]]; then
    log_fail "boot/vmlinuz is still a placeholder"
fi

if [[ -f "${ISO_DIR}/boot/initramfs.img" && ! "$(file -b "${ISO_DIR}/boot/initramfs.img")" =~ ASCII ]]; then
    log_pass "boot/initramfs.img is a real initramfs"
elif [[ -f "${ISO_DIR}/boot/initramfs.img" ]]; then
    log_fail "boot/initramfs.img is still a placeholder"
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

# QEMU/VirtualBox smoke test note.
if command -v qemu-system-x86_64 >/dev/null 2>&1; then
    log_info "qemu-system-x86_64 found; run manual smoke boot test with:"
    log_info "  qemu-system-x86_64 -cdrom ${ISO_PATH} -boot d -m 4096"
else
    log_info "qemu-system-x86_64 not available; VM smoke test must be run manually on a build host"
fi

echo ""
echo "Validation complete: ${PASS} passed, ${FAIL} failed"
exit ${FAIL}
