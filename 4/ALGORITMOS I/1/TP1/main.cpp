#include <iostream>
#include <campanha.h>

int main() {
    int seguidores;
    int propostas;

    std::cin >> seguidores >> propostas;

    while (seguidores != 0 && propostas != 0) {
        int* a = new int[seguidores * 2];
        int* b = new int[seguidores * 2];
        int x1, x2, y1, y2;
        int j = 0;

        for (int i = 0; i < seguidores; i++) {
            std::cin >> x1 >> x2 >> y1 >> y2;
            a[j] = x1 == 0 ? x2 : x1;
            b[j] = x2 == 0 ? x1 : x2;
            j++; // iterando o indíce dos vetores com cada "lado" do par de variáveis pois acabamos de guardar um
            a[j] = y1 == 0 ? -y2 : -y1; // como estamos utilizando CNF, vamos aproveitar que (A || A) <=> A
            b[j] = y2 == 0 ? -y1 : -y2;
            j++; // mesma coisa
        }
        std::cout << (Campanha(seguidores, propostas).satisfaz(a, b) ? "sim" : "nao") << std::endl;
        delete[] a;
        delete[] b;
        std::cin >> seguidores >> propostas;
    }
    return 0;
}