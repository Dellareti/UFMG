<ast> ::= plus(<ast>, <ast>)
        | minus(<ast>, <ast>) 
        | times(<ast>, <ast>)
        | const(<const>)
        | let(<var>, <ast>, <ast>)
        | var(<name>, <const>)
        | fn(<param>, <body>)
        | apply(<fn>, <args>)
        | equals(<ast>, <ast>)
        | if(<condition>, <then>, <else>)

% Evaluation rules for new constructs
evall(minus(X,Y), C, R) :-
    evall(X, C, RX),
    evall(Y, C, RY), 
    R is RX - RY.

evall(equals(X,Y), C, R) :-
    evall(X, C, RX),
    evall(Y, C, RY),
    (RX = RY -> R = 1 ; R = 0).
    
evall(if(Cond,Then,Else), C, R) :-
    evall(Cond, C, RC),
    (RC = 1 -> evall(Then, C, R) ; evall(Else, C, R)).
