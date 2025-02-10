.data
vetor: .word 1 2 3 4 5 6 7
.text
main:
	la x12, vetor				# Seta o primeira paramentro
	addi x13, x0, 7
	addi x13, x13, -1
	slli x13, x13, 2
	add x13, x13, x12			# Seta o segundo paramentro
	jal x1, inverte				# Chama recursivamente a função inverte 
	beq x0, x0, FIM				# Fim do programa
##### START MODIFIQUE AQUI START #####
# Inverte de fora para dentro, onde a chamada mais recursiva irá inverter os elementos do meio do vetor 
# Recebe o endereço do primeiro elemento do vetor em x12
# Recebe o endereço do último elemento do vetor em x13
inverte: 
	addi x2, x2, -4				# Cria espaço na pilha para guardar $ra (x1) para guardar seu valor
	sw x1, 0(x2)				# Salva x1 na pilha
	
	bge x12, x13, inverte_end	# Se todos os elementos foram invertidos, basta retornar
	lw x5, 0(x12)				# Se não, troque o primeiro e o último elemento
	lw x6, 0(x13)
	sw x5, 0(x13)
	sw x6, 0(x12)
	addi x12, x12, 4			# Mover um elemento para frente desde o primeiro
	addi x13, x13, -4			# Move um elemento para trás a partir do último
	jal x1, inverte				# Chama inverte recursivamente
	
inverte_end:	
	lw x1, 0(x2)				# Restaura x1 da pilha
	addi x2, x2, 4				# Libera o espaço na pilha que foi reservado para armazenar $ra (x1)
	jalr x0, 0(x1)
##### END  MODIFIQUE AQUI END #####
FIM: 
	add x1, x0, x10