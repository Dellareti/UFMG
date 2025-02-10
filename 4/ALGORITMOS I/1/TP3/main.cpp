#include "loja.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        std::cin >> m;
        std::vector<int> tapetes(m);
        for (int j = 0; j < m; j++) {
            std::cin >> tapetes[j];
        }
        std::cout << maior_sequencia_tapetes(tapetes) << std::endl;
    }
    return 0;
}
