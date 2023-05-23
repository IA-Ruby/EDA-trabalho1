#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no{
    int chave;
    struct no *esq, *dir;
    int altura;
    int bal;
};

typedef struct no No;

void preordem(No *pt){
    printf("%d ", pt->chave);
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
    return pt->altura; 
}

int getBal(No *pt){
    if(pt == NULL) return 0;
    return pt->bal;
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
        novo->bal = 1;

        if(f == 0)
            (*ptraiz) = novo;
        if(f == 2)
            (*pt)->esq = novo;
        if(f == 3)
            (*pt)->dir = novo;
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

void caso1(No *pt, int *h){
    No **ptu = pt->esq;
    if(getBal(*ptu) == -1){
        pt->esq = (*ptu)->dir;
        (*ptu)->dir = pt;
        pt = (*ptu);
        pt->dir->bal = 0;
    }else{
        No **ptv = (*ptu)->dir;
        (*ptu)->dir = (*ptv)->esq;
        (*ptv)->esq = (*ptu);
        pt->esq = (*ptv)->dir;
        (*ptv)->dir = pt;
        if(getBal(*ptv) == 1){
            pt->bal = 0;
            (*ptu)->bal = -1;
        }else{
            pt->bal = 1;
            (*ptu)->bal = 0;
        }
        pt = (*ptv);
    }
    pt->bal = 0; 
    h = false;
}

void caso2(No *pt, int *h){
    No **ptu = pt->esq;
    if(getBal(*ptu) == -1){
        pt->esq = (*ptu)->dir;
        (*ptu)->dir = pt;
        pt = (*ptu);
        pt->dir->bal = 0;
    }else{
        No **ptv = (*ptu)->dir;
        (*ptu)->dir = (*ptv)->esq;
        (*ptv)->esq = (*ptu);
        pt->esq = (*ptv)->dir;
        (*ptv)->dir = pt;
        if(getBal(*ptv) == 1){
            pt->bal = 0;
            (*ptu)->bal = -1;
        }else{
            pt->bal = 1;
            (*ptu)->bal = 0;
        }
        pt = (*ptv);
    }
    pt->bal = 0; 
    h = false;
}

void inserirAVL(int x, No **pt, bool *h){
    if(pt == NULL){ 
        No *novo = (No*)malloc(sizeof(No));
        novo->chave = x;
        novo->esq = novo->dir = NULL;
        novo->bal = 0;
        novo->altura = 0;

        (*pt) = novo;
        h = true;
    }else{
        if(x == (*pt)->chave){
            printf("Elemento %d já existe\n", x);
        }else{
            if(x < (*pt)->chave){
                inserirAVL(x, (*pt)->esq, h);
                switch(getBal(pt)){
                    case 1: (*pt)->bal = 0; h = false; break;
                    case 0: (*pt)->bal = -1; break;
                    case -1: caso1(pt,h); break;
                }
            }else{
                inserirAVL(x, (*pt)->dir, h);
                switch(getBal(pt)){
                    case 1: (*pt)->bal = 0; h = false; break;
                    case 0: (*pt)->bal = -1; break;
                    case -1: caso2(pt,h); break;
                } 
            }
        }
    }
}

int main(){
    bool h = false;
    int f;
    No *ptraiz = NULL;
    No **pt = &ptraiz;

    inserir(12, &ptraiz);
    inserir(9, &ptraiz);
    inserir(70, &ptraiz);
        
    remover(9, &ptraiz);

    if(ptraiz != NULL)
        preordem(ptraiz);
    else
        printf("AV");
    printf("\n");

    return 0;
}