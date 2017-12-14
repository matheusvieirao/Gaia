#include "Velhor.hpp"

#include "State.hpp"
#include "Game.hpp"
#include "Gaia.hpp"
#include "Camera.hpp"
#include "Gaia.hpp"
#include <iostream>

Velhor::Velhor(float x, float y, int comodo){

    sp_levitando.Open("img/velho_levitando.png");
    sp_levitando.SetFrameTotal(12);
    sp_levitando.SetFrameStart(7);
    sp_levitando.SetFrameAnimation(6);
    sp_levitando.SetFrameTime(0.3);
//    sp_levitando.SetScaleX(0.8);
//    sp_levitando.SetScaleY(0.8);


    altura_pe = 19;
    largura_box_col = 78;
    altura_box_col = 40;
    box.x = x - sp_levitando.GetWidth()/2;
    box.y = y - sp_levitando.GetHeight() + altura_pe;
    box.w = sp_levitando.GetWidth();
    box.h = sp_levitando.GetHeight();

    comodo_atual = comodo;

}

Velhor::~Velhor(){
    //dtor
}

void Velhor::Update(float dt){
    sp_levitando.Update(dt);
}

void Velhor::Render(){
    sp_levitando.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
}

int Velhor::GetAlturaPe(){
    return(altura_pe);
}


void Velhor::NotifyCollision(GameObject& other){
}

bool Velhor::Is(std::string type){
    return(type == "Velhor");
}

bool Velhor::IsDead(){
    return(false);
}
