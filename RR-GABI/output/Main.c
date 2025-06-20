#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "scheduler.h"
#include "rr_scheduler.h"



int main() {
    Scheduler scheduler;
    int quantum, num_processes;
    int Contador_processos = 1;
    int contador_ciclos = 1;

    printf("Ola!\n");
    printf("Digite o valor do quantum: ");
    scanf("%d",&quantum);

    init_scheduler(&scheduler,quantum);


    printf("Quantos processos deseja criar? ");
    scanf("%d", &num_processes);



    // Processos iniciais
    for(int k = 0; k < num_processes; k++) {
        int total_time;
        printf("Digite o tempo total do processo %d: ", Contador_processos);
        scanf("%d", &total_time);

        Process* novo_processo = create_process(Contador_processos, total_time);// Cria novo processo

        if(novo_processo) {
            add_to_ready_queue(&scheduler, novo_processo); //Adiciona um processo à fila do escalonador
            Contador_processos++;
        }
    }

    //Loop da simulação foi inciado
    printf("Simulacao INICIADA\n");
    //E vai continuar enquanto houver processos
    while(scheduler.ready_queue!= NULL){

        printf("\n\n === CICLO %-2d ===\n", contador_ciclos);
        contador_ciclos++;

        //Ciclo do escalonador
        Process* processo_atual = schedule(&scheduler);

        if(processo_atual!=NULL){
            printf("CPU executou o processo:\n");
            print_process(processo_atual);
            // Se o processo executou agora está no estado TERMINADO
            if(processo_atual->state==TERMINADO){
                printf("Processo %d finalizou.\n",processo_atual->pid);
                printf("Removendo da fila...\n");
                handle_terminated_process(&scheduler,processo_atual);
            } else {
            // Se o processo não terminou, existe uma chance de ele ser bloqueado, decidimos deixar uma chance de 15%
            if((rand()%100)<15){
                handle_blocked_process(&schedule,processo_atual);
                }
            }
    } else{
         printf("CPU ociosa\n");
    }
        // Mostra o estado da fila de prontos no final do ciclo
        print_queue(&scheduler);
    }

    printf("Simulacao finalizada");

    return 0;
}

/* PROCESS.H: Cria um novo processo com PID e tempo total especificados */
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

/* PROCESS.H: Libera a memória alocada para um processo */
void destroy_process(Process *p) {
    if(p != NULL) {
        free(p);
    }
}

/* PROCESS.H: Imprime as informações de um processo de forma formatada */
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

        printf("PID: %d | Estado: %s | CPU: %d | Restante: %d | Quantum: %d\n",
               p->pid, state_str, p->total_cpu_time, p->remaining_time, p->quantum_remaining);
    } else {
        printf("Processo nulo.\n");
    }
}


//SCHEDULER.H: Depois de ter a quantidade de quantum definido (pelo process.h), vamos para o ESCALONADOR
void init_scheduler(Scheduler *sched, int quantum){
    sched->ready_queue = NULL; //A fila começa vazia
    sched->quantum = quantum; //Definição do quantum do sistema
}

//SCHEDULER.H:  Processo da fila circular(estado: PRONTOS)
void add_to_ready_queue(Scheduler *sched, Process *p){
    //Não alterei nada , é a mesma "dica de implementação" que está na descrição do projeto
    if (sched->ready_queue == NULL){ //CASO a fila esteja vazia
        sched->ready_queue = p;
        p->next = p;
    } else { //CASO já tenha processos
        p->next = sched->ready_queue->next;
        sched->ready_queue->next=p;
        sched->ready_queue=p;
    }
    p->state = PRONTO;
}

//SCHEDULER.H: Escalona o próximo processo, BASICAMENTE decide quem executa (de acordo com seu grau importância) e atualiza os tempos
Process* schedule(Scheduler *sched){
    if (sched->ready_queue == NULL){
        return NULL;
        //Se a fila de prontos está vazia, não há ninguém para escalonar
    }
    //O processo a ser EXECUTADO vem sempre DEPOIS do último(o primeiro da fila)
    Process *processo_atual = sched->ready_queue->next;

    //Se o processo_atual estava PRONTO, significa que ele está começando sua vez, ou seja, damos a ele uma fatia de quantum completa
    if(processo_atual->state == PRONTO){
        processo_atual->quantum_remaining=sched->quantum;
    }
    //Processo em execução
    processo_atual->state = EXECUTANDO;
    //Execução por unidade de tempo (Variáveis do Process.h)
    processo_atual-> remaining_time--;
    processo_atual->quantum_remaining--;
    processo_atual->total_cpu_time++;

    //Verificação do processo
    if(processo_atual->remaining_time <= 0){
        //Caso 1: O processo TERMINOU sua execução por completo
        processo_atual->state= TERMINADO;
    } else if(processo_atual->quantum_remaining<=0){
        //Caso 2: O processo NÃO terminou , mas seu quantum acabou
        processo_atual->state=PRONTO; //Voltando então para o estado PRONTO
        sched->ready_queue=processo_atual;
    }
    //Caso 3: Se não entrou em nenhum if, ele continua no estado EXECUTANDO,pois ainda tem tempo de sobre no seu quantum

    return processo_atual;
}

////SCHEDULER.H: Exibe todos os processos na fila de prontos.
void print_queue(const Scheduler *sched){
    printf("Fila de prontos\n");
    if(sched->ready_queue ==NULL){
        printf("  Fila vazia.\n");
        return;
    }

    Process *inicial = sched->ready_queue->next; //Pega o primeiro processo
    Process *atual = inicial;

    // Um loop para as listas circulares
    do{
        printf(" ");
        print_process(atual);
        atual = atual->next;
    } while (atual != inicial); //Vai de volta ao início
}


//RR_SCHEDULER.H: Remove um processo bloqueado da fila de prontos
void handle_blocked_process(Scheduler *sched, Process *p){
    if(sched->ready_queue == NULL || p == NULL){
        return;
    }

    printf("\n Processo %d BLOQUEADO!!\n",p->pid);
    printf("Removendo da lista de PRONTOS...\n");

      // Caso 1: O processo a ser removido é o único na fila
     if(p->next == p){
        sched->ready_queue = NULL;
    } else{
        //Caso 2: Há mais de um processo, então achamos o processo ANTERIOR a 'p'
        Process *processo_anterior = p;
        while (processo_anterior->next !=p){
            processo_anterior=processo_anterior->next;
        }
        // faz o ANTERIOR pulara o 'p', ligando-se ao próximo
        processo_anterior->next = p->next;

         // Se por acaso o processo removido era o "último", o novo "último" passa a ser o anterior a ele.
        if(sched->ready_queue == p){
            sched->ready_queue = processo_anterior;
        }
    }
    //Muda para o estado para BLOQUEADO
    p->state = BLOQUEADO;
    //O processo não foi destruído, e então limpamos o ponteiro 'next', já que não está mais na fila
    p->next=NULL;
}

//RR_SCHEDULER.H: Remove um processo finalizado da fila e libera sua memória
void handle_terminated_process(Scheduler *sched, Process *p){
    //Mesma lógica do Blocked process
    if(sched->ready_queue == NULL|| p==NULL){ //Se está vazio, não precisa fazer nada
        return;
    }

    if(p->next == p){
        sched->ready_queue = NULL;
    } else{
        Process *processo_anterior = p;
        while (processo_anterior->next !=p){
            processo_anterior=processo_anterior->next;
        }

        processo_anterior->next = p->next;

        if(sched->ready_queue == p){
            sched->ready_queue = processo_anterior;
        }
    }
    // A única diferença, é que a função 'destroy' (Process.h) é chamada e a memória passa a ser liberada
     destroy_process(p);
}
