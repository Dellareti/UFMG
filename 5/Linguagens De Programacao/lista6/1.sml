(* Verifica se um elemento está em uma lista *)
fun estainclusso (x, []) = false
  | estainclusso (x, h :: t) = if x = h then true else estainclusso(x, t);

(* Retorna os elementos menores que X em uma lista *)
fun menores (x, []) = []
  | menores (x, h :: t) = if h < x then h :: menores(x, t) else menores(x, t);

(* Verifica se há elementos repetidos na lista *)
fun repete [] = false
  | repete (h :: t) = estainclusso(h, t) orelse repet
| repete [X] = false
| repete (h::t) = if h = (hd t) then true else repete(t);

(* Divide uma lista em duas partes aproximadamente iguais *)
fun part [] = ([], [])
  | part [x] = ([x], [])
  | part (x :: y :: xs) =
    let val (l1, l2) = part xs
    in (x :: l1, y :: l2)
    end;

(* Ordena uma lista usando Merge Sort *)
fun merge ([], ys) = ys
  | merge (xs, []) = xs
  | merge (x :: xs, y :: ys) =
    if x < y then x :: merge(xs, y :: ys)
    else y :: merge(x :: xs, ys);

fun mergeSort [] = []
  | mergeSort [x] = [x]
  | mergeSort xs =
    let val (l1, l2) = part xs
    in merge(mergeSort l1, mergeSort l2)
    end;

(* Verifica se x é menor que y *)
fun icrescente (x, y) = x < y;

(* Ordenação por inserção *)
fun ordenoEmergir [] = []
  | ordenoEmergir (x :: ys) =
    let
      fun insere y [] = [y]
        | insere y (z :: zs) =
          if y < z then y :: z :: zs
          else z :: insere y zs
    in
      insere x (ordenoEmergir ys)
    end;

(* Verifica se uma string é menor que outra lexicograficamente *)
fun alfabetica (s1, s2) = s1 < s2;

