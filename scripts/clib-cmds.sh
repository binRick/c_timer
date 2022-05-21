#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
cd ../.
CLIB_JSON=$(pwd)/clib.json
CLIBS_DIR=$(pwd)/deps

[[ -d "$CLIBS_DIR" ]] || mkdir -p "$CLIBS_DIR"

extract_clibs() {
	jq -M '.dependencies' | cut -d'"' -f2 | grep '^[a-z]' | gsed 's/[[:space:]]//g'
}
get_clibs() {
	extract_clibs <"$CLIB_JSON"
}

clib_name() { printf '%s' "$1" | tr '/' '\n' | tail -n1; }
clib_dirname() { printf '%s/%s' "$CLIBS_DIR" "$(clib_name "$m")"; }

clib_cmd() {
	printf '[[ -d "%s/%s" ]] || { clib i "%s"; }' \
		"$CLIBS_DIR" \
		"$(clib_name "$1")" \
		"$1"
}

clib_cmds() {
	while read -r m; do
		ansi >&2 --yellow --bg-black --italic "$(printf '%s\n' "$m")"
		printf '%s\n' "$(clib_cmd "$m")"
	done < <(get_clibs)
}

clib_cmds
