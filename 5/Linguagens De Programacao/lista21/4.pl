fun dividir xs =
    let 
        fun div_aux ([], esq, dir) = (rev esq, rev dir)
          | div_aux ([x], esq, dir) = (rev (x::esq), rev dir)
          | div_aux (h1::h2::t, esq, dir) = 
                div_aux(t, h1::esq, h2::dir)
    in
        div_aux(xs, [], [])
    end
