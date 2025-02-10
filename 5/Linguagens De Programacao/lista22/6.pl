subset_sum(L, Sum, SubL) :-
    subset_sum_helper(L, Sum, [], SubL).

subset_sum_helper(_, 0, Acc, Acc).
subset_sum_helper([H|T], Sum, Acc, SubL) :-
    NewSum is Sum - H,
    NewSum >= 0,
    subset_sum_helper(T, NewSum, [H|Acc], SubL).
subset_sum_helper([_|T], Sum, Acc, SubL) :-
    subset_sum_helper(T, Sum, Acc, SubL).
