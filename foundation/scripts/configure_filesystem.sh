#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export FOUNDATION_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Preserve externally supplied paths (e.g. from the ISO build).
ENV_TARGET_ROOT="${TARGET_ROOT:-}"
ENV_SOURCE_ROOT="${SOURCE_ROOT:-}"

TARGET_ROOT="${FOUNDATION_DIR}/rootfs"
HOSTNAME="baytevora-live"
LOCALE="en_US.UTF-8"
TIMEZONE="UTC"

if [[ -f "${FOUNDATION_DIR}/config/foundation-config.yaml" ]]; then
    eval "$(python3 - <<'PY'
import yaml, os
path = os.environ.get('FOUNDATION_DIR') + '/config/foundation-config.yaml'
with open(path) as f:
    cfg = yaml.safe_load(f)
for k in ['defaultHostname', 'defaultLocale', 'defaultTimezone', 'targetRoot']:
    v = cfg.get(k, '')
    if v:
        name = k.replace('default', '').upper()
        print(f'{name}="{v}"')
PY
    )"
fi

# Re-apply environment overrides after config loading.
TARGET_ROOT="${ENV_TARGET_ROOT:-$TARGET_ROOT}"
SOURCE_ROOT="${ENV_SOURCE_ROOT:-$SOURCE_ROOT}"


log_info() { echo "[INFO]  $*"; }

mkdir -p "${TARGET_ROOT}/etc"

cp "${FOUNDATION_DIR}/filesystem/etc/fstab.template" "${TARGET_ROOT}/etc/fstab"
cp "${FOUNDATION_DIR}/filesystem/etc/hostname.template" "${TARGET_ROOT}/etc/hostname"
sed "s/HOSTNAME_PLACEHOLDER/${HOSTNAME}/g" "${FOUNDATION_DIR}/filesystem/etc/hosts.template" > "${TARGET_ROOT}/etc/hosts"
cp "${FOUNDATION_DIR}/filesystem/etc/locale.gen.template" "${TARGET_ROOT}/etc/locale.gen"
cp "${FOUNDATION_DIR}/filesystem/etc/timezone.template" "${TARGET_ROOT}/etc/timezone"
cp "${FOUNDATION_DIR}/filesystem/etc/resolv.conf.template" "${TARGET_ROOT}/etc/resolv.conf"
cp "${FOUNDATION_DIR}/filesystem/etc/os-release.template" "${TARGET_ROOT}/etc/os-release"
cp "${FOUNDATION_DIR}/filesystem/etc/issue.template" "${TARGET_ROOT}/etc/issue"

cat > "${TARGET_ROOT}/etc/locale.conf" <<EOF
LANG=${LOCALE}
EOF

rm -f "${TARGET_ROOT}/etc/localtime"
ln -sf "/usr/share/zoneinfo/${TIMEZONE}" "${TARGET_ROOT}/etc/localtime"

mkdir -p "${TARGET_ROOT}/etc/sudoers.d"
cp "${FOUNDATION_DIR}/filesystem/etc/sudoers.d/live-user.template" "${TARGET_ROOT}/etc/sudoers.d/live-user"
chmod 440 "${TARGET_ROOT}/etc/sudoers.d/live-user"

log_info "Filesystem configured for ${HOSTNAME} (${LOCALE}, ${TIMEZONE})."
