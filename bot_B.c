/********************************************************************
  Bot-exemplo do jogo Uno

  Esta é uma versão do jogo de baralho Uno, com algumas diferenças:

  A primeira é que este é um jogo baseado em turnos. Ou seja, um jogador só age quando
  for sua vez. Logo, não haverá a opção de gritar "UNO" quando um jogador tiver apenas
  uma carta. A regra de dizer UNO foi deixada de fora. Porém, para descontrair e liberar
  todo o nervosismo da partida, seu bot pode falar o que quiser na sua vez (com seu
  devido respeito!).

  A segunda é que ele é jogado com as cartas do baralho tradicional. Ou seja, ao invés de
  cores, teremos naipes (copas, espadas, ouro e paus) e, ao invés de cartas especiais (como
  "Compre duas" ou "Passe a vez"), teremos cartas do baralho como Valete, Damas, Rei, Ás
  e Coringa. Estas cartas substituem as cartas especiais do Uno, seguindo a correspondência:
    "COMPRE 4"   : C = CORINGA
    "COMPRE 2"   : V = VALETE
    "VOLTA"      : D = DAMA
    "PULA A VEZ" : R = REI
    "MUDE A COR" : A = ÀS (muda o naipe)
  
  A partida será jogada com um único baralho. Assim, teremos quatro cartas de um valor. Por
  exemplo, 7♥, 7♦, 7♣, 7♠, com exceção do coringa, que há apenas duas: um vermelho e um preto.
  Porém, para seguir o padrão das cartas, os coringas terão também um naipe, mas serão apenas
  dos naipes: ♥ (coringa vermelho) e ♣ (coringa preto).

  O jogo é gerenciado por um "simulador" que irá controlar o jogo, dando a vez ao bot da
  rodada. O bot deve ler os dados da entrada-padrão (via scanf) no formato especificado pelo
  simulador, caso contrário ele se perderá e será eliminado da partida.
  O bot também deve enviar suas ações para o simulador via saída-padrão (via printf) no formato
  esperado pelo simulador, novamente sob pena de ser eliminado da partida.

  As cartas do baralho sempre são no formato "ValorNaipe".
  Nesse formato, Valor é um dos valores das cartas tradicionais, ou seja, A, 2, 3, 4, 5, 6,
  7, 8, 9, 10, V (valete), D (dama), R (rei) e C (coringa), e Naipe é um dos seguintes naipes:
  ♥, ♦, ♣, ♠.

  Os naipes são caracteres no formato ascii estendidos, que possuem uma representação maior
  que um byte (char). Isso significa que eles deve ser tratados como se fossem strings.

  A lógica apresentada nesse template visa ilustrar a entrada e saída de dados de um bot.
  Cabe a você aprimorar a lógica das ações do seu bot.

  Bom jogo!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

/**
 * Para "debugar", é possível enviar uma mensagem para a saída de erro padrão (stderr).
 * Essa mensagem não será enviada para o simulador, apenas para o terminal.
 */
void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}

// APESAR DO CÓDIGO ESTAR EM UMA ÚNICA FUNÇÃO, É SEU OBJETIVO ESCREVER A LÓGICA
// DE FORMA ORGANIZADA, USANDO DIFERENTES FUNÇÕES E ARQUIVOS.

int main() {
  // Obs: As variáveis deste template foram definidas apenas para o código compilar e rodar.
  // Então, cabe a você usar as variáveis adequadas em função do que está lendo.
  char temp[MAX_LINE];   // string para leitura temporária de dados
  char my_id[MAX_ID_SIZE];  // identificador do seu bot

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===

  /*
  Antes da partida começar, o simulador irá enviar alguns dados para seu bot, a saber:
  - os bots que estão jogando, no formato: "PLAYERS <bot_1> <bot_2> ...";
  - o identificador de seu bot, no formato: "YOU <id>";
  - as cartas da sua mão, no formato: "HAND [ <c_1> <c_2> ... ]";
  - a carta que se encontra sobre a mesa, no formato "TABLE <c>".

  Um exemplo de dados iniciais é:
    PLAYERS b1 b2 b3
    YOU b1
    HAND [ 4♥ 7♦ 2♣ V♠ A♥ 3♦ 2♣ 9♠ ]
    TABLE 8♦

  Seu bot deve, então, ler todos esses dados no início do programa. Veja que o conjunto
  de cartas na mão do bot está entre []. Cabe a você tratar essa entrada.
  */

  // Lê uma linha até o '\n' com os identificadores dos jogadores.
  // Será necessário separar os identificadores para saber quem são, quantos bots estão
  // jogando e qual a ordem inicial de jogada deles.
  scanf("PLAYERS %[^\n]\n", temp);

  // Caso queira imprimir uma mensagem para debugar, pode chamar 'debug()' passando uma string.
  // Por exemplo: debug(temp);
  debug(temp);

  // Lê o identificador do próprio bot. Isso é importante para testar quando é sua vez.
  scanf("YOU %s\n", my_id);

  // Lê as cartas iniciais que o bot tem na mão. Ex: "[ 4♥ 7♦ 2♣ J♠ A♥ 3♦ 2♣ 9♠ ]".
  // Os caracteres especiais (♥, ♦, ♣ e ♠) são caracteres ascii estendidos e precisam de
  // mais de um byte para armazená-los. Assim, é interesante guardá-los como strings.
  // Obs: lembre-se de tratar os colchetes.
  scanf("HAND %[^\n]\n", temp);

  // Lê a carta aberta sobre a mesa. Ex: TABLE 8♣
  scanf("TABLE %s\n", temp);


  // === PARTIDA ===

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];

  /*
  O `while(1) faz o bot entra num laço infinito, mas não se preocupe. O simulador do jogo irá
  "matar" o seu programa quando o jogo terminar.
  O jogo termina em duas ocasiões:
    1) quando um bot não tiver mais carta (GANHOU!)
    2) quando não tiver mais carta na pilha para comprar.
  Nesse último caso, ganha quem tiver menos cartas na mão. Em caso de mais de um bot ter o menor
  número de cartas na mão, todos eles são considerados os ganhadores.
  */
  while(1) {
    // A primeira coisa fazer é "esperar sua vez".
    // É preciso, então, de um laço enquanto a vez do seu bot não chega.
    do {
      /*
      Enquanto não chega a vez do seu bot, ele estará "escutando" todos os eventos
      do jogo. Estes eventos são repassados para todos os bots em uma linha no formato:
        <ação> <complemento1> [complemento2]
      
      Ou seja, <ação> <complemento1> estão sempre presentes na mensagem do evento, porém
      a presença de [complemento2] vai depender da ação e do complemento1.
      Por exemplo, se um bot descartar um 7 de paus, será gerado o seguinte evento:
        DISCARD 7♣
      A ação é DISCARD e o complemento é 7♣. Portanto, o próximo bot deverá descartar ou
      um 7 (de qualquer naipe) ou uma carta do naipe ♣. Guarde essa informação porque o
      próximo bot poderá ser o seu.
    
      Se a carta descartada for, por exemplo, A♣ (Ás = muda de cor), haverá um segundo
      complemento com o naipe a ser seguido pelos próximos jogadores. Por exemplo: no
      evento "DISCARD A♣ ♥", o próximo bot deverá então descartar alguma carta do naipe ♥.

      O valor da carta descartada pode também pedir uma ação do próximo jogador. Por
      exemplo, se for descartado o V (valete = compre 2), a primeira ação do próximo
      bot (pode ser o seu) deverá ser obrigatoriamente "BUY 2", sob pena do bot ser
      eliminado da partida.
      */

      scanf("%s %s", action, complement);
      // obs: um segundo scanf pode ser realizado par ler o 2º complemento.

      /*      
      Há um evento especial que não é gerado pelos outros bots, mas pelo simulador.
      Ele tem o formato: "TURN <id>".
      O simulador envia esta mensagem quando for a vez do bot de identificador <id>.
      Então, termine este laço interno quando for a vez do seu bot agir.
      */
    } while (strcmp(action, "TURN") || strcmp(complement, my_id));
    
    // agora é a vez do seu bot jogar
    debug("----- MINHA VEZ -----");
    
    /*
    Seu bot realiza uma ação no jogo enviando para a saída-padrão uma string no formato:
      <ação> <complemento1> [complemento2]

    Por exemplo, se o bot anterior soltar uma carta de compra (compre 2 ou compre 4), a
    <ação> que seu bot deve fazer é "BUY" e o <complemento1> será "2" ou "4", dependendo da
    quantidade de cartas que ele deve comprar.
    Ou seja, a string que seu bot deve enviar para a saída-padrão será:
    - "BUY 4", se o bot anterior soltou um Coringa (C), ou;
    - "BUY 2", se o bot anterior soltou um Valete (V).
    Depois do envio desta ação, o simulador irá enviar para o seu bot uma quantidade de cartas
    correspondente ao número solicitado. Então, prepare-se para ler da entrada padrão as cartas.
    Se a ação for "BUY 2", leia duas strings. Elas serão as cartas compradas e você deve
    guardá-las na sua mão. Se for "BUY 4", leia 4 strings.
    Depois da leitura, termina a vez do seu bot e o simulador passa a vez para um outro bot.

    Caso não tenha nenhuma ação de compra a ser realizada, seu bot deve jogar normalmente,
    que é descartar uma carta cujo valor ou naipe é o mesmo da carta da mesa. Ou seja, você
    deve saber qual a última carta descartada ou, se foi um Ás ou Coringa, qual o naipe
    solicitado.

    No exemplo abaixo, a <ação> é "DISCARD" e o <complemento1> é a carta a ser descartada:
      "DISCARD 2♣"

    O bot também pode descartar uma carta especial, independente do naipe da mesa, que pode
    ser um Ás (A = muda de naipe) ou um Coringa (C = além de fazer o próximo comprar 4,
    também muda o naipe). As demais cartas devem obrigatoriamente seguir o naipe da mesa.

    Ao descartar um Ás ou Coringa, você deve enviar um segundo complemento para sua ação com
    o naipe que você deseja. Por exemplo:
      "DISCARD C♣ ♥"
    Neste caso, seu bot soltou um coringa preto e pediu para o naipe mudar para ♥ (o próximo
    jogador precisar comprar 4 cartas e o seguinte levar em conta que o ♥ é o naipe da vez).
    Depois do descarte, a vez do seu bot termina.

    Se o bot não tiver carta com o naipe da mesa para descartar, ele deve comprar uma carta
    do baralho, enviando a ação "BUY" e o complemento "1", informando que ele irá comprar uma
    carta da pilha.
    Assim como as ações "BUY 2" e "BUY 4", após o envio desta ação, seu bot deve ler da
    entrada-padrão a carta puxada da pilha e guarde na sua mão.

    Vale ressaltar que nada impede do bot comprar quantas cartas quiser, mesmo tendo uma carta
    na mão com o valor ou naipe da mesa. Só não é possível comprar uma quantidade diferente de
    cartas quando ele deve obrigatoriamente comprar 2 (por causa de um Valete) ou 4 (por causa
    de um coringa).

    Depois da carta lida, não há opção de descarte. Agora, é a vez de um outro bot jogar.

    Além das ações de descartar (DISCARD) e comprar (BUY), o bot pode também enviar mensagens
    para serem apresentadas no jogo. Essas mensagens não são repassadas para os outros bot, mas
    aparecem no console. Para enviar uma mensagem, o bot deverá enviar para a saída-padrão o
    seguinte comando:
      SAY <text>

    O bot pode enviar quantas mensagens quiser, desde que seja *ANTES* das ações de descarte ou
    de compra. Alguns exemplos de mensagens são:
      "SAY Caramba! Eu já ia bater!"
      "SAY Tu tá lascado!!!"

    Resumindo, o bot pode realizar uma das seguintes ações:
    - "SAY <text>", onde <texto> é uma mensagem que irá aparecer durante a partida.
    - "DISCARD <card> [naipe]", onde <card> é a carta da mão a ser descartada.
      Se <card> for um Coringa (C) ou Ás (A), um naipe deve ser informado também.
    - "BUY <num>", onde <num> é a quantidade de cartas a serem compradas da pilha.

    Exemplos:
      DISCARD 4♥
      DISCARD A♣ ♥
      SAY Droga!
      BUY 2
      BUY 4
      BUY 1

    OBS: Todas as mensagens enviadas **DEVEM terminar com salto de linha ('\n')**, caso
         contrário, o simulador não saberá quando uma ação termina e quebrar o sincronização
         das mensagens.

    Qualquer ação enviada para o simulador que não seja condizente com o estado do jogo,
    haverá uma penalidade para o bot.
    - Se o bot descartar uma carta que não tem na mão ou se o naipe da carta não for o que
      se encontra sobre a mesa, a ação será ignorada. Ou seja, para o simulador, o bot
      continuará com a referida carta na mão.
    - Se o bot precisar comprar 2 ou 4 cartas e não enviar a ação "BUY" com o complemento
      correspondente, o bot sai do jogo e perde de vez a partida. 
    
    Outra penalidade é se o bot demorar mais de 3 segundos para responder uma ação. Isso
    significa que a leitura e escrita dos dados está fora de sincronia com o simulador
    (o bot esperando um dado do simulador e o simulador esperando um dado do bot).
    Nesse caso, o bot também será removido da partida.
    */

    // Nesse exemplo de ação, o bot tenta descartar a carta 4♥.
    // Se ele não tiver na mão, a ação é simplesmente ignorada.
    char card[] = "A♥ ♥";
    printf("DISCARD %s\n", card);
  }

  return 0;
}