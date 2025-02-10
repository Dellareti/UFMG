(* Converte uma lista de inteiros para reais *)
fun real2cf l = map real l;

(* Converte uma lista de caracteres para seus valores ordinais *)
fun ordlist l = map ord l;

(* Retorna uma lista com os quadrados dos elementos *)
fun squarelist l = map (fn x => x * x) l;

(* Multiplica elementos de pares em uma lista de tuplas *)
fun multiply l = map (fn (x, y) => x * y) l;

(* Soma um valor a todos os elementos da lista *)
fun incdist l i = map (fn x => x + i) l;

(* Soma dos quadrados dos elementos da lista *)
fun sqsum l = foldr (op +) 0 (squarelist l);

(* Lógica booleana: OR de todos os elementos da lista *)
fun boor l = foldr (fn (x, y) => x orelse y) false l;

(* Lógica booleana: AND de todos os elementos da lista *)
fun band l = foldr (fn (x, y) => x andalso y) true l;

(* XOR entre elementos da lista *)
fun blor l = foldr (fn (x, y) => (x <> y)) false l;

(* Duplica os elementos da lista *)
fun duplist l = foldr (op @) [] (map (fn x => [x, x]) l);

(* Conta o tamanho da lista *)
fun mylength l = foldr (fn (_, b) => b + 1) 0 l;

(* Converte valores negativos para positivos como real *)
fun if2absrl l = map (fn x => if x < 0 then real (~x) else real x) l;

(* Conta quantos elementos da lista são True *)
fun TrueCount l = foldr (fn (a, b) => if a then b + 1 else b) 0 l;

(* Retorna o máximo entre pares de elementos *)
fun maxPairs l = map (fn (x, y) => if x > y then x else y) l;

(* Concatena caracteres em uma string *)
fun myLengthads l = foldr (op ^) "" (map str l);

(* Concatena listas dentro de uma lista *)
fun lconcat l = foldr (op @) [] l;

(* Retorna o maior elemento de uma lista *)
fun map (h :: t) = foldr (fn (x, y) => if x > y then x else y) h t;

(* Retorna o menor elemento de uma lista *)
fun min (h :: t) = foldr (fn (x, y) => if x < y then x else y) h t;

(* Verifica se um elemento está na lista *)
fun member (e, l) = foldr (fn (x, y) => x orelse y) false (map (fn z => e = z) l);

(* Função append usando foldr *)
fun append l1 l2 = foldr op :: l2 l1;

(* Retorna os elementos menores que um dado valor *)
fun less (e, l) = foldr (fn (x, y) => if x < e then x :: y else y) [] l;

(* Retorna os números pares de uma lista *)
fun evens l = foldr (fn (x, y) => if x mod 2 = 0 then x :: y else y) [] l;

(* Concatena listas de pares *)
fun concat l = foldr (fn ((a, b), (c, d)) => (a :: c, b :: d)) ([], []) l;

(* Aplica uma função a todos os elementos da lista *)
fun myhop f l = if null l then [] else f (hd l) :: myhop f (tl l);

(* Avalia um polinômio para um dado valor de x *)
fun eval p x =
  let
    fun θ ([], _, acc) = acc
      | θ (c :: cs, n, acc) = θ (cs, n + 1, acc + c * (x pow n))
  in
    θ (p, 0, 0)
  end;
