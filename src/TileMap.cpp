#include <iostream>
#include <fstream>
#include <string>
#include "Game.hpp"
#include "TileMap.hpp"
#include "Camera.hpp"
#include "Vec2.hpp"

TileMap::TileMap(std::string file, TileSet* tile_set){
    this->tile_set = tile_set;
    Load(file);
}


void TileMap::Load(std::string file){
    std::ifstream fp;
    char c;
    int num_aux, parar;

    fp.open(file, std::ios::in);
    if(fp.is_open()){
        fp >> map_width >> c >> map_height >> c >> map_depth >> c ;
        parar = map_width*map_height*map_depth;
        while(!fp.eof() && parar > 0){
            fp >> num_aux >> c;
            tile_matrix.push_back(num_aux-1); //reduz de menos 1 porque no arquivo que temos 0 representa a ausencia de tiles, e nao -1
            parar--;
        }
    }
    else {
        std::cout << "Mix_OpenAudio falhou. - Game::Game" << std::endl;
    }
    fp.close();
}

void TileMap::SetTileSet(TileSet* tile_set){
    this->tile_set = tile_set;
}

int& TileMap::At(int x, int y, int z){
    int num_aux = 0;

    num_aux = z * map_width*map_height; //encontrar posicionamento inicial da camanda no vetor tile_matrix
    num_aux += y * map_width;
    num_aux += x;
    return(tile_matrix[num_aux]);

}

void TileMap::RenderLayer(int layer, int camera_x, int camera_y){
    int i, j, k, tile_width, tile_height, tile_total_height, window_width, window_height;
    Vec2 v;

    if(layer >= GetDepth()){
        std::cout << "TileMap esta tentando renderizar uma camada de tile que nao existe - TileMap::RenderLayer(int int int)" << std::endl;
    }

    tile_width = tile_set->GetTileWidth();
    tile_height = tile_set->GetTileHeight();
    tile_total_height = tile_set->GetTileTotalHeight();
    window_width = Game::GetInstance().GetWindowWidth();
    window_height = Game::GetInstance().GetWindowHeight();
    i = map_width*map_height*layer; //encontrar posicionamento inicial da camanda no vetor tile_matrix

    for(j=0; j<map_height; j++){
        for(k=0; k<map_width; k++) {
            v.x = k;
            v.y = j;
            v = v.CardToIsometric(tile_width, tile_height);
            v.x -= camera_x;
            v.y -= camera_y;
            if((v.x>=-tile_width && v.x<=window_width)&&(v.y>=-tile_total_height && v.y<=window_height+tile_total_height)){ //soh renderiza se estiver na tela
                tile_set->Render(tile_matrix[i], v.x, v.y);
            }
            i++;
        }
    }
}


void TileMap::RenderLayer(int layer, int lim_x, int lim_y, int camera_x, int camera_y){
    int i, j, k, tile_width, tile_height, tile_total_height, window_width, window_height;
    Vec2 v;

    if(layer >= GetDepth()){
        std::cout << "TileMap esta tentando renderizar uma camada de tile que nao existe - TileMap::RenderLayer(int int int int int)" << std::endl;
    }

    tile_width = tile_set->GetTileWidth();
    tile_height = tile_set->GetTileHeight();
    tile_total_height = tile_set->GetTileTotalHeight();
    window_width = Game::GetInstance().GetWindowWidth();
    window_height = Game::GetInstance().GetWindowHeight();
    i = map_width*map_height*layer; //encontrar posicionamento inicial da camanda no vetor tile_matrix

    for(j=0; j<map_height; j++){
        for(k=0; k<map_width; k++) {
            if(k>=lim_x && j>=lim_y){
                v.x = k;
                v.y = j;
                v = v.CardToIsometric(tile_width, tile_height);
                v.x -= camera_x;
                v.y -= camera_y;
                if((v.x>=-tile_width && v.x<=window_width)&&(v.y>=-tile_total_height && v.y<=window_height+tile_total_height)){ //soh renderiza se estiver na tela
                    tile_set->Render(tile_matrix[i], v.x, v.y);
                }
            }
            i++;
        }
    }
}

void TileMap::RenderTile(int layer, int t_x, int t_y, int camera_x, int camera_y){
    int i, tile_width, tile_height;
    Vec2 v;

    if(layer >= GetDepth()){
        std::cout << "TileMap esta tentando renderizar uma camada de tile que nao existe - TileMap::RenderTile " << std::endl;
    }

    tile_width = tile_set->GetTileWidth();
    tile_height = tile_set->GetTileHeight();
    i = layer*map_width*map_height + t_y*map_width + t_x;

    v.x = t_x;
    v.y = t_y;
    v = v.CardToIsometric(tile_width, tile_height);
    v.x -= camera_x;
    v.y -= camera_y;
    tile_set->Render(tile_matrix[i], v.x, v.y);
}

void TileMap::Render(int camera_x, int camera_y){
    int i;
    camera_x = 0;
    camera_y = 0;

    for(i = 0; i < map_depth; i++){
        RenderLayer(i, camera_x, camera_y);
    }
}

//sendo x e y ja com o deslocamento da camera
Vec2 TileMap::FindTile(float pos_x, float pos_y){
    float tile_width = tile_set->GetTileWidth();
    float tile_height = tile_set->GetTileHeight();
    Vec2 v(pos_x,pos_y);
    return(v.IsometricToCard(tile_width, tile_height));
}

void TileMap::ChangeTile(int layer, float t_x, float t_y, int nova_info) {
    int indice = layer*map_width*map_height + t_y*map_width + t_x;

    if (t_x>=0 && t_x<map_width && t_y>= 0 && t_y<map_height && indice >= 0 && indice<map_depth*map_width*map_height){
        tile_matrix[indice] = nova_info-1;
    }
}

int TileMap::GetTileInfo(int layer, float t_x, float t_y) {
    int indice = layer*map_width*map_height + t_y*map_width + t_x;
    if (t_x>=0 && t_x<map_width && t_y>= 0 && t_y<map_height && indice>=0 && indice<map_depth*map_width*map_height){
        return (tile_matrix[indice]+1);
    }
    else{
        return(-1);
    }
}

int TileMap::GetWidth(){
    return(map_width);
}

int TileMap::GetHeight(){
    return(map_height);
}

int TileMap::GetDepth(){
    return(map_depth);
}

int TileMap::GetTileWidth(){
    if(tile_set != nullptr){
        return(tile_set->GetTileWidth());
    }
    else{
        return(0);
    }
}

int TileMap::GetTileHeight(){
    if(tile_set != nullptr){
        return(tile_set->GetTileHeight());
    }
    else{
        return(0);
    }
}
