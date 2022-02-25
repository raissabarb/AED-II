/* 
***** Exercício 9 - AED II *****      
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 13/12/2021                  50 pts - ok
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct ITEM{
	int num;
} item;


typedef struct arv{
	item numero;
	struct arv *esq;      // ponteiros para apontar os filhos de cada folha
	struct arv *dir;
	int altura;
} AVL;

AVL *inicializar(){      // iniciando a árvore com 0 elementos, por isso nula
	return NULL;
}

AVL *buscarElem(AVL *raiz, int num){
	if (raiz != NULL){
		if (raiz->numero.num == num){      // caso onde o elemento buscado é a própria raiz da árvore
			return raiz;
		}
		else{
			if (num > raiz->numero.num){      // uma vez que a folha possui flhos, caso o numero procurado seja maior que o analisado no momento, a procura seguirá para a ramificação à direita
			    return buscarElem(raiz->dir, num);      
			}else{      // caso o numero procurado seja menor que o analisado, a procura seguirá para a ramificação à esquerda
			    return buscarElem(raiz->esq, num);      
			}
		}
	}
	return NULL;
}

AVL *novoNo(){
    AVL *novo = (AVL*) malloc(sizeof(AVL));
    if (novo){
        return novo;
    } else{
        exit(1); //interrompe o programa
    }
}

int alturaArv(AVL *raiz){
    if (raiz == NULL){      // se não existe o nó, retorna a altura -1
        return -1;
    } else{
        return raiz->altura;
    }
}

int fatBalanceamento(AVL *raiz){
    int aux;
    aux = alturaArv(raiz->esq) - alturaArv(raiz->dir);
    return aux; 
}

int alturaArvore(AVL *raiz){
	int altD, altE;
	if (raiz == NULL){	
		return -1;
	}
	altE = alturaArvore(raiz->esq);
	altD = alturaArvore(raiz->dir);
	if (altE > altD){
		return altE + 1;
	} else{
		return altD + 1;
	}
}

int maiorElem(int x, int y){
	if (x > y){
		return x;
	}
	else return y;
}

void rotacaoDir(AVL **raiz){      // função para balancear a árvore caso ela tenda para a esquerda
	AVL *aux;
	aux  = (*raiz)->esq;      // colocando os papeis de cada nó próximo ao que se encontra desbalanceado
	(*raiz)->esq  = aux->dir;
	aux->dir = *raiz;      // reposicionando os nós de forma balanceada e atualizando alturas
	(*raiz)->altura = maiorElem(alturaArv((*raiz)->esq), alturaArv((*raiz)->dir)) + 1;      // atualização da altura do nó
	aux->altura = maiorElem (alturaArv(aux->esq), (*raiz)->altura)+1;
	*raiz = aux;
}

void rotacaoEsq(AVL **raiz){      // função para balancear a árvore caso ela tenda para a direita
	AVL *aux;
	aux  = (*raiz)->dir;      // colocando os papeis de cada nó próximo ao que se encontra desbalanceado
	(*raiz)->dir  = aux->esq;
	aux->esq = *raiz;      // reposicionando os nós de forma balanceada e atualizando alturas
	(*raiz)->altura = maiorElem(alturaArv((*raiz)->esq), alturaArv((*raiz)->dir)) + 1;      // atualização da altura do nó
	aux->altura = maiorElem (alturaArv(aux->esq), (*raiz)->altura)+1;
	*raiz = aux;
}

void rotacaoEsqDir(AVL **raiz){      // acontece quando temos a árvore tendendo para a esquerda e o nó filho tem um filho na direita
	rotacaoEsq( & (*raiz)->esq);      // o nó mais abaixo vai para o meio
	rotacaoDir(raiz);      // rotação colocando o do meio como raiz
}

void rotacaoDirEsq(AVL **raiz){      // acontece quando temos a árvore tendendo para a direita e o nó filho tem um filho na esquerda
	rotacaoDir( & (*raiz)->dir);      // o nó mais abaixo vai para o meio
	rotacaoEsq(raiz);      // rotação colocando o do meio como raiz
}

AVL* menorNum(AVL **raiz) {	     //procura pelo nó mais a esq
    AVL *aux, *aux2;
    aux = (*raiz);
    aux2 = (*raiz)->esq;
    while (aux2){
        aux = aux2;
        aux2 = aux2->esq;
    }
    return aux;
}

int inserir(AVL **raiz, int num){
    int cont;
	if (*raiz == NULL){      // caso a árvore ainda esteja vazia, esse número será o primeiro nó, ou seja, a raiz
		AVL *aux = novoNo();
		aux->numero.num = num;
		aux->altura = 0;
		aux->esq  = NULL;
		aux->dir = NULL;
        *raiz = aux;
		return 1;
	}
	AVL *arvAtual;
	arvAtual = *raiz;
    if (num < arvAtual->numero.num){      // se o número for menor que a raiz, ele será destinado a ir para a esquerda, seguindo a regra das árvores
        if ((cont = inserir( & (arvAtual->esq),num)) == 1){
            if (fatBalanceamento(arvAtual) >= 2){
                if (num < (*raiz)->esq->numero.num){
                    rotacaoDir(raiz);
                } else rotacaoEsqDir(raiz);
            }
        }
    } else{      // caso contrário à condição
        if (num > arvAtual->numero.num){
            if ((cont=inserir( & (arvAtual->dir),num)) == 1){
                if (fatBalanceamento(arvAtual) >= 2){
                    if (num > (*raiz)->dir->numero.num){
                        rotacaoEsq(raiz);
                    } else rotacaoDirEsq(raiz);
                }
            }
        } else{      // nenhuma das possibilidades atendidas
            return 0;
        }
    }
    arvAtual->altura = maiorElem(alturaArv(arvAtual->esq), alturaArv(arvAtual->dir)) + 1;      // atualizando a altura do nó
    return cont;
}

int remover(AVL **raiz,int num){
    int cont;
    if (*raiz == NULL){
        return 0;
    }
    if (num < (*raiz)->numero.num){
        if ((cont = remover( & ((*raiz)->esq),num)) == 1){
            if (fatBalanceamento(*raiz) >= 2){
                if (alturaArv((*raiz)->dir->esq) <= alturaArv((*raiz)->dir->dir)){
                    rotacaoEsq(raiz);
                } else rotacaoEsqDir(raiz);
            }
        }
    }
    if (num > (*raiz)->numero.num){
        if ((cont = remover( & ((*raiz)->dir),num)) == 1){
            if (fatBalanceamento(*raiz) >= 2){
                if (alturaArv((*raiz)->esq->dir) <= alturaArv((*raiz)->esq->esq)){
                    rotacaoDir(raiz);
                } else rotacaoDirEsq(raiz);
            }
        }
    }
    if ((*raiz)->numero.num == num){      // remove nós folhas (nós sem filhos)
        if (((*raiz)->esq == NULL) || ((*raiz)->dir == NULL)){
            AVL *aux = *raiz;
            if ((*raiz)->esq != NULL){
                *raiz=(*raiz)->esq;
            } else *raiz=(*raiz)->dir;
            free(aux);
            aux = NULL;
        } else{
            AVL *aux = menorNum( & (*raiz)->dir);
            (*raiz)->numero.num = aux->numero.num;
            remover( & (*raiz)->dir,(*raiz)->numero.num);
            if (fatBalanceamento(*raiz) >= 2){
                if (alturaArv((*raiz)->esq->dir) <= alturaArv((*raiz)->esq->esq)){
                    rotacaoDir(raiz);
                } else rotacaoEsqDir(raiz);
            }
        }
        return 1;
    }
    return cont;
}

int main(){

    AVL *raiz, *busca, *busca2;
    raiz = inicializar();
    int num, num2, aux=0, aux2=0, numbuscarElem;
    while (aux == 0){
        scanf("%d", &num);      // pegando a primeira lista de números e colocando cada número na árvore
        if (num > 0){
            inserir(&raiz, num);
        } else{
            aux = 1;
        }
    }

    int alturaPrin, altE, alturaDir;      // calculando a altura principal, da ramificação da esq e da dir da árvore antes das alterações
    alturaPrin = alturaArvore(raiz);  
    altE = alturaArvore(raiz->esq) + 1;
    alturaDir = alturaArvore(raiz->dir) + 1;
    while (aux2 == 0){
        scanf("%d", &num2);      // pegando mais números para verificar existência na árvore
        if (num2 > 0){  
            busca = buscarElem(raiz, num2);
            if (busca){
                remover(&raiz, num2);
            } else{
                inserir(&raiz, num2);
            }
        } else{
            aux2 = 1;      // contador auxiliar para manter o loop
        }
    }

    int altP2, altE2, altD2, cont;
    scanf("%d", &numbuscarElem);
    busca2 = buscarElem(raiz, numbuscarElem);
    if (busca2 != NULL){
        cont = 1;
        altP2 = alturaArvore(busca2);      // calculando a altura principal, da ramificação da esq e da dir da árvore depois das alterações
        altE2 = alturaArvore(busca2->esq) + 1;
        altD2 = alturaArvore(busca2->dir) + 1;
    } else{
        cont = 0;
    }
    printf("%d, %d, %d\n", alturaPrin, altE, alturaDir);      // output
    if (cont == 1){
        printf("%d, %d, %d", altP2, altE2, altD2);
    } else{
        printf("Valor nao encontrado");
    }
	
    return 0;
}