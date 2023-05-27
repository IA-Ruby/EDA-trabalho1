#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int maior(int a, int b){
    return (a > b)? a: b;
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

void balVerify(No *pt){
    if(pt != NULL){
        setBal(pt);
        balVerify(pt->esq);
        balVerify(pt->dir);
    }
}

void buscar(int x, No ***pt, int *f){
    if( (*(*pt)) == NULL ){
        (*f) = 0;
    }else{
        if( (*(*pt))->chave == x){
            (*f) = 1;
        }else{
            if( x < (*(*pt))->chave){
                if( (*(*pt))->esq == NULL){
                    (*f) = 2;
                }else{
                    (*pt) = &(*(*pt))->esq;
                    buscar(x, pt, f);
                }
            }else{
                if( (*(*pt))->dir == NULL){
                    (*f) = 3;
                }else{
                    (*pt) = &(*(*pt))->dir;
                    buscar(x, pt, f);
                }
            }
        }
    }
}

void inserir(int x, No **ptraiz){
    int f;
    No **pt = ptraiz;
    buscar(x, &pt, &f);

    if(f == 1) printf("Elemento %d já existe\n", x);
    else{
        No *novo = (No*)malloc(sizeof(No));
        novo->chave = x;
        novo->esq = novo->dir = NULL;
        novo->bal = 0;

        if(f == 0)
            (*ptraiz) = novo;
            setBal(*ptraiz);
        if(f == 2)
            (*pt)->esq = novo;
            setBal((*pt)->esq);
        if(f == 3)
            (*pt)->dir = novo;
            setBal((*pt)->dir);

        balVerify((*ptraiz));
    }
}

void remover(int x, No **ptraiz){
    int f;
    No **pt = ptraiz;
    buscar(x, &pt, &f);

    if(f != 1) printf("Elemento não existe");
    else{
        No *aux = (*pt);
        if( (*pt)->esq == NULL){
            (*pt) = (*pt)->dir;
        }else{
            if( (*pt)->dir == NULL){
                (*pt) = (*pt)->esq;
            }else{
                No *s = (*pt)->dir;
                if(s->esq != NULL){
                    No *PaiS;
                    while(s->esq != NULL){
                        PaiS = s;
                        s = s->esq;  
                    }
                    PaiS->esq = s->dir;
                    s->dir = (*pt)->dir;
                }
                s->esq = (*pt)->esq;
                (*pt) = s;
            }
        }
        free(aux);
    }
}

void caso1(No **pt, int *h){
    printf("\ncaso1");
    No *ptu = &(*pt)->esq;
    if(getBal(ptu) == -1){
        printf("\nrotSimples");
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        (*pt)->dir->bal = 0;
    }else{
        printf("\nrotDupla");
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        (*pt)->esq = ptv->dir;
        ptv->esq = ptu;
        ptv->dir = (*pt);

        if(getBal(ptu) == 1){
            (*pt)->bal = 0;
            ptu->bal = -1;
        }else{
            (*pt)->bal = 1;
            ptu->bal = 0;
        }

        printf("a");
        (*pt) = ptu;
    }
    (*pt)->bal = 0; 
    (*h) = 0;
}

void caso2(No **pt, int *h){
    printf("\ncaso2");
    No **ptu = &(*pt)->dir; 
    if(getBal((*ptu)) == -1){
        (*pt)->dir = (*ptu)->esq;  
        (*ptu)->esq = (*pt);
        (*pt) = (*ptu);
        (*pt)->esq->bal = 0;
    }else{
        No **ptv = &(*ptu)->esq;
        (*ptu)->esq = (*ptv)->dir;
        (*ptv)->dir = (*ptu);
        (*pt)->dir = (*ptv)->esq;
        (*ptv)->esq = (*pt);
        if(getBal((*ptv)) == 1){
            (*pt)->bal = 0;
            (*ptu)->bal = -1;
        }else{
            (*pt)->bal = 1;
            (*ptu)->bal = 0;
        }
        (*pt) = (*ptv);
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
            printf("Elemento %d já existe\n", x);
        }else{
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
}

int main(){
    int h = 0;
    int f;
    No *ptraiz = NULL;
    No **pt = &ptraiz;
    
    inserirAVL(12, &ptraiz, &h);
    inserirAVL(9, &ptraiz, &h);
    inserirAVL(70, &ptraiz, &h);
    inserirAVL(69, &ptraiz, &h);
    inserirAVL(71, &ptraiz, &h);
    inserirAVL(6, &ptraiz, &h);
    inserirAVL(8, &ptraiz, &h);
    inserirAVL(7, &ptraiz, &h);

    if(ptraiz != NULL)
        preordem(ptraiz);
    else
        printf("AV");
    printf("\n");

    return 0;
}