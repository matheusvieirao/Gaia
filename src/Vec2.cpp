#include "math.h"
#include "Vec2.hpp"
#include <stdio.h>

Vec2::Vec2() {
    x = 0;
    y = 0;
}

Vec2::Vec2(float a, float b) {
    x = a;
    y = b;
}

Vec2 Vec2::operator+(const Vec2& other) const{
    return Soma(other);
}

Vec2 Vec2::operator-(const Vec2& other) const{
    return Subtracao(other);
}

Vec2 Vec2::operator*(float n) const{
    return Multiplicacao(n);
}

Vec2 Vec2::Soma(const Vec2& v) const {
    return(Vec2(x+v.x, y+v.y));
}

Vec2 Vec2::Subtracao(const Vec2& v) const{
    return(Soma(Vec2(-v.x, -v.y)));
}

Vec2 Vec2::Multiplicacao(const float n) const{
    return(Vec2(x*n, y*n));
}

float Vec2::Magnitude() const{
    return(sqrt((x*x)+(y*y)));
}

Vec2 Vec2::Normalizado() const{
    float mag = Magnitude();
    return(Vec2(x/mag ,y/mag));
}

float Vec2::DistanciaVets(const Vec2& v) const{
    Vec2 v_aux = Subtracao(v);
    return(v_aux.Magnitude());
}

float Vec2::InclinacaoX() const{
    return(atan2(y,x));
}

//o parametro é a posicao final do vetor
float Vec2::InclinacaoReta(const Vec2& v) const{
    Vec2 v_aux = v.Subtracao(*this);
    return(v_aux.InclinacaoX());
}

Vec2 Vec2::Rotate(float teta) const{
    return(Vec2(x * cos(teta) - y * sin(teta),   y * cos(teta) + x * sin(teta)));
}

Vec2 Vec2::MoveTo(const Vec2& v, float mag){
    Vec2 v_aux = v.Subtracao(*this);
    return(Soma(v_aux.Multiplicacao(mag)));
}

//retorna o canto superior esquerdo do tile
Vec2 Vec2::CardToIsometric(float tile_width, float tile_height) const{
    float x_novo = (x - y) * tile_width / 2;
    float y_novo = (x + y) * tile_height /2;
    return (Vec2(x_novo, y_novo));
}

//retorna o centro do tile
Vec2 Vec2::CardToIsometricCenter(float tile_width, float tile_height) const{
    float x_novo = (x - y) * tile_width / 2;
    float y_novo = (x + y) * tile_height /2;
    x_novo += tile_width/2;
    y_novo += tile_height/2;
    return (Vec2(x_novo, y_novo));
}

//retorna a coordenada do tile
Vec2 Vec2::IsometricToCard(float tile_width, float tile_height) const{
    float x_novo = (x-tile_width/2) / (tile_width/2) ;
    float y_novo = (y-tile_height/2) / (tile_height/2) ;

    float x_aux = (y_novo + x_novo)/2;
    float y_aux = (y_novo - x_novo)/2;

    //arredondar
    if(x_aux - floor(x_aux) < 0.5555555555){
        x_novo = floor(x_aux);
    }
    else {
        x_novo = ceil(x_aux);
    }
    if(y_aux - floor(y_aux) < 0.5555555555){
        y_novo = floor(y_aux);
    }
    else {
        y_novo = ceil(y_aux);
    }
    return (Vec2(x_novo, y_novo));
}

Vec2::~Vec2() {
    //dtor
}
