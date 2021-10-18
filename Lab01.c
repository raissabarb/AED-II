/* 
***** Exercício 1 - AED II *****
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 18/10/2021 
*/

#include <stdio.h>
#include <stdlib.h>

void numPrimo (int num){
    int i, qtdDiv;
    qtdDiv = 0;
    for (i=2; i<num; i++){
        if (num % i == 0){
            qtdDiv++;
        }
    }
    if (qtdDiv == 0){
        printf("%d %d\n", num, 1);
    } else if (qtdDiv != 0){
        printf("%d %d\n", num, 0);
    }
}

int main(){

    int qtdNum, num, i;
    scanf("%d", &qtdNum);
    for (i=0; i<qtdNum; i++){
        scanf("%d", &num);
        if ((num == 0) || (num == 1)){
            printf("%d %d\n", num, 0);
        } else numPrimo(num);
    }

    return 0;
}