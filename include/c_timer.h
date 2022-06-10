#pragma once
#ifndef C_TIMER_H
#define C_TIMER_H
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <time.h>
#include <unistd.h>
/////////////////////////////////
#define NANOSECONDS_PER_SECOND     1000000000
#define MICROSECONDS_PER_SECOND    1000000
#define MILLISECONDS_PER_SECOND    1000
/////////////////////////////////

typedef enum ct_unit {
  ct_SECONDS,
  ct_MILLISECONDS,
  ct_MICROSECONDS,
  ct_NANOSECONDS
} ct_unit;
typedef struct ct_node {
  struct timespec start_time;
  struct ct_node  *next;
} ct_node;
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
#ifndef OK
#define OK(MSG)    { fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }
#endif

void ct_set_unit(ct_unit unit);
void ct_start(char const *msg);
char * ct_stop(const char *msg);

#endif
