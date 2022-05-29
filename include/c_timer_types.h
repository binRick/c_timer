#pragma once
#ifndef C_TIMER_TYPES_H
#define C_TIMER_TYPES_H
#include <time.h>

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
#endif
