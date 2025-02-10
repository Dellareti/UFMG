#include<stdio.h>
#include<stdlib.h>

int cont_id = 1;

typedef struct Guerreiro{
    int ataque;
    int defesa;
    int carisma;
    int pontos_vida;
    int id_guerreiro;
}Guerreiro;

Guerreiro *aux,*atacante,*defensor;

//2
int rolaDados(){
    
int soma=0;
int dado=0;
    
    for(int i=0;i<3;i++){
    dado= 1 + ( rand() % 6);
    soma+=dado;
      //printf("%d = %d\n",i,dado);
   }
  // printf("\nsoma = %d ",soma);
   return soma;
}

//3
void criaGuerreiro(Guerreiro *x){
    
    int vida;
    x->ataque=rolaDados();
    x->carisma=rolaDados();
    x->defesa=rolaDados();
    
    for(int i=0;i < 3;i++){
        vida += rolaDados();
    }
    x->pontos_vida = vida;
    x->id_guerreiro = cont_id;
    cont_id++;
}

int bonusCarisma(int carisma){
    int bonus; 
    
    switch (carisma){
        case 18:
            bonus=3;
            break;
        case 17:
        case 16:
            bonus=2;
            break;
        case 15:
        case 14:
            bonus=1;
            break;
        case 7:
        case 6:
            bonus=-1;
            break;
        case 5:
        case 4:
            bonus=-2;
            break;
        case 3:
            bonus=-3;
            break;
        default:
            bonus=0;
            break;
    }
    
    return bonus;
}

void ataca(Guerreiro *a,Guerreiro *b){
    
    int dano,golpe,escudo;
    golpe = rolaDados() + a->ataque + bonusCarisma(a->carisma);
    escudo = rolaDados() + b->defesa + bonusCarisma(b->carisma);
    
    dano= golpe - escudo;
    
    if(dano>0){
        b->pontos_vida-=dano;
    }
}

void jogo(){
   
    while(1){
    ataca(atacante,defensor);
    if(defensor->pontos_vida <=0){
        break;
    }
    aux = atacante;
    atacante = defensor;
    defensor = aux;
    }
     printf("Vencedor: %d\n",atacante->id_guerreiro);
     printf("Pontos de vida restantes: %d\n",atacante->pontos_vida);
}