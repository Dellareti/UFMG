ordered([]).
ordered([_]).
ordered([X,Y|T]) :-
    X =< Y,
    ordered([Y|T]).
