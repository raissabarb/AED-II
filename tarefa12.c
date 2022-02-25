//RA: 148756
#include <stdio.h>
#include <stdlib.h>
#define PRETO 0
#define VERMELHO 1

struct TNo {
	struct TNo *esq, *dir, *pai;
	int chave;
	int cor;
};

typedef struct TNo *No;

No raiz, NILL; 

/* cria novo no (inicia) */
void iniciaNo(No novo){
    novo = (struct TNo *)malloc(sizeof(struct TNo));
	novo->esq = NULL;
	novo->dir = NULL;
    novo->pai = NULL;
	novo->chave = 0;
	novo->cor = VERMELHO;
}

void rotacaoEsquerda(No x){
    No y;

    y = x->dir; /* define y */
    x->dir = y->esq; /*transforma a subarvore a esquerda de y na subarvore a direita de x */

    if(y->esq != NILL){
        y->esq->pai = x;
    }

    y->pai = x->pai; /* liga o pai de x a y */

    if(x->pai == NILL){
        raiz = y;
    } else if(x == x->pai->esq){
        x->pai->esq = y;
    } else {
        x->pai->dir = y;
    }

    y->esq = x; /* coloca x a esquerda de y */
    x->pai = y;
}

void rotacaoDireita(No x){
    No y;

    y = x->esq; /* define y */
    x->esq = y->dir; /* transforma a subarvore a direita de y na subarvore a esquerda de x */

    if(y->dir != NILL){
        y->dir->pai = x;
    }

    y->pai = x->pai; /* liga o pai de x a y */

    if(x->pai == NILL){
        raiz = y;
    } else if(x == x->pai->dir){
        x->pai->dir = y;
    } else {
        x->pai->esq = y;
    }

    y->dir = x; /* coloca x a direita de y */
    x->pai = y;
}

void arrumaInsercao(No z){
    No aux;

    while(z->pai->cor == VERMELHO){
        if(z->pai == z->pai->pai->esq){
            aux = z->pai->pai->dir;

            if(aux->cor == VERMELHO){ /* tio do aux de z eh vermelho */
                z->pai->cor = PRETO;
                aux->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if(z == z->pai->dir){ /* o tio do aux de z eh preto e z eh um filho a direita */
                    z = z->pai;
                    rotacaoEsquerda(z);
                }

                /* o tio do aux de z eh preto e z eh um filho a esquerda */
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(z->pai->pai);
            }
        } else if(z->pai == z->pai->pai->dir){ /* mesmas clausulas com esq e dir trocadas */
            aux = z->pai->pai->esq;

            if(aux->cor == VERMELHO){
                z->pai->cor = PRETO;
                aux->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if(z == z->pai->esq){
                    z = z->pai;
                    rotacaoDireita(z);
                }

                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(z->pai->pai);
            }
        }
    }
    raiz->cor = PRETO; /* a raiz eh sempre preta */
}

void Insercao(int valor){
    No z = (struct TNo *)malloc(sizeof(struct TNo));
    z->pai = NULL;
    z->chave = valor;
    z->esq = NILL;
    z->dir = NILL;
    z->cor = VERMELHO;

    No y = NULL;
    No x = raiz;

    while(x != NULL){
        y = x;

        if(z->chave < x->chave){
            x = x->esq;
        } else {
            x = x->dir;
        }
    }

    z->pai = y;

    if(y == NULL){
        raiz = z;
    } else if (z->chave < y->chave){
        y->esq = z;
    } else {
        y->dir = z;
    }

    if(z->pai->pai == NULL){
        z->cor = PRETO;
        return;
    }

    if(z->pai->pai == NULL){
        return;
    }

    arrumaInsercao(z);
}

No pesquisaNo(No no, int valor){

    if(no == NULL){
        return no;
    } else if (valor == no->chave){
        return no;
    }

    if(valor < no->chave){
        return pesquisaNo(no->esq, valor);
    } else {
        return pesquisaNo(no->dir, valor);
    }
}

int alturaNo(No z){

    if(z == NULL){
        return -1;
    } else {
        int he = alturaNo(z->esq);
        int hd = alturaNo(z->dir);

        if(he < hd){
            return hd + 1;
        } else {
            return he + 1;
        }
    }
}

int alturaNegra(No atual){

    if(atual == NULL || atual->esq == NULL && atual->dir == NULL){
        return 0;
    } else {
        int he = alturaNegra(atual->esq);
        int hd = alturaNegra(atual->dir);

        if(he > hd){
            return he + 1;
        } else {
            return hd + 1;
        }
    }
}

/* imprime a arvore */
void inOrder(No no){
	if (no){
        inOrder(no->esq);
		printf("%d ", no->chave);
		inOrder(no->dir);
	}
}

void mostra(No no){
    if(no == NULL){
        return;
    }
    printf("%d(", no->chave);
    mostra(no->esq);
    mostra(no->dir);
    printf(")");
}

int main(){

    int valor, chaves[1000], pesq, j, i = 0, k = 0;
    for(j = 0; j < 1000; j++){
        chaves[j] = -1;
    }
    scanf("%d", &valor);
    do {
        Insercao(valor);
        scanf("%d", &valor);
    } while (valor > -1);
    printf("\n");
    mostra(raiz);
    int hArv = alturaNo(raiz);
    int hSubDir = alturaNo(raiz->dir);
    int hSubEsq = alturaNo(raiz->esq);
    scanf("%d", &chaves[0]);
    if(chaves[0] != -1){
       do{
        i++;
        scanf("%d", &chaves[i]);
       } while (chaves[i] > -1);
    }
    scanf("%d", &pesq);
    printf("%d, %d, %d", hArv, hSubEsq+1, hSubDir+1);
    while(chaves[k] > -1){
        No temp = pesquisaNo(raiz, chaves[k]);

        if(temp == NULL){
            Insercao(chaves[k]);
        } else {
            int hChave = alturaNo(temp);
            int hCDir = alturaNo(temp->dir);
            int hCEsq = alturaNo(temp->esq);

            printf("\n%d, %d, %d", hChave, hCEsq+1, hCDir+1);
        }
        k++;
    }

    No aux = pesquisaNo(raiz, pesq);

    if(aux == NULL){
        printf("\nValor nao encontrado");
    } else {
        int hPesq = alturaNegra(aux);
        printf("\n%d", hPesq);
    }

    printf("\n");
    mostra(raiz);

    return 0;
}
