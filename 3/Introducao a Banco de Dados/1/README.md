# 🏅 Consultas SQL para Banco de Dados dos Jogos Olímpicos

Este repositório contém consultas SQL para análise de dados dos Jogos Olímpicos de 1896 a 2016. O projeto foi desenvolvido como parte do trabalho prático da disciplina de Introdução a Banco de Dados.

## 📊 Visão Geral do Projeto

O trabalho envolve a criação de consultas SQL baseadas em expressões de álgebra relacional e especificações em linguagem natural. O banco de dados contém informações abrangentes sobre eventos dos Jogos Olímpicos, atletas, países, medalhas e muito mais.

## 📋 Esquema do Banco de Dados

O banco de dados consiste nas seguintes tabelas:
- **jogos**: Edições dos Jogos Olímpicos (1896-2016)
- **cidade**: Cidades-sede
- **jogos_cidade**: Tabela de junção ligando Jogos às cidades-sede
- **pessoa**: Atletas/competidores
- **regiao_con**: Comitês Olímpicos Nacionais (CONs)
- **esporte**: Esportes
- **evento**: Eventos para cada esporte
- **medalha**: Tipos de medalhas
- **pessoa_regiao**: Tabela de junção ligando pessoas aos CONs
- **jogos_competidor**: Tabela de junção ligando pessoas a Jogos específicos
- **competidor_evento**: Tabela de junção ligando competidores a eventos e medalhas

## 🔍 Consultas Implementadas

O repositório inclui implementações SQL para várias consultas analíticas, como:

### Consultas de Álgebra Relacional (A0-A4):
- A0: Listar os nomes completos das pessoas que competiram com 80 anos ou mais
- A1: Listar os nomes dos atletas da Equipe Olímpica de Refugiados
- A2: Listar os anos e as estações dos Jogos Olímpicos que aconteceram em Londres
- A3: Listar nomes completos e alturas das pessoas que competiram nos Jogos Olímpicos de 2016 com altura de 215cm ou mais
- A4: Listar nomes completos de atletas femininas com mais de 200cm de altura

### Consultas em Linguagem Natural (B1-B9):
- B1: Listar o nome, gênero e total de medalhas de ouro da pessoa com mais medalhas de ouro
- B3: Listar cidades que sediaram mais de uma edição dos Jogos Olímpicos e seus respectivos países
- B5: Listar países e continentes com cidades sede dos Jogos Olímpicos de Inverno
- B8: Listar os anos dos Jogos Olímpicos de Inverno e a quantidade de CONs participantes
- B9: Listar CONs que nunca ganharam medalhas na história dos Jogos Olímpicos

## 📝 Estrutura de Arquivos

- `answers.sql`: Consultas SQL de referência para cada problema
- `submission.sql`: Minhas soluções SQL implementadas
- `dictionary.pdf`: Descrição detalhada das tabelas e campos do banco de dados
- `assignment.pdf`: Descrição original do trabalho

## 🛠️ Tecnologias Utilizadas

- SQLite3
- SQL

## 📈 Critérios de Avaliação

As consultas foram avaliadas com base em:
1. Execução correta sem erros
2. Retorno exato das colunas solicitadas na ordem especificada
3. Coeficiente de similaridade do índice de Jaccard entre os resultados retornados e esperados

## 👨‍💻 Sobre o Autor

Este projeto foi implementado como parte da disciplina de Introdução a Banco de Dados. As consultas demonstram habilidades em SQL, álgebra relacional e análise de banco de dados.

## 📚 Como Usar

1. Clone este repositório
2. Configure o SQLite com o esquema de banco de dados fornecido
3. Execute as consultas em `submission.sql` para analisar os dados dos Jogos Olímpicos

---

*Observação: Este banco de dados foi simplificado para fins educacionais e pode não corresponder exatamente aos dados reais dos Jogos Olímpicos.*
