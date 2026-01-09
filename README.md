# CUB3D


REQUISITOS CUB3D

RayCaster com a miniLibX

minimizar, etc.
• Exiba texturas de paredes diferentes (a escolha é sua) que variem dependendo da
direção da parede vista (Norte, Sul, Leste, Oeste).

Seu programa deve permitir configurar as cores do chão e do teto como duas cores
diferentes.

• O programa exibe a imagem numa janela e respeita as seguintes regras:
    ◦ As setas esquerda e direita do teclado devem permitir que você olhe para a
    esquerda e para a direita no labirinto.
    ◦ As teclas W, A, S, e D devem permitir que você mova o ponto de vista através
    do labirinto.
    ◦ Pressionar ESC deve fechar a janela e encerrar o programa de forma limpa.
    ◦ Clicar no X vermelho na borda da janela deve fechar a janela e encerrar o
    programa de forma limpa.
    ◦ The use of images of the minilibX library is strongly recommended.

• Seu programa deve receber como primeiro argumento um arquivo de descrição de
    cena com a extensão .cub.
    ◦ O mapa deve ser composto somente de 6 caracteres possíveis: 0 para um espaço
    vazio, 1 para uma parede, e N,S,E ou W para a posição inicial do jogador e
    orientação de spawn.
    Este é um mapa simples válido:
    111111
    100101
    101001
    1100N1
    111111
    ◦ O mapa deve ser fechado/cercado de paredes, se não o programa deve retornar
    um erro.
    ◦ Exceto pelo conteúdo do mapa, cada tipo de elemento deve ser separado por
    uma ou mais linhas vazias.
    ◦ Exceto pelo conteúdo do mapa, que deve sempre ser o último, cada tipo de
    elemento pode ser escrito em qualquer ordem no arquivo.
    ◦ Exceto pelo mapa, cada tipo de informação de um elemento pode ser separado
    por um ou mais espaços.
    ◦ O mapa deve ser parseado como ele aparece no arquivo. Espaços são uma
    parte válida do mapa e cabe a você lidar com eles. Você deve conseguir parsear
    qualquer tipo de mapa, desde que ele respeite as regras do mapa.
    ◦ Exceto pelo mapa, cada elemento deve começar com seu identificador de tipo
    (composto por um ou dois caracteres), followed by its specific information in
    a strict order:

∗ Textura Norte:
    NO ./path_to_the_north_texture
    · identificador: NO
    · caminho para a textura norte

∗ Textura Sul:
    SO ./path_to_the_south_texture
    · identificador: SO
    · caminho para a textura sul

∗ Textura Oeste:
    WE ./path_to_the_west_texture
    · identificador: WE
    · caminho para a textura oeste

∗ Textura Leste:
    EA ./path_to_the_east_texture
    · identificador: EA
    · caminho para a textura leste

∗ Cor do chão:
    F 220,100,0
    · identificador: F
    · cores R,G,B no intervalo [0,255]: 0, 255, 255

∗ Cor do teto:
    C 225,30,0
    · identificador: C
    · cores R,G,B no intervalo [0,255]: 0, 255, 255
    ◦ Exemplo de uma parte obrigatória com uma cena .cub minimalista:

NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111

◦ Se qualquer tipo de falha de configuração for encontrada no arquivo, o pro-
grama deve sair corretamente e retornar 

"Error\n"seguido de uma mensagem de erro explícita de sua escolha.