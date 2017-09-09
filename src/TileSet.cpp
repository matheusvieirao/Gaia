#include "iostream"
#include "TileSet.hpp"

TileSet::TileSet(int columns, int rows, int tile_floor_height, std::string file):tile_set(file){
    tile_height = tile_set.GetHeight() / rows;
    tile_width = tile_set.GetWidth() / columns;
    this->columns = columns;
    this->rows = rows;
    if(tile_floor_height <= 0){
        this->tile_floor_height = tile_height;
    }
    else{
        this->tile_floor_height = tile_floor_height;
    }

}

void TileSet::Render(int index, int x, int y){
    int x_clip;
    int y_clip;

    y = y + tile_floor_height - tile_height; //transforma o y que recebe que esta na altura maxima do piso na altura maxima da parede

    if(index >= 0 && index < rows*columns) {
            x_clip = (index % columns) * tile_width;
            y_clip = index / columns * tile_height;
            tile_set.SetClip(x_clip, y_clip, tile_width, tile_height);
            tile_set.Render(x, y, 0);
    }
}

int TileSet::GetTileWidth(){
    return(tile_width);
}

int TileSet::GetTileHeight(){
    return(tile_floor_height);
}

int TileSet::GetTileTotalHeight(){
    return(tile_height);
}
