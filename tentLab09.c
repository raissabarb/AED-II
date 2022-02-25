#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int num;
    struct no *dir;      // ponteiros para apontar os filhos de cada folha
    struct no *esq;
    int altura;
} AVL;

void iniciar(AVL *raiz){      // iniciando a árvore com 0 elementos, por isso nula
    return NULL;
}

AVL* novoNo(int num){
    AVL *new = malloc(sizeof(AVL));
    if (new){
        new->num = num;
        new->dir = NULL;
        new->esq = NULL;
        new->altura = 0;
    } //// else para dar erro de alocação --------------
    return new;
}

int maiorNo(int x, int y){
    if (x > y){
        return x;
    } else return y;
}

int alturaNo(AVL *no){
    if (no == NULL){
        return -1;  
    } else{
        return no->altura;
    }
}

int fatBalanceamento(AVL *no){
    int aux;
    if (no){
        aux = alturaNo(no->esq) - alturaNo(no->dir);
        return aux;
    } else return 0;
}

AVL* rotacaoEsq(AVL *raiz){      // função para balancear a árvore caso ela tenda para a direita
    AVL *aux, *filhoAux;
    aux = raiz->dir;      // colocando os papeis de cada nó próximo ao que se encontra desbalanceado
    filhoAux = aux->esq;
    aux->esq = raiz;      // reposicionando os nós de forma balanceada e atualizando alturas
    raiz->dir = filhoAux;
    raiz->altura = maiorNo(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    aux->altura = maiorNo(alturaNo(aux->esq), alturaNo(aux->dir)) + 1;
    return aux;
}

AVL* rotacaoDir(AVL *raiz){      // função para balancear a árvore caso ela tenda para a esquerda
    AVL *aux, *filhoAux;
    aux = raiz->esq;
    filhoAux = aux->dir;
    aux->dir = raiz;
    raiz->esq = filhoAux;
    raiz->altura = maiorNo(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    aux->altura = maiorNo(alturaNo(aux->esq), alturaNo(aux->dir)) + 1;
    return aux;
}

AVL* rotacaoDirEsq(AVL *raiz){      // acontece quando temos a árvore tendendo para a direita e o nó filho tem um filho na esquerda
    raiz->dir = rotacaoDir(raiz->dir);      // o nó mais abaixo vai para o meio
    return rotacaoEsq(raiz);      // rotação colocando o do meio como raiz
}

AVL* rotacaoEsqDir(AVL *raiz){      // acontece quando temos a árvore tendendo para a esquerda e o nó filho tem um filho na direita
    raiz->esq = rotacaoEsq(raiz->esq);
    return rotacaoDir(raiz);
}

AVL* balanceamento(AVL *raiz){
    int fatB = fatBalanceamento(raiz);
    if ((fatB < 1) && (fatBalanceamento(raiz->dir) <= 0)){
        raiz = rotacaoEsq(raiz);
    } else if ((fatB > 1) && (fatBalanceamento(raiz->esq) >= 0)){
        raiz = rotacaoDir(raiz);
    } else if ((fatB < -1) && (fatBalanceamento(raiz->dir) > 0)){
        raiz = rotacaoDirEsq(raiz);
    } else if ((fatB > 1) && (fatBalanceamento(raiz->esq) < 0)){
        raiz = rotacaoEsqDir(raiz);
    }
    return raiz;
}

AVL* inserir(AVL *raiz, int num){
    if (raiz ==NULL){      // caso a árvore ainda esteja vazia, esse número será o primeiro nó, ou seja, a raiz
        return novoNo(num);
    } else{
        if (num < raiz->num){      // se o número for menor que a raiz, ele será destinado a ir para a esquerda, seguindo a regra das árvores
            raiz->esq = inserir(raiz->esq, num);
        } else{      // caso contrário à condição
            raiz->dir = inserir(raiz->dir, num);
        } ///// else para quando o elemento ja existe ------------
    }
    // atualizando a altura do nó
    raiz->altura = maiorNo(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    raiz = balanceamento(raiz);
    return raiz;
}

AVL* buscarElem(AVL *raiz, int num){
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

int testeAltura(AVL *raiz, int num){
    int contD=0, contE=0;
    while(raiz){
        if (num < raiz->num){      
            contE++;
            printf("passando para ESQ\n");
            raiz = raiz->esq;
            
        } else if (num > raiz->num){   
            contD++;
            printf("passando para DIR\n");
            raiz = raiz->dir;
            
        } else{
            printf("contD - %d\ncontE - %d\n", contD, contE);
            return raiz->altura;     
        }
    }
    return -1;
}

int alturaTeste(AVL *no){
	int height_esq = 0;
	int height_dir = 0;
	if(no->esq) height_esq = alturaTeste(no->esq);
	if(no->dir) height_dir = alturaTeste(no->dir);
	return height_dir > height_esq ? ++height_dir : ++height_esq;
}

/*int alturaNoEspecif(AVL *raiz, int valor){  //// teste
    AVL *no = buscarElem(raiz, valor);
    if (no){
        return alturaNo(no);
    } else return -1;
}*/

AVL* remover(AVL *raiz, int chave){
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
                    AVL *aux = raiz->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                    raiz->num = aux->num;
                    aux->num = chave;
                    raiz->esq = remover(raiz->esq, chave);
                    return raiz;
                }
                else{      // remover nós que possuem apenas 1 filho
                    AVL *aux;
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
            else raiz->dir = remover(raiz->dir, chave);
        }
    }
    raiz->altura = maiorNo(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    raiz = balanceamento(raiz); /// conferir dps ----------
    return raiz;
}

void imprimir(AVL *raiz, int nivel){
    int i;
    if (raiz){
        imprimir(raiz->dir, nivel + 1);
        printf(" ");
        printf("%d ", raiz->num);
        imprimir(raiz->esq, nivel + 1);
    }
}

int main(){

    AVL *busca, *busca2, *raiz = NULL;
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
    alturaPrin = alturaNo(raiz);
    alturaEsq = alturaNo(raiz->esq) + 1; //// mudei aqui ----------- 
    alturaDir = alturaNo(raiz->dir) + 1;
    while (aux2 == 0){
        scanf("%d", &num2);      // pegando mais números para verificar existência na árvore
        if (num2 > 0){  
            busca = buscarElem(raiz, num2);
            if (busca){
                raiz = remover(raiz, num2); //// alterei aqui ----------
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
    //printf("busca2 - %d\n", busca2->num);
    /*raiz->num = numPesquisar;
    if (busca2){
        cont = 1;
        altP2 = alturaNo(raiz);      // calculando a altura principal, da ramificação da esquerda e da direita da árvore depois das alterações
        altE2 = alturaNo(raiz->esq);
        altD2 = alturaNo(raiz->dir);
        printf("altura teste - %d\n", testeAltura(busca2, numPesquisar));
    } else{
        cont = 0;
    }*/
    printf("num %d\n", busca2->altura);
    if (busca2 != NULL){
        raiz = balanceamento(raiz);
        cont = 1;
        altP2 = alturaNo(raiz);      // calculando a altura principal, da ramificação da esquerda e da direita da árvore depois das alterações
        altE2 = alturaNo(raiz->esq) + 1;
        altD2 = alturaNo(raiz->dir) + 1;
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

/*

printf("buscar2 - %d\nnum busca2 - %d\n", busca2, busca2->num);
    int altura;
    altura = alturaNo(busca2);
    printf("altura - %d\n", altura);



altP2 = alturaNo(busca2);      // calculando a altura principal, da ramificação da esquerda e da direita da árvore depois das alterações
        if (altP2 == -1) altP2 = 0;
        altE2 = alturaNo(busca2->esq) + 1;
        if (altE2 == -1) altE2 = 0;
        altD2 = alturaNo(busca2->dir) + 1;
        if (altD2 == -1) altD2 = 0;



if (busca2){
        cont = 1;
        altP2 = alturaNoEspecif(raiz, numPesquisar);      // calculando a altura principal, da ramificação da esquerda e da direita da árvore depois das alterações
        altE2 = alturaNo(raiz->esq);
        altD2 = alturaNo(raiz->dir);
    } else{
        cont = 0;
    }



*/