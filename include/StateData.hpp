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
        void Carregar(std::string nome);
        void PrintData();
        Vec2 gaia_t_pos;
        Vec2 gaia_t_pos_antiga;
        Vec2 gaia_t_pos_inicio_comodo;
        int gaia_comodo; // T: 0- Producao | 4- Corredor | 8- Dormitorio | 12- Corredor2 | 16- Refeitorio // SS: 0- Quarto Velho | 4- Corredor | 8- Deposito | 12- Descarga
        int gaia_hp;
        bool p_deposito; //false trancada, true aberta
        bool p_corredor2; //false trancada, true aberta
        bool esteira; //false desligada, true ligada
        bool pegou_chave_rato; //para renderizar rato com a chave ou nao
        int ja_ficou_encurralada;
        bool ja_pressionou_f;
        bool corre;
        bool pegou_chicote;
        bool fala_velho; //false nao falou, true ja falou

        enum Item{CARTAO_ACESSO, CHAVE_ENERGIA, BEBIDINHA};
        std::vector<Item> inventario;
};

#endif // STATEDATA_H
