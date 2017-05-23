# CrossRoads

![Menu Image](/assets/sprites/capa.png)

### Descrição
O jogo é um 2D hack'n slash plataforma, onde o jogador controla um heroi em sua longa aventura.

### Visão Geral
Obejtivo é controlar o personagem por diversas fases, enfrentando seus inimigos em busca do Cálice Mágico. Quando surgem desafios, é necessaria a ajuda, então, controlamos o segundo personagem, que possui diferentes habilidades

### História
Gryth, um grande guerreiro conhecido por todos, vive sua vida em busca de grandes aventuras.. No meio do inverno, ele recebe uma chamada de aventura de Hiron, o grande padre, para uma missão. Nas profundezas da igreja de Pygon, proibida para as pessoas, reside um cálice cujos poderes são gigantescos, mas perigosos. A luta de Gryth é equilibrar seu corpo e mente, e controlar seu poder para derrotar os inimigos no caminho.

----------
## Lista de dependências

* gcc - versão 5.4.0
* g++ - versão 11
* libsdl - versão 2.0.5 (libsdl)
	* sdl_image - versão 2.0.1 dev
	* sdl_mixer - versão 2.0.1 dev
	* sdl_ttf  - versão 2.0.1 dev
* CMake - versão 3.8.1

----------
## Configurando o Jogo

### Instalando as dependências
    sudo apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

### Configurando o Jogo
Download do repositório através do github

    git clone https://github.com/fernand0aguilar/ije-fga-UnB.git

### Compilando 
Utilizando as configurações dos arquivos CmakeList.txt e Makefile

    cd ije-fga-unb
    mkdir build && cd build
    cmake ..
    make
   
#### Execução

    ./game

#### Log de informações

    cat log.txt

----------
### Envolvidos no Projeto

<table>
  <tr>
    <th class="tg-yw4l">Integrante</th>
    <th class="tg-yw4l">Disciplina</th>
    <th class="tg-yw4l">E-mail</th>
    <th class="tg-yw4l">Github</th>
  </tr>
  <tr>
    <td class="tg-yw4l">Fernando Ribeiro</td>
    <td class="tg-yw4l" rowspan="3">Int. Jogos Eletrônicos</td>
    <td class="tg-yw4l">fernando@aguilar.net.br</td>
    <td class="tg-yw4l">fernand0aguilar</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Ulysses Bernard</td>
    <td class="tg-yw4l">ulysses3353@gmail.com</td>
    <td class="tg-yw4l">ulyssesBML</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Caio Nunes</td>
    <td class="tg-yw4l">caiofelipe147@gmail.com</td>
    <td class="tg-yw4l">CaioNunes</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Gustavo Nunes</td>
    <td class="tg-yw4l" rowspan="1">Design de Jogos</td>
    <td class="tg-yw4l">gnaraujo6@gmail.com</td>
    <td class="tg-yw4l">-</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Pedro Neder</td>
    <td class="tg-yw4l" rowspan="1">Musica para Jogos</td>
    <td class="tg-yw4l">caiofelipe147@gmail.com</td>
    <td class="tg-yw4l">-</td>
  </tr>  
</table>

----------

## Controles

* W A S D - Movimentar
* Espaço - Atacar
* Q - Defender
