-- 2021039581
-- A0
SELECT nome_completo 
  FROM pessoa 
  INNER JOIN jogos_competidor jog ON pessoa.id_pessoa = jog.id_pessoa
  WHERE idade >= 80 
  ORDER BY nome_completo;
-- A1
SELECT nome_completo FROM pessoa AS p
   INNER JOIN
   pessoa_regiao AS pr
   ON p.id_pessoa = pr.id_pessoa
   INNER JOIN
   regiao_con AS rc
   ON pr.id_regiao = rc.id_regiao 
   WHERE nome_regiao = "Equipe olímpica de refugiados";
-- A2
SELECT ano_jogos,estacao FROM jogos AS j
   INNER JOIN jogos_cidade AS jc
   ON j.id_jogos = jc.id_jogos
   INNER JOIN
   cidade AS c
   ON c.id_cidade = jc.id_cidade 
   WHERE nome_cidade = "Londres";
-- A3
SELECT nome_completo,altura FROM pessoa AS p
   INNER JOIN
   jogos_competidor AS jc
   ON p.id_pessoa = jc.id_pessoa
   INNER JOIN
   jogos AS j
   ON jc.id_jogos =j.id_jogos
   WHERE altura >= "215" AND ano_jogos="2016";
-- A4
SELECT nome_completo,altura 
  FROM pessoa
  WHERE genero="F" AND altura >=200;
-- B1
SELECT nome_completo,genero,
COUNT (medalha.id_medalha) AS medalhas_ouro
FROM esporte 
  INNER JOIN evento ON evento.id_esporte = esporte.id_esporte
  INNER JOIN competidor_evento ON evento.id_evento = competidor_evento.id_evento
  INNER JOIN jogos_competidor ON jogos_competidor.id_competidor = competidor_evento.id_competidor
  INNER JOIN jogos ON jogos.id_jogos = jogos_competidor.id_jogos
  INNER JOIN pessoa ON pessoa.id_pessoa = jogos_competidor.id_pessoa
  INNER JOIN medalha ON competidor_evento.id_medalha = medalha.id_medalha

WHERE nome_medalha = "Ouro" GROUP BY nome_completo ORDER BY medalhas_ouro DESC LIMIT 1;
-- B3
SELECT nome_cidade,nome_pais FROM cidade AS c
  INNER JOIN jogos_cidade as jc
  ON jc.id_cidade = c.id_cidade

  INNER JOIN jogos AS j
  ON j.id_jogos = jc.id_jogos
  
  GROUP BY nome_cidade
  Having COUNT(c.id_cidade) > 1;
-- B5
SELECT DISTINCT nome_pais, nome_continente FROM cidade
   INNER JOIN 
   (jogos_cidade INNER JOIN jogos ON jogos_cidade.id_jogos=jogos.id_jogos) 
   ON cidade.id_cidade=jogos_cidade.id_cidade 
   WHERE estacao = 'Inverno';
-- B8
SELECT ano_jogos,COUNT(DISTINCT rc.id_regiao) FROM jogos As j
  INNER JOIN jogos_competidor as jc
  ON jc.id_jogos = j.id_jogos
  
  INNER JOIN pessoa AS p
  ON p.id_pessoa = jc.id_pessoa

  INNER JOIN pessoa_regiao AS pr
  ON pr.id_pessoa = p.id_pessoa

  INNER JOIN regiao_con AS rc
    ON rc.id_regiao = pr.id_regiao

  WHERE estacao = "Inverno"
  GROUP BY ano_jogos
  ORDER BY ano_jogos;
-- B9
SELECT 
    con,
    nome_regiao
  FROM 
    regiao_con
  EXCEPT 
   SELECT 
    con,
    nome_regiao
  FROM 
    medalha m
    join competidor_evento ce on m.id_medalha = ce.id_medalha
    join jogos_competidor jc on jc.id_competidor = ce.id_competidor
    join jogos j on j.id_jogos = jc.id_jogos 
    join pessoa p on p.id_pessoa = jc.id_pessoa
    join pessoa_regiao pr on pr.id_pessoa = p.id_pessoa
    join regiao_con rc on rc.id_regiao = pr.id_regiao
    WHERE 
      nome_medalha <> "NA";