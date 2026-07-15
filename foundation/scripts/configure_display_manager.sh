#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Preserve externally supplied paths (e.g. from the ISO build).
ENV_TARGET_ROOT="${TARGET_ROOT:-}"
ENV_SOURCE_ROOT="${SOURCE_ROOT:-}"

TARGET_ROOT="${FOUNDATION_DIR}/rootfs"
LIVE_USER="live"

if [[ -f "${FOUNDATION_DIR}/config/foundation-config.yaml" ]]; then
    eval "$(python3 - <<'PY'
import yaml, os
path = os.environ.get('FOUNDATION_DIR') + '/config/foundation-config.yaml'
with open(path) as f:
    cfg = yaml.safe_load(f)
for k in ['targetRoot', 'liveUser']:
    v = cfg.get(k, '')
    if v:
        name = k.upper().replace('ROOT', '_ROOT')
        print(f'{name}="{v}"')
PY
    )"
fi

# Re-apply environment overrides after config loading.
TARGET_ROOT="${ENV_TARGET_ROOT:-$TARGET_ROOT}"
SOURCE_ROOT="${ENV_SOURCE_ROOT:-$SOURCE_ROOT}"


log_info() { echo "[INFO]  $*"; }

mkdir -p "${TARGET_ROOT}/usr/share/xsessions"
mkdir -p "${TARGET_ROOT}/usr/bin"
mkdir -p "${TARGET_ROOT}/etc/sddm"
mkdir -p "${TARGET_ROOT}/etc/gdm3"

cp "${FOUNDATION_DIR}/filesystem/usr/share/xsessions/Baytevora.desktop" "${TARGET_ROOT}/usr/share/xsessions/Baytevora.desktop"
rm -f "${TARGET_ROOT}/usr/bin/baytevora-session"
cp "${FOUNDATION_DIR}/filesystem/usr/bin/baytevora-session" "${TARGET_ROOT}/usr/bin/baytevora-session"
chmod +x "${TARGET_ROOT}/usr/bin/baytevora-session"
rm -f "${TARGET_ROOT}/usr/bin/baytevora-installer"
cp "${FOUNDATION_DIR}/filesystem/usr/bin/baytevora-installer" "${TARGET_ROOT}/usr/bin/baytevora-installer"
chmod +x "${TARGET_ROOT}/usr/bin/baytevora-installer"

cp "${FOUNDATION_DIR}/display-manager/sddm.conf" "${TARGET_ROOT}/etc/sddm/sddm.conf"
cp "${FOUNDATION_DIR}/display-manager/gdm.conf" "${TARGET_ROOT}/etc/gdm3/custom.conf"

# Create live user
mkdir -p "${TARGET_ROOT}/home/${LIVE_USER}"

append_if_missing() {
    local file="$1" line="$2"
    local user="${line%%:*}"
    if [[ -f "$file" ]] && grep -q "^${user}:" "$file" 2>/dev/null; then
        return
    fi
    echo "$line" >> "$file"
}

append_if_missing "${TARGET_ROOT}/etc/passwd" "${LIVE_USER}:x:1000:1000:Live User:/home/${LIVE_USER}:/bin/bash"
append_if_missing "${TARGET_ROOT}/etc/group" "live:x:1000:"
append_if_missing "${TARGET_ROOT}/etc/group" "sudo:x:27:${LIVE_USER}"
append_if_missing "${TARGET_ROOT}/etc/shadow" "${LIVE_USER}:!:0:0:99999:7:::"

log_info "Display manager configured for ${LIVE_USER} auto-login into Baytevora session."
