
#include <stdio.h>

int contaDigitos(int numero){
    int cont=1;
    if(numero>=10){
        numero=numero/10;
        cont=cont+contaDigitos(numero);
    }
    return cont;
}

int decimalParaBinario(int decimal){
  return 0;
}

// 1
int cadastraUsuario(int *chave,int *senha){
   int contador =0;
   int chaveUser;
   int senhaUser;
   
   chave = &chaveUser;
   senha = &senhaUser;
   
   int qntSenha;
   int qntChave;
   
   
    do{
    //printf("Digite sua chave de cadastro de 4 a 6 digitos\n");
    scanf("%d",&chaveUser);
    
  //  printf("Digite sua senha para cadastro de 4 a 6 digitos\n");
    scanf("%d",&senhaUser);
   
    // printf("A chave e : %d \n",*chave);
    // printf("A senha e : %d \n",*senha);
         
    qntChave = contaDigitos(chaveUser);
    qntSenha = contaDigitos(senhaUser);
    if(qntSenha < 2000){
        
    }
    else if (qntSenha < 999999){
        
    }
    
    }while((qntChave < 4 || qntChave > 6) || (qntSenha < 4 || qntSenha > 6));
    
  return contador;
}

// 2
int verificaSenha(int tentativa,int senha){
    if(tentativa==senha){
        return 1;
    }
    else{
        return 0;
    }
}

//3
int acessoConta(int senha,int n){
    // 1 a digitar é a senha e depois a tolerancia
    
    int contador = 0;
    int senhaReal = 4321;
    int aux = verificaSenha(senha,senhaReal);
   
    do{
      if(aux==0){
          contador = n;
          return 0;
      }
     contador = contador+1;
    
  } while(contador < n);
  
  if(aux==1){
     // printf("Login efetuado \n");
      return 1;
  }
  else{
     // printf("Quantidade de tentativas ultrapassada! ");
      return 0;
  }
   
}

// 4
char cartaoCredito(int score){
    
    if(score <= 400){
        printf("Cartao negado \n");
        return 'N';
    }
    else if(score > 401 && score < 600){
        printf("Necessita de mais detalhes \n");
        return 'X';
    }
    else if(score > 601 && score< 800){
        printf("Cartao Basico \n");
        return 'B';
    }
    else if (score > 801 && score <=1000){
        printf("Cartao gold \n");
        return 'A';
    }
    
    else{
        printf("Score invalido \n");
        return 'X';
    }
}

// 5 
void banco(void){
     int chave,senha;
    // int *pchave;
    // int *psenha;
    // pchave = chave;
    // psenha = senha;
    
    //printf("Digite sua chave : \n");
    scanf("%d",&chave);
    
   // printf("Digite sua senha : \n");
    scanf("%d",&senha);
    
    float score;
   // cadastraUsuario(chave,senha);
    acessoConta(4321,3);
    score= 1234 % 1000;
    
    cartaoCredito(score);
    
}

// 7 
int codigoVerificador(int chave){
    decimalParaBinario(chave);
    return 0;
}