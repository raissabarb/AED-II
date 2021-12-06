/* 
***** Exercício 3.2 - AED II *****      100 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 03/11/2021   
*/

#include <stdio.h>
#include <string.h>

int buscaBinaria(int *seq, int num, int ini, int fim){
    int meio;
    meio = (ini + fim)/2;      // Definindo o meio do vetor
    if (fim <= ini){      // Quando o número referenciado como ulimo é menor ou igual ao primeiro da análise atual, tem-se essa condicional
        if (num > seq[ini]){      // Caso o número buscado seja maior que o inicio
            return ini + 1;      // Retorna-se o posterior ao início
        } else return ini;      // Ou o próprioinício quando eles coincidem 
    }
    if (num == seq[meio]){      // Caso em que o número buscado é o do meio
        return meio + 1;
    } else if (num < seq[meio]){      // Caso onde o número buscado se encontra antes da metade do vetor
        return buscaBinaria(seq, num, ini, meio-1);      // A busca será feita redefinindo o final para o anterior a metade do vetor
    } else return buscaBinaria(seq, num, meio+1, fim);      // Caso contrário, quem é redefinido é o início, passando a ser a posição posterior ao meio
}

void insertionSort_Recursivo(int *seq, int num, int cont){
    int posicao, chave, i;
    if (num <= 1) return;
    insertionSort_Recursivo(seq, num-1, cont+1);      // Verificação do vetor até que esteja tudo ok
    chave = seq[num-1];      // A chave será o número que está sendo analisado por ora, alternando até o final da lista/vetor
    i = num-2;
    posicao = buscaBinaria(seq, chave, 0, i);      // Chamada da busca binária para encontrar a posição do número
    while (i >= posicao){
        seq[i+1] = seq[i];      // Organização do vetor
        i--;
    }
    seq[i+1] = chave;
    printf("%d %d %d\n", cont, chave, posicao);      // Contador sempre presente para contabilizar quantidade de recursões 
}

int main(){

    int tam, i;
    scanf("%d\n", &tam);
    int seq[tam];
    for (i=0; i<tam; i++){
        scanf("%d", &seq[i]);      // Preenchendo o vetor
    }
    insertionSort_Recursivo(seq, tam, 1);
    for (i=0; i<tam; i++){   
        printf("%d ", seq[i]);      // Printando a sequência final
    }
    return 0;
}