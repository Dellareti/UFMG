#include <stdio.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define DEBUG

#define TAM_HEROI 20
#define PASSO 20
#define MAX_MONSTROS 30
#define TAM_OBJ 50
#define MAX_DIST 20
#define FUGIR_CHANCE 80
#define RAIO_PERSONAGENS 100

// ----- Variaveis globais -----

const float FPS = 60;

//  const int SCREEN_W = 1280;
//  const int SCREEN_H = 720;
const int SCREEN_W = 960;
const int SCREEN_H = 540;

ALLEGRO_FONT *FONTE;

int CEU_H;
int X_OPT;
int Y_OPT;
int X_OFFSET;
int Y_OFFSET;
int ALTURA_OBJETOS;

enum ESTADOS
{
    NAVEGACAO,
    BATALHA,
    GAME_OVER,
    VITORIA
};

enum ACOES
{
    ATACAR,
    ESPECIAL,
    FUGIR
};
enum COR
{
    AMARELO,
    AZUL,
    PRETO,
    ROXO,
    VERMELHO,
    BRANCO
};

ALLEGRO_COLOR CORES[6];

//________________________________________
typedef struct Monstro
{
    int x, y;
    ALLEGRO_COLOR COR;
    int vida;
    int vida_max;
    int dano;
} Monstro;

typedef struct Heroi
{
    int x, y;
    ALLEGRO_COLOR COR;
    int vida;
    int vida_max;
    int pontuacao;
    // Batalha
    Monstro *alvo;
    int dano;
    int acao;
    int executar;
    int x_old, y_old;

} Heroi;

typedef struct Projetil
{
    int x, y;
    int dano;
    int velocidade;
    int ativo;
} Projetil;

void initHeroi(Heroi *h)
{

    h->x = 0;
    h->y = SCREEN_H - TAM_HEROI;
    h->COR = CORES[VERMELHO];
    h->vida_max = 300;
    h->vida = h->vida_max;
    h->acao = FUGIR;
    h->dano = 25;
    h->executar = 0;
    h->x_old = h->x;
    h->y_old = h->y;
    h->alvo = NULL;
    h->pontuacao = 0;
}

void inicializaTipo(Monstro *m, int tipo)
{
    m->vida_max = 100 + tipo * 50;
    m->vida = m->vida_max;
    m->dano = 5 + tipo * 3;
    m->COR = CORES[tipo];
}

void initCores()
{
    CORES[AMARELO] = al_map_rgb(255, 255, 0);
    CORES[AZUL] = al_map_rgb(0, 0, 255);
    CORES[PRETO] = al_map_rgb(0, 0, 0);
    CORES[ROXO] = al_map_rgb(128, 0, 128);
    CORES[VERMELHO] = al_map_rgb(255, 0, 0);
    CORES[BRANCO] = al_map_rgb(255, 255, 255);
}

int inteiroAleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int multiploMaisProximo(int num, int mult)
{
    return roundf((float)num / mult) * mult;
}

void initMonstros(Monstro monstros[MAX_MONSTROS])
{
    srand(time(NULL));
    for (int i = 0; i < MAX_MONSTROS; i++)
    {
        monstros[i].x = multiploMaisProximo(inteiroAleatorio((SCREEN_W - TAM_HEROI) / MAX_MONSTROS * i,
                                                             (SCREEN_W - TAM_HEROI) / MAX_MONSTROS * (i + 1)),
                                            PASSO);
        monstros[i].y = multiploMaisProximo(inteiroAleatorio(0, SCREEN_H - TAM_HEROI), PASSO);
        inicializaTipo(&monstros[i], inteiroAleatorio(0, 3));
    }
}

void desenhaPontuacao(Heroi h)
{
    al_draw_textf(FONTE, CORES[BRANCO], 0, 0, ALLEGRO_ALIGN_LEFT, "%d", h.pontuacao);
}

void desenhaVitoria(Heroi h, int recorde)
{
    char texto_pontuacao[6], texto_recorde[6];
    sprintf(texto_pontuacao, "%d", h.pontuacao);
    sprintf(texto_recorde, "%d", recorde);
    al_clear_to_color(al_map_rgb(58, 114, 56));
    int superou = 0;
    if (h.pontuacao > recorde)
    {
        superou = 1;
        recorde = h.pontuacao;
    }
    al_draw_textf(FONTE, CORES[BRANCO], SCREEN_W / 2, SCREEN_H / 2 - 50, ALLEGRO_ALIGN_CENTER, "VOCE VENCEU!");
    al_draw_textf(FONTE, CORES[BRANCO], SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Pontuacao: %d", h.pontuacao);
    al_draw_textf(FONTE, CORES[BRANCO], SCREEN_W / 2, SCREEN_H / 2 + 50, ALLEGRO_ALIGN_CENTER, "Recorde: %d", recorde);
    if (superou)
    {
        al_draw_textf(FONTE, CORES[BRANCO], SCREEN_W / 2, SCREEN_H / 2 + 100, ALLEGRO_ALIGN_CENTER, "NOVO RECORDE!");
        FILE *arquivo = fopen("recorde.dat", "w+"); // sobreescreve o arquivo
        fprintf(arquivo, "%d", recorde);
        fclose(arquivo);
    }
}

void initGlobais()
{

    CEU_H = SCREEN_H / 5;
    X_OPT = 3 * SCREEN_W / 4;
    Y_OPT = 3 * SCREEN_H / 4;
    X_OFFSET = 50;
    Y_OFFSET = 35;
    ALTURA_OBJETOS = CEU_H + Y_OFFSET * 2 + 100;
    initCores();
    int tam_fonte = 25;
    if (SCREEN_H < 300)
        tam_fonte = 20;

    //carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    FONTE = al_load_font("arial.ttf", tam_fonte, 1);
    if (FONTE == NULL)
    {
        fprintf(stderr, "font file does not exist or cannot be accessed!\n");
    }
}
//==================== Navegação ====================

void desenhaHeroiNaveg(Heroi h)
{

    al_draw_filled_rectangle(h.x, h.y, h.x + TAM_HEROI, h.y + TAM_HEROI, h.COR);
}

void desenhaMonstros(Monstro monstros[MAX_MONSTROS])
{
    for (int i = 0; i < MAX_MONSTROS; i++)
    {
        al_draw_filled_rectangle(monstros[i].x, monstros[i].y, monstros[i].x + TAM_HEROI, monstros[i].y + TAM_HEROI, monstros[i].COR);
    }
}

void desenhaCenarioNaveg()
{
    al_clear_to_color(al_map_rgb(58, 114, 56));
    al_draw_filled_rectangle(SCREEN_W - TAM_OBJ, 0, SCREEN_W, TAM_OBJ, al_map_rgb(102, 88, 91));
}

// Movimentação
void processaTeclaNaveg(Heroi *h, int tecla)
{

    h->x_old = h->x;
    h->y_old = h->y;

    switch (tecla)
    {

    case ALLEGRO_KEY_UP:
        if (h->y - PASSO >= 0)
        {
            h->y -= PASSO;
        }
        break;

    case ALLEGRO_KEY_DOWN:
        if (h->y + PASSO + TAM_HEROI <= SCREEN_H)
        {
            h->y += PASSO;
        }
        break;

    case ALLEGRO_KEY_LEFT:
        if (h->x - PASSO >= 0)
        {
            h->x -= PASSO;
        }
        break;

    case ALLEGRO_KEY_RIGHT:
        if (h->x + PASSO + TAM_HEROI <= SCREEN_W)
        {
            h->x += PASSO;
        }
        break;

    default:
        break;
    }
}

// ______________________________________________

int chegouObjetivo(Heroi h)
{
    if (h.x >= SCREEN_W - TAM_OBJ && h.y + TAM_HEROI <= TAM_OBJ)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//==================== Batalha ====================

void desenhaBarraDeVida(int x, int y, int vida, int vida_max, ALLEGRO_COLOR cor)
{
    al_draw_filled_rectangle(x, y - 10, x + vida_max, y - 10 + 10, CORES[BRANCO]);
    al_draw_filled_rectangle(x, y - 10, x + vida, y - 10 + 10, cor);
}

void desenhaMonstro(Monstro *m)
{
    al_draw_filled_circle(X_OFFSET + m->vida_max / 2, CEU_H + Y_OFFSET * 2 + 100, 100, m->COR);
}

void desenhaHeroi(Heroi *h)
{
    al_draw_filled_circle(SCREEN_W - X_OFFSET - h->vida_max / 2, CEU_H + Y_OFFSET * 2 + 100, 100, h->COR);
}

void desenhaBarrasDeVida(Heroi *h)
{
    int x = X_OFFSET;
    int y = CEU_H + Y_OFFSET;
    desenhaBarraDeVida(x, y, h->alvo->vida, h->alvo->vida_max, h->alvo->COR);
    x = SCREEN_W - X_OFFSET - h->vida_max;
    desenhaBarraDeVida(x, y, h->vida, h->vida_max, h->COR);
}

void desenhaProjetil(Projetil *p)
{
    if (p->ativo)
    {
        al_draw_filled_circle(p->x, p->y, p->dano, CORES[VERMELHO]);
    }
}

void desenhaCenarioBatalha(Heroi *h, Projetil *p)
{

    al_clear_to_color(al_map_rgb(58, 114, 56));
    al_draw_filled_rectangle(0, 0, SCREEN_W, CEU_H, al_map_rgb(0, 0, 255));
    desenhaBarrasDeVida(h);
    desenhaMonstro(h->alvo);
    desenhaHeroi(h);
    desenhaProjetil(p);
    al_draw_filled_rectangle(X_OPT, Y_OPT, SCREEN_W, SCREEN_H, al_map_rgb(20, 16, 77));
    al_draw_text(FONTE, CORES[BRANCO], X_OPT + X_OFFSET, Y_OPT + 15, 0, "Atacar");
    al_draw_text(FONTE, CORES[BRANCO], X_OPT + X_OFFSET, Y_OPT + 15 + Y_OFFSET, 0, "Especial");
    al_draw_text(FONTE, CORES[BRANCO], X_OPT + X_OFFSET, Y_OPT + 15 + Y_OFFSET * 2, 0, "Fugir");
    al_draw_filled_circle(X_OPT + X_OFFSET / 2, Y_OPT + 30 + Y_OFFSET * h->acao, 5, CORES[BRANCO]);
}


void desenhaGameOver()
{
    al_clear_to_color(CORES[PRETO]);
    al_draw_text(FONTE, CORES[VERMELHO], SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
}

float dist(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int detectouMonstro(Heroi *h, Monstro m[MAX_MONSTROS])
{
    for (int i = 0; i < MAX_MONSTROS; i++)
    {
        if (dist(h->x, h->y, m[i].x, m[i].y) <= MAX_DIST && m[i].vida > 0)
        {
            printf("Inimigo encontrado!\n");
            h->alvo = &m[i];
            return 1;
        }
    }
    return 0;
}

void processaTeclaBatalha(Heroi *h, int tecla)
{
    switch (tecla)
    {
    case ALLEGRO_KEY_UP:
        h->acao = h->acao > 0 ? h->acao - 1 : FUGIR;
        break;

    case ALLEGRO_KEY_DOWN:
        h->acao = h->acao < FUGIR ? h->acao + 1 : ATACAR;
        break;

    case ALLEGRO_KEY_ENTER:
        h->executar = 1;
        break;
    case ALLEGRO_KEY_M:
        h->COR = CORES[AZUL];
        h->dano+=50;

    default:
        break;
    }
}

int ProcessaAcaoHeroi(Heroi *h, Projetil *p)
{
    if (p->ativo)
    {
        p->x += p->velocidade;
        if (p->x < X_OFFSET + h->alvo->vida_max / 2 + 100)
        {
            h->alvo->vida -= p->dano;
            if (h->alvo->vida <= 0)
            {
                h->pontuacao += h->alvo->vida_max + h->vida_max - h->vida;
                p->ativo = 0;
                return NAVEGACAO;
            }
            p->y = ALTURA_OBJETOS;
            p->x = X_OFFSET + h->alvo->vida_max / 2 + 100;
            p->velocidade = 10;
            p->dano = h->alvo->dano;
        }
        else if (p->x > SCREEN_W - X_OFFSET - h->vida_max / 2 - 100)
        {
            h->vida -= p->dano;
            p->ativo = 0;
        }

        if (h->vida <= 0)
        {
            return GAME_OVER;
        }
    }
    if (h->executar)
    {
        h->executar = 0;

        if (h->acao == FUGIR)
        {
            printf("Tentando fugir com %d%% de chance...\n", FUGIR_CHANCE);
            if (inteiroAleatorio(0, 100) < FUGIR_CHANCE)
            {

                printf("Fugiu!\n");
                h->x = h->x_old;
                h->y = h->y_old;

                return NAVEGACAO;
            }
            printf("Falhou!\n");
            p->ativo = 1;
            p->x = X_OFFSET + h->alvo->vida_max / 2 + 100;
            p->y = ALTURA_OBJETOS;
            p->velocidade = 10;
            p->dano = h->alvo->dano;
        }
        else
        {
            p->ativo = 1;
            p->x = SCREEN_W - X_OFFSET - h->vida_max / 2 - 100;
            p->y = ALTURA_OBJETOS;
            p->velocidade = -10;
            if (h->acao == ATACAR)
            {
                p->dano = h->dano;
            }
            else if (h->acao == ESPECIAL)
            {
                p->dano = (h->vida_max - h->vida + h->dano / 2) / inteiroAleatorio(1,3);
            }
        }
        return BATALHA;
    }

    else
    {
        return BATALHA;
    }
}

int main(int argc, char **argv)
{

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    //----------------------- rotinas de inicializacao ---------------------------------------

    //inicializa o Allegro
    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    //inicializa o módulo de primitivas do Allegro
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

    //inicializa o modulo que permite carregar imagens no jogo
    if (!al_init_image_addon())
    {
        fprintf(stderr, "failed to initialize image module!\n");
        return -1;
    }

    //cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if (!timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    //cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    //instala o teclado
    if (!al_install_keyboard())
    {
        fprintf(stderr, "failed to install keyboard!\n");
        return -1;
    }

    //inicializa o modulo allegro que carrega as fontes
    al_init_font_addon();

    //inicializa o modulo allegro que entende arquivos tff de fontes
    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "failed to load tff font module!\n");
        return -1;
    }

    //cria a fila de eventos
    event_queue = al_create_event_queue();
    if (!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        return -1;
    }

    //registra na fila os eventos de tela (ex: clicar no X na janela)
    al_register_event_source(event_queue, al_get_display_event_source(display));
    //registra na fila os eventos de tempo: quando o tempo altera de t para t+1
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    //registra na fila os eventos de teclado (ex: pressionar uma tecla)
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    //inicia o temporizador
    al_start_timer(timer);

    int recorde;
    FILE *arq_recorde = fopen("recorde.dat", "r");
    if (arq_recorde == NULL)
    {
        recorde = 0;
    }
    else
    {
        fscanf(arq_recorde, "%d", &recorde);
        fclose(arq_recorde);
    }
    int playing = 1;
    int modo_jogo = NAVEGACAO;

    initGlobais();
    Heroi heroi;
    Monstro monstros[MAX_MONSTROS];
    initMonstros(monstros);
    initHeroi(&heroi);
    ALLEGRO_EVENT ev;
    Projetil projetil;
    projetil.ativo = 0;

    while (playing)
    {
        //espera por um evento e o armazena na variavel de evento ev
        al_wait_for_event(event_queue, &ev);

        //se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {

            if (modo_jogo == NAVEGACAO)
            {
                desenhaCenarioNaveg();
                desenhaHeroiNaveg(heroi);

             //desenhaMonstros(monstros); // para debug

            }
            else
            {
                modo_jogo = ProcessaAcaoHeroi(&heroi, &projetil);
                desenhaCenarioBatalha(&heroi, &projetil);
            }
            if (modo_jogo == GAME_OVER)
            {
                playing = 0;
            }
            desenhaPontuacao(heroi);

            //atualiza a tela (quando houver algo para mostrar)
            al_flip_display();
        }
        //se o tipo de evento for o fechamento da tela (clique no x da janela)
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            playing = 0;
        }
        //se o tipo de evento for um pressionar de uma tecla
        else if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
        {

            if (modo_jogo == NAVEGACAO)
            {
                processaTeclaNaveg(&heroi, ev.keyboard.keycode);
                if (detectouMonstro(&heroi, monstros))
                {
                    modo_jogo = BATALHA;
                }

                if (chegouObjetivo(heroi))
                {
                    modo_jogo = VITORIA;
                    playing = 0;
                }
            }
            else if(!projetil.ativo)
            {  
                processaTeclaBatalha(&heroi, ev.keyboard.keycode);
            }

            //imprime qual tecla foi
            printf("codigo tecla: %d\n", ev.keyboard.keycode);
        }

    } //fim do while
    //procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
    if (modo_jogo == GAME_OVER)
    {
        desenhaGameOver();
    }
    else if (modo_jogo == VITORIA)
    {
        desenhaVitoria(heroi, recorde);
    }
    al_flip_display();
    while (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        al_wait_for_event(event_queue, &ev);
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
