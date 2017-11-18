#ifndef GUARDA_H
#define GUARDA_H

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
#include "Vec2.hpp"
#include "Celula.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Gaia.hpp"
#include <iostream>
#include <math.h>

#define S   1
#define SE  2
#define L   3
#define NE  4
#define N   5
#define NO  6
#define O   7
#define SO  8
#define PARADO 9

class Guarda : public GameObject{
    public:
        enum GuardaEstado{DESCANSANDO_PARADO, DESCANSANDO_ANDANDO, PERSEGUINDO, ATACANDO, PARADO_AUTOMATICO, MOVIMENTO_AUTOMATICO, SAIR};
        Guarda(float x, float y, GuardaEstado estado_inicial, int gaia_comodo, std::string nome);
        virtual ~Guarda();
        void Update(float dt);
        void Render();
        int AndarAleatorio(TileMap* t_map);
        void Andar(float vel, TileMap* t_map);
        int MaiorDistancia(Vec2 gaia_t_pos);
        bool EstaNaVisao(Vec2 gaia_t_pos);
        void AcharComodo();
        int GetAlturaPe();
        void SetPause(bool pausar);
        void PushMovimento(int mov);
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
        bool IsDead();

        int CalcularCaminho(Vec2 gaia_t_pos, TileMap* t_map);
        void CalcularMovimentoAtual();
        float QuantoFalta(int x, int y);
        bool VerificarMapa(int x, int y, int map_width, int map_height);
        void InserirOrdenado(int x, int y, Celula *cel_aux);
        void EncontraNoMesmoTile(Vec2 gaia_pos, Vec2 guarda_pos);
    private:
        std::string nome;
        GuardaEstado estado_atual;
        int movimento_atual;
        int movimento_anterior;
        Vec2 guarda_t_pos;
        Vec2 guarda_t_pos_desejada;
        int hp;
        Timer tempo_estado;
        Sprite sp;
        int andar_n_tiles;
        int contador_fuga;
        Rect box_anterior;
        bool mov_automatico;

        std::vector<Celula*> celulas;
        std::vector<Celula*> celulas_nao_checadas;
        std::vector<int> caminho;
        std::vector<int> mapa_aux;
        std::vector<int> movimentos;
        int x_destino;
        int y_destino;
};

#endif // GUARDA_H
