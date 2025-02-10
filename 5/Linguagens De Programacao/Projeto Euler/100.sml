fun calculateAns () =
    let
        (* Definindo o limite como um número grande usando IntInf.int *)
        val limite = 1000000000000 : IntInf.int;
        
        (* Definindo os valores iniciais de n e m como inteiros grandes *)
        val mutable_n = 4 : IntInf.int;
        val mutable_m = 3 : IntInf.int;
        
        (* Função recursiva que faz o loop até que n ultrapasse o limite *)
        fun loop (n, m) =
            if n <= limite then
                let
                    (* Calcula o próximo valor de n e m com base nas fórmulas dadas *)
                    val next_n = (3 * n) + (4 * m) - 3;
                    val next_m = (2 * n) + (3 * m) - 2;
                in
                    (* Chama recursivamente a função loop com os novos valores de n e m *)
                    loop (next_n, next_m)
                end
            else
                (* Retorna o valor de m quando n ultrapassa o limite *)
                m
    in
        (* Inicia o loop com os valores iniciais de n e m *)
        loop (mutable_n, mutable_m)
    end;

(* Calcula o resultado chamando a função calculateAns *)
val resultado = calculateAns ();
val () = print (IntInf.toString resultado ^ "\n");
