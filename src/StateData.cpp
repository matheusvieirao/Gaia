#include "StateData.hpp"

StateData::StateData(){
    s1_num_historia = 1;
    gaia_t_pos = Vec2(0,0);
    gaia_t_pos_antiga = Vec2(0,0);
    gaia_t_pos_inicio_comodo = Vec2(0,0);
    //comecou_jogo = true; //utilizada para atualizar o comodo pela primeira vez da inicializacao do jogo
    state_atual = 2;
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

void StateData::Atribuir(StateData data){
    gaia_t_pos.x = data.gaia_t_pos.x;
    gaia_t_pos.y = data.gaia_t_pos.y;
    gaia_t_pos_antiga.x = data.gaia_t_pos_antiga.x;
    gaia_t_pos_antiga.y = data.gaia_t_pos_antiga.y;
    gaia_t_pos_inicio_comodo.x = data.gaia_t_pos_inicio_comodo.x;
    gaia_t_pos_inicio_comodo.y = data.gaia_t_pos_inicio_comodo.y;
    state_atual = data.state_atual;
    gaia_comodo = data.gaia_comodo;
    gaia_hp = data.gaia_hp;
    p_deposito = data.p_deposito;
    p_corredor2 = data.p_corredor2;
    esteira = data.esteira;
    pegou_chave_rato = data.pegou_chave_rato;
    ja_ficou_encurralada = data.ja_ficou_encurralada;
    ja_pressionou_f = data.ja_pressionou_f;
    corre = data.corre;
    fala_velho = data.fala_velho;
    inventario = data.inventario;
}

void StateData::Carregar(std::string nome){
    if(nome == "inicio animacao"){
        s1_num_historia = 1;
        //gaia_t_pos_inicio_comodo = Vec2(41, 17);
        gaia_t_pos_inicio_comodo = Vec2(46, 16);
        state_atual = 2;
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
    else if(nome == "inicio jogo"){    
        s1_num_historia = 2;
        //gaia_t_pos_inicio_comodo = Vec2(41, 17);
        gaia_t_pos_inicio_comodo = Vec2(46, 16);
        state_atual = 2;
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
    else if(nome == "quase transparente"){    
        s1_num_historia = 2;
        //gaia_t_pos_inicio_comodo = Vec2(41, 17);
        gaia_t_pos_inicio_comodo = Vec2(12, 16);
        state_atual = 2;
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
    else if(nome == "depois da fala SS"){    
        s1_num_historia = 1;
        gaia_t_pos_inicio_comodo = Vec2(25, 16);
        gaia_t_pos_antiga = Vec2(25,16);
        gaia_t_pos_inicio_comodo = Vec2(26,16);
        state_atual = 3;
        gaia_comodo = 4; //corredor, nesse caso do SS
        gaia_hp = 10;
        p_deposito = false; //trancada
        p_corredor2 = false; //trancada
        esteira = false; //desligada
        pegou_chave_rato = false;
        ja_ficou_encurralada = 3;
        ja_pressionou_f = false;
        ja_pressionou_f = false;
        esteira = false;
        p_corredor2 = false;
        p_deposito = false;
        pegou_chicote = false;
        corre = false;
        pegou_chicote = false;
        fala_velho = true; //ja falou
        //inventario.push_back(CHAVE_ENERGIA);
    }
    else if(nome == "galpao com chave e cartao"){    
        s1_num_historia = 1;
        gaia_t_pos_inicio_comodo = Vec2(28, 19);
        gaia_t_pos_antiga = Vec2(28,19);
        gaia_t_pos_inicio_comodo = Vec2(27,16);
        state_atual = 3;
        gaia_comodo = 12; //(se T Corredor2 se SS Descarga, no caso Descarga)
        gaia_hp = 10;
        p_deposito = false; //trancada
        p_corredor2 = false; //trancada
        esteira = false; //desligada
        pegou_chave_rato = false;
        ja_ficou_encurralada = 3;
        ja_pressionou_f = false;
        ja_pressionou_f = false;
        esteira = false;
        p_corredor2 = false;
        p_deposito = false;
        pegou_chicote = false;
        corre = false;
        pegou_chicote = false;
        fala_velho = true; //ja falou
        inventario.push_back(CHAVE_ENERGIA);
        inventario.push_back(CARTAO_ACESSO);
    }
    else if(nome == "cutscene 2"){    
        s1_num_historia = 2;
        gaia_t_pos_inicio_comodo = Vec2(28, 19);
        gaia_t_pos_antiga = Vec2(28,19);
        gaia_t_pos_inicio_comodo = Vec2(27,16);
        state_atual = 1;
        gaia_comodo = 12; //(se T Corredor2 se SS Descarga, no caso Descarga)
        gaia_hp = 10;
        p_deposito = false; //trancada
        p_corredor2 = false; //trancada
        esteira = false; //desligada
        pegou_chave_rato = false;
        ja_ficou_encurralada = 3;
        ja_pressionou_f = false;
        ja_pressionou_f = false;
        esteira = false;
        p_corredor2 = false;
        p_deposito = false;
        pegou_chicote = false;
        corre = false;
        pegou_chicote = false;
        fala_velho = true; //ja falou
        inventario.push_back(CHAVE_ENERGIA);
        inventario.push_back(CARTAO_ACESSO);
        inventario.push_back(BEBIDINHA);
    }
}

void StateData::PrintData(){
    std::cout << "s1_num_historia: " << s1_num_historia << std::endl;
    std::cout << "gaia_t_pos: " << gaia_t_pos.x << ", " << gaia_t_pos.y << std::endl;
    std::cout << "gaia_t_pos_antiga: " << gaia_t_pos_antiga.x << ", " << gaia_t_pos_antiga.y << std::endl;
    std::cout << "gaia_t_pos_inicio_comodo: " << gaia_t_pos_inicio_comodo.x << ", " << gaia_t_pos_inicio_comodo.y << std::endl;
    std::cout << "state_atual: State_0" << state_atual << "_..." << std::endl;
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

    printf("Inventario: ");
    for(unsigned i = 0; i < inventario.size(); i++){
        if(inventario[i] == CARTAO_ACESSO){
            printf("CARTAO_ACESSO, ");
        }
        else if(inventario[i] == CHAVE_ENERGIA){
            printf("CHAVE_ENERGIA, ");
        } 
        else if(inventario[i] == BEBIDINHA){
            printf("BEBIDINHA, ");
        } 
    }
    printf("\n");
}
