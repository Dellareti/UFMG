#include "rock.hpp"
#include <iostream>

int main() {
    int amigos, shows;
    std::cin >> amigos >> shows;
    while (amigos != 0 && shows != 0) {
        double notas[shows] = {};
        for (int i = 0; i < amigos; i++) {
            for (int j = 0; j < shows; j++) {
                double nota;
                std::cin >> nota;
                notas[j] += nota;
            }
        }
        std::cout << escolhe_melhores_shows(notas, shows) << std::endl;
        std::cin >> amigos >> shows;
    }
}