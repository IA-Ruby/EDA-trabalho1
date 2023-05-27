#include <stdio.h>

//tipo nomeFuncao(parametros){ }
void primo(int x){

    int contador = 0;

    for(int i = 2; i < x; i++){
        if(x % i == 0){
            contador++;
        }
    }

    printf("\n%d ", x);
    if(contador == 0){
        printf("E primo\n");
    }else{
        printf("Nao e primo\n");
    }
}

int main(){
   
    primo(1);
    primo(23);
    primo(45);
    primo(27);
    primo(192);
    primo(1020);

    
    return 0;
}