default: all
##########################################################
all: \
	build \
	test
##########################################################
PWD="$(shell pwd)"
BUILD_DIR=$(PWD)/build
##########################################################
PMAN=$(BUILD_DIR)/c_timer
FIELD_RANGE_PARSER=$(BUILD_DIR)/field-range-parser
##########################################################
GC=$(GIT) clone --recurse-submodules
GET_COMMIT=$(GIT) log -q |grep '^commit '|head -n1|cut -d' ' -f2
##########################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
##########################################################
TEST_TITLE=$(BLINE) -a bold:underline:italic:yellow
HELP_STYLE=$(BLINE) -H -a ff00ff
##########################################################
DEV_MAKE_TARGETS = \
				   all
DEV_TEST_TARGETS = \
				   


##########################################################

enabled-bins:
	@\grep -H 'MESON_BIN_ENABLED=true' bins/*.c|cut -d: -f1|sort -u|xargs -I % basename % .c

dev: 
	@$(PASSH) -L .nodemon.log $(NODEMON) -I -V -w 'include/*.h' -w meson -w etc/tpl -w meson.build -w bins -w src -w Makefile -i build -i submodules -i deps -i 'include/embedded-*.h' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make $(DEV_MAKE_TARGETS) $(DEV_TEST_TARGETS)||true'

nodemon:
	@$(PASSH) make

clibs-cmds:
	@./scripts/clib-cmds.sh

submodules-cmds:
	@./scripts/submodules.sh

clibs-install:
	@./scripts/clib-cmds.sh|env bash

submodules-install:
	@./scripts/submodule-cmds.sh|env bash

setup: clibs-install submodules-install tools

tools:
	@command -v nodemon || npm i nodemon -g
	@command -v meson || pip install meson

build: 
	@[[ -d deps && -d submodules && -d .venv ]] || make setup
	@test -d $(BUILD_DIR) && {  meson $(BUILD_DIR) --reconfigure; } || { meson $(BUILD_DIR); }
	@ninja -C build

test:
	@meson test -C $(BUILD_DIR) --verbose

clean:
	@test -d $(BUILD_DIR) && rm -rf $(BUILD_DIR)

install:
	@echo Install OK

pull: git-pull clib build test

clib-update:
	@./update_commit.sh

git-pull:
	@git pull

git-commit:
	@git commit -am 'automated git commit'

push: tidy git-commit
	@git push

do-bins: make-bins

uncrustify:
	@uncrustify -c etc/uncrustify.cfg --replace bins/*.c
	@shfmt -w scripts/*.sh

uncrustify-clean:	
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

fix-dbg:
	@gsed 's|, % s);|, %s);|g' -i bins/*.c
	@gsed 's|, % lu);|, %lu);|g' -i bins/*.c
	@gsed 's|, % d);|, %d);|g' -i bins/*.c
	@gsed 's|, % zu);|, %zu);|g' -i bins/*.c

tidy: uncrustify fix-dbg uncrustify-clean
