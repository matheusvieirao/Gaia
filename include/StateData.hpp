#ifndef STATEDATA_H
#define STATEDATA_H

#include "Vec2.hpp"
#include <vector>
#include <string>
#include <iostream>

class StateData{
    public:
        StateData();
        StateData(std::string nome);
        void Atribuir(StateData data);
        void Carregar(std::string nome);
        void PrintData();

        int s1_num_historia; //1 é a historia do inicio do jogo e 2 a historia de quando zera
        int state_atual; // 2(State_02_IndustriaT), 3(State_03_IndustriaSS)
        int gaia_comodo; // T: 0- Producao | 4- Corredor | 8- Dormitorio | 12- Corredor2 | 16- Refeitorio // SS: 0- Quarto Velho | 4- Corredor | 8- Deposito | 12- Descarga
        Vec2 gaia_t_pos;
        Vec2 gaia_t_pos_antiga;
        Vec2 gaia_t_pos_inicio_comodo; // é utilizado para voltar a esse ponto quando morrer.
        int gaia_hp;
        int gaia_poderes;
        
        bool p_deposito; //false trancada, true aberta (puzzle de empurrar as caixas com o carro)
        bool p_corredor2; //false trancada, true aberta

        bool esteira_ligada; //false desligada, true ligada

        bool ja_mostrou_corre; // do inicio do jogo
        bool ja_mostrou_f_esteira;
        bool ja_mostrou_f_chicote;
        
        int  ja_ficou_encurralada; //no terreo logo antes de descer pelo duto
        bool ja_falou_velho; //false nao falou, true ja falou
        bool ja_pegou_chave_rato; //para renderizar rato com a chave ou nao
        bool ja_pegou_chicote;

        //enum Item{a,b,c};
        //std::vector<Item> inventario;
};

#endif // STATEDATA_H
