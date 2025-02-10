n_queens(N, Queens) :-
    length(Queens, N),
    board_numbers(N, Board),
    queens_positions(Queens, Board),
    safe_queens(Queens).

board_numbers(N, Board) :-
    findall(X, between(1, N, X), Board).

queens_positions([], _).
queens_positions([Q|Queens], Board) :-
    select(Q, Board, RemainingBoard),
    queens_positions(Queens, RemainingBoard).

safe_queens([]).
safe_queens([Q|Queens]) :-
    safe_queen(Q, Queens, 1),
    safe_queens(Queens).

safe_queen(_, [], _).
safe_queen(Q, [Q2|Queens], Dist) :-
    abs(Q - Q2) =\= Dist,
    Dist1 is Dist + 1,
    safe_queen(Q, Queens, Dist1).
