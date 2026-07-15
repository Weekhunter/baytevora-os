#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ISO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
OUTPUT_DIR="${ISO_DIR}/output"

VOLUME_LABEL="${1:-Baytevora OS 0.1 Alpha}"
TIMESTAMP="$(date -u +%Y-%m-%dT%H:%M:%SZ)"
KERNEL_VERSION="unknown"

mkdir -p "${OUTPUT_DIR}"

python3 - <<PY
import json
import os
from datetime import datetime

output_dir = os.environ.get("OUTPUT_DIR", "${OUTPUT_DIR}")
volume_label = """${VOLUME_LABEL}"""
timestamp = """${TIMESTAMP}"""
kernel_version = """${KERNEL_VERSION}"""

components = [
    {"name": "Desktop Shell", "version": "0.1", "path": "/opt/baytevora/desktop-shell"},
    {"name": "Installer", "version": "0.1", "path": "/opt/baytevora/installer"},
    {"name": "BrandingManager", "version": "0.1", "path": "/opt/baytevora/branding"},
    {"name": "StorageManager", "version": "0.1"},
    {"name": "Printing Framework", "version": "0.1"},
    {"name": "Application Framework", "version": "0.1"},
    {"name": "Welcome Center", "version": "0.1"},
    {"name": "PDF Studio", "version": "future"},
    {"name": "Browser", "version": "future"},
    {"name": "Store", "version": "future"},
    {"name": "Settings", "version": "future"}
]

manifest = {
    "version": "0.1 Alpha",
    "buildTimestamp": timestamp,
    "kernelVersion": kernel_version,
    "components": components
}

build_info = {
    "version": "0.1 Alpha",
    "buildTimestamp": timestamp,
    "buildHost": "Baytevora Build System",
    "kernelVersion": kernel_version,
    "parameters": {
        "volumeLabel": volume_label,
        "bootMode": "UEFI",
        "filesystemType": "squashfs",
        "compressionLevel": 9,
        "sourceRoot": "/workspace/app-cwh12h2q3ri9/baytevora-os-main",
        "outputDir": "/workspace/app-cwh12h2q3ri9/baytevora-os-main/iso"
    }
}

with open(os.path.join(output_dir, "version-manifest.json"), "w") as f:
    json.dump(manifest, f, indent=2)

with open(os.path.join(output_dir, "build-info.json"), "w") as f:
    json.dump(build_info, f, indent=2)

print("Manifests generated.")
PY
