#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Preserve externally supplied paths (e.g. from the ISO build).
ENV_TARGET_ROOT="${TARGET_ROOT:-}"
ENV_SOURCE_ROOT="${SOURCE_ROOT:-}"

SOURCE_ROOT="$(cd "${FOUNDATION_DIR}/.." && pwd)"
TARGET_ROOT="${FOUNDATION_DIR}/rootfs"

if [[ -f "${FOUNDATION_DIR}/config/foundation-config.yaml" ]]; then
    eval "$(python3 - <<'PY'
import yaml, os
path = os.environ.get('FOUNDATION_DIR') + '/config/foundation-config.yaml'
with open(path) as f:
    cfg = yaml.safe_load(f)
for k in ['sourceRoot', 'targetRoot']:
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
log_warn() { echo "[WARN]  $*"; }

copy_dir() {
    local src="$1" dst="$2"
    if [[ -d "$src" ]]; then
        rm -rf "$dst"
        mkdir -p "$dst"
        cp -a "$src/." "$dst/"
        log_info "  -> copied $(basename "$dst")"
    else
        log_warn "  -> source not found: $src"
    fi
}

mkdir -p "${TARGET_ROOT}/opt/baytevora"

copy_dir "${SOURCE_ROOT}/desktop/shell" "${TARGET_ROOT}/opt/baytevora/desktop"
copy_dir "${SOURCE_ROOT}/installer" "${TARGET_ROOT}/opt/baytevora/installer"

# Branding assets live at the project tasks/Branding directory.
PROJECT_ROOT="$(cd "${SOURCE_ROOT}/.." && pwd)"
copy_dir "${PROJECT_ROOT}/tasks/Branding" "${TARGET_ROOT}/usr/share/baytevora/branding"

mkdir -p "${TARGET_ROOT}/opt/baytevora/services"
[[ -d "${SOURCE_ROOT}/desktop/shell/services/storage" ]] && \
    copy_dir "${SOURCE_ROOT}/desktop/shell/services/storage" "${TARGET_ROOT}/opt/baytevora/services/storage"
[[ -d "${SOURCE_ROOT}/desktop/shell/services/printing" ]] && \
    copy_dir "${SOURCE_ROOT}/desktop/shell/services/printing" "${TARGET_ROOT}/opt/baytevora/services/printing"
[[ -d "${SOURCE_ROOT}/desktop/shell/services/application" ]] && \
    copy_dir "${SOURCE_ROOT}/desktop/shell/services/application" "${TARGET_ROOT}/opt/baytevora/services/application"

# Symlinks for common launchers
mkdir -p "${TARGET_ROOT}/usr/bin"
ln -sf /opt/baytevora/desktop/build/Baytevora_OS_Shell "${TARGET_ROOT}/usr/bin/baytevora-desktop" 2>/dev/null || true
ln -sf /opt/baytevora/installer/build/Baytevora_OS_Installer "${TARGET_ROOT}/usr/bin/baytevora-installer" 2>/dev/null || true

# Placeholder package manager backend hook
mkdir -p "${TARGET_ROOT}/usr/lib/baytevora"
cat > "${TARGET_ROOT}/usr/lib/baytevora/package-manager-backend" <<'EOF'
#!/bin/sh
# Baytevora Package Manager backend (Alpha read-only hook)
cat /var/lib/dpkg/status
EOF
chmod +x "${TARGET_ROOT}/usr/lib/baytevora/package-manager-backend"

# Component registry
python3 - <<PY
import json, os
registry = {
    "distribution": "debian",
    "version": "0.1 Alpha",
    "components": [
        {"name": "Desktop Shell", "version": "0.1"},
        {"name": "Installer", "version": "0.1"},
        {"name": "Branding", "version": "0.1"},
        {"name": "StorageManager", "version": "0.1"},
        {"name": "Printing Framework", "version": "0.1"},
        {"name": "Application Framework", "version": "0.1"}
    ]
}
path = os.environ['TARGET_ROOT'] + '/opt/baytevora/registry.json'
with open(path, 'w') as f:
    json.dump(registry, f, indent=2)
PY

log_info "Baytevora components installed to ${TARGET_ROOT}/opt/baytevora."
