/* 
***** Exercício 1 - AED II *****      100 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 18/10/2021 
*/

#include <stdio.h>
#include <stdlib.h>

void numPrimo (int num){
    int i, qtdDiv;
    qtdDiv = 0;              //variável destinada a quantificar os possíveis divisores do número em análise
    for (i=2; i<num; i++){   //loop para verificação
        if (num % i == 0){
            qtdDiv++;
        }
    }
    if (qtdDiv == 0){        //como verifiquei a partir do n° 2, caso tenha algum divisor, não é primo
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
        if ((num == 0) || (num == 1)){   //verificando os casos para 1 e 0 que não são primos, para não entrar na função numPrimo
            printf("%d %d\n", num, 0);
        } else numPrimo(num);
    }

    return 0;
}