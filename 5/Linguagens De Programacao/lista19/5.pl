dupList([],[]).  
dupList([A|T], NovaLista):- 
    dupList(T, ResultadoRecursivo),
    append([A,A], ResultadoRecursivo, NovaLista).

% TESTES
% dupList([1,2,3],[1,1,2,2,3,3]).
% true

% dupList([1,2,3],[1,1,2,2,3,4]).
% false