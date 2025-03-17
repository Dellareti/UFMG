# 💰 Consultas SQL - Banco de Dados de Despesas Governamentais

Este repositório contém implementações de consultas SQL para análise de dados de empenhos governamentais, desenvolvido como parte do Trabalho Prático 1 da disciplina de Banco de Dados.

## 📋 Visão Geral do Projeto

O trabalho consiste em elaborar consultas SQL baseadas em expressões de álgebra relacional e especificações em linguagem natural. O banco de dados utilizado contém informações sobre empenhos realizados pelo Governo de vários Estados do Brasil, incluindo órgãos, unidades, favorecidos e itens de empenho.

## 🗄️ Esquema do Banco de Dados

O banco de dados contém as seguintes tabelas:
- **empenho**: Registros de empenhos governamentais
- **favorecido**: Fornecedores que receberam os empenhos
- **item_empenho**: Itens específicos de cada empenho
- **orgao**: Órgãos governamentais
- **unidade**: Unidades dentro de cada órgão

## 🔍 Consultas Implementadas

### Consultas de Álgebra Relacional:
1. Listar nome dos fornecedores de SP
2. Obter códigos de empenho e valores para empenhos superiores a R$1.000.000
3. Listar nomes de fornecedores e valores de empenho para valores inferiores a R$1.000
4. Mostrar nomes de unidades e valores de empenho para a unidade 152005
5. Listar IDs e nomes de unidades do Ministério da Economia

### Consultas em Linguagem Natural:
1. Listar empenhos emitidos em 2020
2. Mostrar as 3 UFs com menos favorecidos cadastrados
3. Listar unidades que começam com "SUPERINTENDENCIA" e seus órgãos
4. Obter códigos de empenho com a palavra "COBRIR" na observação
5. Listar fornecedores com mais de um empenho e a contagem de empenhos
6. Exibir unidades e a soma total de valores de seus itens
7. Mostrar órgãos com mais de 10 favorecidos e suas contagens
8. Listar empenhos relacionados ao Ministério da Saúde
9. Exibir unidades com favorecidos em Minas Gerais
10. Listar descrições dos itens relacionados ao Ministério da Saúde

## 🛠️ Tecnologias Utilizadas

- SQLite3
- Python/Jupyter Notebook

## 📊 Estrutura do Projeto

- **bancoDadosDespesas.sql**: Script SQL com o esquema e dados do banco
- **tp1.ipynb**: Notebook Jupyter com as implementações das consultas
- **README.md**: Este arquivo de documentação

## 🚀 Como Executar

1. Instale o [Anaconda](https://www.anaconda.com/download/)
2. Abra o Anaconda Navigator e inicie o Jupyter Notebook
3. Carregue o arquivo tp1.ipynb
4. Execute as células que configuram o banco de dados
5. Execute as consultas SQL implementadas

## 📝 Observações

O banco de dados foi baseado no portal de transparência do governo brasileiro, mas alguns registros foram modificados para melhor aproveitamento didático.

## 👨‍💻 Autor

Este projeto foi desenvolvido como parte da disciplina de Introdução a Banco de Dados.

---

*Nota: Este repositório serve apenas para fins educacionais e de demonstração de habilidades em SQL e conceitos de banco de dados.*
