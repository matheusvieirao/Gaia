#ifndef GAIA_HPP
#define GAIA_HPP

#include <vector>
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "TileMap.hpp"
#include "Sound.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "State_02_IndustriaT.hpp"
//#include "StateIndustriaSS.hpp"
#include "StateData.hpp"

#define S   1
#define SE  2
#define L   3
#define NE  4
#define N   5
#define NO  6
#define O   7
#define SO  8
#define PARADO 9

class Gaia : public GameObject{
    public:
        Gaia(float x, float y, int hp, int poderes, int comodo);
        virtual ~Gaia();
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
        bool IsDead();
        Vec2 GetPos(); //retorna a posicao x, y global (com camera) da gaia.
        Vec2 GetTPos(); //retorna a posicao em tiles da gaia
        int GetDirecao();
        int GetHP();
        void SetPause(bool pausar);
        void SetPoderes(int codigo); // 0: sem poderes | 1: transparente | 2: chicote
        void PushMovimento(int mov);
        void Andar(int mov, float vel);
        //void Transparente();
        bool EstaTransparente();
        void Parar();
        void MudarMovimento();
        static Gaia* player;
        enum SpritesGaia{ANDANDO, ANDANDO_DEVAGAR, CORRENDO, CHICOTE, TRANSPARENTE, CARRO};
        void SetSpriteAtual(SpritesGaia sprite);
        SpritesGaia sprite_atual;
        SpritesGaia sprite_anterior;
    private:
        std::vector<int> vet_mov;
        int mov_anterior;
        int mov_atual;
        Timer dur_movimento;
        Timer tempo_chicote;
        int ataque_chicote;
        Sprite sp_andando;
        Sprite sp_correndo;
        Sprite sp_chicote;
        Sprite sp_transparente;
        Sprite sp_carro;
        bool modo_manual;
        // GameObject::comodo_atual; // se T: 0- Producao | 4- Corredor | 8- Dormitorio | 12- Corredor2 | 16- Refeitorio
        int hp;
        int poderes;
        Vec2 pos_antiga; // x: box.GetCenter().x | y: box.y+box.h-altura_pe);
        Vec2 pos_inicio_comodo;
        int m_dur;
        int m_sudeste;
        int m_nordeste;
        int m_noroeste;
        int m_sudoeste;
        int direcao;
        bool trocou_de_comodo;
        bool primeiro_mov_modo_manual;
        Rect box_anterior;
        Sound som_transparente;
        Sound som_chicote;
        float vel;// * velocidade em pixel por segundo
};

#endif // GAIA_HPP
