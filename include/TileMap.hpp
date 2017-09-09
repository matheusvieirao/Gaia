#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>
#include "TileSet.hpp"

/**
* TileMap::TileMap seta tile_set e manda o nome do arquivo para Load.
*   @param std::string file: Nome do arquivo txt com o mapa de tiles.
*   @param tile_set: varivel que referencia a classe que contem a imagem de todos os tiles.
*
* TileMap::Load Carrega o mapa de tiles do arquivo texto e coloca em tile_matrix. 0 representa o primeiro tile e -1 representa a ausência de tile.
*   @param tile_set: varivel que referencia a classe que contem a imagem de todos os tiles.
*
* TileMap::SetTileSet seta um novo tile_set.
*   @param std::string file: Nome do arquivo txt com o mapa de tiles.
*
* TileMap::At: recebe x, y, e z que representam a posição do tile em cada dimensão (de 0 a n-1 sendo n o numero de tiles na respectiva dimensão) e retorna uma referencia de sua posição em tileMatrix.
*   @param int x: coordenada do eixo que aponta para o sudeste do tile_set de 0 a n-1 sendo n o numero de tiles na respectiva dimensão.
*   @param int y: coordenada do eixo que aponta para o sudoeste do tile_set de 0 a n-1 sendo n o numero de tiles na respectiva dimensão.
*   @param int z: altura do tile de 0 a n-1 sendo n o numero de tiles na respectiva dimensão.
*
* TileMap::RenderLayer: renderiza uma layer (de 0 a z-1 sendo z o numero de camadas) em uma posicao de camera cameraX e cameraY
*   @param int layer: camada/altura que se deseja renderizar.
*   @param int camera_x: Eixo latitudinal da câmera que será subtraido da posição global.
*   @param int camera_y: Eixo longitudinal da câmera que será subtraido da posição global.
*
* TileMap::RenderTile: Recebe a posicao x,y da matriz de tile e renderiza o tile.
*
* TileMap::Render: Renderiza todas as camadas com auxilio do método RenderLayer
*   @param int camera_x: Eixo latitudinal da câmera que será subtraido da posição global.
*   @param int camera_y: Eixo longitudinal da câmera que será subtraido da posição global.
*
* TileMap::FindTile: Recebe uma posição x,y da tela (já com o deslocamento da câmera) e calcula o tile em que essa posição se encontra.
*   @param int t_x: posicao x na matriz de tiles
*   @param int t_y: posicao y na matriz de tiles
*
* TileMap::GetWidth Retorna map_width que contem a quantidade de tiles no eixo x (eixo sudeste).
*
* TileMap::GetHeight Retorna map_height que contem a quantidade de tiles no eixo y (eixo sudoeste).
*
* TileMap::GetDepth Retorna map_depth que contem a quantidade de tiles no eixo z (eixo da altura).
*
*
* @var std::vector<int> tileMatrix: Vetor com a informação de todos os tiles em todas as dimensões.
* @var TileSet* tile_set: Guarda informações da Classe TileSet que contém as imagens dos tiles.
* @var int map_width: Número de tiles do eixo x (eixo que aponta em direção sudeste).
* @var int map_height: Número de tiles do eixo y (eixo que aponta em direção sudoeste).
* @var int map_depth: Número de tiles do eixo z (eixo que representa a altura. Esse numero vai de 1 a n sendo n o numero de camadas).
**/

class TileMap {
    public:
        TileMap(std::string file, TileSet* tile_set);
        void  Load(std::string file);
        void SetTileSet(TileSet* tile_set);
        int& At(int x, int y, int z);
        void RenderLayer(int layer, int camera_x, int camera_y);
        void RenderLayer(int layer, int lim_x, int lim_y, int camera_x, int camera_y);
        void RenderTile(int layer, int pos_x, int pos_y, int camera_x, int camera_y);
        void Render(int camera_X, int camera_y);
        Vec2 FindTile(float pos_x, float pos_y);
        void ChangeTile(int layer, float t_x, float t_y, int nova_info);
        int GetTileInfo(int layer, float pos_x, float pos_y);
        int GetWidth();
        int GetHeight();
        int GetTileWidth();
        int GetTileHeight();
        int GetDepth();
    private:
        std::vector<int> tile_matrix;
        TileSet *tile_set;
        int map_width;
        int map_height;
        int map_depth;
};

#endif // TILEMAP_H
