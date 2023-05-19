#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// t -> Tabela
// n -> Tamanho da tebela
// i -> Posição da tabela

void imprimeHeap(int *t, int size){
    for(int i = 1; i <= size; i++)
    {
        int j = i;
        if(j%2 == 0){
            j++;
        }
        while(j > 1){
            printf(" ");
            j--;
        }    
        printf("[%d]: %d\n", i, t[i]);
    }
}

void imprimeOrdenado(int *t, int size){
    for(int i = 1; i <= size; i++)
    {
        printf("[%d]: %d\n", i, t[i]);
    }
}

//subir
void subir(int *t, int n, int i){
    int j = i/2;
    if(j <= n && j > 0){
        if(t[i] > t[j]){
            int aux = t[j];
            t[j] = t[i];
            t[i] = aux;
            subir(t, n, j);
        }
    }
}

//descer
void descer(int *t, int n, int i){
    int j = i*2;
    if(j <= n && j > 0){
        if(j < n){
            if(t[j+1] > t[j]){
                j++;
            }
        }
        if(t[i] < t[j]){
            int aux = t[j];
            t[j] = t[i];
            t[i] = aux;
            descer(t, n, j);
        }
    }
}

//inserir
void inserir(int *t, int *n, int i){       
    if((*n) != 0){
        *n = *n + 1;
        t = realloc(t,(*n) * sizeof(int));
        t[(*n)] = i;
        subir(t, (*n), (*n));
    }else{
        t[1] = i;
        *n = *n + 1;
    }
}

//Remover
void remover(int *t, int *n){       
    if((*n) != 0){
        t[1] = t[(*n)];
        *n = *n - 1;
        t = realloc(t,(*n) * sizeof(int));
        descer(t, (*n), 1);
    }else{
        printf("Underflow: tabela vazia");
    }
}

//Construir
void construir(int *t, int n){
    for(int i = n/2; i >= 1; i--){
        descer(t, n, i);
    }
}

//HeapSort
void heapSort(int *t, int n){
    construir(t, n);
    for(int i = n; i >= 2; i--){
        int aux = t[1];
        t[1] = t[i];
        t[i] = aux;
        descer(t,i-1,1);    
    }
}

//InsertionSort
void insertionSort(int *t, int n){
    for(int i = 2; i <= n; i++){
        int chave = t[i];
        int j = i-1;
        while( j >= 1 && t[j] > chave ){
            int swap = t[j+1];
            t[j+1] = t[j];
            t[j] = swap;
            j--;
        }
    }
}

int main(){

    int timer;

    //int size = 1000;
    //int size = 100000;
    int size = 10000000;
    //int size = 1000000000;

    int *vectorSH = (int*)malloc(size * sizeof(int));
    int *vectorIS = (int*)malloc(size * sizeof(int));
    vectorSH[0] = 0;
    vectorIS[0] = 0;

    for(int i = 1; i <= size; i++){
        int aux = rand()%100+1;
        vectorSH[i] = aux;
        vectorIS[i] = aux;
    }

    //Sem Sort
    /*
    printf("Sem ordenação:  \n\n\n");
    imprimeOrdenado(vector, size);
    */
    printf("\n---------------------------------------------------------------------------\n\n");

    //HeapSort

    //Começa o relogio
    int total = 0;
    clock_t before = clock();

    //Ordena o vetor
    heapSort(vectorSH, size);

    //Calcula o tempo do relogio
    clock_t difference = clock() - before;
    total = difference * 1000 / CLOCKS_PER_SEC;

    //Imprime os resultados
    //imprimeOrdenado(vectorSH, size);
    printf("\n---------------------------------------------------------------------------\n\n");
    printf("Tempo HeapSort: \n Segundos: %d\n Milisegundos: %d\n\n", total/1000, total%1000);

    //InsertionSort

    //Reseta o relogio
    total = 0;
    before = clock();

    // Ordena o vetor
    insertionSort(vectorIS, size);
    
    //Cacula o tempo
    difference = clock() - before;
    total = difference * 1000 / CLOCKS_PER_SEC;

    //Imprime os resultados
    //imprimeOrdenado(vectorIS, size);
    printf("\n---------------------------------------------------------------------------\n\n");
    printf("Tempo InsertionSort: \n Segundos: %d\n Milisegundos: %d\n\n", total/1000, total%1000);
    printf("\n---------------------------------------------------------------------------\n\n");


    printf("1.000.000.000");
    int size2 = 1000000000;
    int *vectorSH2 = (int*)malloc(size2 * sizeof(int));
    int *vectorIS2 = (int*)malloc(size2 * sizeof(int));
    vectorSH2[0] = 0;
    vectorIS2[0] = 0;

    printf("\n---------------------------------------------------------------------------\n\n");

    //HeapSort

    //Começa o relogio
    total = 0;
    before = clock();

    //Ordena o vetor
    heapSort(vectorSH, size);

    //Calcula o tempo do relogio
    difference = clock() - before;
    total = difference * 1000 / CLOCKS_PER_SEC;

    //Imprime os resultados
    //imprimeOrdenado(vectorSH, size);
    printf("\n---------------------------------------------------------------------------\n\n");
    printf("Tempo HeapSort: \n Segundos: %d\n Milisegundos: %d\n\n", total/1000, total%1000);

    //InsertionSort

    //Reseta o relogio
    total = 0;
    before = clock();

    // Ordena o vetor
    insertionSort(vectorIS, size);
    
    //Cacula o tempo
    difference = clock() - before;
    total = difference * 1000 / CLOCKS_PER_SEC;

    //Imprime os resultados
    //imprimeOrdenado(vectorIS, size);
    printf("\n---------------------------------------------------------------------------\n\n");
    printf("Tempo InsertionSort: \n Segundos: %d\n Milisegundos: %d\n\n", total/1000, total%1000);
    printf("\n---------------------------------------------------------------------------\n\n");

    return 0;
}