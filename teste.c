#include <stdio.h>
#include <stdlib.h>

void newVector(int *ret, int size){
    for(int i = 1; i <= size; i++)
    {
        ret[i] = rand()%99+1;
    }
}

// t -> Tabela
// n -> Tamanho da tebela
// i -> Posição da tabela

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
        descer(t, (*n), 1);
    }else{
        printf("Underflow: tabela vazia");
    }
}

//Construir
void construir(int *t, int *n){
    for(int i = (*n)/2; i >= 1; i--){
        descer(t, (*n), i);
    }
}

//HeapSort
void heapSort(int *t, int *n){
    construir(t, n);
    for(int i = (*n); i >= 2; i--){
        printf("%d\n",i);
        int aux = t[1];
        t[1] = t[i];
        t[i] = aux;
        descer(t,i-1,1);    
    }
}

//InsertionSort


int main(){

    int timer;

    int size = 0;
    int *vetor = (int*)malloc(size * sizeof(int));
    vetor[0] = 0;

    inserir(vetor, &size, 90);
    inserir(vetor, &size, 100);
    inserir(vetor, &size, 30);
    inserir(vetor, &size, 55);
    inserir(vetor, &size, 18);
    inserir(vetor, &size, 48);
    inserir(vetor, &size, 88);
    inserir(vetor, &size, 71);
    inserir(vetor, &size, 180);

    remover(vetor, &size);
    remover(vetor, &size);

    //newVector(vetor, size);
    size = 10000;    

    newVector(vetor, size);

    /*Sem HeapSort
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
        printf("[%d]: %d\n", i, vetor[i]);
    }
    */
    heapSort(vetor,&size);
 
    /*Com HeapSort
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
        printf("[%d]: %d\n", i, vetor[i]);
    }
    */

    printf("Terminou \n");

    return 0;
}