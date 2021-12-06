/* 
***** Exercício 4 - AED II *****      40 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 10/11/2021  
*/

#include <stdio.h>
#include <string.h>

int mergeSort(int i, int j, int *a, int *aux, int n, int numK){ 
    int meio, topoEsq, topoDir, k, cont=0, auxiliar=0; 
    if (j <= i){
        return;     
    }
    j = 1;
    while (auxiliar < n){      // Enquanto o contador auxiliar não chegar até o valor to tamanho do vetor, o loop é feito
        int condicao;
        condicao = numK * a[j];      // Parte da condição para contabilizar o que é pedido no exercício
        if ((a[i] > condicao) && (i < j)){
            cont++;      // Caso as condições sejam satisfeitas, o contador é incrementado, que será o output
        }
        if (j == n-1){      // Caso onde, após a verificação, o j é do tamanho do vetor
            i++;
            j = i+1;
        } else j++;      // Incrementação normal do j 
        auxiliar++;
    }
    // organização do vetor, caso desejar verificar
    meio = (i+j) / 2;
    mergeSort(i, meio, a, aux, n, numK);      // MergeSort na primeira metade do vetor    
    mergeSort(meio + 1, j, a, aux, n, numK);      // MergeSort na segunda metade do vetor         
    topoEsq = i;      // Norte para o primeiro elemento da sublista da esquerda     
    topoDir = meio + 1;      // Norte para o primeiro elemento da sublista da direita     
    for (k = i; k <= j; k++){
        if (topoEsq == meio + 1){      // Arrumando a lista caso o primeiro elemento da primeira lista é igual ao primeiro elemento da segunda lista     
            aux[k] = a[topoDir];
            topoDir++;
        } else if (topoDir == j + 1){      // Quando o primeiro elemento da segunda lista é igual ao ultimo elemento        
            aux[k] = a[topoEsq];
            topoEsq++;
        } else if (a[topoEsq] < a[topoDir]){      // Quando o elemento da primeira lista é menor que o elemento da segunda lista     
            aux[k] = a[topoEsq];
            topoEsq++;
        } else{      // Quando o elemento da primeira lista é maior que o elemento da segunda lista         
            aux[k] = a[topoDir];
            topoDir++;
        }
    }
    for (k = i; k <= j; k++){      // Copiando o vetor auxiliar pro vetor original
        a[k] = aux[k];
    }
    return cont;      // Contador que representa a saída
}


int main(){

    int a[1000], aux[1000], n, i, numK, cont=0, j, k;
    scanf("%d\n", &n);      // Quantidade de números para o vetor 
    scanf("%d\n", &numK);      // CConstante para fazer a multiplicação como pedido no enunciado
    for (i = 0; i < n; i++){
        scanf("%d", &a[i]);      // Preenchendo o vetor
    }    
    cont = mergeSort(0, n-1, a, aux, n, numK);
    printf("%d", cont);      // Output
    return 0;
}

/*

int encontraNumChave(int *seq, int tam, int pos){
    int i, cont=0;
    for (i=0; i<tam; i++){
        if (seq[i] == pos){
            cont = seq[i];
        }
    }
    return cont;
}

int main(){

	int tam, posNumChave, i, numChave;
    scanf("%d\n", &posNumChave);
    int seq[tam];	
    scanf("%d\n", &tam);
    for (i=0; i<tam; i++){
        scanf("%d", &seq[i]);
    }
	quicksort(seq, 0, tam);
	numChave = encontraNumChave(seq, tam, posNumChave);
    printf("%d° menor elemento eh o %d", posNumChave, numChave);
	for (i=0; i<tam; i++){
		printf("%d ", seq[i]);
	}

	return 0;
}

*/