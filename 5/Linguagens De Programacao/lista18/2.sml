fun contador() = 
  let val x = ref 0
  in x := !x + 1; !x end;

fun teste(a) = a + a;

val resultado = teste(contador());
