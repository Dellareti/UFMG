#include <iostream>
#include <cstring>

using namespace std;

char palavra[46];
char vogalA[]="aA";
char vogalE[]="eE";
char vogalI[]="iI";
char vogalO[]="oO";
char vogalU[]="uU";

int contador,i,j;

int main(){

    cout << "Digite a sua palavra: " <<endl;
    cin >> palavra;

    // Contar A
    contador=0;
    for (i=0;i<=strlen(palavra);i++)
        for (j=0;j<=strlen(vogalA);j++)
            if (palavra[i]==vogalA[j] && palavra[i]!=0) contador++;
            if (contador > 0) cout << "a "  << contador <<endl;

    // Contar E
    contador=0;
    for (i=0;i<=strlen(palavra);i++)
        for (j=0;j<=strlen(vogalE);j++)
            if (palavra[i]==vogalE[j] && palavra[i]!=0) contador++;
            if (contador > 0) cout << "e "  << contador <<endl;

    // Contar I
    contador=0;
    for (i=0;i<=strlen(palavra);i++)
        for (j=0;j<=strlen(vogalI);j++)
            if (palavra[i]==vogalI[j] && palavra[i]!=0) contador++;
            if (contador > 0) cout << "i "  << contador <<endl;

    // Contar O
    contador=0;
    for (i=0;i<=strlen(palavra);i++)
        for (j=0;j<=strlen(vogalO);j++)
            if (palavra[i]==vogalO[j] && palavra[i]!=0) contador++;
            if (contador > 0) cout << "o "  << contador <<endl;

    // Contar U
    contador=0;
    for (i=0;i<=strlen(palavra);i++)
        for (j=0;j<=strlen(vogalU);j++)
            if (palavra[i]==vogalU[j] && palavra[i]!=0) contador++;
            if (contador > 0) cout << "u "  << contador <<endl;

    return 0;
}