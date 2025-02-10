.data
vetor: .word 0 0 0 0
##### START MODIFIQUE AQUI START #####
#
# Este espaço eh para você definir as suas constantes e vetores auxiliares.
##### END MODIFIQUE AQUI END #####
.text
main:
    add s0, zero, zero
#Teste 1
    addi a0, zero, 5
    addi a1, zero, 7
    la a2, vetor
    jal ra, primos
    addi t0, zero, 2
    beq t0, a0, OK1
    beq zero, zero, T2
OK1: 
    addi s0, s0, 1 #Teste ok, passou
#Teste 2
T2: 
    addi a0, zero, 1
    addi a1, zero, 6
    la a2, vetor
    jal ra, primos
    addi t0, zero, 3
    beq t0, a0, OK2
    beq zero, zero, FIM
OK2: 
    addi s0, s0, 1 #Teste ok, passou
    beq zero, zero, FIM
##### START MODIFIQUE AQUI START #####
# Implementa o seguinte código C
#bool isPrime(int n){
#    if (n <= 1)
#        return false;
#    for (int i = 2; i*i <= n; i++)
#        if (n % i == 0)
#            return false;
#    return true;
#}
primos:
    addi t0, zero, 0            # t0 armazenará a contagem dos números primos
    addi t1, zero, 1            # t1 = 1
verifica_cada_numero:    
    bgt a0, a1, verifica_fim    # Verifica se todos os números dentro do intervalo de entrada foram testados
verifica_primo: 
    ble a0, t1, nao_primo     # if (n <= 1), n não é primo
    addi t2, zero, 2            # i = 2
for_loop:
    mul a3, t2, t2              # Encontra i*i
    bgt a3, a0, eh_primo       # Verifica if i*i <= n, se não termina o loop
    rem a4, a0, t2              # Encontra n % i
    beq a4, zero, nao_primo   # if (n % i == 0), n não é primo
    addi t2, t2, 1              # i++
    j for_loop
eh_primo:    
    addi t0, t0, 1              # Incrementa o contador de números primos
    sw a0, 0(a2)                # Salva o número no array
    addi a2, a2, 4              # Move para a próxima posição no array
nao_primo:
    addi a0, a0, 1              # Verifica o próximo número
    j verifica_cada_numero      
verifica_fim:
    add a0, zero, t0            # Define o valor de retorno   
    jalr x0, x1, 0
##### END MODIFIQUE AQUI END #####
FIM: 
    add zero, zero, zero
#Final da execucao, s0 deve ter o valor igual a 2.