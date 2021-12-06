/*#include <stdio.h>
#include <stdlib.h>

void quickSort(int *seq, int tam){
    ajudaOrdenacao(seq, 0, tam-1);
}

void ajudaOrdenacao(int *seq, int prim, int ult){
    int divisao=0;
    if (prim < ult){
        divisao = particao(seq, prim, ult);
        // iria começar a partição para ordenar propriamente dizendo
        ajudaOrdenacao(seq, prim, div-1);
        ajudaOrdenacao(seq, div+1, ult);
    }
}

int particao(int *seq, int prim, int ult){
    int pivo, esquerda, direita, aux=0, cont;
    pivo = seq[prim]; // mudar para ultimo
    esquerda = prim+1;
    direita = ult;
    while (aux == 0){
        while ((esquerda <= direita) && (seq[esquerda] <= pivo)){
            esquerda++;
        }
        while ((seq[direita] >= pivo) && (direita >= esquerda)){
            direita--;
        }
        if (direita < esquerda){
            aux = 1;
        } else{
            cont = seq[esquerda];
            seq[esquerda] = seq[direita];
            seq[direita] = cont;
        }
    }
    cont = seq[prim];
    seq[prim] = seq[direita];
    seq[direita] = cont;
    printf("val direita - %d", direita);
    return direita;
}

int main(){

    int tam, posNumChave, i, numChave;
    //scanf("%d\n", &posNumChave);
	scanf("%d\n", &tam);
    int seq[tam];	
    for (i=0; i<tam; i++){
        scanf("%d", &seq[i]);
    }
	quickSort(seq, tam);
	/*numChave = encontraNumChave(seq, tam, posNumChave);
    printf("%do menor elemento eh o %d\n", posNumChave, numChave);
	for (i=0; i<tam; i++){
		printf("%d ", seq[i]);
	}

    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>

int particiona(int *vector,int inicio,int fim){
    int i,j,guarda,aux;
    i = inicio-1, j = inicio, guarda = vector[fim];

    while(j < fim){
        if((vector[j]>vector[i]) && (vector[j]<guarda) && (j-i)<=1){
        i++;
        j++;
    }
    if((vector[j] > vector[i]) && (vector[j] > guarda)){
        j++;

    }
    if((vector[i] > vector[j]) && (vector[j] < guarda) && (j-i)>1){
        aux = vector[j];
        vector[j] = vector[i+1];
        vector[i+1] = aux;
        i++,j++;
    }
    if((vector[j] > vector[i]) && (vector[j] < guarda) && (j-i)>1){
        aux = vector[j];
        vector[j] = vector[i+1];
        vector[i+1] = aux;
        i++,j++;
    }
 }
   vector[fim] = vector[i+1];
   vector[i+1] = guarda;
   return (j-1);
}
void ordena(int *vector,int inicio,int fim,int tam){
    if(inicio < fim){
    int j,i;
    j = particiona(vector,inicio,fim);
    if(j == tam-1){
        for(i=1; i<tam+1; i++)
            printf("%d ",vector[i]);
    }
    ordena(vector,inicio,j-1,tam);
    ordena(vector,j+1,fim,tam);
  }
}

int main(void){
    int *vector,i=1,N,num;
    scanf("%d",&N);
    vector = (int *)malloc((N+1)*sizeof(int));
    vector[0] = -1;
    while(i < (N+1)){
    scanf("%d",&num);
    vector[i++] = num;
   }
   ordena(vector,1,N,N);
   printf("\n");
   for(i=1; i<N+1; i++)
    printf("%d ",vector[i]);
  return 0;
}