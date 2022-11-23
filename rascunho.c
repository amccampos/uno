/*  Local para colocar as variaveis :)

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

// Struct para os bots

typedef struct {     // struct feita para representar uma unica carta
    char valorCarta;
    char *valorNaipe;
}Carta;

typedef struct  {   // struct para guardar as cartas dos jogadores 
    Carta *cartasDoJogador;
    int qtdDeCartas;
}Mao;

typedef struct {   // representa um jogador 
    char id[MAX_ID_SIZE];
    Mao maoDoJogador;
}Jogador;

typedef struct {   // será utilisado para ler e escreveer as ações de cada jogador por turno 
    char *acao;
    Carta complementoCarta;
    char *complemento1;
    char *complemento2;
}AcoesPorTurno;

Jogador* armazenaJogadores(char *mensagem){   // crial um array onde cada elemento é um jogador  
    int aux = 0, tamanho;                     
    char *pedaco;
    Jogador *array;

    pedaco = strtok(mensagem," ");
    while (pedaco != NULL) {
        if (aux == 0){
            array = malloc(sizeof(Jogador));
            strcpy(array[aux].id, pedaco);
            aux += 1;
        }else{
            array = realloc(array, sizeof(Jogador) * (aux+1));
            strcpy(array[aux].id, pedaco);
            aux += 1;
        }
        pedaco = strtok(NULL," ");
    }
    return array;
}

Mao maoInicial(char *mensagem){     // Faz a leitura das cartas iniciais do bot
    Mao saida;
    Carta aux;
    char *pedaco, vetor[10][10];
    int tamanho, cont = 0;

    pedaco = strtok(mensagem, " ");
    while(pedaco != NULL){
        strcpy(vetor[cont],pedaco);
        cont += 1;
        pedaco = strtok(NULL, " ");
    }

    saida.cartasDoJogador = malloc(sizeof(Carta) * (cont-2));

    for (int i = 1; i < cont - 1; i++) {
        aux.valorCarta = vetor[i][0];
        tamanho = strlen(vetor[i]);
        if (i == 1){
            aux.valorNaipe = malloc(sizeof(char) * tamanho);
            for (int j = 1; j < tamanho; j++){
                aux.valorNaipe[j-1] = vetor[i][j];
            }
        }else{
            aux.valorNaipe = realloc(aux.valorNaipe, sizeof(char) * tamanho);
            for (int j = 1; j < tamanho; j++){
                aux.valorNaipe[j-1] = vetor[i][j];
            }
        }
        saida.cartasDoJogador[i-1].valorNaipe = malloc(sizeof(char) * tamanho);

        saida.cartasDoJogador[i-1].valorCarta = aux.valorCarta;
        strcpy(saida.cartasDoJogador[i-1].valorNaipe, aux.valorNaipe);
        saida.qtdDeCartas = i;
    }
    free(aux.valorNaipe);
    return saida;
}

Carta gerarCarta(char *mensagem){     // transforma uma string com valor e nipe em uma variavel do tipo Carta
    Carta saida;
    int tamanho = strlen(mensagem);

    saida.valorCarta = mensagem[0];
    saida.valorNaipe = malloc(sizeof(char) * tamanho);

    for (int i = 1; i < tamanho; i++){
        saida.valorNaipe[i-1] = mensagem[i];
    }
    return saida;
}

AcoesPorTurno jogadaSemComplemento2(char * mensagem1, char *mensagem2){
    AcoesPorTurno saida;
    int tamanho = strlen(mensagem1);
    saida.acao = malloc(sizeof(char) * tamanho);
    strcpy(saida.acao, mensagem1);
    if (strcmp(mensagem1, "TURN") != 0){
        saida.complementoCarta = gerarCarta(mensagem2);
    }else{
        tamanho = strlen(mensagem2);
        saida.complemento1 = malloc(sizeof(char) * tamanho);
        strcpy(saida.complemento1, mensagem2);
    }
    return saida;
}

AcoesPorTurno jogadaComComplemento2(char * mensagem1, char *mensagem2, char *mensagem3){
    AcoesPorTurno saida;

    int tamanho = strlen(mensagem1);
    saida.acao = malloc(sizeof(char) * tamanho);
    strcpy(saida.acao, mensagem1);
    saida.complementoCarta = gerarCarta(mensagem2);
    tamanho = strlen(mensagem3);
    saida.complemento2 = malloc(sizeof(char) * tamanho);
    strcpy(saida.complemento2, mensagem3);

    return saida;
}

void debug(char *message) {
    fprintf(stderr, "%s\n", message);
}

int main() {

    char temp[MAX_LINE];  
    char my_id[MAX_ID_SIZE]; 
    Jogador *jogadores;
    Mao minhaMao;
    Carta cartaInicial;

    setbuf(stdin, NULL);  
    setbuf(stdout, NULL);  
    setbuf(stderr, NULL);
        

    // Ler quais são os jogadores

    scanf("PLAYERS %[^\n]\n", temp);

    debug(temp);

    jogadores = armazenaJogadores(temp);
    debug(jogadores[1].id);

    // Id do nosso bot
    scanf("YOU %s\n", my_id);
    debug(my_id);

    // A mão recebida

    scanf("HAND %[^\n]\n", temp);
    debug(temp);
    minhaMao = maoInicial(temp); 
    debug(minhaMao.cartasDoJogador[4].valorNaipe);
    
    // exemplos da forma de como acessar os elementos de maoInicial:
    //minhaMao.cartasDoJogador[i].valorCarta
    //minhaMao.cartasDoJogador[i].valorNaipe

    // carta inicial 

    scanf("TABLE %s\n", temp);
    cartaInicial = gerarCarta(temp);
     
    char id[MAX_ID_SIZE];
    char action[MAX_ACTION];
    char complement[MAX_LINE];

    // Fica esperando a vez do seu bot jogar

    while(1) {

    do {

        // ler a jogada do bot anterior a vc 

        scanf("%s %s", action, complement);
        // Fiz duas funcões para leitura de jogadas uma pra quando tiver complemento 2 ou não 
        // jogadaSemComplemento2 e jogadaComComplemento2

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));


    debug("----- MINHA VEZ -----");


    // Exemplo de jogada ----> char card[] = "A♥ ♥";


    // Nossa jogada propriamente dita 

    char card;
    printf("DISCARD %s\n", card);
    
    }

    free(jogadores);
    

    return 0;
}
