#pragma once
#include "../include/includes.h"

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

