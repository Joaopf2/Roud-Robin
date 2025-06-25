# Simulador - Round-Robin
Projeto final realizado para a diciplica Sistemas Operacionais 1, criado pelos alunos: 
* Gabriella Pereira Morais
* João Pedro Freitas Farias
* Sophia Vitoria Albuquerque de Castro
* Vitória Bitencourte Galliac

### Descrição
Este projeto é um simulador de escalonamento de CPU para um sistema operacional hipotético. O objetivo é implementar o algoritmo de escalonamento Round Robin (RR), gerenciando processos através de diferentes estados e utilizando uma fila circular para garantir a preempção baseada em um quantum fixo.

### Funcionalidades
* **Criação Dinâmica de Processos:** Processos são criados no início da simulação com tempos de execução definidos pelo usuário.
* **Fila Circular de Prontos:** Os processos no estado PRONTO são gerenciados em uma fila circular, garantindo que todos recebam tempo de CPU de forma justa.
* **Gerenciamento de Estados:** O simulador controla o ciclo de vida dos processos através dos estados PRONTO, EXECUTANDO, BLOQUEADO e TERMINADO.
* **Preempção por Quantum:** Um processo em execução é interrompido se seu tempo de uso da CPU exceder o quantum, sendo movido para o final da fila.

