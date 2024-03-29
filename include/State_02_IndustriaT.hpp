#ifndef STATE_02_INDUSTRIAT_H
#define STATE_02_INDUSTRIAT_H

#include "Pause2.hpp"    
#include "Game.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "State.hpp"
#include "Vec2.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Timer.hpp"
#include "Sound.hpp"
#include "Resources.hpp"
#include "Music.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "StateData.hpp"
#include "State_00_Title.hpp"
#include "Collision.hpp"
#include "Gaia.hpp"
#include "Guarda.hpp"
#include "GuardaObservador.hpp"
#include "State_01_Historia.hpp"
#include "State_03_IndustriaSS.hpp"

//enum mov{ S, SE, L, NE, N, NO, O, SO, PARADO};

class State_02_IndustriaT : public State{
    public:
        State_02_IndustriaT(StateData data);
        virtual ~State_02_IndustriaT();
        void Update(float dt);
        void Render();
        void TratarEncurralamento();
        void InicializarComodo(int comodo);
        bool EstaZonaF();
        void ZonaF();
        void RenderArray();
        void Pause();
        void Resume();
        bool Is(std::string type);
        //static State_02_IndustriaT& GetInstance();
        TileMap* GetTileMap();
        void TrocarDeComodo(Vec2 t_pos, Vec2 t_pos_antiga);
    private:
        enum StateState{JOGO, FALA};
        StateState estado;
        //static State_02_IndustriaT* instance;
        Sprite bg;
        TileSet* tile_set;
        //int comodo_jogador; //0- Producao | 4- Corredor | 8- Dormitorio | 12- Corredor2 | 16- Refeitorio
        int comodo_jogador_antigo;
        int num_fala;
        int track;
        Timer tempo_encurralada;
        Timer tempo_falas;
        Timer tempo_esteira;
        int estado_esteira;
        Sprite sp_press_d;
        Sprite sp_corre;
        int ficou_encurralada;
        Sound musica1;
        Sound musica2;
        Sound musica3;
        Sound fala;
        Sound efeito;
        Sound som_esteira;
        Sound som_ronco;
        Pause2 pause;
        bool esta_pausado;
};

#endif // STATESTAGE_H
