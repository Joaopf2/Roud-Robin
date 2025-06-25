#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H

#include "scheduler.h"

// Funções específicas do Round Robin
void handle_blocked_process(Scheduler *sched, Process *p);
void handle_terminated_process(Scheduler *sched, Process *p);

#endif