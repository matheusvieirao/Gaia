#ifndef VELHOR_H
#define VELHOR_H

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
#include "Vec2.hpp"
#include "Celula.hpp"

#define S   1
#define SE  2
#define L   3
#define NE  4
#define N   5
#define NO  6
#define O   7
#define SO  8
#define PARADO 9

class Velhor : public GameObject{
    public:
        Velhor(float x, float y, int comodo);
        virtual ~Velhor();
        void Update(float dt);
        void Render();
        void Andar(float vel, TileMap* t_map);
        void AcharComodo();
        int GetAlturaPe();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
        bool IsDead();
    private:
        std::string nome;
        Sprite sp_levitando;
        Sprite sp_aparecendo;
        Sprite sp_desaparecendo;
};

#endif // GUARDA_H
