#include <stdlib.h>
#include <string.h>

void merge(int *seq, int ini, int meio, int fim){
    int topoEsq, topoDir, tam;
    tam = fim-ini;
    int aux[tam];
    topoEsq = ini;
    topoDir = meio+1;
    while ((topoDir != 0) && (topoEsq != 0)){
        if (topoEsq)
    }

}

void mergeSort(int *seq, int ini, int fim){
    if (fim-ini > 1){
        int meio;
        meio = (fim+ini) / 2;
        mergeSort(seq, ini, meio);
        mergeSort(seq, meio+1, fim);
    }
}