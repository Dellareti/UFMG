-- A0.
-- ALGEBRA RELACIONAL
-- Liste o nome completo das pessoas que competiram com 80 ou mais anos
SELECT DISTINCT nome_completo
FROM pessoa P
INNER JOIN jogos_competidor JC
    ON P.id_pessoa = JC.id_pessoa
WHERE JC.idade >= 80;

-- A1.
-- ALGEBRA RELACIONAL
-- Liste o nome das pessoas que fizeram parte da Equipe olímpica de refugiados
SELECT DISTINCT nome_completo
FROM pessoa P
INNER JOIN pessoa_regiao PR
    ON P.id_pessoa = PR.id_pessoa
INNER JOIN regiao_con RC
    ON PR.id_regiao = RC.id_regiao
WHERE RC.nome_regiao = 'Equipe olímpica de refugiados';

-- A2. 
-- ALGEBRA RELACIONAL
-- Liste os anos e as estações das edições dos Jogos Olímpicos que acontecerem em Londres 
SELECT ano_jogos,
         estacao
FROM jogos J
INNER JOIN jogos_cidade JC
    ON J.id_jogos = JC.id_jogos
INNER JOIN cidade C
    ON JC.id_cidade = C.id_cidade
WHERE C.nome_cidade = 'Londres';

-- A3.
-- ALGEBRA RELACIONAL
-- Liste o nome completo e a altura das pessoas que competiram nos Jogos Olímpicos de 2016 com uma altura de 215 centímetros ou mais
SELECT DISTINCT P.nome_completo,
         P.altura
FROM pessoa P
INNER JOIN jogos_competidor JC
    ON P.id_pessoa = JC.id_pessoa
INNER JOIN jogos J
    ON J.id_jogos = JC.id_jogos
WHERE P.altura >= 215
        AND J.ano_jogos = 2016;

-- A4. 
-- ALGEBRA RELACIONAL
-- Liste o nome completo das pessoas do gênero feminino (F) com mais de 200 centímetros de altura
SELECT DISTINCT nome_completo,
         altura
FROM pessoa
WHERE genero = 'F'
        AND altura >= 200;

-- A5.
-- ALGEBRA RELACIONAL
-- Liste os anos que aconteceram os Jogos Olímpicos de Inverno
SELECT DISTINCT ano_jogos
FROM jogos
WHERE estacao = 'Inverno';

-- A6.
-- ALGEBRA RELACIONAL
-- Liste o nome dos esportes presentes nos Jogos Olímpicos de 1896
SELECT DISTINCT ES.nome_esporte
FROM esporte ES
INNER JOIN evento EV
    ON ES.id_esporte = EV.id_esporte
INNER JOIN competidor_evento CE
    ON EV.id_evento = CE.id_evento
INNER JOIN jogos_competidor JC
    ON CE.id_competidor = JC.id_competidor
INNER JOIN jogos J
    ON JC.id_jogos = J.id_jogos
WHERE ano_jogos = 1896;

-- A7.
-- ALGEBRA RELACIONAL
-- Liste o ano e a estação dos Jogos Olímpicos que o Brasil participou
SELECT DISTINCT J.ano_jogos,
         J.estacao
FROM jogos J
INNER JOIN jogos_competidor JC
    ON J.id_jogos = JC.id_jogos
INNER JOIN pessoa P
    ON P.id_pessoa = JC.id_pessoa
INNER JOIN pessoa_regiao PR
    ON P.id_pessoa = PR.id_pessoa
INNER JOIN regiao_con RC
    ON PR.id_regiao = RC.id_regiao
WHERE con = 'BRA';

-- A8.
-- ALGEBRA RELACIONAL
-- Liste o nome dos eventos do esporte Ginástica
SELECT DISTINCT EV.nome_evento
FROM evento EV
INNER JOIN esporte ES
    ON EV.id_esporte = ES.id_esporte
WHERE ES.nome_esporte = 'Ginástica';

--A9.
-- ALGEBRA RELACIONAL
-- Liste o nome completo de pessoas do gênero masculino (M) que competiram com idade entre 10 e 13 anos
SELECT DISTINCT P.nome_completo
FROM pessoa P
INNER JOIN jogos_competidor JC
    ON P.id_pessoa = JC.id_pessoa
WHERE P.genero = 'M'
        AND JC.idade >= 11
        AND JC.idade <= 13;

-- B0.
-- Liste o nome dos esportes que não são 
-- disputados em Jogos Olímpicos de Verão
SELECT DISTINCT ES.nome_esporte
FROM esporte ES
INNER JOIN evento EV
    ON ES.id_esporte = EV.id_esporte
INNER JOIN competidor_evento CE
    ON EV.id_evento = CE.id_evento
INNER JOIN jogos_competidor JC
    ON CE.id_competidor = JC.id_competidor
INNER JOIN jogos J
    ON JC.id_jogos = J.id_jogos
WHERE J.estacao <> 'Verão';


-- B1.
-- Liste o nome completo, o gênero da pessoa que obteve
-- o maior número de medalhas de ouro. 
-- Informe também o número total de medalhas de ouro 
-- para o atleta em questão
SELECT P.nome_completo, P.genero,
    COUNT(*) AS num_medalha_ouro
FROM pessoa P
INNER JOIN jogos_competidor JC
    ON P.id_pessoa = JC.id_pessoa
INNER JOIN competidor_evento CE
    ON JC.id_competidor = CE.id_competidor
INNER JOIN medalha M
    ON CE.id_medalha = M.id_medalha
WHERE nome_medalha = 'Ouro'
GROUP BY P.id_pessoa
ORDER BY num_medalha_ouro DESC
LIMIT 1;


-- B2.
-- Liste o código e nome dos cinco CONs com o maior 
-- número de atletas registrados. Informe também a quantidade 
-- total de atletas para cada CON
SELECT RC.con, RC.nome_regiao, COUNT(*) AS num_atletas
FROM regiao_con RC
INNER JOIN pessoa_regiao PR
    ON RC.id_regiao = PR.id_regiao
GROUP BY RC.id_regiao
ORDER BY num_atletas DESC
LIMIT 5;


-- B3.
-- Liste o nome das cidades que sediaram mais 
-- de uma edição de Jogos Olímpicos
-- e seus respectivos países
SELECT C.nome_cidade, C.nome_pais
FROM cidade C
INNER JOIN jogos_cidade JC
    ON C.id_cidade = JC.id_cidade
GROUP BY JC.id_cidade
HAVING COUNT(JC.id_jogos) > 1;


-- B4.
-- Liste o código e o nome dos CONs que ganharam pelo menos
-- uma medalha (i.e., Ouro, Prata ou Bronze) na história dos Jogos Olímpicos
SELECT RC.con, RC.nome_regiao
FROM regiao_con RC
INNER JOIN pessoa_regiao PR
    ON RC.id_regiao = PR.id_regiao
INNER JOIN pessoa P
    ON PR.id_pessoa = P.id_pessoa
INNER JOIN jogos_competidor JC
    ON P.id_pessoa = JC.id_pessoa
INNER JOIN competidor_evento CE
    ON JC.id_competidor = CE.id_competidor
INNER JOIN medalha M
    ON CE.id_medalha = M.id_medalha
WHERE M.nome_medalha = 'Ouro' OR M.nome_medalha = 'Prata' OR M.nome_medalha = 'Bronze'
GROUP BY RC.con, RC.nome_regiao;


-- B5.
-- Liste o nome dos países e o continente com 
-- cidades sede de Jogos Olímpicos de Inverno
SELECT DISTINCT C.nome_pais, C.nome_continente
FROM cidade C
INNER JOIN jogos_cidade JC
    ON C.id_cidade = JC.id_cidade
INNER JOIN jogos J
    ON JC.id_jogos = J.id_jogos
WHERE J.estacao = 'Inverno';


-- B6.
-- Liste o ano, a cidade e a quantidade de esportes diferentes que foram disputados
-- em cada edição dos Jogos Olímpicos de Verão. 
-- Ordene os resultados da edição mais antiga para a mais recente
SELECT J.ano_jogos, C.nome_cidade, COUNT(DISTINCT EV.id_esporte) AS num_esportes
FROM cidade C
INNER JOIN jogos_cidade JC
    ON C.id_cidade = JC.id_cidade
INNER JOIN jogos J
    ON JC.id_jogos = J.id_jogos
INNER JOIN jogos_competidor JCO
    ON J.id_jogos = JCO.id_jogos
INNER JOIN competidor_evento CE
    ON JCO.id_competidor = CE.id_competidor
INNER JOIN evento EV
    ON CE.id_evento = EV.id_evento
INNER JOIN esporte ES
    ON EV.id_esporte = ES.id_esporte
WHERE J.estacao = 'Verão'
GROUP BY J.id_jogos, C.nome_cidade
ORDER BY J.ano_jogos;


-- B7.
-- Liste o ano e a quantidade de medalhas (i.e., Ouro, Prata ou Bronze) que o Brasil
-- conquistou em edições dos Jogos Olímpicos. 
-- Ordene os resultados da edição mais antiga para a mais recente 
-- Considere a quantidade de medalhas por evento e não por atleta ou esporte
SELECT J.ano_jogos, COUNT(DISTINCT CE.id_evento) AS num_medalhas
FROM regiao_con RC
INNER JOIN pessoa_regiao PR
    ON RC.id_regiao = PR.id_regiao
INNER JOIN pessoa P
    ON PR.id_pessoa = P.id_pessoa
INNER JOIN jogos_competidor JC
    ON P.id_pessoa = JC.id_pessoa
INNER JOIN jogos J
    ON J.id_jogos = JC.id_jogos
INNER JOIN competidor_evento CE
    ON JC.id_competidor = CE.id_competidor
INNER JOIN medalha M
    ON CE.id_medalha = M.id_medalha
WHERE RC.con = 'BRA' AND (M.nome_medalha = 'Ouro' OR M.nome_medalha = 'Prata' OR M.nome_medalha = 'Bronze')
GROUP BY J.ano_jogos
ORDER BY J.ano_jogos;


-- B8.
-- Liste o ano dos Jogos Olímpicos de Inverno e a quantidade de CONs participantes.
-- Ordene os resultados da edição mais antiga para a mais recente 
SELECT J.ano_jogos, COUNT(DISTINCT PR.id_regiao) AS num_cons
FROM jogos J
INNER JOIN jogos_competidor JC
    ON J.id_jogos = JC.id_jogos
INNER JOIN pessoa P
    ON P.id_pessoa = JC.id_pessoa
INNER JOIN pessoa_regiao PR
    ON P.id_pessoa = PR.id_pessoa
INNER JOIN regiao_con RC
    ON RC.id_regiao = PR.id_regiao
WHERE J.estacao = 'Inverno'
GROUP BY J.ano_jogos
ORDER BY J.ano_jogos;


-- B9.
-- Liste o código e o nome dos CONs que nunca ganharam
-- medalhas (i.e., Ouro, Prata ou Bronze) na história dos Jogos Olímpicos
SELECT con, nome_regiao
FROM regiao_con 
WHERE con NOT IN (
    SELECT RC.con
    FROM regiao_con RC
    INNER JOIN pessoa_regiao PR
        ON RC.id_regiao = PR.id_regiao
    INNER JOIN pessoa P
        ON PR.id_pessoa = P.id_pessoa
    INNER JOIN jogos_competidor JC
        ON P.id_pessoa = JC.id_pessoa
    INNER JOIN competidor_evento CE
        ON JC.id_competidor = CE.id_competidor
    INNER JOIN medalha M
        ON CE.id_medalha = M.id_medalha
    WHERE M.nome_medalha = 'Ouro' OR M.nome_medalha = 'Prata' OR M.nome_medalha = 'Bronze'
    GROUP BY RC.nome_regiao 
)
ORDER BY nome_regiao;
