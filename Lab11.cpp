/* 
***** Exercício 11 - AED II *****      
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 04/01/2022  
*/
 
#include <iostream>
#define P 0
#define V 1
 
using namespace std;
 
struct TNo {
    int indexPesquisa;
    int cor;
    TNo *pai, *esq, *dir;
};
 
typedef TNo *No;
 
class ArvoreRubroNegra {
   private:
  No raiz;
  No AUX;
 
  void iniciacao(No y, No pai) {
    y->indexPesquisa = 0;
    y->pai = pai;
    y->esq = NULL;
    y->dir = NULL;
    y->cor = P;
  }
 
  No pesquisarNo(No y, int num) {
    if (y == AUX){
        return y;
    } else if (num == y->indexPesquisa){
      return y;
    }
 
    if (num < y->indexPesquisa) {
      return pesquisarNo(y->esq, num);
    } else{
      return pesquisarNo(y->dir, num);
    }
  }
 
  int consultaArv(No no, int indexPesquisa){
    if(no == AUX) return 0;
 
   No atual = no;
 
    while(atual != AUX){
        if(indexPesquisa == atual->indexPesquisa){
            return 1;
        }
        if(indexPesquisa > atual->indexPesquisa){
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return 0;
  }
 
  int alturaNo(No y){
    if(y == AUX){
        return -1;
    } else {
        int altEsq, altDir;
        altEsq = alturaNo(y->esq) + 1;
        altDir = alturaNo(y->dir) + 1;
        if(altEsq < altDir){
            return altDir;
        } else {
            return altEsq;
        }
    }
  }
 
  int negraSN(No y){
    if(y->cor == P){
      return 1;
    } else {
      return 0;
    }
  }
 
  int alturaNegra(No atual){
    if(atual == AUX){
      return 0;
    } else {
      int altEsq, altDir;
      altEsq = negraSN(atual) + alturaNegra(atual->esq);
      altDir = negraSN(atual) + alturaNegra(atual->dir);
      if(altEsq > altDir){
        return altEsq;
      } else {
        return altDir;
      }
    }
  }
 
  void organizaInsercao(No z) {
    No aux;
    while (z->pai->cor == V) {
      if (z->pai == z->pai->pai->dir) {
        aux = z->pai->pai->esq;
        if (aux->cor == V) { 
          aux->cor = P;
          z->pai->cor = P;
          z->pai->pai->cor = V;
          z = z->pai->pai;
        } else {
          if (z == z->pai->esq) { 
            z = z->pai;
            rotacaoDireita(z);
          }
          z->pai->cor = P;
          z->pai->pai->cor = V;
          rotacaoEsquerda(z->pai->pai);
        }
      } else {
        aux = z->pai->pai->dir;
        if (aux->cor == V) {
          aux->cor = P;
          z->pai->cor = P;
          z->pai->pai->cor = V;
          z = z->pai->pai;
        } else {
          if (z == z->pai->dir) { 
            z = z->pai;
            rotacaoEsquerda(z);
          }
          z->pai->cor = P;
          z->pai->pai->cor = V;
          rotacaoDireita(z->pai->pai);
        }
      }
      if (z == raiz) {
        break;
      }
    }
    raiz->cor = P;
  }
 
   public:
  ArvoreRubroNegra(){ 
    AUX = new TNo;
    AUX->cor = P;
    AUX->esq = NULL;
    AUX->dir = NULL;
    raiz = AUX;
  }
 
  No pesquisa(int k) {
    return pesquisarNo(this->raiz, k);
  }
 
  int consulta(No k, int num){
    return consultaArv(k, num);
  }
 
  int altura(No y){
    return alturaNo(y);
  }
 
  int altNegra(No y){
    return alturaNegra(y);
  }
 
  void rotacaoEsquerda(No x) {
    No y; 
    
    y = x->dir; 
    x->dir = y->esq; 
 
    if (y->esq != AUX) {
      y->esq->pai = x;
    }
 
    y->pai = x->pai;
 
    if (x->pai == NULL) {
      this->raiz = y;
    } else if (x == x->pai->esq) {
      x->pai->esq = y;
    } else {
      x->pai->dir = y;
    }
 
    y->esq = x; 
    x->pai = y;
  }
 
  void rotacaoDireita(No x) {
    No y;
 
    y = x->esq;
    x->esq = y->dir; 
 
    if (y->dir != AUX) {
      y->dir->pai = x;
    }
 
    y->pai = x->pai;
 
    if (x->pai == NULL) {
      this->raiz = y;
    } else if (x == x->pai->dir) {
      x->pai->dir = y;
    } else {
      x->pai->esq = y;
    }
 
    y->dir = x; 
    x->pai = y;
  }
 
  void insercao(int num) {
    No z = new TNo;
    z->pai = NULL;
    z->indexPesquisa = num;
    z->esq = AUX;
    z->dir = AUX;
    z->cor = V;
 
    No y = NULL;
    No x = this->raiz;
 
    while (x != AUX) {
      y = x;
      if (z->indexPesquisa < x->indexPesquisa) {
        x = x->esq;
      } else {
        x = x->dir;
      }
    }
 
    z->pai = y;
 
    if (y == NULL) {
      raiz = z;
    } else if (z->indexPesquisa < y->indexPesquisa) {
      y->esq = z;
    } else {
      y->dir = z;
    }
 
    if (z->pai == NULL) {
      z->cor = P;
      return;
    }
 
    if (z->pai->pai == NULL) {
      return;
    }
 
    organizaInsercao(z);
  }
 
  No pegaRaiz() {
    return this->raiz;
  }
 
};
 
int main() {
  ArvoreRubroNegra RN;
 
  int num, indexPesquisas[1000], pesq;
  int j, i = 0, k = 0;
 
  for(j = 0; j < 1000; j++){
        indexPesquisas[j] = -1;
  }
 
  cin >> num;
 
    do {
        RN.insercao(num);
        cin >> num;
    } while (num > -1);
  
  int altP, altEsq, altDir;
  altP = RN.altura(RN.pegaRaiz());
  altDir = RN.altura((RN.pegaRaiz())->dir) + 1;
  altEsq = RN.altura((RN.pegaRaiz())->esq) + 1;
 
  cin >> indexPesquisas[0];
 
  if(indexPesquisas[0] != -1){
       do{
        i++;
        cin >> indexPesquisas[i];
       } while (indexPesquisas[i] > -1);
  }
 
  cin >> pesq;
 
  cout << altP << ", " << altEsq << ", " << altDir << endl; 
 
  while(indexPesquisas[k] > -1){
    No aux1 = RN.pesquisa(indexPesquisas[k]);
 
    if(RN.consulta(aux1, indexPesquisas[k]) == 0){
      RN.insercao(indexPesquisas[k]);
    } else {
      int altIndex, altD, altE;
      altIndex = RN.altura(aux1);
      altD = RN.altura(aux1->dir) + 1;
      altE = RN.altura(aux1->esq) + 1;
            
      cout << altIndex << ", " << altE << ", " << altD << endl;
    }
    k++;
  }
 
  No aux2 = RN.pesquisa(pesq);
 
    if(RN.consulta(aux2, pesq) == 0){
        cout << "Valor nao encontrado";
    } else {
        int hPesq = RN.altNegra(aux2);
        cout << hPesq;
    }
 
  return 0;
}