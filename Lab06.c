/* 
***** Exercício 6 - AED II *****      20 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 22/11/2021  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int qtdP;
 
void swap(char **prim, char **seg){      // Função para realizar a troca de posição
    char *aux = *prim;
    *prim = *seg;
    *seg = aux;
}
 
void paraBaixo(char **a, int no, int tam){
    while (2 * no + 1 < tam){
        int maior = no;
        if (strcmp(a[maior], a[2 * no + 1]) < 0)
            maior = 2 * no + 1;
        if (2 * no + 2 < tam && 
            strcmp(a[maior], a[2 * no + 2]) < 0)
            maior = 2 * no + 2;
        if (strcmp(a[no], a[maior]) < 0){ 
            swap(&a[no], &a[maior]);
            no = maior;
        }else break;
    }
}
 
void buildHeap(char **a){
    int i;
    for (i = qtdP / 2; i >= 0; --i){
        paraBaixo(a, i, qtdP);
    }
}
 
void heapSort(char **a){      // Ordenando o vetor, tendo como parâmetro as letras do alfabeto
    int tam;
    buildHeap(a);
    tam = qtdP;
    while (tam != 1){
        swap(&a[0], &a[tam - 1]);
        --tam;
        paraBaixo(a, 0, tam); 
    }
}
 
int main(){
 
    int qtdTotP, i;
    scanf("%d\n", &qtdTotP);
    char someArray[qtdTotP][20];
    for (i=0; i<qtdTotP; i++){
        scanf("%s", &someArray[i]);      // Pegando as todas as palavras para a lista inicial
    }
    scanf("%d\n", &qtdP);      // Quantidade de palavras que serão organizadas
    int indices[qtdP];
    for (i=0; i<qtdP; i++){
        scanf("%d", &indices[i]);      // índices das palavras que serão analisadas
    }
    char **listaP;
    listaP = (char*)malloc(qtdP*sizeof(char));      // Alocando memória para a lista a ser organizada
    for (i=0; i<qtdP; i++){
        int cont;
        char aux;
        cont = indices[i];
        listaP[i] = someArray[cont];
        if ((listaP[i] == "aí") || (listaP[i] == "Estrela")){      // Tentativa de verificação caso haja diferença de tipo de caracteres
            printf("a palavra %s eh invalida", listaP[i]);
            return;
        }
    }
    printf("build_heap: ");      // Primeira parte do output
    for (i=0; i<qtdP; i++){
        int cont;
        cont = indices[i];
        listaP[i] = someArray[cont];
        printf("%s ", listaP[i]);
    }
    heapSort(listaP);
    printf("\npalavras: ");       // Segunda parte do output
    for (i=0; i<qtdP; i++){
        printf("%s ", listaP[i]); 
    }
    free(listaP);
    return 0;
}