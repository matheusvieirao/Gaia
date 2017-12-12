#ifndef RECT_H
#define RECT_H

#include "Vec2.hpp"

/**
* Rect::Rect: Seta as variaveis.
*   @param x float Canto latitudinal superior esquerdo do retangulo.
*   @param y float Canto longitudinal superior esquerdo do retangulo.
*   @param w float Largura do retangulo.
*   @param h float Altura do retangulo.
* Rect::EstaDentro Verifica se um ponto está dentro de Rect.
*   @param x float posição latitudinal
*   @param y float posição longitudinal
*   @return bool true se o ponto (x,y) está dentro de Rect, false se não.
* Rect::Centro: Calcula e retorna o centro do Rect.
*   @return Vec2* Coordenadas do centro do Rect.
* Rect::NovoCentro: Recebe coordenadas do novo centro e calcula e atribui os novos x e y.
*   @param x float com coordenada x do novo centro
*   @param y float com coordenada do y do novo centro
* Rect:DistanciaRects: Calcula e retorna a distancia do centro de dois Rects.
*   @param rect Rect* para o qual se vai calcular a distância.
*   @return float distancia de dois Rects.
*
* @var x float Canto latitudinal superior esquerdo do retangulo.
* @var y float Canto longitudinal superior esquerdo do retangulo.
* @var w float Largura do retangulo.
* @var h float Altura do retangulo.
**/

class Rect {
    public:
        Rect();
        Rect(float x, float y, float w, float h);
        virtual ~Rect();
        Rect operator+(const Vec2& v);
        void operator+=(const Vec2& v);
        void SomaVet(const Vec2& v);
        void SubtraiVet(const Vec2& v);
        bool IsInside(float x, float y) const;
        Vec2 GetCenter() const;
        void NovoCentro(float x, float y);
        float DistanciaRects(Rect rect);
        float x;
        float y;
        float w;
        float h;
};

#endif // RECT_H
