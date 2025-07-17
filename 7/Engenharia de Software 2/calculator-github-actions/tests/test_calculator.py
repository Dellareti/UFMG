import pytest
import math
from src.calculator import Calculadora


class TestCalculadora:
    def setup_method(self):
        self.calc = Calculadora()

    def test_soma(self):
        assert self.calc.somar(2, 3) == 5
        assert self.calc.somar(-1, 1) == 0
        assert self.calc.somar(0, 0) == 0
        assert self.calc.somar(-5, -3) == -8

    def test_subtracao(self):
        assert self.calc.subtrair(5, 3) == 2
        assert self.calc.subtrair(0, 5) == -5
        assert self.calc.subtrair(-3, -5) == 2
        assert self.calc.subtrair(10, 0) == 10

    def test_multiplicacao(self):
        assert self.calc.multiplicar(3, 4) == 12
        assert self.calc.multiplicar(-2, 5) == -10
        assert self.calc.multiplicar(0, 100) == 0
        assert self.calc.multiplicar(-3, -4) == 12

    def test_divisao(self):
        assert self.calc.dividir(10, 2) == 5
        assert self.calc.dividir(9, 3) == 3
        assert self.calc.dividir(-10, 2) == -5
        assert self.calc.dividir(7, 4) == 1.75

    def test_divisao_por_zero(self):
        with pytest.raises(ValueError, match="Divisão por zero não é permitida"):
            self.calc.dividir(5, 0)

    def test_potencia(self):
        assert self.calc.potencia(2, 3) == 8
        assert self.calc.potencia(5, 2) == 25
        assert self.calc.potencia(10, 0) == 1
        assert self.calc.potencia(2, -2) == 0.25

    def test_raiz_quadrada(self):
        assert self.calc.raiz_quadrada(4) == 2
        assert self.calc.raiz_quadrada(9) == 3
        assert self.calc.raiz_quadrada(0) == 0
        assert abs(self.calc.raiz_quadrada(2) - 1.4142135623730951) < 1e-10

    def test_raiz_quadrada_negativo(self):
        with pytest.raises(
            ValueError, match="Raiz quadrada de números negativos não é permitida"
        ):
            self.calc.raiz_quadrada(-4)

    def test_logaritmo(self):
        assert self.calc.logaritmo(100, 10) == 2
        assert self.calc.logaritmo(8, 2) == 3
        assert self.calc.logaritmo(1, 10) == 0
        assert abs(self.calc.logaritmo(10) - 1) < 1e-10

    def test_logaritmo_invalido(self):
        with pytest.raises(
            ValueError, match="Logaritmo de números não-positivos não é permitido"
        ):
            self.calc.logaritmo(-5)

        with pytest.raises(
            ValueError, match="Logaritmo de números não-positivos não é permitido"
        ):
            self.calc.logaritmo(0)

        with pytest.raises(ValueError, match="Base do logaritmo inválida"):
            self.calc.logaritmo(10, 0)

        with pytest.raises(ValueError, match="Base do logaritmo inválida"):
            self.calc.logaritmo(10, 1)

    def test_logaritmo_natural(self):
        assert abs(self.calc.logaritmo_natural(math.e) - 1) < 1e-10
        assert self.calc.logaritmo_natural(1) == 0
        assert abs(self.calc.logaritmo_natural(10) - 2.302585092994046) < 1e-10

    def test_logaritmo_natural_invalido(self):
        with pytest.raises(
            ValueError,
            match="Logaritmo natural de números não-positivos não é permitido",
        ):
            self.calc.logaritmo_natural(-1)

        with pytest.raises(
            ValueError,
            match="Logaritmo natural de números não-positivos não é permitido",
        ):
            self.calc.logaritmo_natural(0)

    def test_fatorial(self):
        assert self.calc.fatorial(0) == 1
        assert self.calc.fatorial(1) == 1
        assert self.calc.fatorial(5) == 120
        assert self.calc.fatorial(3) == 6

    def test_fatorial_invalido(self):
        with pytest.raises(
            ValueError,
            match="Fatorial é definido apenas para números inteiros não-negativos",
        ):
            self.calc.fatorial(-1)

        with pytest.raises(
            ValueError,
            match="Fatorial é definido apenas para números inteiros não-negativos",
        ):
            self.calc.fatorial(3.5)

    def test_funcoes_trigonometricas(self):
        assert abs(self.calc.seno(0) - 0) < 1e-10
        assert abs(self.calc.seno(math.pi / 2) - 1) < 1e-10
        assert abs(self.calc.cosseno(0) - 1) < 1e-10
        assert abs(self.calc.cosseno(math.pi) - (-1)) < 1e-10
        assert abs(self.calc.tangente(0) - 0) < 1e-10
        assert abs(self.calc.tangente(math.pi / 4) - 1) < 1e-10

    def test_conversoes(self):
        assert abs(self.calc.graus_para_radianos(180) - math.pi) < 1e-10
        assert abs(self.calc.graus_para_radianos(90) - math.pi / 2) < 1e-10
        assert abs(self.calc.radianos_para_graus(math.pi) - 180) < 1e-10
        assert abs(self.calc.radianos_para_graus(math.pi / 2) - 90) < 1e-10

    @pytest.mark.parametrize(
        "a,b,expected", [(1, 2, 3), (10, -5, 5), (0.5, 0.3, 0.8), (-7, 3, -4)]
    )
    def test_soma_parametrizada(self, a, b, expected):
        assert self.calc.somar(a, b) == expected

    def test_numeros_grandes(self):
        assert self.calc.somar(1e10, 1e10) == 2e10
        assert self.calc.multiplicar(1e6, 1e6) == 1e12
        assert self.calc.potencia(10, 10) == 10000000000
