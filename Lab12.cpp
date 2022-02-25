/* 
***** Exercício 12 - AED II *****      
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 04/01/2022                50 pts - ok
*/
 
#include <iostream>
#define P 0
#define V 1
 
using namespace std;
 
struct NO {
  int index;
  int cor;
  NO *pai, *esq, *dir;
};
 
typedef NO *No;
 
class arvRubroNeg{
   private:
  No raiz, AUX;
 
  void iniciaNo(No y, No pai) {
    y->index = 0;
    y->pai = pai;
    y->esq = NULL;
    y->dir = NULL;
    y->cor = P;
  }
 
  No procuraNo(No y, int num) {
    if (y == AUX){
        return y;
    } else if (num == y->index){
      return y;
    }
 
    if (num < y->index) {
      return procuraNo(y->esq, num);
    } else{
      return procuraNo(y->dir, num);
    }
  }
 
  int consultarArv(No no, int index){
    if(no == AUX) return 0;
 
   No atual = no;
 
    while (atual != AUX){
        if (index == atual->index){
            return 1;
        }
        if (index > atual->index){
            atual = atual->dir;
        } else{
            atual = atual->esq;
        }
    }
    return 0;
  }
 
  int alturaNo(No y){
 
    if (y == AUX){
        return -1;
    } else{
        int altDir, altEsq;
        altEsq = alturaNo(y->esq) + 1;
        altDir = alturaNo(y->dir) + 1;
        if(altEsq < altDir){
            return altDir;
        } else {
            return altEsq;
        }
    }
  }
 
  int rubroSN(No y){
    if(y->cor == V){
      return 1;
    } else {
      return 0;
    }
  }
 
  int alturaRubro(No atual){
    if(atual == AUX){
      return 0;
    } else {
      int altDir, altEsq;      // se o nó for considerado rubro, o contador será igual a 1, caso contrário, 0
      altEsq = rubroSN(atual) + alturaRubro(atual->esq);
      altDir = rubroSN(atual) + alturaRubro(atual->dir);
      if(altEsq > altDir){
        return altEsq;
      } else {
        return altDir;
      }
    }
  }
 
  void organizaInserc(No z) {
    No aux;
    while (z->pai->cor == V) {
 
      if (z->pai == z->pai->pai->dir) {
        aux = z->pai->pai->esq;
 
        if (aux->cor == V) { /* tio do aux de z eh V */
          aux->cor = P;
          z->pai->cor = P;
          z->pai->pai->cor = V;
          z = z->pai->pai;
        } else {
 
          if (z == z->pai->esq) { /* o tio do aux de z eh P e z eh um filho a esquerda */
            z = z->pai;
            rotacaoDir(z);
          }
 
          /* o tio do aux de z eh P e z eh um filho a direita */
          z->pai->cor = P;
          z->pai->pai->cor = V;
          rotacaoEsq(z->pai->pai);
        }
      } else {
        aux = z->pai->pai->dir;
 
        if (aux->cor == V) {
          aux->cor = P;
          z->pai->cor = P;
          z->pai->pai->cor = V;
          z = z->pai->pai;
        } else {
 
          if (z == z->pai->dir) { /* o tio do aux de z eh P e z eh um filho a direita */
            z = z->pai;
            rotacaoEsq(z);
          }
 
          /* o tio do aux de z eh P e z eh um filho a esquerda */
          z->pai->cor = P;
          z->pai->pai->cor = V;
          rotacaoDir(z->pai->pai);
        }
      }
      if (z == raiz) {
        break;
      }
    }
    raiz->cor = P; /* a raiz eh sempre preta */
  }
 
  void ajudaRemocao(No x) {
    No w;
    if((x == raiz) && (x->dir == NULL)){
        raiz == NULL;
    } else if(x == raiz){
        raiz = x->dir;
    }
 
    while (x != raiz && x->cor == P) {
      if (x == x->pai->esq) {
        w = x->pai->dir;
        if (w->cor == V) {
          w->cor = P;
          x->pai->cor = V;
          rotacaoEsq(x->pai);
          w = x->pai->dir;
        }
 
        if (w->esq->cor == P && w->dir->cor == P) {
          w->cor = V;
          x = x->pai;
        } else {
          if (w->dir->cor == P) {
            w->esq->cor = P;
            w->cor = V;
            rotacaoDir(w);
            w = x->pai->dir;
          }
 
          w->cor = x->pai->cor;
          x->pai->cor = P;
          w->dir->cor = P;
          rotacaoEsq(x->pai);
          x = raiz;
        }
      } else {
        w = x->pai->esq;
        if (w->cor == V) {
          w->cor = P;
          x->pai->cor = V;
          rotacaoDir(x->pai);
          w = x->pai->esq;
        }
 
        if (w->dir->cor == P && w->dir->cor == P) {
          w->cor = V;
          x = x->pai;
        } else {
          if (w->esq->cor == P) {
            w->dir->cor = P;
            w->cor = V;
            rotacaoEsq(w);
            w = x->pai->esq;
          }
 
          w->cor = x->pai->cor;
          x->pai->cor = P;
          w->esq->cor = P;
          rotacaoDir(x->pai);
          x = raiz;
        }
      }
    }
    x->cor = P;
  }
 
  void transplante(No u, No v) {
    if (u->pai == AUX) {
      raiz = v;
    } else if (u == u->pai->esq) {
      u->pai->esq = v;
    } else {
      u->pai->dir = v;
    }
    v->pai = u->pai;
  }
 
  void remover(No no, int num) {
    No z = AUX;
    No x, y;
    while (no != AUX) {
      if (no->index == num) {
        z = no;
      }
 
      if (no->index <= num) {
        no = no->dir;
      } else {
        no = no->esq;
      }
    }
 
    if (z == AUX) return;
 
    y = z;
    int y_cor_original = y->cor;
 
    if (z->esq == AUX) {
      x = z->dir;
      transplante(z, z->dir);
    } else if (z->dir == AUX) {
      x = z->esq;
      transplante(z, z->esq);
    } else {
      y = minimo(z->dir);
      y_cor_original = y->cor;
      x = y->dir;
 
      if (y->pai == z) {
        x->pai = y;
      } else {
        transplante(y, y->dir);
        y->dir = z->dir;
        y->dir->pai = y;
      }
 
      transplante(z, y);
      y->esq = z->esq;
      y->esq->pai = y;
      y->cor = z->cor;
    }
 
    delete z;
    if (y_cor_original == P) {
      ajudaRemocao(x);
    }
  }
 
  void ajuda(No raiz2, string indent, bool last) { 
    if (raiz2 != AUX) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }
 
      string sColor = raiz2->cor ? "RED" : "BLACK";
      cout << raiz2->index << "(" << sColor << ")" << endl;
      ajuda(raiz2->esq, indent, false);
      ajuda(raiz2->dir, indent, true);
    }
  }
 
   public:
  arvRubroNeg() {      // inicia o AUX e a raiz
    AUX = new NO;
    AUX->cor = P;
    AUX->esq = NULL;
    AUX->dir = NULL;
    raiz = AUX;
  }
 
  No pesquisar(int k) {
    return procuraNo(this->raiz, k);
  }
 
  int consultar(No k, int num){
    return consultarArv(k, num);
  }
 
  int altura(No y){
    return alturaNo(y);
  }
 
  int altRubro(No y){
    return alturaRubro(y);
  }
 
  No minimo(No no) {
    while (no->esq != AUX) {
      no = no->esq;
    }
    return no;
  }
 
  void rotacaoEsq(No x) {
    No y; 
    
    y = x->dir; 
    x->dir = y->esq;      // faz com que a subarvore a esquerda de y seja transformada na subarvore a direita de x
 
    if (y->esq != AUX) {
      y->esq->pai = x;
    }
 
    y->pai = x->pai;      // faz a ligação entre o pai de x a y
 
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
 
  void rotacaoDir(No x) {
    No y;
 
    y = x->esq; 
    x->esq = y->dir;      // faz com que a subarvore a direita de y seja transformada na subarvore a esquerda de x
 
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
 
    y->dir = x; /* coloca x a direita de y */
    x->pai = y;
  }
 
  void inserir(int num) {
    No z = new NO;
    z->pai = NULL;
    z->index = num;
    z->esq = AUX;
    z->dir = AUX;
    z->cor = V;
 
    No y = NULL;
    No x = this->raiz;
 
    while (x != AUX) {
      y = x;
      if (z->index < x->index) {
        x = x->esq;
      } else {
        x = x->dir;
      }
    }
 
    z->pai = y;
 
    if (y == NULL) {
      raiz = z;
    } else if (z->index < y->index) {
      y->esq = z;
    } else {
      y->dir = z;
    }
 
    if (z->pai == NULL) {
      z->cor = P;
      return;
    }
 
    if (z->pai->pai == NULL) return;
 
    organizaInserc(z);
  }
 
  No usarRaiz() {
    return this->raiz;
  }
 
  void removerNo(int num) {
    remover(this->raiz, num);
  }
 
  void printTree() { 
    if (raiz) {
      ajuda(this->raiz, "", true);
    }
  }
};
 
int main() {
  arvRubroNeg RN;
 
  int num, listaNum[1000], procurar, j, i = 0, k = 0;
 
  for(j = 0; j < 1000; j++){
        listaNum[j] = -1;
  }
 
  cin >> num;
 
    do {
        RN.inserir(num);
        cin >> num;
    } while (num > -1);
 
  int hArv = RN.altura(RN.usarRaiz());
  int hSubDir = RN.altura((RN.usarRaiz())->dir);
  int hSubEsq = RN.altura((RN.usarRaiz())->esq);
 
  cin >> listaNum[0];
 
  if(listaNum[0] != -1){
       do{
        i++;
        cin >> listaNum[i];
       } while (listaNum[i] > -1);
  }
 
  cin >> procurar;
 
  cout << hArv << ", " << hSubEsq+1 << ", " << hSubDir+1 << endl; 
 
  while(listaNum[k] > -1){
    No aux1 = RN.pesquisar(listaNum[k]);
 
    if(RN.consultar(aux1, listaNum[k]) == 0){
      RN.inserir(listaNum[k]);
    } else {
      int hindex = RN.altura(aux1);
      int hCDir = RN.altura(aux1->dir);
      int hCEsq = RN.altura(aux1->esq);
            
      cout << hindex << ", " << hCEsq+1 << ", " << hCDir+1 << endl;
      RN.removerNo(listaNum[k]);
    }
    k++;
  }
 
  No aux2 = RN.pesquisar(procurar);
 
    if(RN.consultar(aux2, procurar) == 0){
        cout << "Valor nao encontrado";
    } else {
        int hprocurar = RN.altRubro(aux2);
        cout << hprocurar;
    }
 
  return 0;
}