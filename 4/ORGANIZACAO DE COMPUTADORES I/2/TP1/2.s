.data
cartao: .word 4 9 1 6 6 4 1 8 5 9 3 6 9 0 8 0 # Valido
##### START MODIFIQUE AQUI START #####
#
# Este espaço eh para você definir as suas constantes e vetores auxiliares.
##### END MODIFIQUE AQUI END #####
.text
main:
    la a0, cartao
    jal ra, verifica
    beq zero, zero, FIM
##### START MODIFIQUE AQUI START #####
verifica: 
    addi sp, sp, -8        
    sw ra, 0(sp)                # Salvar endereço de retorno
    sw a0, 4(sp)                # Salve o parâmetro
    la a0, cartao
    jal ra, multvetores
    addi t0, zero, 10           # t0 = 10
    rem t1, a0, t0              # Divide o resultado por 10 para obter o resto da divisão
    sub t1, t0, t1              # Subtrai o resto da divisão por 10
    rem t1, t1, t0              # Divide o resultado por 10 para obter o resto da divisão
    lw ra, 0(sp)                # Restaura o endereço de retorno
    lw a0, 4(sp)                # Restaura o parâmetro
    addi sp, sp, 8
    lw t2, 60(a0)               # Pega o último dígito
    addi a0, zero, 0            # Seta o valor de retorno como 0
    bne t2, t1, nao_valido
    addi a0, zero, 1            # Return 1
nao_valido:    
    jalr x0, x1, 0              # Return
    
multvetores: 
    addi t0, zero, 0            # t0 vai armazenar a soma
    addi t1, zero, 2            # t1 = 2
    addi t2, zero, 15           # Loop counter
    addi a2, zero, 10           # a2 = 10
    addi a3, zero, 2            # a3 = 2
multvetores_loop: 
    lw a1, 0(a0)                # Pega o digito
    mul a1, a1, t1              # Multiplique por 1 ou 2
    blt a1, a2, digito_unico    # Verifica se o resultado da multiplicação
    rem a1, a1, a2              # Se tiver dois dígitos, encontre o dígito da unidade
    addi a1, a1, 1              # Adiciona os dois dígitos juntos
digito_unico: 
    add t0, t0, a1              # Acumula a soma
    beq t1, a3, multiplier_1
    addi t1, zero, 2            # t1 = 2
    j proximo_digito
multiplier_1: 
    addi t1, zero, 1            # t1 = 1
proximo_digito:    
    addi a0, a0, 4                   # Passar para o próximo dígito
    addi t2, t2, -1                  # Decrementa o contador do loop
    bne t2, zero, multvetores_loop 
    add a0, zero, t0                 # Define o valor de retorno
    jalr x0, x1, 0                   # Return
##### END MODIFIQUE AQUI END #####
FIM: 
    add zero, zero, zero