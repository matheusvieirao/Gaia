#ifndef STATE_02_INDUSTRIAT_H
#define STATE_02_INDUSTRIAT_H

#include "Game.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "State.hpp"
#include "Vec2.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Timer.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "StateData.hpp"
#include "State_00_Title.hpp"
#include "Collision.hpp"
#include "Gaia.hpp"
//#include "Guarda.hpp"
//#include "StateIndustriaSS.hpp"

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
        void PushInventario(StateData::Item item);
        //static State_02_IndustriaT& GetInstance();
        TileMap* GetTileMap();
        void TrocarDeComodo(Vec2 t_pos, Vec2 t_pos_antiga);
        TileMap* tile_map;
    private:
        enum StateState{JOGO, FALA};
        StateState estado;
        //static State_02_IndustriaT* instance;
        Sprite bg;
        Sprite pause1;
        TileSet* tile_set;
        bool entrou_no_comodo;
        //int comodo_jogador; //0- Producao | 4- Corredor | 8- Dormitorio | 12- Corredor2 | 16- Refeitorio
        int comodo_jogador_antigo;
        StateData data;
        int num_fala;
        int track;
        bool pause;
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
};

#endif // STATESTAGE_H
