
(* Função que retorna uma função que usa uma referência *)
fun f x =
    let 
        val r = ref x
        fun g y = !r + y
    in 
        g 
    end;

(* Função que retorna uma função que soma x a um argumento y *)
fun f x =
    let 
        fun g y = x + y
    in 
        g 
    end;

fun f x = 
    let 
        val y = x  
    in 
        fn z => y 
    end;
