male(kent).
male(herbert).
male(jean).
% Adicionado para testes
male(bob).
male(mark).

female(kim).
female(holly).
female(margaret).
female(esther).

parent(kim,holly).
parent(margaret,kim).
parent(margaret,kent).
parent(esther,margaret).
parent(herbert,margaret).
parent(herbert,jean).
% Adicionado para testes
parent(holly,bob).
parent(jean,mark).

% A
mother(X,Y):- female(X), parent(X,Y).

% B
father(X,Y):- male(X), parent(X,Y).

% C
sister(X,Y):- female(X),mother(A,X), father(B,X), mother(A,Y),father(B,Y), not(X = Y).

% D
grandson(X,Y):- male(X),parent(Z,X),parent(Y,Z).

% E
% broter = Brother or sister
broter(X,Y):- mother(A,X), father(B,X), mother(A,Y),father(B,Y).
firstCousin(X,Y):- broter(A,B), parent(A,X), parent(B,Y), not(X = Y), not(broter(X,Y)).
    
% F
descendant(X,Y):- parent(Y,X).
descendant(X,Y):- parent(Z,X),descendant(Z,Y).
