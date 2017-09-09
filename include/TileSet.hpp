#ifndef TILESET_H
#define TILESET_H

#include <string>
#include "Sprite.hpp"

/**
* TileSet::TileSet Recebe o numero de linhas e colunas de um tile set e descobre a largura e a altura de cada tile e se no tile a altura do chao for diferente da altura total seta ela também.
*   @var int columns: quantas colunas tem no tile set.
*   @var int rows: quantas linhas tem no tile set.
*   @var int floor_heigh: qual é a altura do chão do tile (de baixo pra cima) em pixels. Se menor ou igual a 0 a altura do chão é a altura do tile.
*   @var std::string file: Caminho do arquivo de tiles.
*
* TileSet::Render Renderiza 1 tile especificado por index na posição (x,y), x e y são recebidos em coordenadas cardenais globais (com o deslocamento da camera)
*   @var int index: numero referente ao tile (de 0 a numero_de_tiles-1).
*   @var int x: posição da latitude a redenderizar o tile na tela.
*   @var int x: posição da longitude a redenderizar o tile na tela.
*
* TileSet::GetTileWidth Retorna a largura de um tile.
*
* TileSet::GetTileHeight Retorna a altura de um tile.
*
* @var Sprite tile_set: imagem dos vários tiles juntos.
* @var int rows: numero de linhas de tiles na imagem.
* @var int columns: numero de colunas de tiles na imagem.
* @var int tileWidth: Largura de um tile.
* @var int tileHeight: Altura de um tile.
**/

class TileSet{
    public:
        TileSet(int columns, int rows, int floor_heigh, std::string file);
        void Render(int index, int x, int y);
        int GetTileWidth();
        int GetTileTotalHeight();
        int GetTileHeight();
    private:
        Sprite tile_set;
        int rows;
        int columns;
        int tile_width;
        int tile_height;
        int tile_floor_height;
};

#endif // TILESET_H
