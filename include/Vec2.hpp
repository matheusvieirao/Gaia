#ifndef VEC2_H
#define VEC2_H


class Vec2 {
    public:
        Vec2();
        Vec2(float x, float y);
        Vec2 operator-(const Vec2&) const;
        Vec2 operator+(const Vec2&) const;
        Vec2 operator*(const float n) const;
        Vec2 Soma(const Vec2& v) const;
        Vec2 Subtracao(const Vec2& v) const;
        Vec2 Multiplicacao(float n) const;
        float Magnitude() const;
        Vec2 Normalizado() const;
        float DistanciaVets(const Vec2& v) const;
        float InclinacaoX() const; //conferir quadrantes 2 e 3
        float InclinacaoReta(const Vec2& v) const;
        Vec2 Rotate(float teta) const; //em radianos
        Vec2 MoveTo(const Vec2& v, float mag); //move o vec atual em direcao ao vec passado por parametro. multiplica a direcao por mag. retorna o ponto final a que se deseja mover.
        Vec2 CardToIsometric(float tile_width, float tile_height) const; //pega um valor que está na matriz do mapa e transforma em uma coordenada x,y da tela (do canto superior esquerdo do tile)
        Vec2 CardToIsometricCenter(float tile_width, float tile_height) const; //pega um valor que está na matriz do mapa e transforma em uma coordenada x,y da tela (do centro do tile)
        Vec2 IsometricToCard(float tile_width, float tile_height) const; //pega uma coordenada x,y da tela e transforma em um valor que é usado na matriz do mapa (de 0 a n-1 sendo n o tamanho da dimensão)
        float x;
        float y;
        virtual ~Vec2();
    private:
};

#endif // VEC2_H
