#include <iostream>

#include "ExtratorDeDados.hpp"

#include <cmath>
#include <algorithm>
#include <map>

/**
 * \class Num2Sqrt
 *
 * \brief Esta class mapeia numeros em suas raizes quadradas.
 *
 * \tparam NUM_TYPE o tipo do numero. Note que qualquer tipo que aceite a
 * operacao sqrt eh valido: char, int, float, double, etc.
 */
template <class NUM_TYPE>
class Num2Sqrt : public Mapeador<NUM_TYPE, NUM_TYPE> {
    NUM_TYPE transformaDado(NUM_TYPE& d) const override {
        d = sqrt(d);
        return d;
    }
};

/**
 * \class String2Int
 *
 * \brief Esta classe implementa um Mapeador que transforma uma string no
 * numero que aquela string representa. Eh um erro invocar o metodo
 * "transformaDado" em uma string que nao represente um numero.
 */
class String2Int : public Mapeador<std::string, int> {
    int transformaDado(std::string& d) const override {
        return std::stoi(d);
    }
};

/**
 * \class Num2MaiorFator
 *
 * \brief Esta classe implementa um Mapeador que mapeia um numero inteiro em
 * seu maior fator. Exemplos:
 *
 * 10 => 5
 * 12 => 6
 * 9 => 3
 * 3 => 1
 */
class Num2MaiorFator : public Mapeador<int, int> {
    int transformaDado(int& d) const override {
        auto primeiro_div = 1;
        for (int i = 2; i <= sqrt(d); i++)
        {
            if (d % i == 0)
            {
                primeiro_div = i;
                break;
            }
        }
        return primeiro_div == 1 ? 1 : d / primeiro_div;
    }
};

/**
 * \class FiltroNumPositivo.
 *
 * \brief Esta class filtra numeros positivos.
 *
 * \tparam NUM_TYPE o tipo do numero. Note que qualquer tipo que aceite a
 * operacao de comparacao contra zero eh aceitavel: double, int, short, etc.
 */
template <class NUM_TYPE>
class FiltroNumPositivo : public Filtro<NUM_TYPE> {
    bool dadoValido(NUM_TYPE& d) const override {
        return d > 0;
    }
};

/**
 * \class FiltroNumAbundante.
 *
 * \brief Esta class filtra numeros "abundantes", isto eh, cuja soma dos
 * divisores seja maior que o proprio numero.
 *
 * \details
 * Por exemplo, 12 � um n�mero abundante, pois a soma dos seus divisores � 16
 * (exemplo da wikipedia)
 * 1 + 2 + 3 + 4 + 6 = 16
 *
 * Os primeiros dez numeros abundantes sao:
 * 12, 18, 20, 24, 30, 36, 40, 42, 48, 54
 */
class FiltroNumAbundante : public Filtro<int> {
    bool dadoValido(int& num) const override {
        auto soma = 1;
        auto primeiro_div = 1;
        for(int i = 2; i < sqrt(num); i++)
        {
	        if(num % i == 0)
	        {
                primeiro_div = i;
                break;
	        }
        }
        if (primeiro_div == 1)
        {
            return false;
        }
        for (int i = primeiro_div; i <= num / primeiro_div; i++)
        {
            if (num % i == 0)
            {
                soma += i;
            }
        }
        return soma > num;
    }
};

/**
 * \class FiltroNumTriangular.
 *
 * \brief Esta class filtra numeros "triangulares".
 *
 * \details
 * Numeros triangulares sao numeros inteiros que sao a soma de uma progressao
 * aritmetica de incremento 1:
 * 1: 1
 * 3: 1+2
 * 6: 1+2+3
 * 10: 1+2+3+4
 * etc
 */
class FiltroNumTriangular : public Filtro<int> {
    bool dadoValido(int& num) const override {
        auto soma = 0;
    	for(int i = 1; soma < num; i++)
    	{
            soma += i;
    	}
        return soma == num;
    }
};

/**
 * \class FiltroStringNatural
 *
 * \brief Filtra strings que representam numeros naturais.
 *
 * \details
 * As strings validas devem conter somente digitos. Nao consideramos sinais
 * de mais ou menos, nem ponto ou virgula decimal. Somente numeros.
 */
class FiltroStringNatural : public Filtro<std::string> {
    bool dadoValido(std::string& d) const override {
        return std::all_of(d.begin(), d.end(), ::isdigit);
    }
};

/**
 * \brief Preenche um vetor com dados lidos a partir da entrada padrao.
 *
 * \param vec O vetor que serah preenchido
 *
 * \tparam T o tipo dos dados que serao lidos.
 */
template <class T> void read_input(std::vector<T>& vec) {
    T val;
    while (std::cin >> val) {
        vec.push_back(val);
    }
}

/**
 * \brief Imprime na saida padrao os dados armazenados em um vetor.
 *
 * \param vec O vetor que contem os dados a serem impressos.
 *
 * \tparam T o tipo dos dados que serao impressos.
 */
template <class T> void print_output(std::vector<T>& vec) {
    for (T& d : vec) {
        std::cout << d << std::endl;
    }
}

/**
 * \brief Converte strings que forem numeros em valores do tipo inteiro.
 *
 * \details
 * Essa funcao atravesa o vetor de entrada "in", e filtra as strings que
 * denotam numeros "naturais". Um numero natural eh um numero inteiro, sem
 * sinal (e por consequinte, necessariamente positivo). Exemplos:
 *
 * "1.0" -> Nao eh dado valido
 * "-1" -> Nao eh dado valido
 * "1" -> Eh dado valido
 * "1.0e2" -> Nao eh dado valido
 * "Abacaxi" -> Nao eh dado valido
 *
 * \param in Vetor contendo strings de entrada.
 * \param out Vetor que irah armazenar os numeros que puderem ser convertidos.
 */
void convert2int(std::vector<std::string>& in, std::vector<int>& out) {
    auto filtro = FiltroStringNatural();
    auto map = String2Int();
    ExtratorDeDados<std::string, int> e(in, filtro, map);
    e.getData(out);
}

/**
 * \brief Testa se a funcao que extrai raizes quadradas funciona corretamente.
 *
 * \details
 * Este eh um codigo de teste. Normalmente, o codigo de teste eh pre-construido
 * no VPL. Porem, a fim de explicar ao aluno como instanciar um algoritmo
 * generico, ele/a deverah preencher este teste. Fique a vontade para olhar
 * como os demais testes foram feitos. Esse codigo serah muito similar.
 *
 * Os passos para montar o teste sao dados como comentarios no corpo do
 * metodo test_filter_square_roots, logo abaixo.
 */
template <class NUM_TYPE> void test_filter_square_roots() {
    // 1. Declarar os vetores que serao usados para ler e escrever os dados:
    //
    // 2. Ler os dados que deverao ser processados:
    //
    // 3. Instanciar o Filtro que retorna verdadeiro para numeros positivos.
    //
    // 4. Instanciar o Mapa que transforma um numero em sua raiz quadrada.
    //
    // 5. Instanciar o extrator de dados com o filtro e e mapeador construidos
    //    nos passos 3 e 4.
    //
    // 6. Invocar o metodo getData sobre o extrator de dados, para assim preencher
    //    o vetor de dados de saida.
    //
    // 7. Imprimeir os resultados armazenados no vetor de saida de dados.
    //
    // 8. Apagar o filtro e o mapeador criados nos passos 3 e 4:
    std::vector<NUM_TYPE> input;
    std::vector<NUM_TYPE> output;
    read_input(input);
    auto filtro = FiltroNumPositivo<NUM_TYPE>();
    auto map = Num2Sqrt<NUM_TYPE>();
    ExtratorDeDados<NUM_TYPE, NUM_TYPE> e(input, filtro, map);
    e.getData(output);
    print_output(output);
}

/*
 * Codigo de teste.
 * ----------------
 * Voce pode estudar esse codigo, se quiser, mas trata-se de codigo gerado
 * mecanicamente, somente para testar as funcoes desenvolvidas nesse exercicio.
 *
 * Importante: o codigo abaixo nao usa boas normas de programacao: ele eh
 * redundante e desnecessariamente extenso.
 */

void print_only_naturals() {
    std::vector<std::string> input_data;
    std::vector<int> output_data;
    read_input(input_data);
    convert2int(input_data, output_data);
    print_output(output_data);
}

void print_maior_fator_de_numeros_triangulares() {
    std::vector<int> input_data;
    std::vector<int> output_data;
    read_input(input_data);
    Filtro<int>* filtro = new FiltroNumTriangular();
    Mapeador<int, int>* mapeador = new Num2MaiorFator();
    ExtratorDeDados<int, int> extractor(input_data, *filtro, *mapeador);
    extractor.getData(output_data);
    print_output(output_data);
    delete filtro;
    delete mapeador;
}
void print_maior_fator_de_numeros_abundantes() {
    std::vector<int> input_data;
    std::vector<int> output_data;
    read_input(input_data);
    Filtro<int>* filtro = new FiltroNumAbundante();
    Mapeador<int, int>* mapeador = new Num2MaiorFator();
    ExtratorDeDados<int, int> extractor(input_data, *filtro, *mapeador);
    extractor.getData(output_data);
    print_output(output_data);
    delete filtro;
    delete mapeador;
}

void print_maior_fator_de_strings_que_sao_numeros_triangulares() {
    std::vector<std::string> input_data;
    std::vector<int> in_numbers_only;
    read_input(input_data);
    convert2int(input_data, in_numbers_only);
    Filtro<int>* filtro = new FiltroNumTriangular();
    Mapeador<int, int>* mapeador = new Num2MaiorFator();
    ExtratorDeDados<int, int> extractor(in_numbers_only, *filtro, *mapeador);
    std::vector<int> output_data;
    extractor.getData(output_data);
    print_output(output_data);
    delete filtro;
    delete mapeador;
}

void test_filter_maior_fator_positivo() {
    std::vector<int> input_data;
    std::vector<int> output_data;
    read_input(input_data);
    Filtro<int>* filtro = new FiltroNumPositivo<int>();
    Mapeador<int, int>* mapeador = new Num2MaiorFator();
    ExtratorDeDados<int, int> extractor(input_data, *filtro, *mapeador);
    extractor.getData(output_data);
    print_output(output_data);
    delete filtro;
    delete mapeador;
}

int main() {
    int option = 0;
    std::cin >> option;
    switch (option) {
    case 0:
        test_filter_square_roots<int>();
        break;
    case 1:
        test_filter_square_roots<double>();
        break;
    case 2:
        print_maior_fator_de_numeros_triangulares();
        break;
    case 3:
        print_only_naturals();
        break;
    case 4:
        print_maior_fator_de_strings_que_sao_numeros_triangulares();
        break;
    case 5:
        test_filter_maior_fator_positivo();
        break;
    case 6:
        print_maior_fator_de_numeros_abundantes();
        break;
    default:
        std::cout << "Caso de teste desconhecido " << option << std::endl;
    }
}