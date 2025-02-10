.data
vetor: .word 7 8 4 1 7 7 6 1 0 0 0 1 3 0
##### START MODIFIQUE AQUI START #####
##### END MODIFIQUE AQUI END #####
.text
main:
	la x12, vetor					# Defina o primeiro parâmetro, ou seja, o endereço do vetor
	addi x13, x0, 14				# Defina o segundo parâmetro, ou seja, o tamanho do vetor (11 para cpf e 14 para cnpf)
	addi x14, x0, 1					# Defina o terceiro parâmetro. 0 para CPF e 1 para CNPJ
	jal x1, verificadastro			# Verifica CPF ou CPFJ
	beq x0,x0,FIM					# Fim do programa
##### START MODIFIQUE AQUI START #####
# Recebe o endereço do vetor CPF em x12
# Recebe o tamanho do vetor em x13
# Retorna o valor em x10. 1 se CPF for válido e 0 se for inválido
verificacpf:
	addi x5, x0, 11
	bne x13, x5, verificacpf_invalid# Verifique se o tamanho do vetor é 11. Caso contrário, retorne invalido
	add x15, x0, x12				# Salva o endereço do vetor
	addi x5, x0, 0					# soma = 0
	addi x6, x0, 10					# fator = 10
	addi x28, x0, 9					# Defina o contador de loop para ser igual a 9
verificacpf_forloop1:				# Loop para multiplicar cada dígito por seu fator e somar todos
	lw x7, 0(x12)					# Obtem o dígito
	mul x7, x7, x6					# Multiplique pelo seu fator
	add x5, x5, x7					# Acumule
	addi x12, x12, 4				# Move para o próximo digito 
	addi x6, x6, -1					# Diminua o fator
	addi x28, x28, -1				# Diminui o contador de loops
	bgt x28, x0, verificacpf_forloop1	# Repete para todos os dígitos
	addi x6, x0, 0					# Defina o restante como 0 por padrão
	addi x7, x0, 11					# Seta o divisor para 11
	rem x5, x5, x7					# Encontrar soma módulo 11
	sub x5, x7, x5					# Subtraia de 11
	addi x7, x7, -1					# x7 = 10
	beq x7, x5, verificacpf_skipnxt	# Verifique se o resultado do módulo é 10
	add x6, x0, x5					# Se não, define o restante para o resultado do módulo
verificacpf_skipnxt:
	addi x7, x0, 9					# x7 = 9 
	slli x7, x7, 2					# x7 = 9*4 
	add x7, x7, x15					# x7 agora tem o endereço do 10º dígito
	lw x5, 0(x7)					# x5 tem o 10º dígito
	bne x5, x6, verificacpf_invalid # Se sobra não for igual ao 10º dígito, retorna inválido
	addi x5, x0, 0					# soma = 0
	addi x6, x0, 11					# fator = 11	
	add x12, x15, x0				# x12 tem o endereço do vetor
	addi x28, x0, 10				# Seta o contador de loop para ser igual a 10
verificacpf_forloop2:				# Loop para multiplicar cada dígito por seu fator e somar todos
	lw x7, 0(x12)					# Pega o dígito
	mul x7, x7, x6					# Multiplica pelo seu fator
	add x5, x5, x7					# Acumula
	addi x12, x12, 4				# Move para o próximo digito
	addi x6, x6, -1					# Diminui do fator
	addi x28, x28, -1				# Decrementa o contador de loops	
	bgt x28, x0, verificacpf_forloop2# Repita para todos os dígitos
	addi x6, x0, 0					# Define o restante como 0 por padrão
	addi x7, x0, 11					# Seta o divisor para 11
	rem x5, x5, x7					# Encontrar soma módulo 11
	sub x5, x7, x5					# Subtrai de 11
	addi x7, x7, -1					# x7 = 10
	beq x7, x5, verificacpf_skipnext# Verifica se o resultado do módulo é 10
	add x6, x0, x5					# Se não, define o restante para o resultado do módulo
verificacpf_skipnext:
	addi x7, x0, 10					# x7 = 10
	slli x7, x7, 2					# x7 = 10*4
	add x7, x7, x15					# x7 Agora tem o endereço do 11º dígito
	lw x5, 0(x7)					# x5 tem o 11º dígito
	bne x5, x6, verificacpf_invalid # Se sobra não for igual ao 11º dígito, retorna inválido
	addi x10, x0, 1					# Retorna o CPF válido
	jalr x0, 0(x1)
verificacpf_invalid:
	addi x10, x0, 0 	
	jalr x0, 0(x1)

# Recebe o endereço do vetor CNPJ em x12
# Recebe o tamanho do vetor em x13
# Retorna o valor em x10. 1 se o CNPJ for válido e 0 se for inválido
verificacnpj:
	addi x5, x0, 14
	bne x13, x5, verificacnpj_invalid# Verifica se o tamanho do vetor é 14. Caso contrário, retorna inválido	
	addi x5, x0, 0					# soma = 0
	addi x6, x0, 2					# fator = 2
	addi x28, x0, 11				# Define o contador de loop para ser igual a 11
verificacnpj_forloop1:				# Loop para multiplicar cada dígito por seu fator e somar todos
	add x15, x0, x28
	slli x15, x15, 2
	add x15, x15, x12
	lw x7, 0(x15)					# Pega o digita
	mul x7, x7, x6					# Multiplica pelo seu fator
	add x5, x5, x7					# Acumula
	addi x6, x6, 1					# Incrementa o fator
	addi x7, x0, 10					# x7 = 10
	bne x6, x7,verificacnpj_skipnxt	# Se fator ==10, redefina-o para 2
	addi x6, x0, 2 					# fator = 2
verificacnpj_skipnxt:	
	addi x28, x28, -1				# Decrementa o contador do loop
	bge x28, x0, verificacnpj_forloop1	# Repete para todos os dígitos
	addi x6, x0, 0					# Defina o expectDigit13 como 0 por padrão
	addi x7, x0, 11					# Define o divisor para 11
	rem x5, x5, x7					# Encontra a soma módulo 11
	beq x5, x0, verificacnpj_0		# Se o resultado for 0, expectedDigit13 é 0
	addi x7, x0, 1					# x7 = 1
	beq x5, x7, verificacnpj_0		# Se o resultado for 1, expectedDigit13 é 0
	addi x7, x0, 11					# x7 = 11
	sub x6, x7, x5					# Se o resultado for diferente de 0 ou 1, expectedDigit13 é 11-resultado
verificacnpj_0:	
	lw x7, 48(x12)					# Obtem o 13º dígito
	bne x6, x7, verificacnpj_invalid# Se não for igual ao expectedDigit13, então retorne inválido
	addi x5, x0, 0					# soma = 0
	addi x6, x0, 2					# fator = 2
	addi x28, x0, 12				# Seta o contador de loop para ser igual a 12
verificacnpj_forloop2:				# Loop para multiplicar cada dígito por seu fator e somar todos
	add x15, x0, x28
	slli x15, x15, 2
	add x15, x15, x12
	lw x7, 0(x15)					# Pega o dígito
	mul x7, x7, x6					# Multiplica pelo seu fator
	add x5, x5, x7					# Acumula
	addi x6, x6, 1					# Incrementa o fator
	addi x7, x0, 10					# x7 = 10
	bne x6, x7,verificacnpj_skipnext# Se fator ==10, redefina-o para 2
	addi x6, x0, 2 					# fator = 2
verificacnpj_skipnext:	
	addi x28, x28, -1				# Decrementa o contador do loop
	bge x28, x0, verificacnpj_forloop2	# Repete para todos os dígitos
	addi x6, x0, 0					# Seta expectedDigit14 para 0 por padrão
	addi x7, x0, 11					# Seta o divisor para 11
	rem x5, x5, x7					# Acha a soma do modulo 11
	beq x5, x0, verificacnpj_zero	# Se o resultado for 0, expectedDigit14 é 0
	addi x7, x0, 1					# x7 = 1
	beq x5, x7, verificacnpj_zero	# Se o resultado for 1, expectedDigit14 é 0
	addi x7, x0, 11					# x7 = 11
	sub x6, x7, x5					# Se o resultado for diferente de 0 ou 1, expectedDigit14 é 11-resultado
verificacnpj_zero:	
	lw x7, 52(x12)					# Pega o 14º dígito
	bne x6, x7, verificacnpj_invalid# Se não for igual ao expectedDigit14, então retorne inválido
	addi x10, x0, 1					# Caso contrário, retorna CNPJ válido
	jalr x0, 0(x1)
verificacnpj_invalid:
	addi x10, x0, 0 	
	jalr x0, 0(x1)
	
# Recebe o endereço do vetor em x12
# Recebe o tamanho do vetor em x13
# Recebe se o vetor é CPF (0) ou CPNJ (1) em x14
# Retorna o valor em x10. 1 se É válido e 0 se for inválido
verificadastro:
	addi x2, x2, -4				# Cria espaço na pilha para armazenar $ra (x1) para preservar seu valor
	sw x1, 0(x2)				# Salva x1 na pilha
	beq x14, x0, call_verificacpf	# Se x14 for 0, chama verificacpf
	jal verificacnpj			# Senão,chama verificacnpj
	beq x0, x0, verificadastro_return		
call_verificacpf:
	jal verificacpf
verificadastro_return:
	lw x1, 0(x2)				# Restaura x1 da pilha
	addi x2, x2, 4				# Libera o espaço na pilha que foi reservado para armazenar $ra (x1)
	jalr x0, 0(x1)
##### END MODIFIQUE AQUI END #####
FIM: add x1, x0, x10
