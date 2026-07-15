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

mkdir -p "${TARGET_ROOT}/usr/share/applications"
mkdir -p "${TARGET_ROOT}/usr/share/mime/packages"
mkdir -p "${TARGET_ROOT}/usr/share/icons/baytevora"

cp -a "${FOUNDATION_DIR}/filesystem/usr/share/applications/." "${TARGET_ROOT}/usr/share/applications/"
cp "${FOUNDATION_DIR}/filesystem/usr/share/mime/packages/baytevora.xml" "${TARGET_ROOT}/usr/share/mime/packages/baytevora.xml"
cp -a "${FOUNDATION_DIR}/filesystem/usr/share/icons/baytevora/." "${TARGET_ROOT}/usr/share/icons/baytevora/"

log_info "Baytevora applications registered."
