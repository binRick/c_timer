#pragma once
#ifndef C_TIMER_C
#define C_TIMER_C
/**********************************/
#include "../include/c_timer.h"
/**********************************/
/////////////////////////////////
static struct timespec ct_start_time  = { 0, 0 };
static ct_node         *ct_stack      = NULL;
static ct_unit         ct_output_unit = ct_SECONDS;


/////////////////////////////////
void ct_set_unit(ct_unit unit) {
  ct_output_unit = unit;
}


void ct_start(char const *msg) {
  ct_node *new_node = (ct_node *)malloc(sizeof(ct_node));

  assert(new_node);

  clock_gettime(CLOCK_REALTIME, &(new_node->start_time));
  new_node->next = ct_stack;

  ct_stack = new_node;
}


char * ct_stop(const char *msg) {
  static struct timespec end_time;
  static double          elapsed_time;
  static char const      *unit = "s";

  assert(ct_stack);
  memcpy(&ct_start_time, &(ct_stack->start_time), sizeof(struct timespec));

  ct_node *old_top = ct_stack;

  ct_stack = ct_stack->next;
  free(old_top);

  clock_gettime(CLOCK_REALTIME, &end_time);
  elapsed_time = (end_time.tv_nsec - ct_start_time.tv_nsec) + (end_time.tv_sec - ct_start_time.tv_sec) * NANOSECONDS_PER_SECOND;

  switch (ct_output_unit) {
  case ct_SECONDS:
    unit          = "s";
    elapsed_time /= NANOSECONDS_PER_SECOND;
    break;
  case ct_MILLISECONDS:
    unit          = "ms";
    elapsed_time /= MILLISECONDS_PER_SECOND;
    break;
  case ct_MICROSECONDS:
    unit          = "us";
    elapsed_time /= MICROSECONDS_PER_SECOND;
    break;
  case ct_NANOSECONDS:
    unit = "ns";
    break;
    /* elapsed_time is already sorted. */
  }

  char *buf = malloc(1024);

  if (strlen(msg) < 1) {
    sprintf(buf, "%f%s", elapsed_time, unit);
  }else{
    sprintf(buf, "%s: %f%s", msg, elapsed_time, unit);
  }
  return(strdup(buf));
} // ct_stop

#endif
