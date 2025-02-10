oddSize([_]).
oddSize([_,_|T]):- oddSize(T).

% TESTES
% oddSize([1,2,3,4]).
% false

% oddSize([1,2,3,4,5]).
% true