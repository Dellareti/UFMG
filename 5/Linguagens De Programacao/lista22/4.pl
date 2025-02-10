merge_sort([], []).
merge_sort([X], [X]).
merge_sort(List, Sorted) :-
    length(List, Len),
    Len > 1,
    split_list(List, Left, Right),
    merge_sort(Left, SortedLeft),
    merge_sort(Right, SortedRight),
    merge(SortedLeft, SortedRight, Sorted).

split_list(List, Left, Right) :-
    length(List, Len),
    HalfLen is Len div 2,
    length(Left, HalfLen),
    append(Left, Right, List).

merge([], Right, Right).
merge(Left, [], Left).
merge([L|Left], [R|Right], [L|Merged]) :-
    L =< R,
    merge(Left, [R|Right], Merged).
merge([L|Left], [R|Right], [R|Merged]) :-
    L > R,
    merge([L|Left], Right, Merged).
