# StarFleet Protocol - Batalha de Naves Espaciais

Sistema cliente-servidor TCP/IP para simular combates espaciais por turnos entre uma nave humana e uma nave controlada por computador.

## Descrição

O ano é 3142. A humanidade já se espalhou por centenas de sistemas estelares, mas a paz interestelar não durou. Você é o capitão da nave SS-42 Voyager, uma das últimas linhas de defesa da Federação. Sua missão: enfrentar uma frota inimiga que ameaça destruir seu setor.

A batalha é travada turno a turno. Você decide a manobra da sua nave; o inimigo reage. Os escudos brilham, torpedos atravessam o vácuo, motores de dobra se preparam para a fuga. No fim, apenas uma nave permanecerá intacta.

## Características Técnicas

- Protocolo cliente-servidor TCP customizado (StarFleet Protocol)
- Suporte dual-stack: IPv4 e IPv6
- Implementação em C puro com sockets POSIX
- Arquitetura modular com separação de responsabilidades
- Sistema de combate baseado em tabela de decisões
- Gerenciamento de estado centralizado no servidor

## Estrutura do Projeto

```
TP1/
├── app/
│   ├── client.c      # Implementação do cliente
│   └── server.c      # Implementação do servidor
├── core/
│   ├── game.c        # Lógica de combate
│   ├── game.h
│   ├── protocol.c    # Protocolo de comunicação
│   └── protocol.h
├── bin/              # Executáveis gerados (criado pelo make)
├── Makefile
├── Documentacao.pdf
└── enunciado.pdf
```

## Requisitos

- Sistema Operacional: Linux
- Compilador: GCC com suporte a C99
- Bibliotecas: POSIX sockets (padrão em sistemas Linux)

## Compilação

Para compilar o projeto, execute:

```bash
make
```

Isso irá gerar os executáveis `bin/server` e `bin/client`.

Para limpar os arquivos compilados:

```bash
make clean
```

## Uso

### Servidor

O servidor pode ser iniciado em modo IPv4 ou IPv6:

```bash
# IPv4
./bin/server v4 5001

# IPv6
./bin/server v6 5001
```

**Parâmetros:**
- Primeiro argumento: `v4` para IPv4 ou `v6` para IPv6
- Segundo argumento: número da porta (1-65535)

**Nota sobre Dual-Stack:**
- Servidor IPv4 aceita apenas conexões IPv4
- Servidor IPv6 aceita conexões IPv4 e IPv6 (dual-stack habilitado por padrão)

### Cliente

O cliente conecta-se ao servidor especificando host e porta:

```bash
# Conectar via IPv4
./bin/client 127.0.0.1 5001

# Conectar via IPv6
./bin/client ::1 5001
```

**Parâmetros:**
- Primeiro argumento: endereço IP ou hostname do servidor
- Segundo argumento: número da porta

## Regras do Jogo

### Pontos de Vida
- Cada nave inicia com 100 HP
- Dano base de ataques bem-sucedidos: 20 HP
- Jogo termina quando qualquer nave atinge 0 HP ou quando há fuga

### Ações Disponíveis

| Opção | Ação            | Efeito                                             |
|-------|-----------------|-----------------------------------------------------|
| 0     | Laser Attack    | Ataque básico de energia, penetra camuflagem        |
| 1     | Photon Torpedo  | Ataque pesado, vence laser mas bloqueado por escudos|
| 2     | Shields Up      | Defende-se de todos os ataques                      |
| 3     | Cloaking        | Evita torpedos, mas vulnerável a laser              |
| 4     | Hyper Jump      | Fuga imediata (encerra a partida)                   |

### Tabela de Interações

- **Laser vs Laser**: Ambos sofrem 20 HP de dano
- **Torpedo vs Torpedo**: Ambos sofrem 20 HP de dano
- **Torpedo vence Laser**: Laser sofre 20 HP, Torpedo ileso
- **Shields bloqueia tudo**: Nenhum ataque causa dano contra escudos
- **Laser penetra Cloaking**: Cloaking sofre 20 HP
- **Torpedo bloqueado por Cloaking**: Nenhum dano
- **Hyper Jump**: Encerra imediatamente a partida

### Ordem de Avaliação

1. **Hyper Jump tem prioridade**: Se qualquer lado escolher fuga, a partida termina imediatamente
2. **Resolução de bloqueios**: Shields e Cloaking são avaliados primeiro
3. **Resolução de ataques**: Ataques são comparados e danos aplicados

## Protocolo de Comunicação

### Estrutura da Mensagem

```c
typedef struct {
    int type;               // Tipo da mensagem (MessageType)
    int client_action;      // Ação escolhida pelo cliente
    int server_action;      // Ação escolhida pelo servidor
    int client_hp;          // HP do cliente
    int server_hp;          // HP do servidor
    int client_torpedoes;   // Número de torpedos usados
    int client_shields;     // Número de escudos usados
    char message[256];      // Mensagem textual
} BattleMessage;
```

### Tipos de Mensagem

- `MSG_INIT`: Boas-vindas ao conectar
- `MSG_ACTION_REQ`: Servidor solicita ação do cliente
- `MSG_ACTION_RES`: Cliente responde com ação escolhida
- `MSG_BATTLE_RESULT`: Resultado do turno
- `MSG_INVENTORY`: Estatísticas finais da partida
- `MSG_ESCAPE`: Término por fuga
- `MSG_GAME_OVER`: Término por destruição

### Fluxo de Comunicação

1. Cliente conecta ao servidor
2. Servidor envia MSG_INIT (boas-vindas)
3. Loop de turnos:
   - Servidor envia MSG_ACTION_REQ
   - Cliente responde com MSG_ACTION_RES
   - Servidor processa e envia MSG_BATTLE_RESULT
4. Ao final:
   - Servidor envia MSG_INVENTORY (estatísticas)
   - Servidor envia MSG_ESCAPE ou MSG_GAME_OVER
5. Conexão encerrada

## Exemplos de Execução

### Exemplo 1: Vitória por Torpedo

```
> 1
Você disparou um Photon Torpedo!
Servidor usou Cloaking.
Resultado: Acerto! Nave inimiga perdeu 20 HP.
Placar: Você 100 x 80 Inimigo
```

### Exemplo 2: Defesa com Escudos

```
> 2
Você ativou os Escudos!
Servidor disparou um Photon Torpedo!
Resultado: Ataque inimigo bloqueado!
Placar: Você 100 x 100 Inimigo
```

### Exemplo 3: Fuga

```
> 4
Você acionou o Hyper Jump!
Sua nave escapou para o hiperespaço.

Inventário final:
- HP restante: 75
- Torpedos usados: 3
- Escudos usados: 2
- Turnos jogados: 5
Obrigado por jogar!
```

## Inventário Final

Ao término da partida, são exibidas as seguintes estatísticas:

- HP final da nave do cliente
- HP final da nave inimiga
- Total de turnos jogados
- Número de torpedos disparados pelo cliente
- Número de vezes que escudos foram ativados

## Decisões de Implementação

### Arquitetura Modular

O código foi organizado em camadas lógicas:
- **core/**: Lógica de negócio reutilizável (protocolo e regras de jogo)
- **app/**: Implementações específicas de cliente e servidor

### Table-Driven Combat

A lógica de combate utiliza abordagem table-driven, centralizando todas as regras em estrutura de dados declarativa. Isso melhora legibilidade e facilita manutenção.

### Estado Centralizado

Todo o estado da partida é mantido no servidor através da estrutura `BattleSession`. O cliente é stateless, apenas exibindo informações recebidas e enviando ações.

### Dual-Stack Automático

O cliente usa `getaddrinfo` com `AF_UNSPEC`, tentando automaticamente todas as opções de endereçamento disponíveis (IPv4 e IPv6).

## Limitações Conhecidas

- O servidor processa uma conexão por vez (single-threaded)
- A IA do servidor escolhe ações completamente aleatórias
- Não há persistência de histórico de partidas
- Não há sistema de autenticação ou múltiplos jogadores simultâneos

## Possíveis Melhorias

1. **IA mais inteligente**: Implementar análise de padrões de comportamento do jogador
2. **Níveis de dificuldade**: Diferentes estratégias de seleção de ações
3. **Histórico de partidas**: Salvar estatísticas em arquivo para acompanhar progresso
4. **Suporte multi-jogador**: Permitir múltiplas conexões simultâneas
5. **Replay de partidas**: Gravar e reproduzir combates anteriores

## Documentação Adicional

Para informações detalhadas sobre implementação, decisões de design e análise técnica, consulte o arquivo [Documentacao.pdf](Documentacao.pdf).

Para especificação completa do trabalho, consulte o arquivo [enunciado.pdf](enunciado.pdf).

## Referências

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [TCP Server-Client Implementation in C - GeeksforGeeks](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/)
- [getaddrinfo(3) - Linux Manual Page](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
- TANENBAUM, Andrew S.; FEAMSTER, Nick; WETHERALL, David J. Redes de Computadores. 6ª ed. Pearson Education, 2021.
