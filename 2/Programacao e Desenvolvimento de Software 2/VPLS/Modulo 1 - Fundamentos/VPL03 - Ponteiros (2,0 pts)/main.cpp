#include<iostream>
using namespace std;

int main(){

    // 1) Declare uma variável do tipo inteiro e atribua o valor '10'  ok
    int n = 10;

    // 2) Declare um ponteiro para inteiros e inicialize com valor nulo  ok
    int *p1;
    p1 = new int;
    
    // 3) Declare um vetor de inteiros e inicialize com valores de 9 a 0 (nessa ordem)  ok
    int v[10] = {9,8,7,6,5,4,3,2,1,0};

    // 4) Imprima o ENDEREÇO da variável declarada em (1)    ok
    cout << &n << endl;

    // 5) Imprima o VALOR da variável declarada em (1)       ok
    cout << n << endl;

    // 6) Imprima o ENDEREÇO da variável declarada em (2)    ok
    cout << p1 << endl;
    
    // 7) Imprima o VALOR da variável declarada em (2)       ok
    cout << *p1 << endl;

    // 8) Imprima o ENDEREÇO da variável declarada em (3)    ok
    cout << &v << endl;

    // 9) Imprima o ENDEREÇO da primeira posição da variável declarada em (3)   ok
     cout << &v[0] << endl;
     
    // 10) Imprima o VALOR da primeira posição da variável declarada em (3)     ok
    cout << v[0] << endl;

    // 11) Atribua o ENDEREÇO da variável declarada em (1) à variável declarada em (2)  Ok
    p1 = &n;

    // 12) Imprima o VALOR da variável declarada em (2)   Ok
    cout << p1 << endl;
    
    // 13) Imprima o VALOR guardado no ENDEREÇO apontado por (2) Ok
    cout << *p1 << endl;
    
    // 14) Imprima o resultado da comparação do ENDEREÇO de (1) e do VALOR de (2)   ok
    if(p1 == &n){
        cout << "1" << endl;

    }
    else{
        cout << "0" << endl;
    }

    // 15) Coloque o VALOR '5' no ENDEREÇO apontado por (2)  Ok
    *p1 = 5;

    // 16) Imprima o VALOR da variável declarada em (1)   Ok
    cout << n << endl;

    // 17) Atribua o ENDEREÇO da variável (3) à variável declarada em (2)   ok ??
    p1 = &v[0];
    p1 = &v[1];
    p1 = &v[2];
    p1 = &v[3];
    p1 = &v[4];
    p1 = &v[5];
    p1 = &v[6];
    p1 = &v[7];
    p1 = &v[8];
    p1 = &v[9];

    
    // 18) Imprima o VALOR da variável declarada em (2)   ok
    cout << p1 << endl;

    // 19) Imprima o VALOR guardado no ENDEREÇO apontado por (2)   ok
    cout << v[0] << endl;
    
    // 20) Atribua o ENDEREÇO da primeira posição de (3) à variável declarada em (2)  ok
    p1 = &v[0];

    // 21) Imprima o VALOR da variável declarada em (2)  ok
    cout << p1 << endl;

    // 22) Imprima o VALOR guardado no ENDEREÇO apontado por (2)   ok
    cout << *p1 << endl;

    // 23) Multiplique todos os valores do vetor declarado em (3) por '10', porém manipulando apenas a variável (2)
    
    for(int i = 0; i < 10;i++){
        p1[i] = p1[i] * 10;        
    }
    
    // 24) Imprima os elementos de (3) a partir variável do vetor utilizando a notação [] (colchetes)
    
    // for(int j = 0;j < 10;j++){
    //     cout << v[j] << " ";
    // }
    cout << v[0]<< " ";
    cout << v[1]<< " ";
    cout << v[2]<< " ";
    cout << v[3]<< " ";
    cout << v[4]<< " ";
    cout << v[5]<< " ";
    cout << v[6]<< " ";
    cout << v[7]<< " ";
    cout << v[8]<< " ";
    cout << v[9];

    
   cout << endl;
    // 25) Imprima os elementos de (3) a partir variável do vetor utilizando a notação ponteiro/deslocamento
    
    // for(int k = 0;k < 10;k++){
    //     cout << v[k] << " ";
    // }
    
    cout << v[0]<< " ";
    cout << v[1]<< " ";
    cout << v[2]<< " ";
    cout << v[3]<< " ";
    cout << v[4]<< " ";
    cout << v[5]<< " ";
    cout << v[6]<< " ";
    cout << v[7]<< " ";
    cout << v[8]<< " ";
    cout << v[9];
    
    
      cout << endl;

    // 26) Imprima os elementos de (3) utilizando a variável (2) e a notação ponteiro/deslocamento
    
    //  for(int l = 0;l < 10;l++){
    //     cout << p1[l] << " ";
    // }
    cout << p1[0] << " ";
    cout << p1[1] << " ";
    cout << p1[2] << " ";
    cout << p1[3] << " ";
    cout << p1[4] << " ";
    cout << p1[5] << " ";
    cout << p1[6] << " ";
    cout << p1[7] << " ";
    cout << p1[8] << " ";
    cout << p1[9];

    
    cout << endl;

    // 27) Atribua o ENDEREÇO da quinta posição de (3) à variável declarada em (2)
    cout << &p1 << endl;

    // 28) Imprima o VALOR da variável declarada em (2)
    p1 = &v[4];

    // 29) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *p1 << endl;

    // 30) Imprima o VALOR guardado no ENDEREÇO do ponteiro (2) decrementado de 4
    cout << v[0] << endl;

    // 31) Declare um ponteiro para ponteiro e o inicialize com o ENDEREÇO da variável (2)
    cout << p1 << endl;

    // 32) Imprima o VALOR da variável declarada em (31)
    int p2 = *p1;

    // 33) Imprima o ENDEREÇO da variável declarada em (31)
    cout << p1 << endl;

    // 34) Imprima o VALOR guardado no ENDEREÇO apontado por (31)
    cout << &p2 << endl;


    // 35) Imprima o VALOR guardado no ENDEREÇO do ponteiro apontado por (31)
    cout << p2;
    

    return 0;
}