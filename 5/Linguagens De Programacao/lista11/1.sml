(* datatype tree = INT of int | LIST of tree list | Empty | Node of tree * int list * tree *)

(* Soma todos os elementos de uma estrutura de lista *)
fun addUp (LIST []) = 0
  | addUp (INT x) = x
  | addUp (LIST (h :: t)) =
      case h of 
        INT h => h + addUp (LIST t)
      | LIST h => addUp (LIST h) + addUp (LIST t);

(* Produto dos elementos de uma lista *)
fun prod [] = 1
  | prod (h :: t) = h * prod t;

(* Inverte uma lista *)
fun reverse [] = []
  | reverse (h :: t) = reverse t @ [h];

(* Concatena duas listas *)
fun append [] b = b
  | append (h :: t) b = h :: append t b;

(* Concatena todas as subárvores de um nó *)
fun appendall Empty = []
  | appendall (Node (x, y, z)) = appendall x @ y @ appendall z;

(* Verifica se uma árvore binária é completa *)
fun complete (Node (Empty, _, Empty)) = true
  | complete (Node (Empty, _, _)) = false
  | complete (Node (_, _, Empty)) = false
  | complete (Node (x, _, z)) = complete x andalso complete z;
