#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct {
    Process *ready_queue; // Ponteiro para a fila circular de prontos
    int quantum;          // Quantum do sistema (ex: 4 unidades)
} Scheduler;



// Funções obrigatórias
void init_scheduler(Scheduler *sched, int quantum); //Inicializa o escalonador com o quantum
void add_to_ready_queue(Scheduler *sched, Process *p); // Adiciona um processo à fila circular de prontos
Process* schedule(Scheduler *sched); //Escalona o próximo processo, decrementando seu quantum e tempo restante.
void print_queue(const Scheduler *sched); // Exibe todos os processos na fila de prontos.

#endif