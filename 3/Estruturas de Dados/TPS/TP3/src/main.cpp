#include <fstream>
#include <getopt.h>
#include <iostream>

#include <memlog.h>
#include <tabela_hash.h>

int main(int argc, char** argv) try {
    std::string nome_entrada, nome_saida;
    int opt;
    while ((opt = getopt(argc, argv, "o:O:i:I:")) != -1) {
        switch (opt) {
        case 'i':
        case 'I':
            nome_entrada = optarg;
            break;
        case 'o':
        case 'O':
            nome_saida = optarg;
            break;
        }
    }
    if (nome_entrada.empty() || nome_saida.empty()) {
        throw std::invalid_argument("Nome de arquivo nao informado");
    }

    std::ifstream entrada(nome_entrada);
    if (entrada.bad()) {
        throw std::ios_base::failure("Erro ao abrir arquivo de entrada");
    }
    std::ofstream saida(nome_saida);
    if (saida.bad()) {
        throw std::ios_base::failure("Erro ao abrir arquivo de saida");
    }
    const char* log_mem = "log_mem.txt";
    iniciaMemLog(log_mem);
    ativaMemLog();
    defineFaseMemLog(0);
    int tamanho_tabela;
    entrada >> tamanho_tabela;
    hash_table tabela(tamanho_tabela);
    int usuario, id, lixo;
    std::string comando;
    while (entrada >> comando) {
        if (comando == "ENTREGA") {
            entrada >> usuario >> id >> lixo;
            std::string texto;
            std::getline(entrada, texto);
            texto.erase(0, 1); // removendo o espaço no início da mensagem
            mensagem mensagem = {id, usuario, texto};
            if (tabela.insere(usuario, mensagem)) {
                saida << "OK: MENSAGEM " << mensagem.id << " PARA " << usuario << " ARMAZENADA EM "
                      << tabela.hash(usuario) << std::endl;
            } else {
                saida << "ERRO" << std::endl;
            }
        } else if (comando == "CONSULTA") {
            entrada >> usuario >> id;
            mensagem* mensagem = tabela.encontra(usuario, id);
            if (mensagem == nullptr || mensagem->usuario != usuario) {
                saida << "CONSULTA " << usuario << " " << id << ": MENSAGEM INEXISTENTE" << std::endl;
            } else {
                saida << "CONSULTA " << usuario << " " << id << ": " << mensagem->m << std::endl;
            }
        } else if (comando == "APAGA") {
            entrada >> usuario >> id;
            if (tabela.remove(usuario, id)) {
                saida << "OK: MENSAGEM APAGADA" << std::endl;
            } else {
                saida << "ERRO: MENSAGEM INEXISTENTE" << std::endl;
            }
        } else {
            throw std::invalid_argument("Comando invalido");
        }
    }
    finalizaMemLog();
    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}