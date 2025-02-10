#include <alfabeto.h>
#include <io.h>
#include <lista.h>
#include <memlog.h>
#include <sort.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) try {
    int opt, tam_mediana = 1, tam_particao = 0;
    std::string nome_entrada, nome_saida;
    dados_linha_comando(argc, argv, nome_entrada, nome_saida, tam_mediana, tam_particao);

    const char* log_mem = "log_mem.txt";
    iniciaMemLog(log_mem);
    ativaMemLog();

    std::ifstream entrada(nome_entrada);
    if (entrada.bad()) {
        throw std::ios_base::failure("Erro ao abrir arquivo de entrada");
    }
    std::ofstream saida(nome_saida);
    if (saida.bad()) {
        throw std::ios_base::failure("Erro ao abrir arquivo de saida");
    }
    Alfabeto* alfabeto;
    Lista* lista;
    std::string linha;
    std::stringstream texto = limpa_texto(entrada, ",.!?:;_");
    defineFaseMemLog(0);
    while (std::getline(texto, linha)) {
        if (linha == "#TEXTO") {
            lista = new Lista();
            while (std::getline(texto, linha)) {
                if (linha == "#ORDEM") {
                    break;
                }
                while (!linha.empty()) {
                    auto token = parse_token(linha, " \t\n\r\v\f");
                    if (!token.empty()) {
                        if (token[token.size() - 1] == '-') {
                            token += parse_token(linha, " \t\n\r\v\f");
                        }
                        lista->atualiza(token);
                    }
                }
            }
        }
        if (linha == "#ORDEM") {
            std::getline(texto, linha);
            alfabeto = new Alfabeto(linha);
        }
    }
    auto palavras = lista->to_array();
    defineFaseMemLog(1);
    quicksort(palavras, 0, lista->get_tamanho() - 1, alfabeto, tam_particao, tam_mediana);

    for (int i = 0; i < lista->get_tamanho(); i++) {
        saida << palavras[i].palavra << " " << palavras[i].ocorrencias << std::endl;
    }
    saida << "#FIM" << std::endl;
    finalizaMemLog();
    delete alfabeto;
    delete lista;
    return EXIT_SUCCESS;

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}