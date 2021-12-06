#include <stdio.h>
#include <stdlib.h>


void Merge(int *A, int *L, int leftCount, int *R, int rightCount){   // colocar um contador como parametro
	int i, j, k;
	i = 0; j = 0; k =0;
    
	while(i<leftCount && j< rightCount) {
		if(L[i] < R[j]){
            A[k++] = L[i++];
            printf("num 1 op - %d\n", A[k++]);
		} else{
            A[k++] = R[j++];
            printf("num 2 op - %d\n", A[k++]);
        }
	}
	while(i < leftCount){
        A[k++] = L[i++];
        printf("num 3 op - %d\n", A[k++]);
    }
	while(j < rightCount){
        A[k++] = R[j++];
        printf("num 4 op - %d\n", A[k++]);
    }
}

void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; // base condition. If the array has less than two element, do nothing. 

	mid = n/2;  // find the mid index. 

	L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

	MergeSort(L,mid);  // sorting the left subarray
	MergeSort(R,n-mid);  // sorting the right subarray
	Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
        free(L);
        free(R);
}

int main(){
	int tam, num;
	int i,numberOfElements;
    scanf("%d\n", &tam);
    scanf("%d", &num);
    int A[tam];  
    for (i=0; i<tam; i++){
        scanf("%d", &A[i]);
    }
	numberOfElements = sizeof(A)/sizeof(A[0]); 
    int j=1, cont=0;
    i = 0;
    while ((i < tam) && (j < tam)){
        int condicao;
        condicao = num * A[j];
        if ((A[i] > condicao) && (i < j)){
            cont++;
        }
        if (j == tam-1){
            i++;
            j = i+1;
        } else j++;
    }
	MergeSort(A,numberOfElements);
    printf("%d", cont);
	return 0;
}

/*

int j=1, cont=0;
    i = 0;
    while ((i < tam) && (j < tam)){
        printf("valor %d\n", a[i]);
        printf("valor j %d\n", a[j]);
        printf("i - %d\nj - %d\n", i, j);
        printf("%d\n", condicao);
        int condicao;
        condicao = num + A[j];
        //printf("num condicao %d\n\n", condicao);
        if (A[i] > condicao){
            cont++;
        }
        if (j == tam-1){
            i++;
            j = i+1;
        } else j++;
    }

*/