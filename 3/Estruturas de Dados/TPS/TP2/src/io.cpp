#include <io.h>

#include <fstream>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

void dados_linha_comando(int argc, char* argv[], std::string& nome_entrada, std::string& nome_saida, int& tam_mediana,
                         int& tam_particao) {
    int opt;
    while ((opt = getopt(argc, argv, "o:O:i:I:m:M:s:S:")) != -1) {
        switch (opt) {
        case 'i':
        case 'I':
            nome_entrada = optarg;
            break;
        case 'o':
        case 'O':
            nome_saida = optarg;
            break;
        case 'm':
        case 'M':
            tam_mediana = std::stoi(optarg);
            break;
        case 's':
        case 'S':
            tam_particao = std::stoi(optarg);
        }
    }
    if (nome_entrada.empty() || nome_saida.empty()) {
        throw std::invalid_argument("Nome de arquivo nao informado");
    }
    if (tam_mediana < 1) {
        throw std::invalid_argument("Tamanho da mediana nao pode ser menor que 1");
    }
    if (tam_particao < 0) {
        throw std::invalid_argument("Tamanho da particao nao pode ser negativo");
    }
}

std::string parse_token(std::string& line, const char* delimiters) {
    std::string token;
    auto lastPos = line.find_first_not_of(delimiters, 0);
    auto pos = line.find_first_of(delimiters, lastPos);
    if (std::string::npos != pos || std::string::npos != lastPos) {
        token = line.substr(lastPos, pos - lastPos);
        line.erase(0, pos);
        return token;
    }
    line.erase(0, line.size());
    return "";
}

static bool eh_delimitador(char c, const char* delimiters) {
    for (int i = 0; delimiters[i] != '\0'; i++) {
        if (c == delimiters[i]) {
            return true;
        }
    }
    return false;
}

std::stringstream limpa_texto(std::ifstream& entrada, const char* delimiters) {
    std::stringstream texto;
    char ch;
    while ((ch = entrada.get()) != std::char_traits<char>::eof()) {
        if (!eh_delimitador(ch, delimiters)) {
            texto << ch;
        }
    }
    return texto;
}
