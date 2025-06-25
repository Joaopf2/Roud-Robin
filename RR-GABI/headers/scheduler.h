#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
/*
  _Mudança no SCHEDULER.H_

 Como entramos em contado o senhor professor Modesto, fizemos uma mudança neste arquivo!

 Em um sistema operacional real, processos frequentemente pausam para esperar por eventos
 externos, como por exemplo a leitura de um arquivo . A 'ready_queue' (fila de prontos) sozinha não consegue
 modelar este comportamento, pois um processo removido dela seria permanentemente perdido. E como não existe nenhuma função
 que tenha esse objetivo, nossa solução foi a adição do 'blocked_queue', ele serve como uma sala de espera para esses
 processos bloqueados. Lá eles aguardam quando não estão aptos a usar a CPU.

 Durante a simulação no 'main', um evento aleatório pode ser acionado para o processo
 que está em execução. Um evento é uma chance aleatória para que o processo atualmente em execução sofra
 um evento de bloqueio. Quando isso ocorre, a função 'handle_blocked_process' é chamada, removendo o processo da
 'ready_queue' e o adiciona no início da 'blocked_queue'.

 No início de cada ciclo do loop principal ('while' na main), há uma chance aleatória de um processo ser "acordado".
 Se a 'blocked_queue' não estiver vazia e a sorte for favorável, o primeiro processo da lista de bloqueados é removido dela
 e reinserido na 'ready_queue' através da função 'add_to_ready_queue'.

 */

typedef struct {
    Process *ready_queue; // Ponteiro para a fila circular de prontos
    Process *blocked_queue; // Ponteiro adicionado para fila de bloqueados
    int quantum;          // Quantum do sistema (ex: 4 unidades)
} Scheduler;



// Funções obrigatórias
void init_scheduler(Scheduler *sched, int quantum); //Inicializa o escalonador com o quantum
void add_to_ready_queue(Scheduler *sched, Process *p); // Adiciona um processo à fila circular de prontos
Process* schedule(Scheduler *sched); //Escalona o próximo processo, decrementando seu quantum e tempo restante.
void print_queue(const Scheduler *sched); // Exibe todos os processos na fila de prontos.

#endif
