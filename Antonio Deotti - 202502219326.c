#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Define o valor maximo para uma variavel
#define MAX 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;

}Componentes;

void adicionarComponente(Componentes mochila[], int *quantidade){
    if(*quantidade >= MAX){
        printf("\n\nMochila cheia! Descarte algo\n\n");
        return;
    }

    Componentes novo;

    getchar();

    printf("\nInforme o nome do componete: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Informe o tipo (controle, suporte, propulcao): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Informe a prioridade: ");
    scanf("%d", &novo.prioridade);

    mochila[*quantidade] = novo;
    (*quantidade)++;

    printf("\nItem coletado com sucesso!\n\n");

}

void listarComponentes(Componentes mochila[], int quantidade){
    if(quantidade == 0){
        printf("\nA mochila esta vazia!\n\n");
        return;
    }

    printf("\n== ITENS NA MOCHILA ==\n");

    for(int i = 0; i < quantidade; i++){
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].prioridade);
    }
    printf("\n\n");
}

void descartarComponente(Componentes mochila[], int *quantidade){
    if(*quantidade < 0){
        printf("\nA mochila esta vazia!\n\n");
        return;
    }

    getchar();

    char nomeRemover[30];

    printf("Informe qual componente vai ser descartado: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;

    for(int i = 0; i < *quantidade; i++){
        if(strcmp(mochila[i].nome, nomeRemover) == 0){
            encontrado = i;
        }
    }

    if (encontrado == -1) {
        printf("\nComponente '%s' nao encontrado.\n\n", nomeRemover);
        return;
    }

    for(int i = encontrado; i < *quantidade; i++){
        mochila[i] = mochila[i+1];
    }

    (*quantidade)--;

    printf("\nItem removido com sucesso\n\n");



}

void selectionSort(Componentes mochila[], int quantidade){
    clock_t time1, time2, timeTotal;
    
    time1 = clock(); 
    
    if(quantidade == 0){
        printf("\nA mochila esta vazia!\n\n");
        return;
    }

    for(int i = 0; i < quantidade - 1; i++){
        int prioridadeMaior = i;

        for(int j = i+1; j < quantidade; j++){
            if(mochila[j].prioridade > mochila[prioridadeMaior].prioridade){
                prioridadeMaior = j;
            }
        }

        if(prioridadeMaior != i){
            Componentes temp = mochila[i];
            mochila[i] = mochila[prioridadeMaior];
            mochila[prioridadeMaior] = temp;
        }
    }

    time2 = clock(); 
    timeTotal = time2 - time1;
    printf("\nMochila organizada com sucesso! O tempo para organizar a mochila foi de %1d tiks.\n\n", (long)timeTotal);


}

void insertionSort(Componentes mochila[], int quantidade){
    clock_t time1, time2, timeTotal;
    
    time1 = clock(); 

    if(quantidade == 0){
        printf("\nA mochila esta vazia!\n\n");
        return;
    }


    for(int i = 0; i < quantidade; i++){
        Componentes atual = mochila[i];
        int j = i - 1;

        while (j >= 0 && strcmp(mochila[j].tipo, atual.tipo) > 0) {
        mochila[j + 1] = mochila[j];
        j--;
        }

        
        mochila[j + 1] = atual;
    }
    
    time2 = clock(); 
    timeTotal = time2 - time1;
    printf("\nMochila organizada com sucesso! O tempo para organizar a mochila foi de %1d tiks.\n\n", (long)timeTotal);
}


void bubbleSort(Componentes mochila[], int quantidade){
    clock_t time1, time2, timeTotal;
    
    time1 = clock(); 
   
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - 1 - i; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
               Componentes temp = mochila[j];
               mochila[j] = mochila[j+1];
               mochila [j+1] = temp;
            }
        }
    }

    time2 = clock(); 
    timeTotal = time2 - time1;
    printf("\nMochila organizada com sucesso! O tempo para organizar a mochila foi de %1d tiks.\n\n", (long)timeTotal);
}

int main(){

    int opcao;
    Componentes mochila[MAX];
    int quantidade = 0;

        printf("=============================================\n");
        printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("=============================================\n");

    do{
        printf("Itens na Mochila: %d/20\n",quantidade);
        printf("Status de ordenacao por nome: ");
        printf("\n\n");
        printf("1. Adicionar componete\n");
        printf("2. Descartar componete\n");
        printf("3. Listar Componetes (inventario)\n");
        printf("4. Organizar Mochila (Por prioridade)\n");
        printf("5. Organizar Mochila (Por tipo)\n");
        printf("6. Organizar Mochila (por nome)\n");
        printf("0. ATIVA TORRE DE FUGA (Sair)\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

    switch (opcao){
    case 1:
        adicionarComponente(mochila, &quantidade);
        break;

    case 2:
        descartarComponente(mochila, &quantidade);
        break;

    case 3:
        listarComponentes(mochila, quantidade);
        break;
    
    case 4:
        selectionSort(mochila, quantidade);
        break;

    case 5:
        insertionSort(mochila, quantidade);
        break;
    
    case 6:
        bubbleSort(mochila, quantidade);
        break;

    case 0:
    
    printf("\nEncerrando o sistema...\n");
           
        break;

    default:
    printf("\nOpcao invalida!\n");
        break;
    }


    } while (opcao != 0);
    
   return 0;
}