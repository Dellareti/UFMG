fun prefixCopy x n =
    let
        fun copy_aux ([], _, acc) = rev acc
          | copy_aux (_, 0, acc) = rev acc
          | copy_aux (head::tail, n, acc) = 
                copy_aux(tail, n-1, head::acc)
    in
        if n = 0 then x
        else copy_aux(x, n, [])
    end
