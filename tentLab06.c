#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int qtdP;
 
void swap(char **first, char **second)
{
    char *temp = *first;
    *first = *second;
    *second = temp;
}
 
void siftDown(char **a, int node, int size)
{
    while (2 * node + 1 < size)
    {
        int largest = node;
        //If the child has a sibling and the child's value is less than its sibling's
        if (strcmp(a[largest],a[2 * node + 1]) < 0)
            largest = 2 * node + 1;
        if (2 * node + 2 < size && 
            strcmp(a[largest],a[2 * node + 2]) < 0)
            largest = 2 * node + 2;
 
        if (strcmp(a[node],a[largest]) < 0)
        { //out of max-heap order
            swap(&a[node], &a[largest]);
            node = largest;
        }
        else
            break;
    }
}
 
void makeHeap(char **a)
    //This function will play a in a max-heap order.
    //The shiftDown function is called.
{
    int i;
    for (i = qtdP / 2; i >= 0; --i)
        siftDown(a, i, qtdP);
}
 
void heapSort(char **a)
    //This function will sort the values using heap
    //sort. makeHeap and shiftDown functions are called.
{
    int size;
    makeHeap(a);//first place a in max-heap order
    size = qtdP;
 
    while (size != 1)
    {//swap the root(maximum value) of the heap with the last element of the heap
        swap(&a[0], &a[size - 1]);
        //decrease the size of the heap by one so that the previous max value will
        //stay in its proper placement
        --size;
        siftDown(a, 0, size);//put the heap back in max-heap order   
    }
}
 
int main(){
 
    int qtdTot, i;
    scanf("%d\n", &qtdTot);
    char listaInicial[qtdTot][20];
    for (i=0; i<qtdTot; i++){
        scanf("%s", &listaInicial[i]);
    }
    scanf("%d\n", &qtdP);
    int indices[qtdP];
    for (i=0; i<qtdP; i++){
        scanf("%d", &indices[i]);
    }
    char **listaP;
    listaP = (char*)malloc(qtdP*sizeof(char));
    for (i=0; i<qtdP; i++){
        int cont;
        cont = indices[i];
        listaP[i] = listaInicial[cont];
    }
    for (i=0; i<qtdTot; i++){      // tentativa de verificar caracteres diferentes
        printf("%s\n", listaInicial[i]);
        if ((listaInicial[i] == "aí") || (listaInicial[i] == "Estrela")){
            printf("a palavra %s eh invalida", listaInicial[i]);
            return;
        }
    }
    printf("build_heap: ");
    for (i=0; i<qtdP; i++){
        int cont;
        cont = indices[i];
        listaP[i] = listaInicial[cont];
        printf("%s ", listaP[i]);
    }
    heapSort(listaP);
    printf("\npalavras: ");
    for (i=0; i<qtdP; i++){
        printf("%s ", listaP[i]); 
    }
    free(listaP);
    return 0;
}