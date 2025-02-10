<ast> ::= ... % Previous definitions
        | fun(<name>, <param>, <body>)

% New function value type for recursive functions        
evall(fun(Name, Param, Body), C, rfval(Name, Param, Body, C)).

% Modified apply for recursive functions
evall(apply(Function, Arg), C, R) :-
    evall(Function, C, rfval(Name, Param, Body, Cfn)),
    evall(Arg, C, ArgVal),
    evall(Body, [bind(Name,rfval(Name,Param,Body,Cfn)), 
                 bind(Param,ArgVal)|Cfn], R).
