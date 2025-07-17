import math


class Calculadora:
    def somar(self, a, b):
        return a + b

    def subtrair(self, a, b):
        return a - b

    def multiplicar(self, a, b):
        return a * b

    def dividir(self, a, b):
        if b == 0:
            raise ValueError("Divisão por zero não é permitida")
        return a / b

    def potencia(self, base, expoente):
        return base**expoente

    def raiz_quadrada(self, numero):
        if numero < 0:
            raise ValueError(
                "Raiz quadrada de números negativos não é permitida"
            )
        return math.sqrt(numero)

    def logaritmo(self, numero, base=10):
        if numero <= 0:
            raise ValueError(
                "Logaritmo de números não-positivos não é permitido"
            )
        if base <= 0 or base == 1:
            raise ValueError("Base do logaritmo inválida")
        return math.log(numero, base)

    def logaritmo_natural(self, numero):
        if numero <= 0:
            raise ValueError(
                "Logaritmo natural de números não-positivos não é permitido"
            )
        return math.log(numero)

    def fatorial(self, n):
        if not isinstance(n, int) or n < 0:
            raise ValueError(
                "Fatorial é definido apenas para números inteiros "
                "não-negativos"
            )
        return math.factorial(n)

    def seno(self, angulo):
        return math.sin(angulo)

    def cosseno(self, angulo):
        return math.cos(angulo)

    def tangente(self, angulo):
        return math.tan(angulo)

    def graus_para_radianos(self, graus):
        return math.radians(graus)

    def radianos_para_graus(self, radianos):
        return math.degrees(radianos)
