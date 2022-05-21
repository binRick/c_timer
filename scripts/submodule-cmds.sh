#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
cd ../.
SUBMODULES_DIR=$(pwd)/submodules
GIT_CLONE_ARGS="--recurse-submodules"
[[ -d "$SUBMODULES_DIR" ]] || mkdir -p "$SUBMODULES_DIR"

get_modules() { grep 'url =' .gitmodules | cut -d= -f2 | gsed 's/[[:space:]]//g'; }
module_dirname() { printf '%s' "$1" | tr '/' '\n' | tail -n1; }
submodule_dirname() { printf '%s/%s' "$SUBMODULES_DIR" "$(module_dirname "$m")"; }
module_cmd() {
	printf '[[ -d "%s" ]] || { git clone "%s" "%s"; }\n' \
		"$(submodule_dirname "$1")" \
		"$1" \
		"$(submodule_dirname "$1")"
}
module_cmds() {
	while read -r m; do
		ansi >&2 --yellow --bg-black --italic "$(printf '%s\n' "$m")"
		printf '%s\n' "$(module_cmd "$m")"
	done < <(get_modules)
}

module_cmds
