#pragma once
#define _DEFAULT_SOURCE
#define ASSERTF_DEF_ONCE
/////////////////////////////////////////////////////
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <getopt.h>
#include <glob.h>
#include <inttypes.h>
#include <libgen.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sysexits.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>
/////////////////////////////////////////////////////
#include "../deps/b64/b64.h"
/////////////////////////////////////////////////////

#define OK(MSG){ fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }







