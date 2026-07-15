#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
# Preserve externally supplied paths (e.g. from the ISO build).
ENV_TARGET_ROOT="${TARGET_ROOT:-}"
ENV_SOURCE_ROOT="${SOURCE_ROOT:-}"

TARGET_ROOT="${FOUNDATION_DIR}/rootfs"

PASS=0
FAIL=0

log_pass() { echo "[PASS]  $*"; PASS=$((PASS + 1)); }
log_fail() { echo "[FAIL]  $*" >&2; FAIL=$((FAIL + 1)); }
log_info() { echo "[INFO]  $*"; }

# Root filesystem directories
for dir in bin sbin lib lib64 usr etc var tmp run home root opt srv mnt media dev proc sys; do
    if [[ -d "${TARGET_ROOT}/${dir}" ]]; then
        log_pass "Rootfs directory /${dir} exists"
    else
        log_fail "Rootfs directory /${dir} missing"
    fi
done

# Debian base markers
if [[ -f "${TARGET_ROOT}/etc/apt/sources.list" ]]; then
    log_pass "APT sources configured"
else
    log_fail "APT sources missing"
fi

if [[ -f "${TARGET_ROOT}/var/lib/dpkg/status" ]]; then
    log_pass "dpkg status file exists"
else
    log_fail "dpkg status file missing"
fi

# Filesystem configuration
for f in fstab hostname hosts locale.gen timezone resolv.conf os-release issue sudoers.d/live-user; do
    if [[ -f "${TARGET_ROOT}/etc/${f}" ]]; then
        log_pass "Configuration /etc/${f} exists"
    else
        log_fail "Configuration /etc/${f} missing"
    fi
done

# Baytevora components
for component in desktop installer; do
    if [[ -d "${TARGET_ROOT}/opt/baytevora/${component}" ]]; then
        log_pass "Component /opt/baytevora/${component} installed"
    else
        log_fail "Component /opt/baytevora/${component} missing"
    fi
done

if [[ -d "${TARGET_ROOT}/usr/share/baytevora/branding" ]]; then
    log_pass "Branding assets installed"
else
    log_fail "Branding assets missing"
fi

if [[ -f "${TARGET_ROOT}/opt/baytevora/registry.json" ]]; then
    log_pass "Component registry exists"
else
    log_fail "Component registry missing"
fi

# Session and display manager
if [[ -f "${TARGET_ROOT}/usr/share/xsessions/Baytevora.desktop" ]]; then
    log_pass "Baytevora.desktop session file exists"
else
    log_fail "Baytevora.desktop session file missing"
fi

if [[ -x "${TARGET_ROOT}/usr/bin/baytevora-session" ]]; then
    log_pass "baytevora-session launcher exists"
else
    log_fail "baytevora-session launcher missing"
fi

if [[ -f "${TARGET_ROOT}/etc/sddm/sddm.conf" ]]; then
    log_pass "SDDM configured"
else
    log_fail "SDDM configuration missing"
fi

# Applications
for app in baytevora-pdf-studio baytevora-browser baytevora-store baytevora-settings baytevora-welcome; do
    if [[ -f "${TARGET_ROOT}/usr/share/applications/${app}.desktop" ]]; then
        log_pass "Desktop entry ${app}.desktop exists"
    else
        log_fail "Desktop entry ${app}.desktop missing"
    fi
done

# Services
for unit in baytevora-storage.service baytevora-printing.service baytevora-application.service; do
    if [[ -f "${TARGET_ROOT}/etc/systemd/system/${unit}" ]]; then
        log_pass "Service unit ${unit} exists"
    else
        log_fail "Service unit ${unit} missing"
    fi
done

for conf in NetworkManager/NetworkManager.conf pipewire/pipewire.conf cups/cupsd.conf; do
    if [[ -f "${TARGET_ROOT}/etc/${conf}" ]]; then
        log_pass "Service config /etc/${conf} exists"
    else
        log_fail "Service config /etc/${conf} missing"
    fi
done

# Live user
if grep -q "^live:" "${TARGET_ROOT}/etc/passwd" 2>/dev/null; then
    log_pass "Live user configured"
else
    log_fail "Live user not configured"
fi

# Hardware support via udev rules placeholder
mkdir -p "${TARGET_ROOT}/etc/udev/rules.d"
if [[ -f "${TARGET_ROOT}/etc/udev/rules.d/99-baytevora.rules" ]] || true; then
    log_info "udev rules directory ready"
fi

echo ""
echo "Foundation validation complete: ${PASS} passed, ${FAIL} failed"
exit ${FAIL}
