#include<iostream>

using namespace std;

void BubbleSort(int a[],int b[],int c[],string pais[],int n){
// cria os dois paises para comparar    
    int i=0;
// cria os paises para comparar    
    while(i < n-1){
        int j = 0;
        while(j < n-i-1){
            // Comparação entre ouros (Principal desempate)
            if(a[j+1]>a[j]){
                swap(a[j],a[j+1]);swap(b[j],b[j+1]);swap(c[j],c[j+1]);swap(pais[j],pais[j+1]);
            }
            //Comparação entre Prata e bronze
            if(a[j+1] == a[j]){
                if(b[j+1] > b[j]){
                swap(a[j],a[j+1]);swap(b[j],b[j+1]);swap(c[j],c[j+1]);swap(pais[j],pais[j+1]);
                }
                if(b[j+1] == b[j]){
                    if(c[j+1] > c[j]){
                swap(a[j],a[j+1]);swap(b[j],b[j+1]);swap(c[j],c[j+1]);swap(pais[j],pais[j+1]);
                }
                // Se todas as medalhas forem iguais ordena pelo alfabeto(Cai nesse caso)
                // Compara as strings e retorna 0 se iguais | -1 para string i menor que j | 1+ para i maior que j 
                if(c[j] == c[j+1]){
                    if(pais[j+1]<pais[j]){
                        swap(a[j],a[j+1]);swap(b[j],b[j+1]);swap(c[j],c[j+1]);swap(pais[j],pais[j+1]);
                    }
                  }
                }
            }
            j++;
        }
        i++;
    }
}

int main(){
    int n;  
    // Lendo n
    cin >> n;
    int a[n],b[n],c[n];
    string pais[n];
    //nome ouro prata bronze
    for(int i= 0;i< n;i++){
        cin >>pais[i]>>a[i]>>b[i]>>c[i];
    }
    // Ordenação
    BubbleSort(a,b,c,pais,n);
    // Imprime Saída
    for(int j= 0;j< n;j++){
        cout<<pais[j]<<" "<<a[j]<<" "<<b[j]<<" "<<c[j]<<endl;
    }
    return 0;
}
