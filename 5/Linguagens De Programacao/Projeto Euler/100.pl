% Define um limite grande para o número de discos azuis
limite(1000000000000).

% Inicializa o número de discos azuis (n) e discos vermelhos (m)
inicializa_discos(4, 3).

% Regra principal para encontrar o número de discos vermelhos quando a condição é satisfeita
encontra_resultado(Resultado) :-
    limite(Limite),
    inicializa_discos(NumDiscosAzuis, NumDiscosVermelhos),
    loop(Limite, NumDiscosAzuis, NumDiscosVermelhos, Resultado).

% Loop até que o número de discos azuis exceda o limite
loop(Limite, NumDiscosAzuis, NumDiscosVermelhos, Resultado) :-
    NumDiscosAzuis =< Limite,
    novo_num_discos(NumDiscosAzuis, NumDiscosVermelhos, NovoNumDiscosAzuis, NovoNumDiscosVermelhos),
    loop(Limite, NovoNumDiscosAzuis, NovoNumDiscosVermelhos, Resultado).

% Caso base: quando o número de discos azuis excede o limite
loop(Limite, NumDiscosAzuis, NumDiscosVermelhos, NumDiscosVermelhos) :-
    NumDiscosAzuis > Limite.

% Atualiza os valores de num_discos_azuis e num_discos_vermelhos usando as fórmulas recursivas
novo_num_discos(NumDiscosAzuis, NumDiscosVermelhos, NovoNumDiscosAzuis, NovoNumDiscosVermelhos) :-
    NovoNumDiscosAzuis is 3 * NumDiscosAzuis + 4 * NumDiscosVermelhos - 3,
    NovoNumDiscosVermelhos is 2 * NumDiscosAzuis + 3 * NumDiscosVermelhos - 2.

% Predicado principal para iniciar o programa e imprimir o resultado
main :-
    encontra_resultado(Resultado),
    write(Resultado), nl.

% Iniciar o programa
:- main.