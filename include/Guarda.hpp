#ifndef GUARDA_H
#define GUARDA_H

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
#include "Vec2.hpp"
#include "Celula.hpp"
#include "State.hpp"
#include "Sound.hpp"
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
        enum GuardaEstado{DESCANSANDO_PARADO, DESCANSANDO_ANDANDO, PERSEGUINDO, ATACANDO, PARADO_AUTOMATICO, MOVIMENTO_AUTOMATICO, VIGIANDO_PORTA};
        Guarda(float x, float y, GuardaEstado estado_inicial, int gaia_comodo, std::string nome);
        virtual ~Guarda();
        void Update(float dt);
        void Render();
        int GetAlturaPe();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
        bool IsDead();
        void PushMovimento(int mov); //para andar no automatico
        // int MaiorDistancia(Vec2 gaia_t_pos);
        // void AcharComodo();
        // void SetPause(bool pausar);

        //Usadas para o Algoritmo A*
        int CalcularCaminho(Vec2 gaia_t_pos, TileMap* t_map);
        float QuantoFalta(int x, int y);
        bool VerificarMapa(int x, int y, int map_width, int map_height);
        void InserirOrdenado(int x, int y, Celula *cel_aux);

        bool TileAndavel(Vec2 pos); //recebe uma posicao (sem ser a posicao do tile, a posicao original do box) e ve se nesse tile o personagem pode andar
        void CalcularMovimentoAtual(TileMap* t_map);
        void Andar(float vel); //Anda em direção a guarda_pos_desejada
		
        void AndarAleatorio(TileMap* t_map);
        bool EstaNaVisao(Vec2 gaia_t_pos);

        /////////////////////////// void EncontraNoMesmoTile(Vec2 gaia_pos, Vec2 guarda_pos);
        // void DrawRectangle(int x1, int y1, int x2, int y2);
        // void DrawRectangleX(int x1, int y1, int x2, int y2);
        // void DrawRectangle(Vec2 v);
        // void DrawRectangleX(Vec2 v);

    private:
        Sprite sp_andando;
        Sprite sp_morrendo;

        std::string nome;
        int hp;
        Timer tempo_estado;
        Timer pausa;
        GuardaEstado estado_atual;
        Rect box_anterior;
        Sound som_chicote_hit;

        //////////////////////// int andar_n_tiles;
        // int contador_fuga;
        bool mov_automatico; //usada para andar no automatico


        //std::vector<int> movimentos;

        //Variaveis utilizadas para o algoritmo de busca A*, (CalcularCaminho, QuantoFalta, VerificarMapa, InserirOrdenado)
        std::vector<Celula*> celulas; 
        std::vector<Celula*> celulas_nao_checadas;
        int x_destino;
        int y_destino;
        std::vector<int> caminho; //coordenadas que o guarda deve tomar para chegar ate a Gaia
        std::vector<int> mapa_aux; // é Utilizada em CalcularCaminho e VerificarMapa

        int movimento_atual;
        int movimento_anterior; //utilizado na função Andar para ver quando inicializar uma nova animação
        Vec2 guarda_pos;
        Vec2 guarda_t_pos;
        Vec2 guarda_pos_desejada;
        Vec2 guarda_t_pos_desejada;
        bool calcular_proximo_passo;

        bool acabou_de_entrar_no_estado;

};

#endif // GUARDA_H
