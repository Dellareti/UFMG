# Calculadora Científica com GitHub Actions

Atividade prática sobre testes de unidade e GitHub Actions para a matéria Engenharia de Software 2 da UFMG.

## Como Executar

### Programa Interativo
```bash
git clone https://github.com/Italo-Dell-Areti/calculator-github-actions.git
```
```bash
cd calculator-github-actions
```
```bash
python main.py
```

### Executar Testes
```bash
python -m venv venv
```
```bash
source venv/bin/activate  # Linux/Mac
# venv\Scripts\activate   # Windows
```
# Instalar dependências de teste
```bash
pip install -r requirements-dev.txt
```
# Executar testes
```bash
pytest tests/ -v
```
```bash
pytest tests/ -v --cov=src --cov-report=html
```

### Verificar Qualidade do Código
```bash
flake8 src tests main.py --max-line-length=88
```

## Funcionalidades

**Operações Básicas:**
- Soma, subtração, multiplicação, divisão

**Operações Científicas:**
- Potência, raiz quadrada, logaritmo, logaritmo natural, fatorial

**Trigonometria:**
- Seno, cosseno, tangente (aceita graus ou radianos)
- Conversões entre graus e radianos

## Estrutura do Projeto

```
calculator-github-actions/
├── main.py                    # Programa interativo
├── src/
│   └── calculator.py          # Classe Calculadora
├── tests/
│   └── test_calculator.py     # 21 testes unitários
├── .github/workflows/ci.yml   # GitHub Actions
├── requirements.txt           # Dependências principais (vazio)
├── requirements-dev.txt       # Dependências de desenvolvimento
└── README.md                  # documentação
```

## CI/CD

O GitHub Actions executa automaticamente:
- Testes em Ubuntu, macOS e Windows
- Utiliza múltiplas versões do Python (3.9, 3.11, 3.12)
- Verificação de qualidade com flake8
- Cobertura de código com pytest-cov

## Desenvolvimento

**Instalar dependências de desenvolvimento:**

```bash
pip install -r requirements-dev.txt
```

**Executar todos os comandos de verificação:**
```bash
flake8 src tests main.py --max-line-length=88
```
```bash
pytest tests/ -v --cov=src
```
```bash
python main.py
```

## Cobertura de Testes

- 21 testes unitários
- 100% cobertura de código
- Testes de exceções e casos extremos
- Testes parametrizados para múltiplos cenários