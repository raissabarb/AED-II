/* 
***** Exercício 13 - AED II *****      
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 10/01/2022                    100 pts - okk
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no *prox;
} No;

typedef struct{
    No *ini;
    int tam; 
} Lista;

void iniciaLista(Lista *l){
    l->ini = NULL;
    l->tam = 0;
}

void inserirLista(Lista *l, int valor){      // Função para inserir os numeros na lista (cada linha do hash é uma lista)
    No *novo = malloc(sizeof(No));
    No *atual = l->ini;
    novo->prox = NULL;
    if (l->tam == 0){
        novo->chave = valor;
        novo->prox = l->ini;
        l->ini = novo;
    } else{
        while (atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = novo;
        novo->chave = valor;
        novo->prox = NULL;
    }
    l->tam++;
}

int buscarLista(Lista *l, int num){      // Função de busca que será auxiliar em buscas posteriores
    No *aux = l->ini;
    while(aux && aux->chave != num)
        aux = aux->prox;
    if(aux)
        return aux->chave;
    return -1;
}

int removerLista(Lista *l, int num){      // Remoção de itens
    No *ant, *atual;
    ant = l->ini;
    if (ant->chave == num){
        l->ini = ant->prox;
        free(ant);
        return 1;
    } else{
        atual = ant->prox;
        while (atual != NULL){
            if (atual->chave == num){
                ant->prox = atual->prox;
                free(atual);
                return 1;
            }
            ant = atual;
            atual = atual->prox;
        }
    }
    return -1; 
}

void imprimirLista(Lista *l){      // Função usada para imprimir a lista pedida no final do exercício
    No *aux = l->ini;
    while(aux){
        printf("%d ", aux->chave);
        aux = aux->prox;
    }
}

void iniciaTabelaH(Lista t[], int tam){ 
    int i;
    for(i=0; i<tam; i++)
        iniciaLista(&t[i]);
}

int funcaoHash(int num, int tam){      // Função de transformação 
    if (num == 0) return 0;
    return num % tam;
}

void inserir(Lista t[], int num, int tam){     
    int id = funcaoHash(num, tam);
    inserirLista(&t[id], num);      // Inserindo um elemento na lista correspondente à sua função de transformação
}

int buscar(Lista t[], int num, int tam){ 
    int id = funcaoHash(num, tam);
    return buscarLista(&t[id], num);
}

void buscarLinha(Lista t[], int num, int tam){      // Função para encontrar e imprimir a linha do numero que foi pedido, que está na tabela hash 
    int id = funcaoHash(num, tam), resultBusca, linha;
    printf("[%d] ", num); 
    imprimirLista(&t[id]);
}

int remover(Lista t[], int num, int tam){ 
    int id = funcaoHash(num, tam);
    return removerLista(&t[id], num);
}

int main(){

    int num, tam, aux=0;
    scanf("%d", &tam);      // Quantidade de elementos da tabela hash

    Lista listaNum[tam];
    iniciaTabelaH(listaNum, tam);      // Iniciando a tabela hash

    while (aux == 0){
        scanf("%d", &num);   
        if (num >= 0){ 
            inserir(listaNum, num, tam);      // Inserindo os números na tabela hash
        } else{
            aux = 1;
        }
    }

    int chave, resultBusca, removendo, cont;
    scanf("%d", &chave);      // Pegando a chave a ser procurada
    resultBusca = buscar(listaNum, chave, tam);     
    if (resultBusca != -1){
        cont = -1;
        removendo = remover(listaNum, chave, tam);      // Caso a chave seja encontrada ela será removida aqui
    } else cont = -2;      // Contador para confirmar que a mensagem de valor não encontrado terá que ser mostrada

    int linhaTabelaH;
    scanf("%d", &linhaTabelaH);

    if (cont == -2)
        printf("Valor nao encontrado\n");      // Impressão quando o número a ser procurado não é encontrado
    buscarLinha(listaNum, linhaTabelaH, tam);      // Impressão da linha pesquisada

    return 0;
}
