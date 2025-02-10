evenSize([]).
evenSize([_,_|T]):- evenSize(T).

% TESTES
% evenSize([1,2,3,4]).
% true

% evenSize([1,2,3,4,5]).
% false