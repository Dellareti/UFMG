puzzle(_, [], []).
puzzle(E, [_|Tail], [E|TailResult]) :-
    puzzle(E, Tail, TailResult).
