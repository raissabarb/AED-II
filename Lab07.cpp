/*  
***** Exercício 7 - AED II *****       100 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 30/11/2021                       
*/

#include <iostream>
using namespace std;
using std::string;

int maiorPalavra(string str[], int tam){      // Função para encontrar a maior palavra
    int maior = str[0].size(), k;
    for(k=0; k<tam; k++){
        if(str[k].size() > maior){
            maior = str[k].size();
        }
    }
    return maior;
}

void minuscula(string str[], int tam){
    int i, j;
    for(i=0; i<tam; i++){
        for(j=0; j<str[i].size(); j++){
            str[i][j] = tolower(str[i][j]);      // Colocando as letras das palavras em caixa baixa
        }
    }
}

void preencheEspacos(string str[], int tam, int d){
    int i;
    for(i=0; i<tam; i++){
        if(str[i].size() < d){
            while(str[i].size() < d){      // Enquanto o tamanho das palavras não seja igual ao da maior de todas, um espaço é adicionado
                str[i] += " ";
            }
        }
    }
}

void counting_sort(string A[], string B[], int n, int d){
    int i, j, m, l, r, cont;
    int *C = NULL;
    C = new int[27];
    for(i=0; i<27; i++){
        C[i] = 0;
    }
    for(j=0; j<n; j++){
        if(A[j][d] == ' '){
            C[0]++;
        } else{
            C[A[j][d]-96]++;
        }
    }
    for(m=1; m<27; m++){
        C[m] += C[m-1];
    }
    for(cont=0; cont<27; cont++){
        cout << C[cont] << " ";
    }
    cout << endl;
    for(l=n-1; l>=0; l--){
        if(A[l][d] == ' '){
            B[C[0]-1] = A[l];
            C[0]--;
        } else{
            B[C[A[l][d]-96]-1] = A[l];
            C[A[l][d]-96]--;
        }
    }
    for (r = 0; r < n; r++){
        A[r] = B[r];
    }
}

void radix_sort(string A[], string B[], int n, int d){
    int dig;
    for(dig=d; dig>0; dig--){
        counting_sort(A, B, n, dig-1);
    }
}

int main() {

    int N, i, P, M, cont;
    cin >> N;
    string entrada[N];
    for(i=0; i<N; i++){
        cin >> entrada[i];      // Pegando as palavras para serem analisadas
    }
    cin >> P;      // Pegando a primeira paravra que será printada
    cin >> M;      // Quantas palavras depois dessa primeira serão printadas
    minuscula(entrada, N);
    int d = maiorPalavra(entrada, N);
    for(i=0; i<N; i++){
        cout << entrada[i] << "." << endl;
    }
    cout << d << endl;
    preencheEspacos(entrada, N, d);
    string saida[N];
    radix_sort(entrada, saida, N, d);
    for(cont = P-1; cont < (P-1)+M; cont++){
        cout << saida[cont] << endl;
    }
    return 0;
}
