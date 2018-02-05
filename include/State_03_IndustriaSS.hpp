#ifndef STATE_03_INDUSTRIASS_HPP
#define STATE_03_INDUSTRIASS_HPP

#include "State.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "Pause2.hpp"
#include "StateData.hpp"
#include "State_02_IndustriaT.hpp"
#include "Gaia.hpp"
#include "State_00_Title.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Vec2.hpp"
#include "Rato.hpp"
#include "Collision.hpp"
#include "Velhor.hpp"

class State_03_IndustriaSS : public State{
    public:
        State_03_IndustriaSS(StateData data);
        virtual ~State_03_IndustriaSS();
        void Update(float dt);
        void Render();
        void InicializarComodo(int comodo);
        void RenderArray();
        void Pause();
        void Resume();
        bool Is(std::string type);
        bool Falar(float delay, std::string arquivo);
        //static State_03_IndustriaSS& GetInstance();
        TileMap* GetTileMap();
        void TrocarDeComodo();
        void PushInventario(StateData::Item item);

        TileMap* tile_map;
    private:
        enum StateState{JOGO, FALA};
        StateState estado;
        //static State_03_IndustriaSS* instance;
        Sprite bg;
        Sprite press_f;
        Sprite pause1;
        TileSet* tile_set;
        //int comodo_jogador; //0- Quarto Velho | 4- Corredor | 8- Deposito | 12- Descarga
        int comodo_jogador_antigo;
        StateData data;
        bool entrou_no_comodo;
        bool printa_f;
        int num_fala;
        int track;
        Timer tempo_falas;
        Timer tempo_esteira;
        Sound fala;
        Sound efeito;
        Sound som_esteira;
        Sound musica1;
        Pause2 pause;
        bool esta_pausado;
};

#endif // State_03_IndustriaSS_HPP
