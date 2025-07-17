"""
Calculadora Científica Interativa
Execute: python main.py
"""
from src.calculator import Calculadora


class CalculadoraInterativa:
    def __init__(self):
        self.calc = Calculadora()
        self.opcoes = {
            '1': ('Soma', self.soma),
            '2': ('Subtração', self.subtracao),
            '3': ('Multiplicação', self.multiplicacao),
            '4': ('Divisão', self.divisao),
            '5': ('Potência', self.potencia),
            '6': ('Raiz Quadrada', self.raiz_quadrada),
            '7': ('Logaritmo', self.logaritmo),
            '8': ('Logaritmo Natural', self.logaritmo_natural),
            '9': ('Fatorial', self.fatorial),
            '10': ('Seno', self.seno),
            '11': ('Cosseno', self.cosseno),
            '12': ('Tangente', self.tangente),
            '13': ('Graus para Radianos', self.graus_para_radianos),
            '14': ('Radianos para Graus', self.radianos_para_graus),
            '0': ('Sair', None)
        }

    def mostrar_menu(self):
        print("\n" + "=" * 50)
        print("   CALCULADORA CIENTÍFICA INTERATIVA")
        print("=" * 50)
        print("Escolha uma opção:")
        print()
        for codigo, (nome, _) in self.opcoes.items():
            if codigo == '0':
                print(f"{codigo}. {nome}")
            else:
                print(f"{codigo:>2}. {nome}")
        print("=" * 50)

    def obter_numero(self, mensagem="Digite um número: "):
        while True:
            try:
                return float(input(mensagem))
            except ValueError:
                print("Por favor, digite um número válido!")

    def obter_inteiro(self, mensagem="Digite um número inteiro: "):
        while True:
            try:
                valor = int(input(mensagem))
                return valor
            except ValueError:
                print("Por favor, digite um número inteiro válido!")

    def soma(self):
        print("\nSOMA")
        a = self.obter_numero("Digite o primeiro número: ")
        b = self.obter_numero("Digite o segundo número: ")
        resultado = self.calc.somar(a, b)
        print(f"{a} + {b} = {resultado}")

    def subtracao(self):
        print("\nSUBTRAÇÃO")
        a = self.obter_numero("Digite o primeiro número: ")
        b = self.obter_numero("Digite o segundo número: ")
        resultado = self.calc.subtrair(a, b)
        print(f"{a} - {b} = {resultado}")

    def multiplicacao(self):
        print("\nMULTIPLICAÇÃO")
        a = self.obter_numero("Digite o primeiro número: ")
        b = self.obter_numero("Digite o segundo número: ")
        resultado = self.calc.multiplicar(a, b)
        print(f"{a} x {b} = {resultado}")

    def divisao(self):
        print("\nDIVISÃO")
        a = self.obter_numero("Digite o dividendo: ")
        b = self.obter_numero("Digite o divisor: ")
        try:
            resultado = self.calc.dividir(a, b)
            print(f"{a} / {b} = {resultado}")
        except ValueError as e:
            print(f"Erro: {e}")

    def potencia(self):
        print("\nPOTÊNCIA")
        base = self.obter_numero("Digite a base: ")
        expoente = self.obter_numero("Digite o expoente: ")
        resultado = self.calc.potencia(base, expoente)
        print(f"{base}^{expoente} = {resultado}")

    def raiz_quadrada(self):
        print("\nRAIZ QUADRADA")
        numero = self.obter_numero("Digite o número: ")
        try:
            resultado = self.calc.raiz_quadrada(numero)
            print(f"√{numero} = {resultado}")
        except ValueError as e:
            print(f"Erro: {e}")

    def logaritmo(self):
        print("\nLOGARITMO")
        numero = self.obter_numero("Digite o número: ")
        base = self.obter_numero("Digite a base (padrão 10): ")
        try:
            resultado = self.calc.logaritmo(numero, base)
            print(f"log_{base}({numero}) = {resultado}")
        except ValueError as e:
            print(f"Erro: {e}")

    def logaritmo_natural(self):
        print("\nLOGARITMO NATURAL")
        numero = self.obter_numero("Digite o número: ")
        try:
            resultado = self.calc.logaritmo_natural(numero)
            print(f"ln({numero}) = {resultado}")
        except ValueError as e:
            print(f"Erro: {e}")

    def fatorial(self):
        print("\nFATORIAL")
        numero = self.obter_inteiro("Digite um número inteiro: ")
        try:
            resultado = self.calc.fatorial(numero)
            print(f"{numero}! = {resultado}")
        except ValueError as e:
            print(f"Erro: {e}")

    def seno(self):
        print("\nSENO")
        print("1 - Ângulo em graus")
        print("2 - Ângulo em radianos")
        opcao = input("Escolha (1 ou 2): ")

        if opcao == '1':
            graus = self.obter_numero("Digite o ângulo em graus: ")
            radianos = self.calc.graus_para_radianos(graus)
            resultado = self.calc.seno(radianos)
            print(f"sen({graus}°) = {resultado:.6f}")
        elif opcao == '2':
            radianos = self.obter_numero("Digite o ângulo em radianos: ")
            resultado = self.calc.seno(radianos)
            print(f"sen({radianos} rad) = {resultado:.6f}")
        else:
            print("Opção inválida!")

    def cosseno(self):
        print("\nCOSSENO")
        print("1 - Ângulo em graus")
        print("2 - Ângulo em radianos")
        opcao = input("Escolha (1 ou 2): ")

        if opcao == '1':
            graus = self.obter_numero("Digite o ângulo em graus: ")
            radianos = self.calc.graus_para_radianos(graus)
            resultado = self.calc.cosseno(radianos)
            print(f"cos({graus}°) = {resultado:.6f}")
        elif opcao == '2':
            radianos = self.obter_numero("Digite o ângulo em radianos: ")
            resultado = self.calc.cosseno(radianos)
            print(f"cos({radianos} rad) = {resultado:.6f}")
        else:
            print("Opção inválida!")

    def tangente(self):
        print("\nTANGENTE")
        print("1 - Ângulo em graus")
        print("2 - Ângulo em radianos")
        opcao = input("Escolha (1 ou 2): ")

        if opcao == '1':
            graus = self.obter_numero("Digite o ângulo em graus: ")
            radianos = self.calc.graus_para_radianos(graus)
            resultado = self.calc.tangente(radianos)
            print(f"tan({graus}°) = {resultado:.6f}")
        elif opcao == '2':
            radianos = self.obter_numero("Digite o ângulo em radianos: ")
            resultado = self.calc.tangente(radianos)
            print(f"tan({radianos} rad) = {resultado:.6f}")
        else:
            print("Opção inválida!")

    def graus_para_radianos(self):
        print("\nCONVERSÃO: GRAUS → RADIANOS")
        graus = self.obter_numero("Digite o ângulo em graus: ")
        resultado = self.calc.graus_para_radianos(graus)
        print(f"{graus}° = {resultado:.6f} radianos")

    def radianos_para_graus(self):
        print("\nCONVERSÃO: RADIANOS → GRAUS")
        radianos = self.obter_numero("Digite o ângulo em radianos: ")
        resultado = self.calc.radianos_para_graus(radianos)
        print(f"{radianos} rad = {resultado:.6f}°")

    def executar(self):
        print("Bem-vindo à Calculadora Científica!")

        while True:
            self.mostrar_menu()

            opcao = input("\nDigite sua opção: ").strip()

            if opcao == '0':
                print("\nAté logo!")
                break

            if opcao in self.opcoes and opcao != '0':
                nome, funcao = self.opcoes[opcao]
                try:
                    funcao()
                except KeyboardInterrupt:
                    print("\n\nOperação cancelada pelo usuário.")
                except Exception as e:
                    print(f"\nErro inesperado: {e}")

                input("\nPressione Enter para continuar...")
            else:
                print("Opção inválida! Tente novamente.")
                input("\nPressione Enter para continuar...")


def main():
    calculadora = CalculadoraInterativa()
    calculadora.executar()


if __name__ == "__main__":
    main()
