#include <iostream>
#include <algorithm>
#include <cstring>

int Binary_search(int x[],int tam,int buscado){
    int maximo= tam-1;
    int min = 0;
    int mean;
    while (maximo>min){
        mean = (maximo+min)/2;
        if (x[mean] == buscado){
            return mean;
        }
        else if(x[mean] > buscado){
            maximo = (mean-1);
        }
        else{
            min = (mean+1);
        }
    }
    return -1;
}

using namespace std;

void Sort(int *array, int tam) {
   int chave, j;
   for(int i = 1; i<tam; i++) {
      chave = array[i];
      j = i;
      while(j > 0 && array[j-1]>chave) {
         array[j] = array[j-1];
         j--;
      }
      array[j] = chave;  
   }
}

int main(){

    int quantidade[1000000];
	int n, x, y, p, temp;
	int* low;
	int* up;

	while(scanf("%d", &n) == 1){

		memset(quantidade, 0, sizeof(quantidade));
		temp = 0;

		for (int i = 0; i < n; ++i){
			scanf("%d %d", &x, &y);
			for (int j = x; j <= y; ++j){
				quantidade[temp++] = j;
            }
		}

		sort(quantidade, quantidade + temp);
		scanf("%d", &p);

		if(binary_search(quantidade, quantidade + temp, p)){
  			low = lower_bound (quantidade, quantidade + temp, p);
  			up = upper_bound (quantidade, quantidade + temp, p);

  			printf("%d found from %ld to %ld\n", p, (low- quantidade), (up - quantidade) - 1);
		}
        else{
			printf("%d not found\n", p);
		}
	}

	return 0;
}
