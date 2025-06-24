#include <stdio.h>
#include <stdlib.h>
#include "headers/process.h"        
#include "headers/scheduler.h"
#include "headers/rr_scheduler.h"



int main() {   
    int i, j, num_processes;
    
    printf("Quantos processos deseja criar? ");
    scanf("%d", &num_processes);
    
    // Array para armazenar os ponteiros dos processos
    Process *processes[num_processes];
    
    // Loop para criar vários processos
    for(int k = 0; k < num_processes; k++) {
        printf("Digite o PID e o tempo total do processo %d (separados por espaco): ", k+1);
        scanf("%d %d", &i, &j);
        
        processes[k] = create_process(i, j);  // Cria novo processo
        
        if(processes[k]) {
            print_process(processes[k]);  // Imprime o processo logo após criação
        }
    }
    
    // Libera a memória alocada para todos os processos
    for(int k = 0; k < num_processes; k++) {
        destroy_process(processes[k]);
    }
    
    return 0;
}

/* Cria um novo processo com PID e tempo total especificados */
Process* create_process(int pid, int total_time) {
    Process *p = (Process *)malloc(sizeof(Process));
    if(p == NULL) return NULL;
    
    // Inicializa os campos do processo
    p->pid = pid;
    p->state = PRONTO;
    p->total_cpu_time = 0;
    p->remaining_time = total_time;
    p->quantum_remaining = 2;  // Valor padrão para quantum
    p->next = NULL;
    
    return p;
}

/* Libera a memória alocada para um processo */
void destroy_process(Process *p) {
    if(p != NULL) {
        free(p);
    }
}

/* Imprime as informações de um processo de forma formatada */
void print_process(const Process *p) {
    if(p) {
        const char *state_str;
        switch(p->state) {
            case PRONTO: state_str = "PRONTO"; break;
            case EXECUTANDO: state_str = "EXECUTANDO"; break;
            case BLOQUEADO: state_str = "BLOQUEADO"; break;
            case TERMINADO: state_str = "TERMINADO"; break;
            default: state_str = "DESCONHECIDO";
        }
        
        printf("PID: %d | Estado: %s | CPU Usado: %d | Tempo Restante: %d | Quantum Restante: %d\n",
               p->pid, state_str, p->total_cpu_time, p->remaining_time, p->quantum_remaining);
    } else {
        printf("Processo nulo.\n");
    }
}