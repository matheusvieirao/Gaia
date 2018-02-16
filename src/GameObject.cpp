#include "GameObject.hpp"
#include "TileMap.hpp"
#include "Game.hpp"

GameObject::GameObject(){
    rotation = 0;
    altura_pe = 0;
    altura_box_col = 24;
    largura_box_col = 80;
    comodo_atual = -1;
}

GameObject::~GameObject(){
}

int GameObject::GetAlturaPe(){
    return(altura_pe);
}

int GameObject::GetComodoAtual(){
    return(comodo_atual);
}

Rect GameObject::GetBoxColisao(){
    Rect box_colisao;

    box_colisao.x = box.GetCenter().x - largura_box_col/2;
    box_colisao.w = largura_box_col;
    box_colisao.y = box.y + box.h -altura_pe - altura_box_col/2;
    box_colisao.h = altura_box_col;

    return(box_colisao);
}

void GameObject::PushMovimento(int mov){
}

void GameObject::AcharComodo(){
    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();


    if(t_map == nullptr){
        std::cout << "t_map nao pode ser nullptr. - GameObject::AcharComodo"  << std::endl;
        return;
    }

    Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
    for(int i=0; i<t_map->GetDepth(); i=i+4){
        if(t_map->GetTileInfo(i, t_pos.x, t_pos.y) != 0){
            comodo_atual = i;
            break;
        }
    }
}

void GameObject::SetPause(bool pausar){
    pause = pausar;
}
