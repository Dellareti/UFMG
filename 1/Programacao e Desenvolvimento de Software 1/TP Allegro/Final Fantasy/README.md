# Final Fantasy

Um jogo estilo RPG simples desenvolvido em C usando a biblioteca Allegro. Este projeto foi criado como parte da disciplina de Programação e Desenvolvimento de Software I (PDS1) da Universidade Federal de Minas Gerais (UFMG).

## Descrição

Final Fantasy é um RPG 2D onde o objetivo do jogador é chegar à saída do mapa. Durante o trajeto, existem vários inimigos escondidos em posições aleatórias que atacarão o jogador e iniciarão o modo de batalha. O jogo apresenta dois modos principais:

1. **Modo de Exploração**: O jogador navega pelo mapa tentando alcançar a saída enquanto evita inimigos.
2. **Modo de Batalha**: Quando o jogador encontra um inimigo, o jogo muda para o modo de batalha onde o jogador pode escolher atacar, usar um movimento especial ou tentar fugir.

À medida que o jogador derrota inimigos, ele ganha pontos. Ao alcançar a saída, o jogador recebe uma pontuação final baseada no número de inimigos derrotados.

## Características

- Dois modos de jogo distintos: Exploração e Batalha
- Geração aleatória de inimigos com quatro tipos diferentes (diferenciados por cor)
- Sistema de batalha por turnos com três ações: Atacar, Especial e Fugir
- Acompanhamento de pontuação e armazenamento de recordes
- Representação visual de barras de vida e ataques
- Múltiplos tipos de inimigos com estatísticas variadas

## Controles

### Modo de Exploração
- **Teclas de seta**: Movimentar o personagem

### Modo de Batalha
- **Teclas de seta para cima/baixo**: Navegar pelas opções de batalha
- **Enter**: Selecionar uma ação
- **M**: Power-up secreto (aumenta o dano de ataque em 50)

## Instalação

### Requisitos
- Compilador C (GCC recomendado)
- Biblioteca Allegro 5

### Dependências
O jogo requer a biblioteca Allegro 5. Você pode instalá-la através do seu gerenciador de pacotes.

Por exemplo, no Ubuntu:
```
sudo apt-get install liballegro5-dev
```

### Compilando a partir do código-fonte

1. Clone o repositório
```
git clone https://github.com/seuusuario/final-fantasy.git
cd final-fantasy
```

2. Compile o jogo
```
make
```

3. Execute o jogo
```
./ffantasy
```

Se você precisar modificar o caminho do Allegro no Makefile, edite a variável `PATH_ALLEGRO` de acordo com a configuração do seu sistema.

## Mecânicas do Jogo

### Tipos de Inimigos
Existem quatro tipos de inimigos, cada um com características diferentes:
- Amarelo: Inimigo básico
- Azul: Mais forte que o amarelo
- Roxo: Mais forte que o azul
- Preto: Inimigo mais forte

### Sistema de Batalha
- **Atacar**: Dano fixo de 25 pontos
- **Especial**: Dano variável com 33% de chance de dano baixo, 33% de chance de dano médio e 33% de chance de dano alto
- **Fugir**: 80% de chance de sucesso, 20% de chance de falha

### Pontuação
A pontuação é calculada como: `vida máxima do inimigo + vida máxima do jogador - vida atual do jogador`

## Estrutura do Projeto

- `ffantasy.c`: Código-fonte principal do jogo
- `Makefile`: Configuração de compilação
- `recorde.dat`: Arquivo que armazena a pontuação mais alta
- `arial.ttf`: Arquivo de fonte necessário para renderização de texto

## Autor

Ítalo Dell Areti

## Agradecimentos

- Disciplina de Programação e Desenvolvimento de Software I da UFMG
- Equipe de desenvolvimento do Allegro pela biblioteca de jogos
