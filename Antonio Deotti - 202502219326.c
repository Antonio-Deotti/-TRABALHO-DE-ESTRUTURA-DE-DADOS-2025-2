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

//funcao para adicionar itens ao inventario
void adicionarComponente(Componentes mochila[], int *quantidade){
    //verificando se a mochila está vazial
    if(*quantidade >= MAX){
        printf("\n\nMochila cheia! Descarte algo\n\n");
        return;
    }

    Componentes novo;

    getchar();//limpar o buffer, remove os \n restantes

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

//funcao para varre o struct "componentes" exibindo uma lista de componentes
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

/*Primeiro usamos uma funcao if para identificar se a struct está vazia,
depois solicitamos o usuario o nome do item que deseja remover, em seguido o programa
inicia uma varredura no array comparando as strings, ao identificar duas identicas a varivael "encontrado" assume o valor
da posicao, em seguida varremos os arrays novamente a partir de posicao "encontrado" fazendo "i" receber "i+1"
excluindo o item desejado e empurrando os demais para frente. Por fim diminuimos em "1" o valor de "quantidade"
o que simboliza a diminuição de itens no inventário  */
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

/*
1. Iniciamos verificando se a mochila está vazia.
2. Para organizar utilizamos dois "for" aninhandos comparando o valor de prioridade seguidos de um if realizando a troca se o valor de "i"
assumir um valor diferente do inicial.
3. Primeiro assumimos que a posicao 0 é o valor maior.
4. Comparamos ela com os demais, se o valor da posicao "j" for maior de "prioridadeMaior", "prioridadeMaior" assume o valor de "j".
5. Apos percorres todas posicoes do array usamos "if" para verificar se o valor inicial é igual ao valor final,
sendo diferente o valor incial é armazenado em um slot temporario, então o valor valor maior é colocado na posicao atual e o
valor inicial é colocado na posicao a frente da inicial e o ciclo recomeça.
*/
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

/*
1. Iniciamos verificando se a mochila esta vazia
2. Pegamos o valor de "i" e colocamos na variavel "atual".
3. Definimos o valo de "j" como um valor antes da posição inicial de "i"
4. Então, enquanto "j" não chegar a 0 e enquanto o "tipo" do elemento for maior alfabeticamente, o elemento move uma posicao para
frente e "j" uma para traz
5. Apos sair do loop, coloca o elemento na posicao correta e o ciclo recomeca.
*/
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

/*
1. Iniciamos definindo dois loops aninhados
2. Onde o loop externo define a quantidade de passadas jogando o valor maior para o final
3. O loop iterno compara os valores, o "- 1" reduz a area analizada pois os maiores já estão no final
4. O "if" compara os valores alfabeticamente, se o atual for maior que o sucessor, ele troca os dois de lugar 
usando um slot temporario.
*/
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