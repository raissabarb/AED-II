#include <stdio.h>
#include <stdlib.h>
#define ordem 5
#define maximoDeChaves ordem -1
#define minimoDeChaves 2

typedef int TipoChave;

typedef struct{ 
    TipoChave chave;
/* ... */
} Registro;

typedef struct _No{
    int numChaves;
    Registro registros[maximoDeChaves];
    struct _No *filhos[ordem];
} No;

typedef No *ArvoreB;

void inserir(Registro reg, ArvoreB *arvore){
    int cresceu;
    Registro regRetorno;
    No *filhoDir;
    No *novaRaiz;
    inserirAux(reg, *arvore, &cresceu, &regRetorno, &filhoDir);
    if (cresceu) { /*Aumetará a altura da árvore criando uma nova raiz*/
        novaRaiz = (No *) malloc(sizeof(No));
        novaRaiz->numChaves = 1;
        novaRaiz->registros[0] = regRetorno;
        novaRaiz->filhos[1] = filhoDir;
        novaRaiz->filhos[0] = *arvore;
        *arvore = novaRaiz;
    }
}

void inserirAux(Registro reg, ArvoreB arvore, int *cresceu, Registro
*regRetorno, ArvoreB *arvRetorno)
{
    No *temp;
    int i, j;
    if (arvore == NULL){ /*O nó anterior é o ideal para inserir a nova chave*/
        *cresceu = 1;
        *regRetorno = reg;
        *arvRetorno = NULL;
        return;
    }
    /*desce na árvore para localizar o nó folha onde deve-se inserir a chave*/
    for (i=1; i < arvore->numChaves && reg.chave > arvore->registros[i - 1].chave; i++);
    if (reg.chave == arvore->registros[i - 1].chave){/*chave já pertence a árvore*/
        printf("\n Erro: Registro ja esta presente.\n");
        *cresceu = 0;
        return;
    }
    if (reg.chave < arvore->registros[i - 1].chave)
        inserirAux(reg, arvore->filhos[i - 1], cresceu, regRetorno, arvRetorno);
    else
        inserirAux(reg, arvore->filhos[i], cresceu, regRetorno, arvRetorno);
    if (!*cresceu)
        return;
    if (arvore->numChaves < maximoDeChaves){ /* Nó tem espaço para inserção da nova chave*/
        inserirChaveNoNo(arvore, *regRetorno, *arvRetorno);
        *cresceu = 0;
        return;
    }
    /* Overflow: Nó tem que ser dividido */
    temp = (No *) malloc(sizeof(No));
    temp->numChaves = 0;
    temp->filhos[0] = NULL;
    if (i <= minimoDeChaves + 1) /*Insere adequadamente a chave no*/
    { /*novo nó ou no nó atual*/
        inserirChaveNoNo(temp, arvore->registros[maximoDeChaves - 1],
        arvore->filhos[maximoDeChaves]);
        arvore->numChaves--;
        inserirChaveNoNo(arvore, *regRetorno, *arvRetorno);
    }
    else
        inserirChaveNoNo(temp, *regRetorno, *arvRetorno);
    for (j = minimoDeChaves + 2; j <= maximoDeChaves; j++)
        inserirChaveNoNo(temp, arvore->registros[j - 1], arvore->filhos[j]);
    arvore->numChaves = minimoDeChaves;
    temp->filhos[0] = arvore->filhos[minimoDeChaves + 1];
    *regRetorno = arvore->registros[minimoDeChaves];
    *arvRetorno = temp;
}

void inserirChaveNoNo(ArvoreB arvore, Registro reg, No *subArvDir){
    int k;
    int naoAchouPosicao;
    k = arvore->numChaves;
    naoAchouPosicao = k > 0;
    while (naoAchouPosicao){
        if (reg.chave >= arvore->registros[k - 1].chave){
            naoAchouPosicao = 0;
            break;
        }
        arvore->registros[k] = arvore->registros[k - 1];
        arvore->filhos[k + 1] = arvore->filhos[k];
        k--;
        if (k < 1)
            naoAchouPosicao = 0;
    }
    arvore->registros[k] = reg;
    arvore->filhos[k + 1] = subArvDir;
    arvore->numChaves++;
}





/*#include <stdio.h>      20 PONTOS POR ENQUANTO
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
    scanf("%d", &numPesquisar);
    
    busca2 = buscarElem(raiz, numPesquisar);

    printf("%d\n", 1);
    if(busca2 == NULL) printf("Valor nao encontrado");
        
    return 0;
}*/