#include "Guarda.hpp"

int turno = 0;
int flag_perseguindo = 0;

Guarda::Guarda(float x, float y, GuardaEstado estado_inicial, int comodo, std::string nome):sp("img/personagens/guarda_andando.png", 16, 1, 4, 0.2){
    tempo_estado.Restart();
    this->nome = nome;
    mov_automatico = false;
    pause = false;


    altura_pe = 19;
    largura_box_col = 78;
    altura_box_col = 40;
    box.x = x - sp.GetWidth()/2;
    box.y = y - sp.GetHeight() + altura_pe;
    box.w = sp.GetWidth();
    box.h = sp.GetHeight();

    box_anterior.x = box.x;
    box_anterior.y = box.y;
    box_anterior.w = box.w;
    box_anterior.h = box.h;

    comodo_atual = comodo;
    hp = 1;
    estado_atual = estado_inicial;
    movimento_atual = NO;

    if(estado_atual == PERSEGUINDO){
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
    }

}

Guarda::~Guarda(){
    //dtor
}

void Guarda::Update(float dt){
    if(Game::GetInstance().IsStateStackEmpty()){
        return;
    }
    turno++;
    printf("-------------------%d--------------------\n",turno);

    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    int tile_width = t_map->GetTileWidth();
    int tile_height = t_map->GetTileHeight();
    Vec2 gaia_pos = Gaia::player->GetPos();
    Vec2 gaia_t_pos = gaia_pos.IsometricToCard(tile_width, tile_height);
    Vec2 guarda_pos = Vec2(box.GetCenter().x, box.y+box.h-altura_pe);
    guarda_t_pos = guarda_pos.IsometricToCard(tile_width, tile_height);
    float vel_devagar = 200*dt;
    float vel_rapido = 550*dt;
    float tempo_devagar = (float)(tile_height*dt)/(vel_devagar);//tempo de andar 1 tile na velocidade devagar. a conta esta simplificada, o certo seria: "(tile_height/2) / ((vel_rapido*0.5)/dt) sendo 0.5 o seno do angulo da inclinacao do tile
    float tempo_rapido = (float)(tile_height*dt)/(2*vel_rapido);//tempo de andar 1 tile na velocidade rapido

    sp.Update(dt);

    tempo_estado.Update(dt);

    if(!pause){

        if(estado_atual == DESCANSANDO_PARADO){
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
        else if(estado_atual == PERSEGUINDO){
         //   printf("PERSEGUINDO\n");

            if(contador_fuga > 2 || tempo_estado.Get() > 2){
                contador_fuga = 0;
                caminho.clear();
                CalcularCaminho(gaia_t_pos, t_map);
                CalcularMovimentoAtual();
                tempo_estado.Restart();
            }
            
            printf("GP dx %.0f, x %.0f, dy %.0f, y %.0f\n",guarda_t_pos_desejada.x, guarda_t_pos.x, guarda_t_pos_desejada.y, guarda_t_pos.y);
            printf("tempo_estado %.4f, tempo rapido %.4f\n", tempo_estado.Get(), tempo_rapido);

            if(guarda_t_pos_desejada.x == guarda_t_pos.x && guarda_t_pos_desejada.y == guarda_t_pos.y){
                printf("_1\n");
                if (flag_perseguindo == 0){
                    printf("_1.1\n");
                    tempo_estado.Restart();
                    flag_perseguindo = 1;
                }
            }


            if(flag_perseguindo == 1 && tempo_estado.Get() > tempo_rapido){
                printf("_2\n");
                flag_perseguindo = 0;
                if(caminho.size() == 0){
                    printf("_3\n");
                    CalcularCaminho(gaia_t_pos, t_map);
                }
                CalcularMovimentoAtual();
                tempo_estado.Restart();
                contador_fuga++;
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
            }
        }
    }


    if(t_map == nullptr){
        Game::GetInstance().AddErro(12, "Guarda::Update");
    }
}

void Guarda::Render(){
    sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
}

int Guarda::AndarAleatorio(TileMap* t_map){
    int direcao;
    bool direcao_errada = true;
    int modulo = rand() % 12; //(0,3,4,5,8,9) = 1 tile | (1,2,6,10) = 2 tiles| (7,11) = 3 tiles
    int max_repeticoes = 0;

    if(modulo == 7|| modulo == 11){
        modulo = 3;
    }
    else if(modulo == 1 || modulo == 2 || modulo == 6 || modulo == 10){
        modulo = 2;
    }
    else{
        modulo = 1;
    }

    while(direcao_errada && max_repeticoes<10) {
        max_repeticoes++;
        direcao = rand() % 16;
        if(direcao == 0 || direcao == 9 || direcao == 11 || direcao == 15){ //SE
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x+1, guarda_t_pos.y) != 0 ){
                    movimento_atual = SE;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x+1, guarda_t_pos.y) != 0  &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x+2, guarda_t_pos.y) != 0 ){
                    movimento_atual = SE;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x+1, guarda_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x+2, guarda_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x+3, guarda_t_pos.y) != 0 ){
                    movimento_atual = SE;
                    direcao_errada = false;
                }
            }
        }
        else if(direcao == 1 || direcao == 3 || direcao == 7 || direcao == 14) { //NE
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y-1) != 0 ){
                    movimento_atual = NE;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y-1) != 0  &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y-2) != 0 ){
                    movimento_atual = NE;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y-1) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y-2) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y-3) != 0 ){
                    movimento_atual = NE;
                    direcao_errada = false;
                }
            }
        }
        else if(direcao == 2 || direcao == 5 || direcao == 10 || direcao == 13) { //NO
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x-1, guarda_t_pos.y) != 0 ){
                    movimento_atual = NO;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x-1, guarda_t_pos.y) != 0  &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x-2, guarda_t_pos.y) != 0 ){
                    movimento_atual = NO;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x-1, guarda_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x-2, guarda_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x-3, guarda_t_pos.y) != 0 ){
                    movimento_atual = NO;
                    direcao_errada = false;
                }
            }
        }
        else if(direcao == 4 || direcao == 6 || direcao == 8 || direcao == 12) { //SO
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y+1) != 0 ){
                    movimento_atual = SO;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y+1) != 0  &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y+2) != 0 ){
                    movimento_atual = SO;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y+1) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y+2) != 0 &&
                   t_map->GetTileInfo(comodo_atual, guarda_t_pos.x, guarda_t_pos.y+3) != 0 ){
                    movimento_atual = SO;
                    direcao_errada = false;
                }
            }
        }
    }

    return(modulo);
}

void Guarda::Andar(float vel, TileMap* t_map){
    float cos_angulo = 0.866025403784438646763723170752936183471402626905190314027; //30º
    float sen_angulo = 0.5; //30º
    int m_dur = 4; //quantos frames de animaçao tem em cada movimento
    int m_sudeste = 1;
    int m_nordeste = 5;
    int m_noroeste = 9;
    int m_sudoeste = 13;

    sp.ResumeAnimation();
    box_anterior.x = box.x;
    box_anterior.y = box.y;

    if(movimento_atual == SE){
        printf("se\n");
        if(movimento_anterior != SE){
            sp.SetFrameStart(m_sudeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = SE;
        }
        box.x += cos_angulo * vel;
        box.y += sen_angulo* vel;
        //se andar em tiles vazios voltar o movimento feito (ficar parado)
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        int tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x -= cos_angulo * vel;
            box.y -= sen_angulo* vel;
            sp.SetFrame(m_sudeste+1);
            sp.PauseAnimation();
        }
    }
    else if(movimento_atual == NE){
        printf("neee\n");
        if(movimento_anterior != NE){
            sp.SetFrameStart(m_nordeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = NE;
        }
        box.x += cos_angulo * vel;
        box.y -= sen_angulo* vel;
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        int tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x -= cos_angulo * vel;
            box.y += sen_angulo* vel;
            sp.SetFrame(m_nordeste+1);
            sp.PauseAnimation();
        }
    }
    else if(movimento_atual == NO){
        printf("no\n");
        if(movimento_anterior != NO){
            sp.SetFrameStart(m_noroeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = NO;
        }
        box.x -= cos_angulo * vel;
        box.y -= sen_angulo* vel;
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        int tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x += cos_angulo * vel;
            box.y += sen_angulo* vel;
            sp.SetFrame(m_noroeste+1);
            sp.PauseAnimation();
        }
    }
    else if(movimento_atual == SO){
        printf("so\n");
        if(movimento_anterior != SO){
            sp.SetFrameStart(m_sudoeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = SO;
        }
        box.x -= cos_angulo * vel;
        box.y += sen_angulo* vel;
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        int tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x += cos_angulo * vel;
            box.y -= sen_angulo* vel;
            sp.SetFrame(m_sudoeste+1);
            sp.PauseAnimation();
        }
    }
}

int Guarda::MaiorDistancia(Vec2 gaia_t_pos){
    int dif_x = (int)guarda_t_pos.x - (int)gaia_t_pos.x;
    int dif_y = (int)guarda_t_pos.y - (int)gaia_t_pos.y;
    int mod_dif_x = dif_x;
    if(dif_x < 0){
        mod_dif_x = -dif_x;
    }
    int mod_dif_y = dif_y;
    if(dif_y < 0){
        mod_dif_y = -dif_y;
    }
    if(mod_dif_x > mod_dif_y){
        return(mod_dif_x);
    }
    else{
        return(mod_dif_y);
    }
}

bool Guarda::EstaNaVisao(Vec2 gaia_t_pos){
    int gx = gaia_t_pos.x;
    int gy = gaia_t_pos.y;
    int ix = guarda_t_pos.x;
    int iy = guarda_t_pos.y;

    printf("visao gx %d, gy %d, ix %d, iy %d\n",gx,gy,ix,iy);

    if(sp.GetFrameStart() <= 4){ //olhando pra SE
        printf("olhando para SE\n");
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
        printf("olhando para NE\n");
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
        printf("olhando para NO\n");
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
        printf("olhando para SO\n");
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

void Guarda::AcharComodo(){

    if(!Game::GetInstance().IsStateStackEmpty()){

        TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();

        if(t_map == nullptr){
            Game::GetInstance().AddErro(12, "Guarda::AcharComodo");
            return;
        }
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);

        for(int i=0; i<t_map->GetDepth(); i=i+4){
            if(t_map->GetTileInfo(i, t_pos.x, t_pos.y) != 0){
                comodo_atual = i;
                break;
            }
        }
    }
}

int Guarda::GetAlturaPe(){
    return(altura_pe);
}

void Guarda::PushMovimento(int mov){
    movimentos.push_back(mov);
    mov_automatico = true;
}

void Guarda::NotifyCollision(GameObject& other){
    if(other.Is("Guarda")){
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
}

bool Guarda::Is(std::string type){
    return(type == "Guarda" || type == nome);
}

bool Guarda::IsDead(){
    return(false);
}

//retorna o tamanho do vetor caminho, que contem as coordenadas a se andar
int Guarda::CalcularCaminho(Vec2 gaia_t_pos, TileMap* t_map){
    printf("calccaminho\n");
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
                //printf("%d,%d | ",(int)cel_aux->x, (int)cel_aux->y);
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

void Guarda::CalcularMovimentoAtual(){
    printf("calc mov atual\n");
    if(caminho.size() > 0){
        movimento_atual = caminho.back();
        caminho.pop_back();
        if(movimento_atual == NE){
            printf("ne\n");
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
    }
}

bool Guarda::VerificarMapa(int x, int y, int map_width, int map_height){
    if (x>=0 && x<map_width && y>= 0 && y<map_height){
        if(mapa_aux[y*map_width + x] != 0){
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

float Guarda::QuantoFalta(int x, int y){
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

void Guarda::InserirOrdenado(int x, int y, Celula* cel_aux){
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

void Guarda::EncontraNoMesmoTile(Vec2 gaia_pos, Vec2 guarda_pos){
    Vec2 gaia_tine_t_pos = gaia_pos.IsometricToCard(6.9282032, 4);
    Vec2 guarda_tine_t_pos = guarda_pos.IsometricToCard(6.9282032, 4);

    int dif_x = (int)gaia_tine_t_pos.x - (int)guarda_tine_t_pos.x;
    int dif_y = (int)gaia_tine_t_pos.y - (int)guarda_tine_t_pos.y;
    int mod_dif_x = dif_x;
    if(dif_x < 0){
        mod_dif_x = -dif_x;
    }
    int mod_dif_y = dif_y;
    if(dif_y < 0){
        mod_dif_y = -dif_y;
    }

    if(mod_dif_x > mod_dif_y){
        if(dif_x > 3){
            movimento_atual = SE;
        }
        else if(dif_x < -3){
            movimento_atual = NO;
        }
        else{
            movimento_atual = PARADO;
        }
    }
    else{
        if(dif_y > 3){
            movimento_atual = SO;
        }
        else if(mod_dif_y < -3){
            movimento_atual = NE;
        }
        else{
            movimento_atual = PARADO;
        }
    }
}
