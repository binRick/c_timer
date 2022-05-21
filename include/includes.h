#pragma once
#ifndef C_TIMER_INCLUDES_H
#define C_TIMER_INCLUDES_H
/////////////////////////////////////////////////////
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
/////////////////////////////////////////////////////
#include "../deps/b64/b64.h"
#include "../include/c_timer.h"
/////////////////////////////////////////////////////

#define OK(MSG)    { fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }

#endif
