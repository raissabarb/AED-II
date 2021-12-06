/* 
***** Exercício 8 - AED II *****      70 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 06/12/2021  
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int num;
    struct no *dir;      // ponteiros para apontar os filhos de cada folha
    struct no *esq;
} arvBinBusca;

void iniciar(arvBinBusca *raiz){      // iniciando a árvore com 0 elementos, por isso nula
    return NULL;
}

arvBinBusca* inserir(arvBinBusca *raiz, int num){
    arvBinBusca *new;
    new = malloc(sizeof(int));
    if (raiz ==NULL){      // caso a árvore ainda esteja vazia, esse número será o primeiro nó, ou seja, a raiz
        new->num = num;
        new->esq = NULL;
        new->dir = NULL;
        return new;
    } else{
        if (num < raiz->num){      // se o número for menor que a raiz, ele será destinado a ir para a esquerda, seguindo a regra das árvores
            raiz->esq = inserir(raiz->esq, num);
        } else{      // caso contrário à condição
            raiz->dir = inserir(raiz->dir, num);
        }
        return raiz;
    }
}

arvBinBusca* buscarElem(arvBinBusca *raiz, int num){
    while(raiz){
        if (num < raiz->num){      // uma vez que a folha possui flhos, caso o numero procurado seja menor que o analisado no momento, a procura seguirá para a ramificação à esquerda
            raiz = raiz->esq;
        } else if (num > raiz->num){     // já se for maior, seguirá procurando no sentido aos filhos da direita
            raiz = raiz->dir;
        } else{
            return raiz;      // se nenhum dos casos anteriores forem satisfeitos, o numero procurado é a própria raiz da árvore
        }
    }
    return NULL;
}

int altura(arvBinBusca *raiz){
    if (raiz == NULL){
        return -1;
    } else{
        int arvEsq = altura(raiz->esq);      // calculando a altura
        int arvDir = altura(raiz->dir);
        if (arvEsq > arvDir){
            return arvEsq + 1;
        } else return arvDir + 1;
    }
}

arvBinBusca* remover(arvBinBusca *raiz, int chave){
    if(raiz == NULL){
        return NULL;
    } else {      // procura o nó a remover
        if(raiz->num == chave){      // remove nós folhas (nós sem filhos)
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            }
            else{      // remover nós que possuem 2 filhos
                if(raiz->esq != NULL && raiz->dir != NULL){
                    arvBinBusca *aux = raiz->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                    raiz->num = aux->num;
                    aux->num = chave;
                    raiz->esq = remover(raiz->esq, chave);
                    return raiz;
                }
                else{      // remover nós que possuem apenas 1 filho
                    arvBinBusca *aux;
                    if(raiz->esq != NULL)
                        aux = raiz->esq;
                    else
                        aux = raiz->dir;
                    free(raiz);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->num)
                raiz->esq = remover(raiz->esq, chave);
            else
                raiz->dir = remover(raiz->dir, chave);
            return raiz;
        }
    }
}

void imprimir(arvBinBusca *raiz){
    if (raiz){
        printf("%d ", raiz->num);
        imprimir(raiz->esq);
        imprimir(raiz->dir);
    }
}

void imprimirOrdenado(arvBinBusca *raiz){
    if (raiz){
        imprimir(raiz->esq);
        printf("%d ", raiz->num);
        imprimir(raiz->dir);
    }
}

int main(){

    arvBinBusca *busca, *busca2, *raiz = NULL;
    iniciar(raiz);      // iniciando a árvore
    int num, num2, aux=0, aux2=0, numPesquisar;
    while (aux == 0){
        scanf("%d", &num);      // pegando a primeira lista de números e colocando cada número na árvore
        if (num > 0){
            raiz = inserir(raiz, num);
        } else{
            aux = 1;
        }
    }
    int alturaPrin, alturaEsq, alturaDir;      // calculando a altura principal, da ramificação da esquerda e da direita da árvore antes das alterações
    alturaPrin = altura(raiz);
    alturaEsq = altura(raiz->esq) + 1;
    alturaDir = altura(raiz->dir) + 1;
    while (aux2 == 0){
        scanf("%d", &num2);      // pegando mais números para verificar existência na árvore
        if (num2 > 0){  
            busca = buscarElem(raiz, num2);
            if (busca){
                remover(raiz, num2);
            } else{
                raiz = inserir(raiz, num2);
            }
        } else{
            aux2 = 1;      // contador auxiliar para manter o loop
        }
    }
    int altP2, altE2, altD2, cont;
    scanf("%d", &numPesquisar);
    busca2 = buscarElem(raiz, numPesquisar);
    if (busca2 != NULL){
        cont = 1;
        altP2 = altura(busca2);      // calculando a altura principal, da ramificação da esquerda e da direita da árvore depois das alterações
        altE2 = altura(busca2->esq) + 1;
        altD2 = altura(busca2->dir) + 1;
    } else{
        cont = 0;
    }
    printf("%d, %d, %d\n", alturaPrin, alturaEsq, alturaDir);      // output
    if (cont == 1){
        printf("%d, %d, %d", altP2, altE2, altD2);
    } else{
        printf("Valor nao encontrado");
    }
    return 0;
}