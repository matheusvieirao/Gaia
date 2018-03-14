#include "GuardaObservador.hpp"

GuardaObservador::GuardaObservador(std::vector<Vec2> coord_vet, int comodo, TileMap* t_map):sp("img/personagens/observador.png", 16, 1, 4, 0.2){
    this->coord_vet = coord_vet;
    coord_vigilia_atual = 0;

    tempo_estado.Restart();
    pause = false;

    altura_pe = 28;
    largura_box_col = 78;
    altura_box_col = 40;

    Vec2 guarda_pe_pos = coord_vet[0].CardToIsometricCenter(t_map->GetTileWidth(), t_map->GetTileHeight());
    box.x = guarda_pe_pos.x - sp.GetWidth()/2;
    box.y = guarda_pe_pos.y - sp.GetHeight() + altura_pe;
    box.w = sp.GetWidth();
    box.h = sp.GetHeight();

    box_anterior.x = box.x;
    box_anterior.y = box.y;
    box_anterior.w = box.w;
    box_anterior.h = box.h;

    comodo_atual = comodo;
    hp = 1;
    estado_atual = VIGILIA_PARADO;

    movimento_anterior = SE;
    movimento_atual = SE;
    sp.SetFrameStart(1);
    sp.SetFrameAnimation(4);
    
}

GuardaObservador::~GuardaObservador(){
}

void GuardaObservador::Update(float dt){
    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    int tile_width = t_map->GetTileWidth();
    int tile_height = t_map->GetTileHeight();

    float vel_devagar = 200*dt;
    float vel_rapido = 700*dt;
    //float tempo_devagar = (float)(tile_height*dt)/(vel_devagar);//tempo de andar 1 tile na velocidade devagar. a conta esta simplificada, o certo seria: "(tile_height/2) / ((vel_rapido*0.5)/dt) sendo 0.5 o seno do angulo da inclinacao do tile
    //float tempo_rapido = (float)(tile_height*dt)/(2*vel_rapido);//tempo de andar 1 tile na velocidade rapido

    Vec2 gaia_pos = Gaia::player->GetPos();
    Vec2 gaia_t_pos = gaia_pos.IsometricToCard(tile_width, tile_height);
    guarda_pos = Vec2(box.GetCenter().x, box.y+box.h-altura_pe);
    guarda_t_pos = guarda_pos.IsometricToCard(tile_width, tile_height);


    if(Game::GetInstance().IsStateStackEmpty()){
        return;
    }
    
    sp.Update(dt);
    pausa.Update(dt);

    tempo_estado.Update(dt);

    if(!pause){

        if(estado_atual == VIGILIA_PARADO){
            if(tempo_estado.Get() > 1.5){
                //AndarAleatorio(t_map);
                calcular_proximo_passo = true;
                estado_atual = VIGILIA_ANDANDO;
                tempo_estado.Restart();
            }

            if(!Gaia::player->EstaTransparente() && EstaNaVisao(gaia_t_pos)){
                calcular_proximo_passo = true; //para inicializar a busca pela gaia em PERSEGUICAO
                estado_atual = PERSEGUINDO;
                tempo_estado.Restart();
            }
        }
        
        else if(estado_atual == VIGILIA_ANDANDO){
        	if(calcular_proximo_passo){
                CalcularMovimentoAtual(t_map);
                calcular_proximo_passo = false;
            }

          	Andar(vel_devagar);
            

            if(!Gaia::player->EstaTransparente() && EstaNaVisao(gaia_t_pos)){
                calcular_proximo_passo = true;
                estado_atual = PERSEGUINDO;
                tempo_estado.Restart();
            }
        }

        //talvez pensar num modo do guarda sair do modo perseguindo se a distancia for mt grande  
        else if(estado_atual == PERSEGUINDO){
            tempo_estado.Restart();

            if(calcular_proximo_passo){
                caminho.clear();    
                CalcularCaminho(gaia_t_pos, t_map);
                CalcularMovimentoAtual(t_map);
                calcular_proximo_passo = false;
            }

            if(movimento_atual != PARADO){
                Andar(vel_rapido);
            }
            else {
            	calcular_proximo_passo = true;
            }

            if(Gaia::player->EstaTransparente()){
                estado_atual = VIGILIA_PARADO;
                movimento_atual = PARADO;
                tempo_estado.Restart();
                acabou_de_entrar_no_estado = true;
            }

            if(gaia_t_pos.x == guarda_t_pos.x && gaia_t_pos.y == guarda_t_pos.y){
                caminho.clear();
                guarda_pos_desejada = gaia_pos;
            }
        }
    
    }


    if(t_map == nullptr){
        std::cout << "t_map não pode ser nullptr. GuardaObservador::Update"  << std::endl;
    }
}

void GuardaObservador::Render(){
    sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
    //sp.RenderBox(box.x-Camera::pos.x, box.y-Camera::pos.y);

    /*//Hitbox
    int x1 = box.GetCenter().x - largura_box_col/2 -Camera::pos.x;
    int y1 = box.y + box.h -altura_pe - altura_box_col/2 -Camera::pos.y;
    int x2 = x1 + largura_box_col;
    int y2 = y1 + altura_box_col;
    SDL_Renderer* GameRenderer = Game::GetInstance().GetRenderer();
    SDL_RenderDrawLine(GameRenderer, x1, y1, x1, y2);
    SDL_RenderDrawLine(GameRenderer, x1, y2, x2, y2);
    SDL_RenderDrawLine(GameRenderer, x2, y2, x2, y1);
    SDL_RenderDrawLine(GameRenderer, x2, y1, x1, y1);
    */
}

int GuardaObservador::GetAlturaPe(){
    return(altura_pe);
}

void GuardaObservador::NotifyCollision(GameObject& other){
    if(other.Is("GuardaObservador")){
        //durante a colisao com outros guardas, o que colidir por tras fica parado
        if(movimento_atual == NO || movimento_atual == NE || movimento_atual == N || movimento_atual == O){
            if(box.y > other.box.y){
                box.x = box_anterior.x;
                box.y = box_anterior.y;
            }
        }
        else if(movimento_atual == SO || movimento_atual == SE || movimento_atual == S || movimento_atual == L){
            if(box.y < other.box.y){
                box.x = box_anterior.x;
                box.y = box_anterior.y;
            }
        }
    }
    else if(other.Is("Chicote")){

        som_chicote_hit.Open("audio/sons/hit.ogg");
        som_chicote_hit.Play(0);
        hp--;

        Vec2 direcao, direcao_anterior;
        direcao.x = box.x;
        direcao.y = box.y;
        direcao_anterior.x = box_anterior.x;
        direcao_anterior.y = box_anterior.y;

        int modulo = 10;
        while(modulo > 0){
            direcao = direcao.MoveTo(direcao_anterior, modulo);
            if(TileAndavel(direcao)){
                box.x = direcao.x;
                box.y = direcao.y;
                modulo = -1;
            }
            else{
                modulo--;
            }
        }
    }
}

bool GuardaObservador::Is(std::string type){
    return(type == "GuardaObservador");
}

bool GuardaObservador::IsDead(){
    return(hp<0);
}

void GuardaObservador::PushMovimento(int mov){
}



//retorna o tamanho do vetor caminho, que contem as coordenadas a se andar
int GuardaObservador::CalcularCaminho(Vec2 gaia_t_pos, TileMap* t_map){
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
                }
                else if(cel_aux->y < cel_aux->ptr_cel_antiga->y){
                    caminho.push_back(NE);
                }
                else if(cel_aux->x > cel_aux->ptr_cel_antiga->x){
                    caminho.push_back(SE);
                }
                else if(cel_aux->y > cel_aux->ptr_cel_antiga->y){
                    caminho.push_back(SO);
                }
            }
            if(cel_aux->x < guarda_t_pos.x){
                caminho.push_back(NO);
            }
            else if(cel_aux->y < guarda_t_pos.y){
                caminho.push_back(NE);
            }
            else if(cel_aux->x > guarda_t_pos.x){
                caminho.push_back(SE);
            }
            else if(cel_aux->y > guarda_t_pos.y){
                caminho.push_back(SO);
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
bool GuardaObservador::VerificarMapa(int x, int y, int map_width, int map_height){
    if (x>=0 && x<map_width && y>= 0 && y<map_height){
        //0 é aonde nao tem tile e 18 é o tile que nao pode ser pisado
        int valor_mapa = mapa_aux[y*map_width + x];
        if(valor_mapa != 0 && valor_mapa != 13 && valor_mapa != 14 && valor_mapa != 18 && valor_mapa != 19){
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
float GuardaObservador::QuantoFalta(int x, int y){
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
void GuardaObservador::InserirOrdenado(int x, int y, Celula* cel_aux){
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


void GuardaObservador::CalcularMovimentoAtual(TileMap* t_map){
    if(estado_atual == PERSEGUINDO){
        if(caminho.size() > 0){
            movimento_atual = caminho.back();
            caminho.pop_back();
            if(movimento_atual == NE){
                guarda_t_pos_desejada.x = guarda_t_pos.x;
                guarda_t_pos_desejada.y = guarda_t_pos.y-1;
            }
            else if(movimento_atual == SE){
                guarda_t_pos_desejada.x = guarda_t_pos.x+1;
                guarda_t_pos_desejada.y = guarda_t_pos.y;
            }
            else if(movimento_atual == SO){
                guarda_t_pos_desejada.x = guarda_t_pos.x;
                guarda_t_pos_desejada.y = guarda_t_pos.y+1;
            }
            else if(movimento_atual == NO){
                guarda_t_pos_desejada.x = guarda_t_pos.x-1;
                guarda_t_pos_desejada.y = guarda_t_pos.y;
            }
            else if(movimento_atual == PARADO){
                guarda_t_pos_desejada.x = guarda_t_pos.x;
                guarda_t_pos_desejada.y = guarda_t_pos.y;
            }

            guarda_pos_desejada = guarda_t_pos_desejada.CardToIsometricCenter(t_map->GetTileWidth(), t_map->GetTileHeight()); //retorna o ponto no centro do tile
        }
    }
    else{
        int coord_vigilia_antiga = coord_vigilia_atual;
        
        if(coord_vigilia_atual+1 == (int) coord_vet.size()){
            coord_vigilia_atual = 0;
        }
        else{
            coord_vigilia_atual++;
        }
        guarda_t_pos_desejada.x = coord_vet[coord_vigilia_atual].x;
        guarda_t_pos_desejada.y = coord_vet[coord_vigilia_atual].y;
        guarda_pos_desejada = guarda_t_pos_desejada.CardToIsometricCenter(t_map->GetTileWidth(), t_map->GetTileHeight());

        //calcular a direcao de movimento_atual. parte do presuposto que todos os movimentos de vigilia só andam uma cooredana, ou X ou Y
        if(coord_vet[coord_vigilia_atual].x == coord_vet[coord_vigilia_antiga].x){
            if(coord_vet[coord_vigilia_atual].y > coord_vet[coord_vigilia_antiga].y){
                movimento_atual = SO;
            }
            else{
                movimento_atual = NE;
            }
        }
        else{
            if(coord_vet[coord_vigilia_atual].x > coord_vet[coord_vigilia_antiga].x){
                movimento_atual = SE;
            }
            else{
                movimento_atual = NO;
            }
        }
    }
}
//tem que chamar CalcularMovimentoAtual() para calcular "guarda_pos_desejada" antes de chamar Andar()
void GuardaObservador::Andar(float vel){
    int m_dur = 4; //quantos frames de animaçao tem em cada movimento
    int m_sudeste = 1; //o primeiro frame andando em direcao sudeste
    int m_nordeste = 5;
    int m_noroeste = 9;
    int m_sudoeste = 13;
    Vec2 direcao;


    sp.ResumeAnimation(); // #verdps se continuar dando erro 18/02
    box_anterior.x = box.x;
    box_anterior.y = box.y;

    guarda_pos.x = box.GetCenter().x;
    guarda_pos.y = box.y + box.h - altura_pe;

    direcao = guarda_pos_desejada - guarda_pos;
    float distancia_falta = guarda_pos_desejada.DistanciaVets(guarda_pos);
    direcao = direcao.Normalizado();
    direcao = direcao * vel;
    float distancia_a_percorrer = direcao.Magnitude();

    //se for passar, so andar ate o limite
    if(distancia_a_percorrer >= distancia_falta){
        direcao = guarda_pos_desejada - guarda_pos;
        calcular_proximo_passo = true;
        if(estado_atual == VIGILIA_ANDANDO){
            estado_atual = VIGILIA_PARADO;
            tempo_estado.Restart();
        }
    }
    else{
        box.SomaVet(direcao);

        //se colidir em algo
        if(!TileAndavel(guarda_pos)){
            box.x = box_anterior.x;
            box.y = box_anterior.y;
            box.SubtraiVet(direcao*1.8);
            movimento_atual = PARADO;
            sp.PauseAnimation();
        }

        if(calcular_proximo_passo){
            movimento_atual = PARADO;
        }


        //Animação
        if(movimento_atual == SE){
            if(movimento_anterior != SE){
                sp.SetFrameStart(m_sudeste);
                sp.SetFrameAnimation(m_dur);
                movimento_anterior = SE;
            }
        }
        else if(movimento_atual == NE){
            if(movimento_anterior != NE){
                sp.SetFrameStart(m_nordeste);
                sp.SetFrameAnimation(m_dur);
                movimento_anterior = NE;
            }
        }
        else if(movimento_atual == NO){
            if(movimento_anterior != NO){
                sp.SetFrameStart(m_noroeste);
                sp.SetFrameAnimation(m_dur);
                movimento_anterior = NO;
            }
        }
        else if(movimento_atual == SO){
            if(movimento_anterior != SO){
                sp.SetFrameStart(m_sudoeste);
                sp.SetFrameAnimation(m_dur);
                movimento_anterior = SO;
            }
        }
    }       
    
}



bool GuardaObservador::TileAndavel(Vec2 pos){
    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    Vec2 t_pos = t_map->FindTile(pos.x, pos.y);
    int tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);

    if(t_map == nullptr){
        std::cout << "Tile map nao pode ser nullptr. GuardaObservador::TileAndavel" << std::endl;
        return(true);
    }

    //se colidir em algo
    if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
        return(false);
    }
    else{
        return(true);
    }
}

bool GuardaObservador::EstaNaVisao(Vec2 gaia_t_pos){
    int gx = gaia_t_pos.x;
    int gy = gaia_t_pos.y;
    int ix = guarda_t_pos.x;
    int iy = guarda_t_pos.y;

    if(sp.GetFrameStart() <= 4){ //olhando pra SE
        if((gx==ix&&gy==iy)  ||
        (gx==ix+1&&gy==iy-1) || (gx==ix+1&&gy==iy) || (gx==ix+1&&gy==iy+1) ||
        (gx==ix+2&&gy==iy-1) || (gx==ix+2&&gy==iy) || (gx==ix+2&&gy==iy+1)){
            return(true);
        }
        else{
            return(false);
        }
    }
    else if(sp.GetFrameStart() <= 8){ //olhando para NE
        if((gx==ix&&gx==iy)  ||
        (gx==ix-1&&gy==iy-1) || (gx==ix&&gy==iy-1) || (gx==ix+1&&gy==iy-1) ||
        (gx==ix-1&&gy==iy-12) || (gx==ix&&gy==iy-2) || (gx==ix+1&&gy==iy-2)){
            return(true);
        }
        else{
            return(false);
        }
    }
    else if(sp.GetFrameStart() <= 12){ //olhando para NO
        if((gx==ix&&gx==iy)  ||
        (gx==ix-1&&gy==iy-1) || (gx==ix-1&&gy==iy) || (gx==ix-1&&gy==iy+1) ||
        (gx==ix-2&&gy==iy-1) || (gx==ix-2&&gy==iy) || (gx==ix-2&&gy==iy+1)){
            return(true);
        }
        else{
            return(false);
        }
    }
    else{ //olhando para SO
        if((gx==ix&&gy==iy)  ||
        (gx==ix-1&&gy==iy+1) || (gx==ix&&gy==iy+1) || (gx==ix+1&&gy==iy+1) ||
        (gx==ix-1&&gy==iy+2) || (gx==ix&&gy==iy+2) || (gx==ix-2&&gy==iy+2)){
            return(true);
        }
        else{
            return(false);
        }
    }
}