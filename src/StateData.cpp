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
        gaia_t_pos_inicio_comodo = Vec2(41, 17);
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

void StateData::PrintData(){
    std::cout << "gaia_t_pos: " << gaia_t_pos.x << ", " << gaia_t_pos.y << std::endl;
    std::cout << "gaia_t_pos_antiga: " << gaia_t_pos_antiga.x << ", " << gaia_t_pos_antiga.y << std::endl;
    std::cout << "gaia_t_pos_inicio_comodo: " << gaia_t_pos_inicio_comodo.x << ", " << gaia_t_pos_inicio_comodo.y << std::endl;
    if (gaia_comodo == 0){
        std::cout << "gaia_comodo: 0 (se T Produção, se SS Quarto Velho)" << std::endl;
    }
    else if (gaia_comodo == 4){
        std::cout << "gaia_comodo: 4 (Corredor)" << std::endl;
    }
    else if (gaia_comodo == 8){
        std::cout << "gaia_comodo: 8 (se T Doritorio, se SS Deposito)" << std::endl;
    }
    else if (gaia_comodo == 12){
        std::cout << "gaia_comodo: 12 (se T Corredor2 se SS Descarga)" << std::endl;
    }
    else if (gaia_comodo == 16){
        std::cout << "gaia_comodo: 16 (T Refeitorio)" << std::endl;
    }
    std::cout << "gaia_hp: " << gaia_hp << std::endl;
    if(p_deposito){
        std::cout << "p_deposito: true (aberta)" << std::endl;
    }
    else{
        std::cout << "p_deposito: false (trancada)" << std::endl;
    }
    if(p_corredor2){
        std::cout << "p_corredor2: true (aberta)" << std::endl;
    }
    else{
        std::cout << "p_corredor2: false (trancada)" << std::endl;
    }
    if(esteira){
        std::cout << "esteira: true (ligada)" << std::endl;
    }
    else{
        std::cout << "esteira: false (desligada)" << std::endl;
    }
    if(pegou_chave_rato){
        std::cout << "pegou_chave_rato: true (ja pegou a chave, nao renderizar a chave)" << std::endl;
    }
    else{
        std::cout << "pegou_chave_rato: false (nao pegou a chave, renderizar a chave)" << std::endl;
    }
    std::cout << "ja_ficou_encurralada: " << ja_ficou_encurralada << std::endl;
    std::cout << "ja_pressionou_f: " << ja_pressionou_f << std::endl;
    std::cout << "corre: " << corre << std::endl;
    std::cout << "pegou_chicote: " << pegou_chicote << std::endl;
    if(fala_velho){
        std::cout << "fala_velho: true (ja falou)" << std::endl;
    }
    else{
        std::cout << "fala_velho: false (nao falou)" << std::endl;
    }

    //enum Item{CARTAO_ACESSO, CHAVE_ENERGIA, BEBIDINHA};
    //std::vector<Item> inventario;
}
