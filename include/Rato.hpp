#ifndef RATO_HPP
#define RATO_HPP

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "TileMap.hpp"
#include "Sound.hpp"

#define S   1
#define SE  2
#define L   3
#define NE  4
#define N   5
#define NO  6
#define O   7
#define SO  8
#define PARADO 9

class Rato : public GameObject{
    public:
        Rato(float x, float y, bool chave);
        virtual ~Rato();
        void Update(float dt);
        int AndarAleatorio(float vel, Vec2 rato_t_pos, TileMap* t_map);
        void Andar(float vel, TileMap* t_map);
        void PararParaTras();
        int CalcularFulga(Vec2 rato_t_pos, Vec2 gaia_t_pos, TileMap* t_map);
        int MaiorDistancia(Vec2 rato_t_pos, Vec2 gaia_t_pos);
        void Render();
        int GetAlturaPe();
        void PushMovimento(int mov);
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
        bool IsDead();
    private:
        Sprite sp;
        Sprite sp_chave;
        enum RatoEstado{DESCANSANDO_PARADO, DESCANSANDO_ANDANDO, ESPREITA, FUGINDO};
        RatoEstado estado_atual;
        int movimento_atual;
        int movimento_anterior;
        int hp;
        int andar_n_tiles;
        bool chave;
        Timer tempo_estado;
        Timer tempo_som;
        Sound som;
        Sound som_item;
};

#endif // RATO_HPP
