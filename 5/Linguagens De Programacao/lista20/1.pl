% Adiciona descrição do portão
description(gate, 'You are at a heavy iron gate blocking the path to the mountain peak.').

% Conexões do novo local
connect(fork, forward, gate).
connect(gate, forward, mountaintop).

% Estado do portão e chave
:- dynamic gate_locked/0.
:- dynamic has_key/0.
assert(gate_locked).
assert(at(key, maze(2))).

% Comandos para pegar e soltar a chave
take :- 
    at(you, Loc),
    at(key, Loc),
    retract(at(key, Loc)),
    assert(has_key),
    write('You pick up a rusty key.\n'),
    !.

drop :-
    has_key,
    at(you, Loc),
    retract(has_key),
    assert(at(key, Loc)),
    write('You drop the key.\n'),
    !.

% Comando para usar a chave no portão
unlock :-
    at(you, gate),
    has_key,
    gate_locked,
    retract(gate_locked),
    write('You unlock the gate with the key.\n'),
    !.

% Verifica condições especiais do portão
move(forward) :-
    at(you, gate),
    gate_locked,
    write('The gate is locked.\n'),
    !.

move(forward) :-
    at(you, gate),
    has_key,
    write('As you try to pass through with the key, a lightning bolt strikes you dead!\n'),
    retract(at(you, gate)),
    assert(at(you, done)),
    !.
