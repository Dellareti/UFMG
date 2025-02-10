(* Calcula o cubo de um número inteiro *)
fun cuboX (x: int) = x * x * x;

(* Calcula o cubo de um número real *)
fun cuboR (x: real) = x * x * x;

(* Retorna o quarto elemento de uma lista *)
fun quarto (_ :: _ :: _ :: h4 :: _) = h4
  | quarto _ = raise Fail "Lista com menos de 4 elementos";

(* Retorna o menor dentre três números inteiros *)
fun min3 (x: int, y: int, z: int) =
    if x < y andalso x < z then x
    else if y < x andalso y < z then y
    else z;

(* Retorna o terceiro caractere de uma string *)
fun terceiro (str: string) =
    if size str < 3 then raise Fail "String muito curta"
    else String.sub (str, 2);

(* Rotaciona a lista uma posição para a esquerda *)
fun ciclo1 [] = []
  | ciclo1 (h :: t) = t @ [h];

(* Ordena três números reais em ordem crescente *)
fun ordena3 (xs: real list) =
    case xs of
        [x, y, z] =>
            if x < y andalso x < z then
                if y < z then [x, y, z] else [x, z, y]
            else if y < x andalso y < z then
                if x < z then [y, x, z] else [y, z, x]
            else
                if x < y then [z, x, y] else [z, y, x]
      | _ => raise Fail "A lista deve conter exatamente 3 elementos";

(* Soma dos quadrados de 1 até n *)
fun sqsum 0 = 0
  | sqsum n = n * n + sqsum (n - 1);

(* Rotaciona a lista 'm' vezes para a esquerda *)
fun ciclo (l, 0) = l
  | ciclo ([], _) = []
  | ciclo (l, m) = ciclo (tl l @ [hd l], m - 1);

(* Verifica se um número é divisível por algum número até sua raiz quadrada *)
fun dividir (x, y) =
    if y * y > x then true
    else if x mod y = 0 then false
    else dividir (x, y + 1);

(* Verifica se um número é primo *)
fun ePrimo n =
    if n < 2 then false
    else dividir (n, 2);
