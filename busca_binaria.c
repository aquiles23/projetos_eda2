#include<stdio.h>
void numeronaoencontrado(int * v){
  printf("seu numero não foi encontrado \n");
  free(v);
}
int procura(int busca, int *v,int tam){
	int aux = 0;
	if (v[divide(tam)] == busca){
		return v[divide(tam)];
	}
	else if (v[divide(tam)]>busca){
		while(1){
			aux = divide(tam) - 1 - aux;
			if (v[aux] == busca){
				return v[aux];
			}
       			else if (aux == 0){
			        numeronaoencontrado(v);	
				exit(0);
			}

		}
	}
	else if (v[divide(tam)]<busca){
		while(1){
			aux = divide(tam) + 1 + aux;
			 if (aux == tam - 1 || aux> tam-1){
                                numeronaoencontrado(v); 
				exit(0);
			}else if (v[aux] == busca){
				return v[aux];
			}
		}
	}


}

int divide(int tam) {
	int i;
	if(tam%2==0) {
		i=tam/2;
	}
	else {
		i=(tam+1)/2;
	}
	return i;
}

void insertionSort(int* v, int tam) {
	int i, j, aux = 0;

	for (i=1; i<tam; i++) {
		aux = v[i];
		j = i - 1;
		while (j >= 0 && v[j] > aux) {
			v[j + 1] = v[j];
			j = j - 1;
		}
		v[j + 1] = aux;
	}

	return v;

}
int main(int argc, char const *argv[])
{
	int i, *v, tam,valor_vetor, busca,resultado;
	printf("insira o tamanho do vetor \n");
	scanf("%d",&tam);
	v = (int *) malloc(tam * sizeof(int));
	for(i=0;i<tam;i++){
		printf("insira o valor do vetor na posicao %d \n",i);
		scanf("%d",&valor_vetor);
		v[i] = valor_vetor;
	}
	
	insertionSort(v,tam);
        

	// o trecho a seguir é para debugar o que ja foi feito
	for(i=0;i<tam;i++){
		printf("posicao do vetor: %d valor do vetor: %d \n",i,v[i]);
	}
	printf("insira o numero no qual deseja pesquisar \n");
	scanf("%d",&busca);
	
	resultado = procura(busca, v,tam);
	
	printf("sua pesquisa retornou %d \n",resultado);
	free (v);
	return 0;
}

