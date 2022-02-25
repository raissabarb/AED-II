//RA: 148756
#include <iostream>
#define PRETO 0
#define VERMELHO 1

using namespace std;

struct TNo {
  int chave;
  int cor;
  TNo *pai, *esq, *dir;
};

typedef TNo *No;

class ArvRN {
   private:
  No raiz;
  No NILL;

  void iniciaNo(No y, No pai) {
    y->chave = 0;
    y->pai = pai;
    y->esq = NULL;
    y->dir = NULL;
    y->cor = PRETO;
  }

  No pesquisaNo(No y, int valor) {
    if (y == NILL){
        return y;
    } else if (valor == y->chave){
      return y;
    }

    if (valor < y->chave) {
      return pesquisaNo(y->esq, valor);
    } else{
      return pesquisaNo(y->dir, valor);
    }
  }

  int consultaArv(No no, int chave){
    if(no == NILL){
        return 0;
    }

   No atual = no;

    while(atual != NILL){
        if(chave == atual->chave){
            return 1;
        }
        if(chave > atual->chave){
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return 0;
  }

  int alturaNo(No y){

    if(y == NILL){
        return -1;
    } else {
        int he = alturaNo(y->esq);
        int hd = alturaNo(y->dir);

        if(he < hd){
            return hd + 1;
        } else {
            return he + 1;
        }
    }
  }

  int ehRubro(No y){
    if(y->cor == VERMELHO){
      return 1;
    } else {
      return 0;
    }
  }

  int alturaRubro(No atual){

    if(atual == NILL){
      return 0;
    } else {
      /* se o no for rubro, conta 1, se nao, conta 0 */
      int he = ehRubro(atual) + alturaRubro(atual->esq);
      int hd = ehRubro(atual) + alturaRubro(atual->dir);

      if(he > hd){
        return he;
      } else {
        return hd;
      }
    }
  }

  void arrumaInsercao(No z) {
    No aux;
    while (z->pai->cor == VERMELHO) {

      if (z->pai == z->pai->pai->dir) {
        aux = z->pai->pai->esq;

        if (aux->cor == VERMELHO) { /* tio do aux de z eh vermelho */
          aux->cor = PRETO;
          z->pai->cor = PRETO;
          z->pai->pai->cor = VERMELHO;
          z = z->pai->pai;
        } else {

          if (z == z->pai->esq) { /* o tio do aux de z eh preto e z eh um filho a esquerda */
            z = z->pai;
            rotacaoDireita(z);
          }

          /* o tio do aux de z eh preto e z eh um filho a direita */
          z->pai->cor = PRETO;
          z->pai->pai->cor = VERMELHO;
          rotacaoEsquerda(z->pai->pai);
        }
      } else {
        aux = z->pai->pai->dir;

        if (aux->cor == VERMELHO) {
          aux->cor = PRETO;
          z->pai->cor = PRETO;
          z->pai->pai->cor = VERMELHO;
          z = z->pai->pai;
        } else {

          if (z == z->pai->dir) { /* o tio do aux de z eh preto e z eh um filho a direita */
            z = z->pai;
            rotacaoEsquerda(z);
          }

          /* o tio do aux de z eh preto e z eh um filho a esquerda */
          z->pai->cor = PRETO;
          z->pai->pai->cor = VERMELHO;
          rotacaoDireita(z->pai->pai);
        }
      }
      if (z == raiz) {
        break;
      }
    }
    raiz->cor = PRETO; /* a raiz eh sempre preta */
  }

  void arrumaRemocao(No x) {
    No w;

    if((x == raiz) && (x->dir == NULL)){
        raiz == NULL;
    } else if(x == raiz){
        raiz = x->dir;
    }

    while (x != raiz && x->cor == PRETO) {
      if (x == x->pai->esq) {
        w = x->pai->dir;
        if (w->cor == VERMELHO) {
          w->cor = PRETO;
          x->pai->cor = VERMELHO;
          rotacaoEsquerda(x->pai);
          w = x->pai->dir;
        }

        if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
          w->cor = VERMELHO;
          x = x->pai;
        } else {
          if (w->dir->cor == PRETO) {
            w->esq->cor = PRETO;
            w->cor = VERMELHO;
            rotacaoDireita(w);
            w = x->pai->dir;
          }

          w->cor = x->pai->cor;
          x->pai->cor = PRETO;
          w->dir->cor = PRETO;
          rotacaoEsquerda(x->pai);
          x = raiz;
        }
      } else {
        w = x->pai->esq;
        if (w->cor == VERMELHO) {
          w->cor = PRETO;
          x->pai->cor = VERMELHO;
          rotacaoDireita(x->pai);
          w = x->pai->esq;
        }

        if (w->dir->cor == PRETO && w->dir->cor == PRETO) {
          w->cor = VERMELHO;
          x = x->pai;
        } else {
          if (w->esq->cor == PRETO) {
            w->dir->cor = PRETO;
            w->cor = VERMELHO;
            rotacaoEsquerda(w);
            w = x->pai->esq;
          }

          w->cor = x->pai->cor;
          x->pai->cor = PRETO;
          w->esq->cor = PRETO;
          rotacaoDireita(x->pai);
          x = raiz;
        }
      }
    }
    x->cor = PRETO;
  }

  void transplante(No u, No v) {
    if (u->pai == NILL) {
      raiz = v;
    } else if (u == u->pai->esq) {
      u->pai->esq = v;
    } else {
      u->pai->dir = v;
    }
    v->pai = u->pai;
  }

  void remocao(No no, int valor) {
    No z = NILL;
    No x, y;
    while (no != NILL) {
      if (no->chave == valor) {
        z = no;
      }

      if (no->chave <= valor) {
        no = no->dir;
      } else {
        no = no->esq;
      }
    }

    if (z == NILL) {
      return;
    }

    y = z;
    int y_cor_original = y->cor;

    if (z->esq == NILL) {
      x = z->dir;
      transplante(z, z->dir);
    } else if (z->dir == NILL) {
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
    if (y_cor_original == PRETO) {
      arrumaRemocao(x);
    }
  }

  void printHelper(No root, string indent, bool last) {
    if (root != NILL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->cor ? "RED" : "BLACK";
      cout << root->chave << "(" << sColor << ")" << endl;
      printHelper(root->esq, indent, false);
      printHelper(root->dir, indent, true);
    }
  }

   public:
  ArvRN() { /* inicia NILL e a raiz */
    NILL = new TNo;
    NILL->cor = PRETO;
    NILL->esq = NULL;
    NILL->dir = NULL;
    raiz = NILL;
  }

  No pesquisa(int k) {
    return pesquisaNo(this->raiz, k);
  }

  int consulta(No k, int valor){
    return consultaArv(k, valor);
  }

  int altura(No y){
    return alturaNo(y);
  }

  int altRubro(No y){
    return alturaRubro(y);
  }

  No minimo(No no) {
    while (no->esq != NILL) {
      no = no->esq;
    }
    return no;
  }

  void rotacaoEsquerda(No x) {
    No y; 
    
    y = x->dir; /* define y */
    x->dir = y->esq; /*transforma a subarvore a esquerda de y na subarvore a direita de x */

    if (y->esq != NILL) {
      y->esq->pai = x;
    }

    y->pai = x->pai; /* liga o pai de x a y */

    if (x->pai == NULL) {
      this->raiz = y;
    } else if (x == x->pai->esq) {
      x->pai->esq = y;
    } else {
      x->pai->dir = y;
    }

    y->esq = x; /* coloca x a esquerda de y */
    x->pai = y;
  }

  void rotacaoDireita(No x) {
    No y;

    y = x->esq; /* define y */
    x->esq = y->dir; /* transforma a subarvore a direita de y na subarvore a esquerda de x */

    if (y->dir != NILL) {
      y->dir->pai = x;
    }

    y->pai = x->pai; /* liga o pai de x a y */

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

  void insercao(int valor) {
    No z = new TNo;
    z->pai = NULL;
    z->chave = valor;
    z->esq = NILL;
    z->dir = NILL;
    z->cor = VERMELHO;

    No y = NULL;
    No x = this->raiz;

    while (x != NILL) {
      y = x;
      if (z->chave < x->chave) {
        x = x->esq;
      } else {
        x = x->dir;
      }
    }

    z->pai = y;

    if (y == NULL) {
      raiz = z;
    } else if (z->chave < y->chave) {
      y->esq = z;
    } else {
      y->dir = z;
    }

    if (z->pai == NULL) {
      z->cor = PRETO;
      return;
    }

    if (z->pai->pai == NULL) {
      return;
    }

    arrumaInsercao(z);
  }

  No pegaRaiz() {
    return this->raiz;
  }

  void removeNo(int valor) {
    remocao(this->raiz, valor);
  }

  void printTree() {
    if (raiz) {
      printHelper(this->raiz, "", true);
    }
  }
};

int main() {
  ArvRN RN;

  int valor, chaves[1000], pesq;
  int j, i = 0, k = 0;

  for(j = 0; j < 1000; j++){
        chaves[j] = -1;
  }

  cin >> valor;

    do {
        RN.insercao(valor);
        cin >> valor;
    } while (valor > -1);

  int hArv = RN.altura(RN.pegaRaiz());
  int hSubDir = RN.altura((RN.pegaRaiz())->dir);
  int hSubEsq = RN.altura((RN.pegaRaiz())->esq);

  cin >> chaves[0];

  if(chaves[0] != -1){
       do{
        i++;
        cin >> chaves[i];
       } while (chaves[i] > -1);
  }

  cin >> pesq;

  cout << hArv << ", " << hSubEsq+1 << ", " << hSubDir+1 << endl; 

  while(chaves[k] > -1){
    No aux1 = RN.pesquisa(chaves[k]);

    if(RN.consulta(aux1, chaves[k]) == 0){
      RN.insercao(chaves[k]);
    } else {
      int hChave = RN.altura(aux1);
      int hCDir = RN.altura(aux1->dir);
      int hCEsq = RN.altura(aux1->esq);
            
      cout << hChave << ", " << hCEsq+1 << ", " << hCDir+1 << endl;
      RN.removeNo(chaves[k]);
      RN.printTree();
    }
    k++;
  }

  No aux2 = RN.pesquisa(pesq);

    if(RN.consulta(aux2, pesq) == 0){
        cout << "Valor nao encontrado";
    } else {
        int hPesq = RN.altRubro(aux2);
        cout << hPesq;
    }

  return 0;
}