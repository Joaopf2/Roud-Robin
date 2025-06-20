#ifndef PROCESS_H
#define PROCESS_H

typedef enum {
    PRONTO,
    EXECUTANDO,
    BLOQUEADO,
    TERMINADO
} ProcessState;

typedef struct Process {
    int pid;                // Identificador único
    ProcessState state;     // Estado atual
    int total_cpu_time;     // Tempo total de CPU consumido
    int remaining_time;     // Tempo restante para término
    int quantum_remaining;  // Tempo restante do quantum
    struct Process *next;   // Ponteiro para o próximo processo
} Process;

// Funções obrigatórias
Process* create_process(int pid, int total_time);
void destroy_process(Process *p);
void print_process(const Process *p);

#endif