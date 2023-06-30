#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

typedef struct no *NO;

typedef struct no{
	int chave;
	char cor;
	NO dir, esq, pai;
}no;

NO externo = NULL;

void rotacaoE(NO *ptRaiz, NO x);
void rotacaoD(NO *ptRaiz, NO x);
int inserirChave(NO *ptRaiz, int chave);
int inserirRN(NO *ptRaiz, NO z);
void rotaRN(NO *ptRaiz, NO z);
void moverPai(NO *ptRaiz, NO u, NO v);

NO buscarNO(NO ptRaiz, int chave);

void rotaRemoverRN(NO *ptRaiz, NO x);
NO sucessor(NO x);
void removerRN(NO *ptRaiz, NO z);
void removerChave(NO *ptRaiz, int chave);

void esvazia(NO ptRaiz);

int contaNos(NO ptRaiz);
int verRN (NO ptRaiz);
int verAll(NO ptRaiz, int qnt, int ver);

int main(){
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));

    // ajeitando o externo aqui pq n deu certo fazer lá em cima
    externo = (NO) malloc(sizeof(struct no));
    externo->chave = 0;
    externo->cor = 'N';
    externo->dir = externo;
    externo->esq = externo;
    externo->pai = externo;

    // criando o ponteiro da raiz e apotando pro externo
    NO ptRaiz = externo;

    // testes

    int numeroDeArvores = 1000;
    int numeroDeNos = 10000;
    int numeroDeRemocoes = 1000;
    int intervaloChave = 100000;

    for(int i = 1; i <= numeroDeArvores; i++){

        int qntRepeticoes = 0;
        for(int j = 0; j < numeroDeNos; j++){
            qntRepeticoes += inserirChave(&ptRaiz, (rand()%(intervaloChave+1)));
        }
        printf("\nQnt de Nos A[%d]: %d, repeticoes %i", i, contaNos(ptRaiz), qntRepeticoes);

        
        for(int j = 0; j < numeroDeRemocoes; j++){
            removerChave(&ptRaiz, (rand()%(intervaloChave+1)));
            printf("\n%d", j);
        }
        printf(" -|- Qnt apos remocoes: %d", contaNos(ptRaiz));
        
       
        esvazia(ptRaiz);

        ptRaiz = externo;
    }
}

void rotacaoE (NO *ptRaiz, NO x) {
    NO y;
    y = x->dir;
    x->dir = y->esq;

    if (y->esq != externo){
        y->esq->pai = x;
    }

    y->pai = x->pai;

    if (x->pai == externo) {
        (*ptRaiz) = y;
    }else{ 
        if(x == x->pai->esq){
            x->pai->esq = y;
        }else{
            x->pai->dir = y;
        }
    }
    y->esq = x;
    x->pai = y;
}

void rotacaoD (NO *ptRaiz, NO x) {
    NO y;
    y = x->esq;
    x->esq = y->dir;

    if(y->dir != externo){
        y->dir->pai = x;
    }

    y->pai = x->pai;

    if(x->pai == externo){
        (*ptRaiz) = y;
    } else 
        if(x == x->pai->dir){
            x->pai->dir = y;
        } else {
            x->pai->esq = y;
        }
    y->dir = x;
    x->pai = y;
}

int inserirChave(NO *ptRaiz, int chave){
    NO novo = (NO)malloc(sizeof(struct no));
    novo->chave = chave;
    novo->dir = externo;
    novo->esq = externo;
    novo->pai = NULL;
    novo->cor = 'R';   
    return inserirRN(ptRaiz, novo);
}

int inserirRN(NO *ptRaiz, NO z){
    NO y, pt;
    y = externo;
    pt = *ptRaiz;

    while(pt != externo){
        y = pt;
        if(z->chave == pt->chave){
            //printf("Chave existente");
            y = NULL;
            pt = externo;
            return 1;
        }else{
            if(z->chave < pt->chave)
                pt = pt->esq;
            else
                pt = pt->dir;
        }
    }

    if(y != NULL){
        z->pai = y;
        if(y == externo){
            *ptRaiz = z;
        }else if(z->chave < y->chave){
            y->esq = z;
        }else{
            y->dir = z;
        }
        rotaRN(ptRaiz, z);
    }
    return 0;
}

void rotaRN (NO *ptRaiz, NO z) {
    NO y;
    while (z->pai->cor == 'R') {
        if(z->pai == z->pai->pai->esq){
            y = z->pai->pai->dir;
            if (y->cor == 'R') {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoE(ptRaiz, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                rotacaoD(ptRaiz, z->pai->pai);
            }
        }else{
            y = z->pai->pai->esq;
            if (y->cor == 'R') {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaoD(ptRaiz, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                rotacaoE(ptRaiz, z->pai->pai);
            }
        }
    }
    (*ptRaiz)->cor = 'N';
}

void moverPai (NO *ptRaiz, NO u, NO v) {
    if (u->pai == externo) {
        (*ptRaiz) = v;
    }else{
        if(u == u->pai->esq)
            u->pai->esq = v;
        else
            u->pai->dir = v;
    }
    v->pai = u->pai;
}

NO buscarNO (NO ptRaiz, int chave) {
    if(ptRaiz->chave == chave || ptRaiz == externo){
        return ptRaiz;
    }else{
        if(chave < ptRaiz->chave){
            buscarNO(ptRaiz->esq, chave);
        }else{
            buscarNO(ptRaiz->dir, chave);
        }
    }
}

void rotaRemoverRN (NO *ptRaiz, NO x) {
    NO w;

    while(x != (*ptRaiz) && x->cor != 'R') {
        if(x == x->pai->esq) { // filho da esquerda
            w = x->pai->dir; // irmão
            if(w->cor == 'R'){
                x->pai->cor = 'R';
                w->cor = 'N';
                rotacaoE(ptRaiz, x->pai);
                w = x->pai->dir;
            }
            if (w->dir->cor == 'N' && w->esq->cor == 'N'){
                w->cor = 'R';
                x= x->pai;
            }else{
                if(w->esq->cor == 'R') {
                    w->esq->cor =  'N';
                    w->cor = 'R';
                    rotacaoD(ptRaiz, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->dir->cor;
                w->dir->cor = 'N';
                rotacaoE(ptRaiz, x->pai);
                x = *ptRaiz;
            }
        }else{ // operação analoga, filho da direita
            w = x->pai->esq; // irmão
            if(w->cor == 'R'){
                x->pai->cor = 'R';
                w->cor = 'N';
                rotacaoD(ptRaiz, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == 'N' && w->esq->cor == 'N'){
                w->cor = 'R';
                x= x->pai;
            }else{
                if(w->dir->cor == 'R') {
                    w->dir->cor =  'N';
                    w->cor = 'R';
                    rotacaoE(ptRaiz, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->esq->cor;
                w->esq->cor = 'N';
                rotacaoE(ptRaiz, x->pai);
                x = *ptRaiz;
            }
        }
    }
    x->cor = 'N';
}

NO sucessor (NO x) {
    NO y = x;
    while (y->esq != externo) {
        y = y->esq;
    }
    return y;
}

void removerRN (NO *ptRaiz, NO z) {
    NO y = z;
    char corOriginal = y->cor;
    NO x;

    if(y->esq == externo){
        x = z->dir;
        moverPai(ptRaiz, z, z->dir);
    }else{ 
        if(y->dir == externo){
            x = z->esq;
            moverPai(ptRaiz, z, z->esq);
        }else{
            y = sucessor(z);
            corOriginal = y->cor;
            x = y->dir;
            if (y->pai != z) {
                moverPai(ptRaiz, y, x);
                y->dir = z->dir;
                y->pai->dir = y;
            }
            moverPai(ptRaiz, z, y);
            y->esq = z->esq;
            y->esq->pai = y;
        }
    }
    if (corOriginal == 'N') {
        rotaRemoverRN(ptRaiz, x);
    }
    (*ptRaiz)->cor = 'N';
}

void removerChave (NO *ptRaiz, int chave) {
    NO z = buscarNO((*ptRaiz), chave);
    NO aux = z;
    if (z != externo){
        removerRN(ptRaiz, z);
        free(aux);
    }
}

void esvazia (NO ptRaiz) {
    if (ptRaiz != externo) {
        esvazia(ptRaiz->dir);
        esvazia(ptRaiz->esq);
        free(ptRaiz);
    }
}

int contaNos(NO ptRaiz){
    if(ptRaiz == externo) return 0;
    else {
        int soma = 1;
        if(ptRaiz->esq != externo) soma += contaNos(ptRaiz->esq);
        if(ptRaiz->dir != externo) soma += contaNos(ptRaiz->dir);
        return soma;
    }
}

int verRN (NO ptRaiz){
    NO aux = ptRaiz;
    int qnt = 0;
    while(aux != externo){
        if(aux->cor == 'N') qnt++;
        aux = aux->esq;    
    }
    return verAll(ptRaiz, qnt, 0); // Se for igual a 0 não é RN
}

int verAll(NO ptRaiz, int qnt, int ver){
    if(ptRaiz != externo){
        if(ptRaiz->cor == 'N') ver = ver+1;

        int aux = verAll(ptRaiz->esq, qnt, ver);
        int aux2 = verAll(ptRaiz->dir, qnt, ver);

        if(aux > aux2) return aux2;
        else return aux;
    }else{
        if(ver != qnt) return 0;
        else return 1;
    }
}