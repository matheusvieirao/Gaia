#include "Guarda2.hpp"

int turno_atual = 0; //usado no debug para se ver em qual loop o programa se encontra

Guarda2::Guarda2(float x, float y, GuardaEstado estado_inicial, int comodo, std::string nome):sp("img/personagens/guarda_andando.png", 16, 1, 4, 0.2){
    tempo_estado.Restart();
    this->nome = nome;
    //mov_automatico = false;
    pause = false;

    altura_pe = 19;
    largura_box_col = 78;
    altura_box_col = 40;
    box.x = x - sp.GetWidth()/2;
    box.y = y - sp.GetHeight() + altura_pe;
    box.w = sp.GetWidth();
    box.h = sp.GetHeight();

    //box_anterior.x = box.x;
    //box_anterior.y = box.y;
    //box_anterior.w = box.w;
    //box_anterior.h = box.h;

    comodo_atual = comodo;
    hp = 3;
    estado_atual = estado_inicial;
    //movimento_atual = NO;

    /*if(estado_atual == PERSEGUINDO){
        movimento_atual = PARADO;
        contador_fuga = 99;
    }
    else if(estado_atual == PARADO_AUTOMATICO){
        movimento_atual = PARADO;
        if(nome == "b1"){
            sp.SetFrame(10);
        }
        else if(nome == "b2"){
            sp.SetFrame(10);
        }
        else if(nome == "c1"){
            sp.SetFrame(2);
        }
        else if(nome == "c2"){
            sp.SetFrame(2);
        }
        sp.PauseAnimation();
    }*/
}

Guarda2::~Guarda2(){
}

void Guarda2::Update(float dt){
    if(Game::GetInstance().IsStateStackEmpty()){
        return;
    }
    turno_atual++;
    printf("-------------------%d--------------------\n",turno_atual);

    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    int tile_width = t_map->GetTileWidth();
    int tile_height = t_map->GetTileHeight();

    Vec2 gaia_pos = Gaia::player->GetPos();
    Vec2 gaia_t_pos = gaia_pos.IsometricToCard(tile_width, tile_height);
    Vec2 guarda_pos = Vec2(box.GetCenter().x, box.y+box.h-altura_pe);
    guarda_t_pos = guarda_pos.IsometricToCard(tile_width, tile_height);

    // float vel_devagar = 200*dt;
    // float vel_rapido = 100*dt;
    // float tempo_devagar = (float)(tile_height*dt)/(vel_devagar);//tempo de andar 1 tile na velocidade devagar. a conta esta simplificada, o certo seria: "(tile_height/2) / ((vel_rapido*0.5)/dt) sendo 0.5 o seno do angulo da inclinacao do tile
    // float tempo_rapido = (float)(tile_height*dt)/(2*vel_rapido);//tempo de andar 1 tile na velocidade rapido

    sp.Update(dt);

    tempo_estado.Update(dt);

    if(!pause){

        /*if(estado_atual == DESCANSANDO_PARADO){
           // printf("DESCANSANDO_PARADO\n");

            if(tempo_estado.Get() > tempo_devagar*0.973){
                andar_n_tiles = AndarAleatorio(t_map);
                estado_atual = DESCANSANDO_ANDANDO;
                tempo_estado.Restart();
            }

            if(!Gaia::player->EstaTransparente() && EstaNaVisao(gaia_t_pos)){
                printf("ACHOOOU\n");
                contador_fuga = 0;
                estado_atual = PERSEGUINDO;
                caminho.clear();
                CalcularCaminho(gaia_t_pos, t_map);
                CalcularMovimentoAtual();
                tempo_estado.Restart();
            }
        }

        else if(estado_atual == DESCANSANDO_ANDANDO){
        //    printf("DESCANSANDO_ANDANDO\n");

            Andar(vel_devagar, t_map);

            if(tempo_estado.Get() > andar_n_tiles*tempo_devagar*0.973){
                estado_atual = DESCANSANDO_PARADO;
                tempo_estado.Restart();
            }

            if(!Gaia::player->EstaTransparente() && EstaNaVisao(gaia_t_pos)){
                printf("ACHOOOU\n");
                contador_fuga = 0;
                estado_atual = PERSEGUINDO;
                caminho.clear();
                CalcularCaminho(gaia_t_pos, t_map);
                CalcularMovimentoAtual();
                tempo_estado.Restart();
            }
        }

        else if(estado_atual == SAIR){
         //   printf("SAIR\n");

            if(Gaia::player->EstaTransparente()){
                movimento_atual = PARADO;
                if(tempo_estado.Get() > 2){
                    if(guarda_pos.y > gaia_pos.y){
                        movimento_atual = SE;
                    }
                    else{
                        movimento_atual = NO;
                    }
                }
            }
            else if(EstaNaVisao(gaia_t_pos)){
                contador_fuga = 0;
                estado_atual = PERSEGUINDO;
                caminho.clear();
                CalcularCaminho(gaia_t_pos, t_map);
                CalcularMovimentoAtual();
                tempo_estado.Restart();
            }


            if(MaiorDistancia(gaia_t_pos) > 3 || tempo_estado.Get() > 5){
                estado_atual = DESCANSANDO_PARADO;
                tempo_estado.Restart();
            }

            Andar(vel_devagar, t_map);
        }

        else if(estado_atual == PARADO_AUTOMATICO){
        //    printf("PARADO_AUTOMATICO\n");
            if(mov_automatico){
                estado_atual = MOVIMENTO_AUTOMATICO;
                movimento_atual = movimentos.back();
                movimentos.pop_back();
                tempo_estado.Restart();
            }
        }

        else if(estado_atual == MOVIMENTO_AUTOMATICO){
          //  printf("MOVIMENTO_AUTOMATICO\n");
            vel_rapido = 500 * dt;
            tempo_rapido = (float)tile_height/((vel_rapido)/dt);

            if(tempo_estado.Get() > tempo_rapido*0.973){
                if(movimentos.size()!=0){
                    movimento_atual = movimentos.back();
                    movimentos.pop_back();
                    tempo_estado.Restart();
                }
                else{
                    mov_automatico = false;
                    movimento_atual = PARADO;
                    tempo_estado.Restart();
                }
            }

            if(Gaia::player->EstaTransparente()){
                movimentos.clear();
                mov_automatico = false;
                estado_atual = SAIR;
                tempo_estado.Restart();
            }

            Andar(vel_rapido, t_map);
        }

        //talvez pensar num modo do guarda sair do modo perseguindo se a distancia for mt grande  
        else*/ if(estado_atual == PERSEGUINDO){

                caminho.clear();
                CalcularCaminho(gaia_t_pos, t_map);
                /*CalcularMovimentoAtual();
                tempo_estado.Restart();
            
            
                                                                                                                                        for(unsigned i = 0; i < caminho.size() ; i++) {
                                                                                                                                            if(caminho[i] == SE){
                                                                                                                                                printf("| SE ");
                                                                                                                                            }
                                                                                                                                            else if(caminho[i] == SO){
                                                                                                                                                printf("| SO ");
                                                                                                                                            }
                                                                                                                                            else if(caminho[i] == NE){
                                                                                                                                                printf("| NE ");
                                                                                                                                            }
                                                                                                                                            else if(caminho[i] == NO){
                                                                                                                                                printf("| NO ");
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        if(caminho.size()>0){
                                                                                                                                            printf("|\n");
                                                                                                                                        }

            //chega no tile desejado
            if(guarda_t_pos_desejada.x == guarda_t_pos.x && guarda_t_pos_desejada.y == guarda_t_pos.y){
                printf("Chegou no tile desejado!\n");
                CalcularCaminho(gaia_t_pos, t_map);
                if(caminho.size() > 0){
                    CalcularMovimentoAtual();
                }
                else{
                    EncontraNoMesmoTile(gaia_pos, guarda_pos);
                }
                if (flag_perseguindo == 0){
                    printf("flag perseguindo == 0\n");
                    tempo_estado.Restart();
                    flag_perseguindo = 1;
                    contador_fuga++;
                }
            }
            else{
                flag_perseguindo = 0;
            }

            Andar(vel_rapido, t_map);

            //se estiver no mesmo tile q a gaia
            if(gaia_t_pos.x == guarda_t_pos.x && gaia_t_pos.y == guarda_t_pos.y){
                caminho.clear();
                EncontraNoMesmoTile(gaia_pos, guarda_pos);
            }

            if(Gaia::player->EstaTransparente()){
                estado_atual = SAIR;
                tempo_estado.Restart();
            }*/
        }
    }


    if(t_map == nullptr){
        Game::GetInstance().AddErro(12, "Guarda2::Update");
    }
}

void Guarda2::Render(){
    sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
    
    /*Vec2 ponto_pe_guarda;
    Vec2 guarda_pos_desejada;

    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    guarda_pos_desejada = guarda_t_pos_desejada.CardToIsometric(t_map->GetTileWidth(), t_map->GetTileHeight());
    ponto_pe_guarda.x = box.GetCenter().x;
    ponto_pe_guarda.y = box.y + box.h - altura_pe;

    ponto_pe_guarda.x -= Camera::pos.x;
    ponto_pe_guarda.y -= Camera::pos.y;
    guarda_pos_desejada.x -= Camera::pos.x;
    guarda_pos_desejada.y -= Camera::pos.y;

    DrawRectangle(ponto_pe_guarda);
    DrawRectangleX(guarda_pos_desejada);*/
}

int Guarda2::GetAlturaPe(){
    return(altura_pe);
}

void Guarda2::NotifyCollision(GameObject& other){
    if(other.Is("Guarda")){
    	//durante a colisao com outros guardas, o que colidir por tras fica parado
        if(movimento_atual == NO || movimento_atual == NE || movimento_atual == N || movimento_atual == O){
            if(box.y < other.box.y){
                box.x = box_anterior.x;
                box.y = box_anterior.y;
            }
        }
        else if(movimento_atual == SO || movimento_atual == SE || movimento_atual == S || movimento_atual == L){
            if(box.y > other.box.y){
                box.x = box_anterior.x;
                box.y = box_anterior.y;
            }
        }
    }
}

bool Guarda2::Is(std::string type){
    return(type == "Guarda" || type == nome);
}

bool Guarda2::IsDead(){
    return(hp<0);
}



//retorna o tamanho do vetor caminho, que contem as coordenadas a se andar
int Guarda2::CalcularCaminho(Vec2 gaia_t_pos, TileMap* t_map){
    printf("calc caminho\n");
    bool achou = false;

    int map_width = t_map->GetWidth();
    int map_height = t_map->GetHeight();
    this->x_destino = gaia_t_pos.x;
    this->y_destino = gaia_t_pos.y;



    if(celulas_nao_checadas.size()!=0){
        celulas_nao_checadas.clear();
    }
    for(int i = celulas.size()-1; i >= 0 ; i--){
        free(celulas[i]);
    }
    if(celulas.size()!=0){
        celulas.clear();
    }
    if(mapa_aux.size()!=0){
        mapa_aux.clear();
    }
    if(caminho.size()!=0){
        caminho.clear();
    }

    for(int j = 0; j < map_height; j++){
        for(int i = 0; i < map_width; i++){
            mapa_aux.push_back(t_map->GetTileInfo(comodo_atual, i, j));
        }
    }


    if(VerificarMapa(guarda_t_pos.x, guarda_t_pos.y, map_width, map_height)){
        Celula *cel_origem = new Celula(guarda_t_pos.x, guarda_t_pos.y, nullptr);
        cel_origem->custo_ate_agora = 0;
        cel_origem->custo_total = QuantoFalta(cel_origem->x, cel_origem->y);
        celulas.push_back(cel_origem);
        celulas_nao_checadas.push_back(celulas.back());
    }
    else{
        return (-1); //impossivel ligar origem ao destino
    }

    while(!achou && tempo_estado.Get() < 1.5){
        Celula* cel_aux = celulas_nao_checadas.back();
        celulas_nao_checadas.pop_back();
        if(cel_aux->x == x_destino && cel_aux->y == y_destino){
            //nao entra no vetor caminho a celula aonde o guarda se encontra
            for( ; cel_aux->ptr_cel_antiga!=nullptr; cel_aux=cel_aux->ptr_cel_antiga){
                if(cel_aux->x < cel_aux->ptr_cel_antiga->x){
                    caminho.push_back(NO);
                    printf("NO ");
                }
                else if(cel_aux->y < cel_aux->ptr_cel_antiga->y){
                    caminho.push_back(NE);
                    printf("NE ");
                }
                else if(cel_aux->x > cel_aux->ptr_cel_antiga->x){
                    caminho.push_back(SE);
                    printf("SE ");
                }
                else if(cel_aux->y > cel_aux->ptr_cel_antiga->y){
                    caminho.push_back(SO);
                    printf("SO ");
                }
                //printf("%d,%d | ",(int)cel_aux->x, (int)cel_aux->y);
            }
            if(cel_aux->x < guarda_t_pos.x){
                caminho.push_back(NO);
                    printf("NO ");
            }
            else if(cel_aux->y < guarda_t_pos.y){
                caminho.push_back(NE);
                    printf("NE ");
            }
            else if(cel_aux->x > guarda_t_pos.x){
                caminho.push_back(SE);
                    printf("SE ");
            }
            else if(cel_aux->y > guarda_t_pos.y){
                caminho.push_back(SO);
                    printf("SO ");
            }
            achou = true;
        }
        else{
            if(VerificarMapa(cel_aux->x, cel_aux->y+1, map_width, map_height)){
                InserirOrdenado(cel_aux->x, cel_aux->y+1, cel_aux);
            }
            if(VerificarMapa(cel_aux->x-1, cel_aux->y, map_width, map_height)){
                InserirOrdenado(cel_aux->x-1, cel_aux->y, cel_aux);
            }
            if(VerificarMapa(cel_aux->x, cel_aux->y-1, map_width, map_height)){
                InserirOrdenado(cel_aux->x, cel_aux->y-1, cel_aux);
            }
            if(VerificarMapa(cel_aux->x +1, cel_aux->y, map_width, map_height)){
                InserirOrdenado(cel_aux->x+1, cel_aux->y, cel_aux);
            }
        }
    }
    return(caminho.size());
}

bool Guarda2::VerificarMapa(int x, int y, int map_width, int map_height){
    if (x>=0 && x<map_width && y>= 0 && y<map_height){
        //0 é aonde nao tem tile e 18 é o tile que nao pode ser pisado
        if(mapa_aux[y*map_width + x] != 0 && mapa_aux[y*map_width + x] != 18){
            mapa_aux[y*map_width + x] = 0;
            return (true);
        }
        else{
            return (false);
        }
    }
    else{
        return(false);
    }
}

float Guarda2::QuantoFalta(int x, int y){
    float mod_x = x - x_destino;
    float mod_y = y - y_destino;

    if(mod_x < 0){
        mod_x = -mod_x;
    }
    if(mod_y < 0){
        mod_y = -mod_y;
    }

    return(sqrt(mod_x*mod_x + mod_y*mod_y));
}

void Guarda2::InserirOrdenado(int x, int y, Celula* cel_aux){
    Celula* nova_cel = new Celula(x, y, cel_aux);
    nova_cel->custo_ate_agora = cel_aux->custo_ate_agora + 1;
    nova_cel->custo_total = nova_cel->custo_ate_agora + QuantoFalta(x, y);
    celulas.push_back(nova_cel);
    celulas_nao_checadas.push_back(celulas.back());

    //ordenar vetor
    int i = celulas_nao_checadas.size();
    i--;
    while(i>0 && celulas_nao_checadas[i]->custo_total > celulas_nao_checadas[i-1]->custo_total){
        std::swap(celulas_nao_checadas[i], celulas_nao_checadas[i-1]);
        i--;
    }
}


