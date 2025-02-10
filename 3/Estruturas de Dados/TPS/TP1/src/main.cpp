#include "io.h"
#include "jogador.h"
#include "jogo.h"
#include "memlog.h"

#include <fstream>
#include <string>

int main(){

    std::ifstream input("../entrada.txt");
    std::ofstream output("../saida.txt");
    char log[] = "poker.out";

    iniciaMemLog(log);
    ativaMemLog();
    Jogo game(input, output);

    game.comeca();
    game.resultado();
    input.close();
    output.close();
    
    finalizaMemLog();
    return 0;
}