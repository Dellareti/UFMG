#pragma once

#include <string>

void dados_linha_comando(int argc, char* argv[], std::string& nome_entrada, std::string& nome_saida, int& tam_mediana,
                         int& tam_particao);

std::string parse_token(std::string& line, const char* delimiters);

std::stringstream limpa_texto(std::ifstream& entrada, const char* delimiters);