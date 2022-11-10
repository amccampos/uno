# Uno

Vídeo de apresentação do projeto:
https://www.loom.com/share/6dd991e2abef48618560d80ae4c8bfdb

## Introdução

Esta é uma versão do jogo de baralho Uno, com algumas diferenças:

A primeira é que este é um jogo baseado em turnos. Ou seja, um jogador só age quando for sua vez. Logo, não haverá a opção de gritar "UNO" quando um jogador tiver apenas uma carta. Essa regra foi deixada de fora.

A segunda é que ele é jogado com as cartas do baralho tradicional. Ou seja, ao invés de  cores, teremos naipes (copas, espadas, ouro e paus) e, ao invés de cartas especiais (como "Compre duas" ou "Passe a vez"), teremos cartas do baralho como Valete, Damas, Rei, Ás e Coringa. Estas cartas substituem as cartas especiais do Uno, seguindo a correspondência:
* "COMPRE 4"   : C = CORINGA
* "COMPRE 2"   : V = VALETE
* "VOLTA"      : D = DAMA
* "PULA A VEZ" : R = REI
* "MUDE A COR" : A = ÀS (muda o naipe)

A partida será jogada com um único baralho. Assim, teremos quatro cartas de um valor. Por exemplo, 7♥, 7♦, 7♣, 7♠, com exceção do coringa, que há apenas dois: um vermelho e um preto. Porém, para seguir o padrão das cartas, os coringas terão também um naipe, mas serão apenas dos naipes: ♥ (vermelho) e ♣ (preto).

O jogo é gerenciado por um "simulador" que irá controlar o jogo, dando a vez ao bot da rodada. O bot deve ler os dados da entrada-padrão (scanf) no formato especificado pelo simulador, caso contrário ele se perderá e será eliminado da partida. O bot também deve enviar suas ações para o simulador via saída-padrão (printf) no formato esperado pelo simulador, novamente sob pena de ser eliminado da partida.

As cartas do baralho sempre são no formato "ValorNaipe".
Nesse formato, Valor é um dos valores das cartas tradicionais, ou seja, A, 2, 3, 4, 5, 6, 7, 8, 9, 10, V, D, R e C, e Naipe é um dos seguintes naipes: ♥, ♦, ♣, ♠.

Os naipes são caracteres no formato ascii estendidos, que possuem uma representação maior que um byte (char). Isso significa que eles deve ser tratados como se fossem strings.

A lógica apresentada nesse template visa ilustrar a entrada e saída de dados de um bot. Cabe a você aprimorar a lógica das ações do seu bot.

Bom jogo!!!

## Executando o jogo

O gerenciador do jogo Uno se encontra no formato binário do Linux. Então, você precisará executá-lo sobre esse sistema operacional. Se seu computador for Windows, poderá usar o [WSL](https://learn.microsoft.com/pt-br/windows/wsl/install).

Caso não tenha o WSL, nem queira instalá-lo, você poderá executar o jogo também via replit. Assim, você pode tanto baixar os arquivos do github e trabalhar localmente, quanto acessar e trabalhar remotamente pelo replit, como descrito a seguir.

### Trabalhando localmente

Para trabalhar no seu projeto localmente, instale o git (caso não já tenha) e crie um clone do projeto (ou faça um fork) digitando a seguinte linha no terminal (linux):

```sh
git clone https://github.com/amccampos/uno
```

Você encontrará 6 arquivos:
- `readme.md`: este arquivo.
- `bot_A.c`: template inicial com explicações para a criação de um bot.
- `bot_B.c`: contém o mesmo conteúdo de `bot_A.c`, permitindo ter um backup das explicações.
- `bot_A`: executável com um comportamento básico para fins de teste.
- `bot_B`: mesmo executável `bot_A`, mas outro nome para você poder colocar um para jogar com o outro.
- `uno`: programa gerenciador do jogo Uno.

Os arquivos `uno`, `bot_A` e `bot_B` são executáveis no formato do linux (não funcionam em outro S.O.). Você deve trabalhar, portanto, no Linux ou no WSL (sobre o Windows).

Para ter uma ideia do funcionamento do jogo, chame o programa `uno` passando como parâmetro os dois programas-bot que irão jogar na partida.

```sh
./uno bot_A bot_B
```

O console apresentará a sequência de ações realizadas pelos bots.

Para construir teu projeto, edite um dos arquivos `bot_A.c` ou `bot_B.c`. Estes arquivos são templates de um bot rudimentar, mas com instruções preciosas para você começar a implementar teu próprio bot. O arquivo compila e executa normalmente, usando, por exemplo:

```sh
gcc bot_A.c -o bot_A
```

Com esse comando, uma nova versão do programa `bot_A` é gerada e pode ser testada com `./uno bot_A bot_B`. Porém, como você verá, o comportamento é simples. O único comportamento que ele tem é descartar a carta A♥ na sua vez. Cabe a você melhorá-lo.

Lembre-se de organizar tua solução em diferentes funções e separando em diferentes módulos (arquivos .c e .h). Você pode, por exemplo, ter um módulo só com operações sobre as cartas do baralho, outro com as funções de raciocínio sobre as cartas que os outros jogadores têm na mão, entre outros.

### Trabalhando no replit

Antes de qualquer coisa, quem for trabalhar no replit terá que criar um fork do projeto que se encontra em https://replit.com/@amccampos/uno. O botão "Fork Repl" fará isso.

Os mesmos encaminhamentos fornecidos para quem for trabalhar localmente são válidos para quem for trabalhar no replit, visto que há também um terminal Linux sobre o qual você poderá trabalhar.

A principal diferença é que você não precisará instalar nada. Além disso, o botão "Play" do projeto está configurado para executar o comando:
```sh
./uno bot_A bot_B
```

Ao clicar no Play, uma nova partida será executada com os bots `bot_A` `bot_B`, levando em conta que eles já foram compilados. A responsabilidade de gerar o executável do seu bot é sua. Portanto, **sempre que você fizer uma alteração no código-fonte de seu bot, certifique-se de compilá-lo antes de clicar no botão Play**.

A forma de compilar é idêntica à compilação de quem trabalha localmente:

```sh
gcc bot_A.c -o bot_A
```
