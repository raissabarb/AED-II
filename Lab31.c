/* 
***** Exercício 3.1 - AED II *****      100 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 03/11/2021   
*/

#include <stdio.h>
#include <stdlib.h>

int bubbleSort(int tam, int *seq){
    int i, j, aux, cont=0;
    for (i=0; i<tam; i++){  
        for (j=i+1; j<tam; j++){    
            if (seq[i] > seq[j]){      // Verificando se o número atual da análise é maior do que o próximo da lista
                aux = seq[i];      // Em caso positivo, a troca é feita a partir dessa pequena lógica
                seq[i] = seq[j];
                seq[j] = aux;
                cont++;
            }
        }
    }
    return cont;
}

int main(){

    int tam, i, winner;
    scanf("%d", &tam);
    if (tam <= 1000){
        int seq[tam];
        for (i=0; i<tam; i++){   
            scanf("%d", &seq[i]);      // Pegando os valores do vetor
        }
        winner = bubbleSort(tam, seq);      // Atribuindo um valor para a função para contabilizar o vencedor posteriormente
        for (i=0; i<tam; i++){   
            printf("%d ", seq[i]);
        }
        printf("\n");
        if (winner%2 == 0){      // Lógica para ver o vencedor, caso o número de trocas seja ímpar, o ganhador é o Marcelo, caso contrário, o Carlos     
            printf("Carlos");     
        } else printf("Marcelo");
    }
    return 0;
}