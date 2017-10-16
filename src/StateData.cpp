#include "StateData.hpp"

StateData::StateData(){
    gaia_t_pos = Vec2(0,0);
    gaia_t_pos_antiga = Vec2(0,0);
    gaia_t_pos_inicio_comodo = Vec2(0,0);
    gaia_comodo = 4;
    gaia_hp = 10;
    corre = true;
    ja_ficou_encurralada = 0; // 3 se ja passou fugiu do encurralamento
    fala_velho = false;
    pegou_chave_rato = false;
    ja_pressionou_f = false;
    esteira = false; // false - desligada
    p_corredor2 = false; // false - trancada
    p_deposito = false; //false - trancada
    pegou_chicote = false;
}

StateData::StateData(std::string nome){
    
}


void StateData::Carregar(std::string nome){
    if(nome == "inicio jogo"){    
        gaia_t_pos_inicio_comodo = Vec2(47, 15);
        gaia_comodo = 4;
        gaia_hp = 10;
        corre = true;
        ja_ficou_encurralada = 0;
        fala_velho = false;
        pegou_chave_rato = false;
        ja_pressionou_f = 0;
        esteira = false;
        p_corredor2 = false;
        p_deposito = false;
        pegou_chicote = false;
    }
}
