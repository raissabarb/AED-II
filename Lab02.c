/* 
***** Exercício 2 - AED II *****      60 pontos - ok
NOME: Raissa Barbosa dos Santos     
RA: 148551
DATA: 29/10/2021 
*/

#include <stdio.h>
#include <stdlib.h>

int encomendas(int livros, int vale, int cont, int aux){
    int qtdLivro, qtdVale, i, sobraLivros, opc1;                                           
    qtdLivro = livros / vale;                                                                     
    qtdVale = qtdLivro;                                                                           
    sobraLivros = qtdLivro;      // livros que não foram trocados, para contabilizar depois, no final        
    aux += livros % vale;     // livros que sobraram na divisão pelo valor do vale                                                                    
    if (qtdLivro >= vale){      // quando a quantidade de livros é igual ou superior ao valor do vale
        cont += qtdLivro;                              
        sobraLivros -= qtdLivro;
        encomendas(qtdLivro, vale, cont, aux);
    } else{                                                
        i = aux / vale;      // livros que sobraram divididos pelo valor do vale, resultando em mais i livros                   
        cont += sobraLivros;      // contabiliza a quantidade de livros que não totalizou no valor do vale                       
        cont += i;                                        
        opc1 = sobraLivros + aux;     
        if (opc1 / vale >= 1){
            cont += opc1 / vale;
        }
        return cont;      // a quantidade de livros que puderam ser trocados
    }
}

int main(){

    int qtdLivros, qtdVerificacao, dinheiro, preco, vale, cont=0, aux=0, totLivros, livrosAdd, i;
    scanf("%d\n", &qtdVerificacao);
    if (qtdVerificacao <= 10){
        for (i=0; i<qtdVerificacao; i++){
            scanf("%d %d %d", &dinheiro, &preco, &vale);
            if ((vale > 1) && (preco != 0)){
                qtdLivros = dinheiro / preco;      // quantidade de livros que podem ser trocados por vales, que vão para a função
                livrosAdd = encomendas(qtdLivros, vale, cont, aux);
                totLivros = qtdLivros + livrosAdd;     // soma dos livros comprados com os livros trocados por vales
                printf("%d\n", totLivros);
            }
        }
    }
    return 0;
}