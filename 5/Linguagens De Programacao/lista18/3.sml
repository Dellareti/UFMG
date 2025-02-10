fun g x = x + 1;

fun f y = 
  let val temp = y + 2
  in g(temp) end;

