#ifndef GUARDAOBSERVADOR_H
#define GUARDAOBSERVADOR_H

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
#include "Collision.hpp"
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

class GuardaObservador : public GameObject{
    public:
        enum GuardaObservadorEstado{VIGILIA_PARADO, VIGILIA_ANDANDO, PERSEGUINDO, ATACANDO};
        GuardaObservador(std::vector<Vec2> coord, int gaia_comodo, TileMap* t_map);
        virtual ~GuardaObservador();
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
		
        bool EstaNaVisao(Vec2 gaia_t_pos);

    private:
        Sprite sp;
        int hp;
        Timer tempo_estado;
        Timer pausa;
        GuardaObservadorEstado estado_atual;
        Rect box_anterior;
        Sound som_chicote_hit;

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

        //usadas no estado de vigilia
        std::vector<Vec2> coord_vet; //vetor com todos os pontos em que o observador passa durante a vigilia. os pontos sao percorridos em ordem e dps voltam ao inicio (ex: 0, 1, 2, 3, 0, 1...)
        int coord_vigilia_atual;
};

#endif // GUARDAOBSERVADOR_H
