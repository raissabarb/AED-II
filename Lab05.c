/* 
***** Exercício 5 - AED II *****      100 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 17/11/2021  
*/

#include <stdio.h>
#include <stdlib.h>

void troca(int *seq, int a, int b){      // Função para fazer a troca entre os elementos quando um é menor que outro na lógica
	int temp = seq[a];
	seq[a] = seq[b];
	seq[b] = temp;
}

int modifica(int *seq, int num, int left, int right){
    int j, i = left;
    for (j=left; j<=right-1; j++){
        if (seq[j] <= num){      // Após fazer a verificação entre os contadores da esquerda e da direita, caso haja necessidade, a função para fazer a trca é chamada
            troca(seq, i, j);
            i++;
        }
    }
    return i;
}

int particiona(int *seq, int esq, int dir){      // Função que vai fazer a partição do vetor
    int x, aux=0;
	x = seq[dir];
    aux = modifica(seq, x, esq, dir);
    troca(seq, aux, dir);
    return aux;      // Retorno da posição do pivô já em seu local ordenado
}

int encontraNum(int *seq, int esq, int dir, int aux){      // Função para retornar uma das informações pedidas 
	int indice;
    if ((aux>0) && (aux<=(dir-esq)+1)){
        indice = particiona(seq, esq, dir);
        if ((indice-esq) == (aux-1)){
            return seq[indice];
        } else if ((indice-esq) > (aux-1)){
            return encontraNum(seq, esq, indice-1, aux);
        } else {
            return encontraNum(seq, indice+1, dir, aux-indice+esq-1);
        }
    }
    return 0; 
}

int main(){

	int tam, posNumChave, i;
    scanf("%d\n", &posNumChave);      // Número da posição do número chave que é pedido
	scanf("%d\n", &tam);      // Tamanho do vetor
    int seq[tam];	
    for (i=0; i<tam; i++){      // Colocando os valores no vetor
        scanf("%d", &seq[i]);
    }
    printf("%do menor elemento eh o %d\n", posNumChave, encontraNum(seq, 0, tam - 1, posNumChave));     // Output parte 1
	for (i=0; i<tam; i++){
		printf("%d ", seq[i]);      // Output parte 2, com o número chave em seu devido lugar
	}
	return 0;
}