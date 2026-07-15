#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Preserve externally supplied paths (e.g. from the ISO build).
ENV_TARGET_ROOT="${TARGET_ROOT:-}"
ENV_SOURCE_ROOT="${SOURCE_ROOT:-}"

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

# Re-apply environment overrides after config loading.
TARGET_ROOT="${ENV_TARGET_ROOT:-$TARGET_ROOT}"
SOURCE_ROOT="${ENV_SOURCE_ROOT:-$SOURCE_ROOT}"


log_info() { echo "[INFO]  $*"; }

mkdir -p "${TARGET_ROOT}/etc/systemd/system"
mkdir -p "${TARGET_ROOT}/etc/NetworkManager"
mkdir -p "${TARGET_ROOT}/etc/pipewire"
mkdir -p "${TARGET_ROOT}/etc/cups"

cp "${FOUNDATION_DIR}/services/systemd/"*.service "${TARGET_ROOT}/etc/systemd/system/"
cp "${FOUNDATION_DIR}/services/config/NetworkManager.conf" "${TARGET_ROOT}/etc/NetworkManager/NetworkManager.conf"
cp "${FOUNDATION_DIR}/services/config/pipewire.conf" "${TARGET_ROOT}/etc/pipewire/pipewire.conf"
cp "${FOUNDATION_DIR}/services/config/cups.conf" "${TARGET_ROOT}/etc/cups/cupsd.conf"

# Create placeholder service executables if the real ones are missing.
for unit in baytevora-storage baytevora-printing baytevora-application; do
    exec_path="${TARGET_ROOT}/opt/baytevora/services/${unit#baytevora-}/${unit#baytevora-}-daemon"
    [[ "$unit" == "baytevora-application" ]] && exec_path="${TARGET_ROOT}/opt/baytevora/services/application/app-framework"
    mkdir -p "$(dirname "$exec_path")"
    if [[ ! -x "$exec_path" ]]; then
        cat > "$exec_path" <<EOF
#!/bin/sh
# Placeholder for ${unit}
exit 0
EOF
        chmod +x "$exec_path"
    fi
done

mkdir -p "${TARGET_ROOT}/etc/systemd/system/multi-user.target.wants"
for service in NetworkManager.service bluetooth.service cups.service systemd-timesyncd.service udisks2.service polkit.service sddm.service baytevora-storage.service baytevora-printing.service baytevora-application.service; do
    link="${TARGET_ROOT}/etc/systemd/system/multi-user.target.wants/${service}"
    source="${TARGET_ROOT}/etc/systemd/system/${service}"
    rm -f "$link"
    if [[ -f "$source" ]]; then
        ln -s "$source" "$link"
    else
        # Marker for sandbox validation without real systemd paths.
        : > "${link}.placeholder"
    fi
done

log_info "System services configured."
