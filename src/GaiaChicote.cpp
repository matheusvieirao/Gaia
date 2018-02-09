#include "GaiaChicote.hpp"

GaiaChicote::GaiaChicote(float x, float y){
    is_dead = false;

    altura_pe = 30;
    altura_box_col = 80;
    largura_box_col = 100;

    box.x = x - largura_box_col/2;
    box.y = y - altura_box_col + altura_pe;
    box.w = largura_box_col;
    box.h = altura_box_col*2;
}

GaiaChicote::~GaiaChicote(){
    //dtor
}

void GaiaChicote::Update(float dt){

}

void GaiaChicote::Render(){
    
}


void GaiaChicote::NotifyCollision(GameObject& other){
    
}

bool GaiaChicote::Is(std::string type){
    return(type == "GaiaChicoteChicote" || type == "Chicote");
}

bool GaiaChicote::IsDead(){
    return(is_dead);
}
