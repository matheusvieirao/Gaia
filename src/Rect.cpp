#include "Rect.hpp"


Rect::Rect() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

Rect::~Rect() {
    //dtor
}

Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect::operator+(const Vec2& v){
    return(Rect(this->x+=v.x, this->y+=v.y, this->w, this->h));
}

void Rect::operator+=(const Vec2& v){
    this->x += v.x;
    this->y += v.y;
}

void Rect::SomaVet(const Vec2& v){
    this->x += v.x;
    this->y += v.y;
}

bool Rect::IsInside(float a, float b) const{
    return(a>=x && a<=(x+w) && b>=y && b<=(y+h));
}

Vec2 Rect::GetCenter() const{
    return(Vec2(x+w/2, y+h/2));
}

void Rect::NovoCentro(float x, float y){
    this->x = x - w/2;
    this->y = y - h/2;
}

float Rect::DistanciaRects(Rect rect){
    Vec2 v1 = Vec2(this->GetCenter().x, this->GetCenter().y);
    Vec2 v2 = Vec2(rect.GetCenter().x, rect.GetCenter().y);
    return(v1.DistanciaVets(v2));
}

