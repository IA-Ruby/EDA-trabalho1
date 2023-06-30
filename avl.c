#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int qntRemovidos = 0;
struct no{
    int chave;
    struct no *esq, *dir;
    int bal;
};

typedef struct no No;

void preordem(No *pt){
    printf("\n%d - bal: %d", pt->chave, pt->bal);
    if(pt->esq != NULL)
        preordem(pt->esq);
    if(pt->dir != NULL)
        preordem(pt->dir); 
}

int qntNos(No *pt){
    if(pt == NULL) return 0;
    return (qntNos(pt->esq) + qntNos(pt->dir) + 1);
}

int maior(int a, int b){
    return (a > b)? a: b;
}

int menor(int a, int b){
    return (b > a)? a: b;
}

int getAltura(No *pt){
    if(pt == NULL) return 0;
    return maior(getAltura(pt->esq),getAltura(pt->dir)) + 1; 
}

int getBal(No *pt){
    if(pt == NULL) return 0;
    return pt->bal;
}

void setBal(No *pt){
    if(pt != NULL) pt->bal = getAltura(pt->dir) - getAltura(pt->esq);
}

int calcBal(No *pt){
    if(pt != NULL) return getAltura(pt->dir) - getAltura(pt->esq);
}

void balVerify(No *pt){
    if(pt != NULL){
        setBal(pt);
        balVerify(pt->esq);
        balVerify(pt->dir);
    }
}

int verAVL(No *pt){
    if(pt == NULL) return 1;
    int aux = calcBal(pt);
    if(aux > 1 || aux < -1) return 0;
    return menor(verAVL(pt->esq),verAVL(pt->dir));
}

void caso1(No **pt, int *h){
    //printf("Caso 1 - chave: %d", (*pt)->chave);
    No *ptu = (*pt)->esq;
    if(getBal(ptu) == -1){
        //printf(" (simples)\n");
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        (*pt)->dir->bal = 0;
    }else{
        //printf(" (dupla)\n");
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        (*pt) = ptv;
        switch(getBal(ptv)){
            case -1: ptu->bal =  0; (*pt)->dir->bal = 1; break;
            case  0: ptu->bal =  0; (*pt)->dir->bal = 0; break;
            case  1: ptu->bal = -1; (*pt)->dir->bal = 0; break;
        }
    }
    (*pt)->bal = 0;
    (*h) = 0;
}

void caso2(No **pt, int *h){
    //printf("Caso 2 - chave: %d", (*pt)->chave);
    No *ptu = (*pt)->dir; 
    if(getBal(ptu) == 1){
        //printf(" (simples)\n");
        (*pt)->dir = ptu->esq;  
        ptu->esq = (*pt);
        (*pt) = ptu;
        (*pt)->esq->bal = 0;
    }else{
        //printf(" (dupla)\n");
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);
        (*pt) = ptv;
        switch(getBal(ptv)){
            case  1: ptu->bal = 0; (*pt)->esq->bal = -1; break;
            case  0: ptu->bal = 0; (*pt)->esq->bal =  0; break;
            case -1: ptu->bal = 1; (*pt)->esq->bal =  0; break;
        }
    }
    (*pt)->bal = 0; 
    (*h) = 0;
}

void inserirAVL(int x, No **pt, int *h){
    if((*pt) == NULL){ 
        No *novo = (No*)malloc(sizeof(No));
        novo->chave = x;
        novo->esq = novo->dir = NULL;
        novo->bal = 0;
        (*pt) = novo;
        (*h) = 1;
    }else{
        if(x == (*pt)->chave){
            //printf("Elemento %d já existe\n", x);
            return;
        }
        if(x < (*pt)->chave){    
            inserirAVL(x, &(*pt)->esq, h);
            if((*h) == 1){
                switch(getBal((*pt))){
                    case 1: (*pt)->bal = 0; (*h) = 0; break;
                    case 0: (*pt)->bal = -1; break;
                    case -1: caso1(pt,h); break;
                }
            }
        }else{
            inserirAVL(x, &(*pt)->dir, h);
            if((*h) == 1){
                switch(getBal((*pt))){
                    case -1: (*pt)->bal = 0; (*h) = 0; break;
                    case 0: (*pt)->bal = 1; break;
                    case 1: caso2(pt,h); break;
                } 
            }
        }
    }
}

void caso1R(No **pt, int *h){
    //printf("Caso 1R - chave: %d", (*pt)->chave);
    No *ptu = (*pt)->esq;
    if(getBal(ptu) <= 0){
        //printf(" (simples)\n");
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        if(getBal(ptu) == -1){
            ptu->bal = (*pt)->dir->bal = 0;    
            (*h) = 1;
        }else{
            ptu->bal = 1;
            (*pt)->dir->bal = -1;    
            (*h) = 0;
        }
    }else{
        //printf(" (dupla)\n");
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        (*pt) = ptv;
        switch(getBal(ptv)){
            case -1: ptu->bal =  0; (*pt)->dir->bal = 1; break;
            case  0: ptu->bal =  0; (*pt)->dir->bal = 0; break;
            case  1: ptu->bal = -1; (*pt)->dir->bal = 0; break;
        }
        (*pt)->bal = 0;
        (*h) = 1;
    }
}

void caso2R(No **pt, int *h){
    //printf("Caso 2R - chave: %d", (*pt)->chave);
    No *ptu = (*pt)->dir; 
    if(getBal(ptu) >= 0){
        //printf(" (simples)\n");
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        if(getBal(ptu) == 1){
            ptu->bal = (*pt)->esq->bal = 0;    
            (*h) = 1;
        }else{
            ptu->bal = -1;
            (*pt)->esq->bal = 1;    
            (*h) = 0;
        }
    }else{
        //printf(" (dupla)\n");
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);
        (*pt) = ptv;
        switch(getBal(ptv)){
            case  1: ptu->bal = 0; (*pt)->esq->bal = -1; break;
            case  0: ptu->bal = 0; (*pt)->esq->bal =  0; break;
            case -1: ptu->bal = 1; (*pt)->esq->bal =  0; break;
        }
        (*pt)->bal = 0; 
        (*h) = 1;
    }
}

void balancear(No **pt, int r, int *h){
    if((*h) == 1){
        if(r == 1){ //direita
            switch(getBal((*pt))){
                case  1: (*pt)->bal = 0; break;
                case  0: (*pt)->bal = -1; (*h) = 0; break;
                case -1: caso1R(pt,h); break;
            }
        }else{ //esquerda
            switch(getBal((*pt))){
                case -1: (*pt)->bal = 0; break;
                case  0: (*pt)->bal = 1; (*h) = 0; break;
                case  1: caso2R(pt,h); break;
            }
        }
    }
}

void removerAVL(int x, No **pt, int *h){
    if((*pt) == NULL){ 
        //printf("Elemento não existe!"); 
        (*h) = 0;
    }else{
        if(x < (*pt)->chave){
            removerAVL(x,&(*pt)->esq, h);
            balancear(pt, 0, h);
        }else{
            if(x > (*pt)->chave){
                removerAVL(x,&(*pt)->dir, h);
                balancear(pt, 1, h);
            }else{
                No *aux = (*pt);
                if((*pt)->esq == NULL){
                    //printf("\n(1)    ");
                    (*pt) = (*pt)->dir;
                    (*h) = 1;
                }else{
                    if((*pt)->dir == NULL){
                        //printf("\n(2)    ");
                        (*pt) = (*pt)->esq;
                        (*h) = 1;
                    }else{
                        No *s = (*pt)->dir;
                        if(s->esq == NULL){
                            //printf("\n(3)    ");
                            s->esq = (*pt)->esq;
                            s->bal = (*pt)->bal;
                            (*pt) = s;
                            (*h) = 1;
                        }else{ 
                            //printf("\n(4)    ");
                            No *PaiS;
                            while(s->esq != NULL){
                                PaiS = s;
                                s = s->esq;  
                            }   
                            
                            // troca(pt,PaiS);

                            int troca = (*pt)->chave;
                            (*pt)->chave = PaiS->esq->chave;
                            PaiS->esq->chave = troca;

                            troca = (*pt)->bal;
                            (*pt)->bal = PaiS->esq->bal;
                            PaiS->esq->bal = troca;

                            aux = PaiS->esq;

                            removerAVL(x,&(*pt)->dir,h);
                            aux = NULL;
                        }
                        balancear(pt,1,h);
                    }
                }
                
                if(aux != NULL){
                    free(aux);
                    qntRemovidos++;
                }
            }
        }  
    }
}

void esvaziaAVL(No **pt){
    if((*pt)->esq != NULL) esvaziaAVL(&(*pt)->esq);
    if((*pt)->dir != NULL) esvaziaAVL(&(*pt)->dir);
    free((*pt));
}

int main(){
    srand(time(NULL));
    int h = 0;
    No *ptraiz = NULL;
    No **pt = &ptraiz;
/*
    inserirAVL(15, &ptraiz, &h);
    inserirAVL(11, &ptraiz, &h);
    inserirAVL(70, &ptraiz, &h);
    inserirAVL(69, &ptraiz, &h);
    inserirAVL(73, &ptraiz, &h);
    inserirAVL(4, &ptraiz, &h);
    inserirAVL(10, &ptraiz, &h);
    inserirAVL(7, &ptraiz, &h);
    inserirAVL(8, &ptraiz, &h);
    inserirAVL(12, &ptraiz, &h);
    inserirAVL(75, &ptraiz, &h);
    inserirAVL(74, &ptraiz, &h);
    inserirAVL(68, &ptraiz, &h);
    inserirAVL(64, &ptraiz, &h);
    inserirAVL(76, &ptraiz, &h);
    inserirAVL(9, &ptraiz, &h);
    inserirAVL(5, &ptraiz, &h);
    inserirAVL(13, &ptraiz, &h);

    removerAVL(9, &ptraiz, &h);

    if(ptraiz != NULL){
        preordem(ptraiz);
        printf("\n- Tamanho: %d", qntNos(ptraiz));
        printf("\n- E AVL? %d", verAVL(ptraiz));
    }else
        printf("Arvore Vasia");
    printf("\n");
*/

    int qntAVLs = 100;
    int qntNoAVLs = 1000;
    int numerosAVLs = 100000;
    int qntRemover = 100;

    for(int i = 1; i <= qntAVLs; i++){
        ptraiz = NULL;
        pt = &ptraiz;
        printf("\n-------------------------------------------------\n");

        int total = 0;
        while(true){
            int j = 1;
            while(j <= qntNoAVLs-total){
                inserirAVL(rand()%(numerosAVLs+1), &ptraiz, &h);
                j++;
            }

            total = qntNos(ptraiz); 
            if(total == qntNoAVLs) break; 
        }

        printf("Avore numero: %d", i);
        printf("\n- Tamanho: %d", qntNos(ptraiz));
        printf("\n- E AVL? (1 = SIM / 0 = NAO): %d \n", verAVL(ptraiz));
        balVerify(ptraiz);
        printf("\n- E AVL depois da analise? (1 = SIM / 0 = NAO): %d \n", verAVL(ptraiz));

        while(qntRemovidos < qntRemover){
            int wait = qntRemovidos;
            int aux = rand()%(numerosAVLs+1);
            removerAVL(rand()%aux, &ptraiz, &h);
            /*
            if(wait < qntRemovidos){
                printf(" %d", qntRemovidos);
                printf(" T: %d", qntNos(ptraiz));
                printf(" N: %d",aux);
                printf(" AVL: %d\n\n",verAVL(ptraiz));
            }
            */
        }
      
        printf("\n- Numero de remocoes: %d", qntRemovidos);
        printf("\n- Tamanho após remocoes: %d", qntNos(ptraiz));
        printf("\n- E AVL? (1 = SIM / 0 = NAO): %d ", verAVL(ptraiz));
     
        esvaziaAVL(&ptraiz);
        h = 0;
        qntRemovidos = 0;
    }

    return 0;
}


// O conteudo a seguir é uma compilação de falhas realizadas pelo aluno :)

/*
void troca(No **x, No **y){ 
   
   
    No *aux = (No*)(malloc(sizeof(No)));
    aux = (*y);
    aux->chave = (*x)->chave;
    (*x)->chave = (*y)->chave;
    (*y) = aux;


    int aux = (*x)->chave;
    (*x)->chave = (*y)->chave;
    (*y)->chave = aux;


    No *aux = (*x);
    (*x) = (*y);
    (*y) = aux;

    aux = (*x)->esq;
    (*x)->esq = (*y)->esq;
    (*y)->esq = aux; 
   
    aux = (*x)->dir;
    (*x)->dir = (*y)->dir;
    (*y)->dir = aux;

   
    No *aux = (*x)->esq;
    (*x)->esq = (*y)->esq;
    (*y)->esq = (*x)->esq;
    
    aux = (*x)->dir;
    (*x)->dir = (*y)->dir;
    (*y)->dir = aux;

    int aux2 = (*x)->bal;
    (*x)->bal = (*y)->bal;
    (*y)->bal = aux2;

    aux2 = (*x)->chave;
    (*x)->chave = (*y)->chave;
    (*y)->chave = aux2;
    

    
    int aux = (*x)->chave;
    (*x)->chave = (*y)->chave;
    (*y)->chave = aux;

    aux = (*x)->bal;
    (*x)->bal = (*y)->bal;
    (*y)->bal = aux;
    
}
*/