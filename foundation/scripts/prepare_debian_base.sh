#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Preserve externally supplied paths (e.g. from the ISO build).
ENV_TARGET_ROOT="${TARGET_ROOT:-}"
ENV_SOURCE_ROOT="${SOURCE_ROOT:-}"

# Load configuration
SOURCE_ROOT="$(cd "${FOUNDATION_DIR}/.." && pwd)"
TARGET_ROOT="${FOUNDATION_DIR}/rootfs"
PACKAGES_LIST="${FOUNDATION_DIR}/debian-base/packages.list"
SOURCES_LIST="${FOUNDATION_DIR}/debian-base/sources.list"
APT_PREFERENCES="${FOUNDATION_DIR}/debian-base/apt-preferences"

if [[ -f "${FOUNDATION_DIR}/config/foundation-config.yaml" ]]; then
    eval "$(python3 - <<'PY'
import yaml, os
path = os.environ.get('FOUNDATION_DIR') + '/config/foundation-config.yaml'
with open(path) as f:
    cfg = yaml.safe_load(f)
for k in ['sourceRoot', 'targetRoot', 'packagesListPath', 'sourcesListPath', 'aptPreferencesPath', 'debianMirror', 'debianVersion']:
    v = cfg.get(k, '')
    if v:
        name = k.upper().replace('PATH', '_PATH').replace('ROOT', '_ROOT')
        print(f'{name}="{v}"')
PY
    )"
fi

# Re-apply environment overrides after config loading.
TARGET_ROOT="${ENV_TARGET_ROOT:-$TARGET_ROOT}"
SOURCE_ROOT="${ENV_SOURCE_ROOT:-$SOURCE_ROOT}"


log_info() { echo "[INFO]  $*"; }
log_warn() { echo "[WARN]  $*"; }
log_error() { echo "[ERROR] $*" >&2; }

check_tool() { command -v "$1" >/dev/null 2>&1; }

mkdir -p "${TARGET_ROOT}"{/bin,/sbin,/lib,/lib64,/usr/bin,/usr/sbin,/usr/lib,/usr/share,/etc/apt/preferences.d,/var/lib/dpkg,/var/cache/apt,/var/log,/tmp,/run,/home,/root,/opt,/srv,/mnt,/media,/dev,/proc,/sys}

log_info "Configuring APT sources..."
cp "${SOURCES_LIST}" "${TARGET_ROOT}/etc/apt/sources.list"
cp "${APT_PREFERENCES}" "${TARGET_ROOT}/etc/apt/preferences.d/baytevora"

if check_tool debootstrap && check_tool chroot; then
    log_info "Attempting real Debian base installation with debootstrap..."
    if debootstrap stable "${TARGET_ROOT}" http://deb.debian.org/debian 2>/dev/null; then
        log_info "Debian base installed successfully."
        exit 0
    else
        log_warn "debootstrap failed; falling back to placeholder environment."
    fi
else
    log_warn "debootstrap/chroot not available; creating placeholder Debian base."
fi

log_info "Creating placeholder dpkg status..."
: > "${TARGET_ROOT}/var/lib/dpkg/status"
while IFS= read -r pkg || [[ -n "$pkg" ]]; do
    [[ -z "$pkg" || "$pkg" =~ ^# ]] && continue
    cat >> "${TARGET_ROOT}/var/lib/dpkg/status" <<EOF
Package: ${pkg}
Status: install ok installed
Version: 0.1-alpha
Description: placeholder package entry for Baytevora OS Alpha

EOF
done < "${PACKAGES_LIST}"

log_info "Creating placeholder essential tools..."
for tool in systemctl bash sh mount umount modprobe udevadm dbus-daemon NetworkManager pipewire cupsd sddm gdm3 apt-get dpkg; do
    cat > "${TARGET_ROOT}/usr/bin/${tool}" <<EOF
#!/bin/sh
# Placeholder for ${tool}
echo "[BOS PLACEHOLDER] ${tool} not functional in Alpha sandbox" >&2
exit 0
EOF
    chmod +x "${TARGET_ROOT}/usr/bin/${tool}"
done

# Create a minimal systemd placeholder so live-init can switch_root into systemd.
mkdir -p "${TARGET_ROOT}/usr/lib/systemd"
cat > "${TARGET_ROOT}/usr/lib/systemd/systemd" <<'EOF'
#!/bin/sh
# Placeholder systemd for Baytevora OS Alpha sandbox
echo "[BOS PLACEHOLDER] systemd not functional in Alpha sandbox" >&2
exec /bin/sh
EOF
chmod +x "${TARGET_ROOT}/usr/lib/systemd/systemd"
ln -sf /usr/lib/systemd/systemd "${TARGET_ROOT}/sbin/init"

log_info "Placeholder Debian base prepared at ${TARGET_ROOT}."
