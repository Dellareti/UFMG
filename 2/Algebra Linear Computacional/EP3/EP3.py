import numpy as np

nome = "Ítalo Dell Areti"
matricula =2021039581 

def EP_answers(A, B):
    import numpy as np
    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    np.random.seed(1)
    U, Sigma, Sigma_vet, Vt, imgReconst_3, log_Sigma, cumul_Sigma, rmseReconst_3 = [None]*8
    imgReconst_10, rmseReconst_10, imgReconst_100 = [None]*3
    rmseReconst_100, imgReconst_500, rmseReconst_500 = [None]*3
    uso_k_10, uso_k_100, uso_k_500, lim_energ = [None]*4
    B_media, Bm, S, w2, V2, valores_sing, Sigma_vals_sing, Sigma_inv, U2_10, imgs2_10 = [None]*10
    #########################################################################

    ### PARTE 1
    
     ## 1.1
    ## Insira seu código aqui
    
    ## NÃO EDITAR ESSA CÉLULA
    
    U, Sigma_vet, Vt = np.linalg.svd(A)
    
    ## 1.2
    ## Insira seu código aqui
    
    Sigma = np.diag(Sigma_vet)

    print("U:",U.shape)
    print("-Sigma:",Sigma.shape)
    print("Vt:",Vt.shape)
    
    ## 1.3
    ## Insira seu código aqui
    
    def reconstrucao_aproximada(U, Sigma,Vt,k):
        return U[:, :k] @ Sigma[:k, :k] @ Vt[:k, :]
    
    imgReconst_3 = reconstrucao_aproximada(U,Sigma,Vt,k=3)
    
    ## 1.4
    ## Insira seu código aqui
    
    log_Sigma = np.log(Sigma_vet)
    cumul_Sigma = np.cumsum(Sigma_vet)
    
    ## 1.5
    ## Insira seu código aqui
    
    def calcula_RMSE(img_original, img_rec):
        return np.sqrt((np.power ((img_original - img_rec), 2)).mean())

    rmseReconst_3 = calcula_RMSE(A,imgReconst_3)

    ## 1.6
    ## Insira seu código aqui
    
    imgReconst_10 = reconstrucao_aproximada(U,Sigma,Vt, k=10)
    rmseReconst_10 = calcula_RMSE(imgReconst_10,A)

    imgReconst_100 = reconstrucao_aproximada(U,Sigma,Vt, k=100)
    rmseReconst_100 = calcula_RMSE(imgReconst_100,A)

    imgReconst_500 = reconstrucao_aproximada(U,Sigma,Vt, k=500)
    rmseReconst_500 = calcula_RMSE(imgReconst_500,A)
    
    ## 1.7
    ## Insira seu código aqui
    
    def calcula_qtd_elementos(U,Sigma_vet,Vt,k):
        return U[:, :k].size + Sigma_vet[:k].size + Vt[:k, :].size

    uso_k_10 = calcula_qtd_elementos(U,Sigma_vet,Vt,k=10)
    uso_k_100 = calcula_qtd_elementos(U,Sigma_vet,Vt,k=100)
    uso_k_500 = calcula_qtd_elementos(U,Sigma_vet,Vt,k=500)
   
    ## 1.8
    ## Insira seu código aqui
    
    def get_limite(energia,cumul_Sigma):
        limit =1
        tam=cumul_Sigma.size
    
        for limit in range (tam-1):
            if(cumul_Sigma[limit] / cumul_Sigma[tam-1] >= energia):
                return limit

    lim_energ = get_limite(0.8, cumul_Sigma)
    

    ### PARTE 2
    ## Insira seu código aqui

    ## 2.1
    ## Insira seu código aqui
    B_media = np.mean(B, axis=0)

    Bm = B.astype('float64')
    
    for i in range(B.shape[1]):
        Bm[:, i] -= B_media[i]

    
    ## 2.2
    ## Insira seu código aqui
    
    S = Bm.T @ Bm
    print(S.shape)
    
    
    ## 2.3
    ## Insira seu código aqui
    
    
    w2, V = np.linalg.eig(S)
    #V = np.linalg.eig(S)
    indices = np.argsort(w2)
    indices = np.flip(indices, axis = -1)
    
    w2 = np.sort(w2)
    w2 = np.flip(w2, axis = -1)
    
    i = 0
    V2 = np.zeros(V.shape)
    for numero in indices:
        V2[:,i] = V[:,numero].copy()
        i += 1



    ## 2.4
    ## Insira seu código aqui
    
    valores_sing = np.sqrt(w2)

    ## 2.5
    ## Insira seu código aqui
    
        
    Sigma_vals_sing = np.diag(valores_sing)
    Sigma_inv = np.linalg.inv(Sigma_vals_sing)
    print(Sigma_vals_sing.shape,Sigma_inv.shape)

    ## 2.6
    ## Insira seu código aqui
    
    # U2_10 = Bm[:10] @ V2 @ Sigma_inv

    # posto_k_q27 = 200
    # imgs2_10 = reconstrucao_aproximada(U2_10,Sigma_vals_sing,V2.T,k=posto_k_27)

    # print(imgs2_10.shape)

    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    answers = {
        "1.1.1" : U,
        "1.1.2" : Sigma_vet,
        "1.1.3" : Vt,
        "1.2" : Sigma,
        "1.3" : imgReconst_3,
        "1.4.1" : log_Sigma,
        "1.4.2" : cumul_Sigma,
        "1.5" : rmseReconst_3,
        "1.6.1" : imgReconst_10,
        "1.6.2" : rmseReconst_10,
        "1.6.3" : imgReconst_100,
        "1.6.4" : rmseReconst_100,
        "1.6.5" : imgReconst_500,
        "1.6.6" : rmseReconst_500,
        "1.7.1" : uso_k_10,
        "1.7.2" : uso_k_100,
        "1.7.3" : uso_k_500,
        "1.8" : lim_energ,
        "2.1.1" : B_media,
        "2.1.2" : Bm,
        "2.2" : S,
        "2.3.1" : w2,
        "2.3.2" : V2,
        "2.4" : valores_sing,
        "2.5.1" : Sigma_vals_sing,
        "2.5.2" : Sigma_inv,
        "2.6.1" :  U2_10,
        "2.6.2" : imgs2_10
    }
    return answers
    ##########################################################################

