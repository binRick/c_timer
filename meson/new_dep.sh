#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
N="$1"
mkdir deps/$N
cp deps/template.build deps/$N/meson.build
gsed -i "s|__NAME__|$N|g" deps/$N/meson.build
