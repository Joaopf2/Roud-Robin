#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct {
    Process *ready_queue; // Ponteiro para a fila circular de prontos
    int quantum;          // Quantum do sistema (ex: 4 unidades)
} Scheduler;

// Funções obrigatórias
void init_scheduler(Scheduler *sched, int quantum);
void add_to_ready_queue(Scheduler *sched, Process *p);
Process* schedule(Scheduler *sched);
void print_queue(const Scheduler *sched);

#endif