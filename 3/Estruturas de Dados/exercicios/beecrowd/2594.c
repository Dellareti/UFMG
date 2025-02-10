#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

typedef struct{ 
	char senha[256];
} string;

int main(){
	char palavra[256];
	char temporario[256], *auxiliar;
	string texto[256];
	unsigned n, i;
	
	scanf("%u", &n);

	while (n--) {
		i = 0;
		scanf(" %[^\n]", temporario);
		scanf(" %s", palavra);

		auxiliar = strtok(temporario, " ");
		strcpy(texto[i++].senha, auxiliar);

		do {
        	auxiliar = strtok(0, " ");
			if (auxiliar) {
				strcpy(texto[i++].senha, auxiliar);
            }
		} while (auxiliar);

		_Bool flag = true;
		unsigned tamanho = 0;

		for (int j = 0; j < i; ++j) {
			if (strcmp(texto[j].senha, palavra) == 0) {
				if (!flag) {
					printf(" %u", tamanho);
                } else {
					printf("%u", tamanho), flag = false;
                }    
            }        
			tamanho += strlen(texto[j].senha) + 1;
		}

		if (flag) {
			printf("-1\n");
        } else {
			printf("\n");
        }
	}

	return 0;
}
