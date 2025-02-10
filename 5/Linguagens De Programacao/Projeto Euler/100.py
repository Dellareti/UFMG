# Define um limite grande para o número de discos azuis
LIMITE = 10 ** 12

# Inicializa o número de discos azuis (n) e discos vermelhos (m)
num_discos_azuis = 4
num_discos_vermelhos = 3

# Loop até que o número de discos azuis exceda o limite
while num_discos_azuis <= LIMITE:
    # Atualiza os valores de num_discos_azuis e num_discos_vermelhos usando as fórmulas recursivas
    novo_num_discos_azuis = 3 * num_discos_azuis + 4 * num_discos_vermelhos - 3
    novo_num_discos_vermelhos = 2 * num_discos_azuis + 3 * num_discos_vermelhos - 2
    
    # Atualiza os valores para a próxima iteração
    num_discos_azuis = novo_num_discos_azuis
    num_discos_vermelhos = novo_num_discos_vermelhos

# A resposta é o número de discos vermelhos quando a condição é satisfeita
resultado = num_discos_vermelhos

print(resultado)