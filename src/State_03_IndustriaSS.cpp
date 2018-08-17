#include "State_03_IndustriaSS.hpp"

//State_03_IndustriaSS* State_03_IndustriaSS::instance = nullptr;

State_03_IndustriaSS::State_03_IndustriaSS(StateData data):bg("img/telas/background.jpg"){

    //if(instance == nullptr) //da erro se fizer isso ----------
    //instance = this;
    num_fala = 0;
    track = 0;
    estado = JOGO;
    esta_pausado = false;
    printa_f = false;
    printa_mapa_sem_x = false;
    printa_mapa_com_x = false;

    bg.SetScaleX((float)Game::GetInstance().GetWindowWidth()/bg.GetWidth());
    bg.SetScaleY((float)Game::GetInstance().GetWindowHeight()/bg.GetHeight());
    tile_set = new TileSet(12, 11, 152, "img/tiles/tile_set.png");

    tile_map = nullptr;
    tile_map = new TileMap("map/02_industria/State_03_IndustriaSS.txt", tile_set);

    press_f.Open("img/teclas/tecla_f.png");
    float scale = (float)(Game::GetInstance().GetWindowWidth()/3)/press_f.GetWidth();
    press_f.SetScaleX(scale);
    press_f.SetScaleY(scale);

    mapa_com_x.Open("img/mapa/Industria SS com x.jpg");
    scale = (float)(Game::GetInstance().GetWindowWidth()/1.5)/mapa_com_x.GetWidth();
    mapa_com_x.SetScaleX(scale);
    mapa_com_x.SetScaleY(scale);

    mapa_sem_x.Open("img/mapa/Industria SS sem x.jpg");
    scale = (float)(Game::GetInstance().GetWindowWidth()/1.5)/mapa_sem_x.GetWidth();
    mapa_sem_x.SetScaleX(scale);
    mapa_sem_x.SetScaleY(scale);


    this->data.Atribuir(data);
    this->data.state_atual = 3;
    
    Vec2 gaia_pe_pos = this->data.gaia_t_pos.CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
    gaia_pe_pos.x = gaia_pe_pos.x + tile_set->GetTileWidth()/2;
    gaia_pe_pos.y = gaia_pe_pos.y + tile_set->GetTileHeight()/2;
    AddObject(new Gaia(gaia_pe_pos.x, gaia_pe_pos.y, data));

    Camera::Follow(Gaia::player);
    quitRequested = false;

    InicializarComodo(data.gaia_comodo);
}

State_03_IndustriaSS::~State_03_IndustriaSS(){
    objectArray.clear();
}

void State_03_IndustriaSS::Update(float dt){
    int game_w = Game::GetInstance().GetWindowWidth();
    int game_h = Game::GetInstance().GetWindowHeight();

    InputManager& In = InputManager::GetInstance();
    Vec2 gaia_pos(0,0);
    if(Gaia::player != nullptr){
        gaia_pos = Gaia::player->GetPos();
    }

    data.gaia_t_pos_antiga.x = data.gaia_t_pos.x;
    data.gaia_t_pos_antiga.y = data.gaia_t_pos.y;
    data.gaia_t_pos = tile_map->FindTile(gaia_pos.x, gaia_pos.y);

    int gaia_direcao = Gaia::player->GetDirecao();

    comodo_jogador_antigo = data.gaia_comodo;
    TrocarDeComodo();

    int tile_info = tile_map->GetTileInfo(data.gaia_comodo, data.gaia_t_pos.x, data.gaia_t_pos.y);

    Camera::Update(dt);
    tempo_falas.Update(dt);

    //inicializar os comodos, colocar os inimigos e etc
    if(data.gaia_comodo != comodo_jogador_antigo){
        InicializarComodo(data.gaia_comodo);
        for(unsigned i = 0; i < objectArray.size(); i++){
            if(objectArray[i]->GetComodoAtual() == comodo_jogador_antigo){
                objectArray.erase(objectArray.begin() + i);
                i--;
            }
        }
    }

    ////input
    if(In.KeyPress(SDLK_ESCAPE)){
        Game::GetInstance().Push(new State_00_Title());
        PopRequest();
    }

    if(In.QuitRequested()){
        quitRequested = true;
    }


    ////pause
    if(!esta_pausado){
        if(In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
            pause.SetPause();
            Pause(); //para parar as musicas
        }
    }
    if(esta_pausado){ //esse if tem que estar depois do if passado.
        pause.Update(data);
        if(!pause.IsPaused()){
            Resume();
        }
    }
    if(pause.QuitRequested()){
        Game::GetInstance().Push(new State_00_Title());
        PopRequest();
    }
    esta_pausado = pause.IsPaused();


    ////jogo
    if(estado == JOGO && !esta_pausado){
        UpdateArray(Game::GetInstance().GetDeltaTime());

        if(data.gaia_t_pos.x != data.gaia_t_pos_antiga.x || data.gaia_t_pos.y != data.gaia_t_pos_antiga.y){
            //subir esteira
            if(tile_info == 15 ){
                data.gaia_hp = Gaia::player->GetHP();
                data.gaia_t_pos_inicio_comodo.x = data.gaia_t_pos.x;
                data.gaia_t_pos_inicio_comodo.y = data.gaia_t_pos.y-2;
                data.gaia_t_pos.y = data.gaia_t_pos.y-2; // #verdps ver se programa nao crasha com essa linha
                data.gaia_comodo = 0;
                Game::GetInstance().Push(new State_02_IndustriaT(data));
                PopRequest();
            }

            //fala com velhinho
            if(!data.ja_falou_velho && data.gaia_t_pos.x == 16){
                Vec2 velho_t_pos(17,15);
                Vec2 velho_pe_pos = velho_t_pos.CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
                velho_pe_pos.x = velho_pe_pos.x + tile_set->GetTileWidth()/2;
                velho_pe_pos.y = velho_pe_pos.y + tile_set->GetTileHeight()/2;
                AddObject(new Velhor(velho_pe_pos.x, velho_pe_pos.y, data.gaia_comodo));
                estado = FALA;
                tempo_falas.Restart();
            }

            //tile da poçao do chicote
            if(tile_map->GetTileInfo(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y) == 89){
                tile_map->ChangeTile(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y, 0);
                efeito.Open("audio/sons/got item.ogg");
                efeito.Play(0);
                data.ja_pegou_chicote = true;
                data.gaia_poderes = 2;
                Gaia::player->AtualizarData(data);
            }

            //entrar no carrinho
            if(tile_map->GetTileInfo(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y) == 90){
                tile_map->ChangeTile(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y, 0);
                Gaia::player->SetSpriteAtual(Gaia::CARRO);
            }
        }

        if(data.esteira_ligada && data.gaia_comodo == 12){
            if(!som_esteira.IsOpen()){
                som_esteira.Open("audio/sons/esteira loop.ogg");
                som_esteira.Play(-1);
            }
            tempo_esteira.Update(dt);
            if(tempo_esteira.Get() > 0.1){
                tempo_esteira.Restart();
                for(int j = 0; j < tile_map->GetHeight(); j++){
                    for(int i = 0; i < tile_map->GetWidth(); i++){
                        tile_info = tile_map->GetTileInfo(14,i,j);
                        if(tile_info >= 25 && tile_info <= 52){
                            if(tile_info == 27 || tile_info == 30 || tile_info == 33 || tile_info == 36 ||
                            tile_info == 43 || tile_info == 46 || tile_info == 49 || tile_info == 52){
                                tile_map->ChangeTile(14, i, j, tile_info-2);
                            }
                            else{
                                tile_map->ChangeTile(14, i, j, tile_info+1);
                            }
                        }
                    }
                }
            }
        }
        else{
            if(som_esteira.IsOpen())
                som_esteira.Stop();
        }

        //esta atras do controle da esteira
        if(gaia_direcao == NE && tile_map->GetTileInfo(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y-1) == 88){
            if(data.ja_pegou_chave_rato == true) {
                if(!data.ja_mostrou_f_esteira){
                        printa_f = true;
                }
                if(In.KeyPress(SDLK_f)){
                    if(!data.esteira_ligada){
                        efeito.Open("audio/sons/liga esteira.ogg");
                        data.esteira_ligada = true;
                        data.ja_mostrou_f_esteira = true;
                        printa_f = false;
                    }
                    else{
                        efeito.Open("audio/sons/desliga esteira.ogg");
                        data.esteira_ligada = false;
                    }
                    efeito.Play(0);
                    Gaia::player->AtualizarData(data);
                }
            }
        }
        else{
            printa_f = false;
        }

        if(!data.ja_mostrou_f_chicote && data.ja_pegou_chicote && data.gaia_comodo == 12){
            printa_f = true;
            if(In.KeyPress(SDLK_f)){
                printa_f = false;
                data.ja_mostrou_f_chicote = true;
            }
        }

        if(!data.esteira_ligada){
            tile_map->ChangeTile(12, 33, 15, 0);
        }
        else{
            tile_map->ChangeTile(12, 33, 15, 15);
        }

        if(!data.p_deposito){
            tile_map->ChangeTile(12, 26, 22, 0);
        }
        else{
            tile_map->ChangeTile(12, 26, 22, 14);
        }
    }
    else if(estado == FALA && !esta_pausado){
        if(In.KeyPress(SDLK_SPACE)){
            if(fala.IsOpen()){
                fala.Stop();
            }
            track++;
        }

        if(!data.ja_falou_velho){
            switch(track){
                case 0:
                    if(Falar(0.1, "audio/02_industria/005V - entao vc eh a garota.ogg")){
                        track = 1;
                    }
                    break;

                case 1:
                    if(Falar(0.2, "audio/02_industria/006G - quem eh vc.ogg")){
                        track = 2;
                    }
                    break;

                case 2:
                    if(Falar(0.4, "audio/02_industria/007V - apenas um velho trabalhador.ogg")){
                        track = 3;
                    }
                    break;

                case 3:
                    if(Falar(0.4, "audio/02_industria/008G - ja tentou fugir.ogg")){
                        track = 4;
                    }
                    break;

                case 4:
                    if(Falar(0.4, "audio/02_industria/009V - varias.ogg")){
                        track = 5;
                    }
                    break;

                case 5:
                    if(Falar(0.4, "audio/02_industria/010G - algum plano.ogg")){
                        track = 6;
                    }
                    break;

                case 6:
                    if(Falar(0.4, "audio/02_industria/011V - vc ta falando com a pessoa certa.ogg")){
                        track = 7;
                    }
                    break;

                case 7:
                    if(Falar(0, "audio/02_industria/012V - depois de tanto tempo eu tenho o mapa.ogg")){
                        track = 8;
                        ja_tocou_track_8 = false;
                    }
                    break;

                case 8:

                    if(!fala.IsOpen() && !ja_tocou_track_8){
                        fala.Open("audio/02_industria/013V - agora vai ate esse local.ogg");
                        fala.Play(0);
                    }
                    else if(!fala.IsPlaying()){
                        if(fala.IsOpen()){
                            fala.Stop();
                        }
                        ja_tocou_track_8 = true;
                    }

                    if(tempo_falas.Get() < 1){
                        printa_mapa_com_x = false;
                        printa_mapa_sem_x = true;
                    }
                    if(tempo_falas.Get() > 1) {
                        printa_mapa_com_x = true;
                        printa_mapa_sem_x = false;
                    }
                    if(tempo_falas.Get() > 2){
                        tempo_falas.Restart();
                    }

                    if(In.KeyPress(SDLK_SPACE || SDLK_RETURN || SDLK_RETURN2)){
                        track = 9;
                    }

                    break;

                case 9:
                    estado = JOGO;
                    track = 0;
                    data.ja_falou_velho = true;
                    printa_mapa_com_x = false;
                    printa_mapa_sem_x = false;
                    break;
            }
        }
    }


    //Colisao de objetos
    unsigned k = 1;
    for (unsigned i = 0; i < objectArray.size(); i++) {
        for (unsigned j = k; j < objectArray.size(); j++) {
            if(Collision::IsColliding(objectArray[i]->GetBoxColisao(), objectArray[j]->GetBoxColisao())){
                objectArray[i]->NotifyCollision(*objectArray[j]);
                objectArray[j]->NotifyCollision(*objectArray[i]);
            }
        }
    }

    //Deletar quem morrer
    for (unsigned i = 0; i < objectArray.size(); i++) {
        if(objectArray[i]->IsDead()){
            if(objectArray[i]->Is("Gaia")){

                int r = rand() % 347;
                Sound som_morte;
                if(r<160){
                    som_morte = Sound("audio/sons/morte1.ogg");
                }
                else if (r<305){
                    som_morte = Sound("audio/sons/morte2.ogg");
                }
                else{
                    som_morte = Sound("audio/sons/morri.ogg");
                }
                som_morte.Play(0);
                SDL_Delay(1800);
                data.gaia_hp = 10;
                data.gaia_t_pos = data.gaia_t_pos_inicio_comodo;
                Game::GetInstance().Push(new State_03_IndustriaSS(data));
                PopRequest();
            }
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }

    if(popRequested==true){
        if(musica1.IsOpen())
            musica1.Stop();
        if(fala.IsOpen())
            fala.Stop();
    }
}

void State_03_IndustriaSS::Render(){
    int game_w = Game::GetInstance().GetWindowWidth();
    int game_h = Game::GetInstance().GetWindowHeight();

    bg.Render(0, 0, 0); //Renderiza o Background

    tile_map->RenderLayer(data.gaia_comodo, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_piso_producao
    tile_map->RenderLayer(data.gaia_comodo+1, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_parede_up_producao
    tile_map->RenderLayer(data.gaia_comodo+2, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_objeto_producao

    RenderArray(); //Renderiza Objetos

    //Desenha caixas de colisao
    /*for (unsigned i = 0; i < objectArray.size(); i++) {
        Rect box2 = objectArray[i]->GetBoxColisao();
        box2.x -= Camera::pos.x;
        box2.y -= Camera::pos.y;
        Collision::DrawHitbox(box2);
    }*/

    if(printa_f){
        press_f.Render(game_w/2-press_f.GetWidth()/2, game_h/4, 0);
    }
    if(printa_mapa_sem_x){
        mapa_sem_x.Render(game_w/2-mapa_sem_x.GetWidth()/2, game_h/2-mapa_sem_x.GetHeight()/2, 0);
    }
    if(printa_mapa_com_x) {
        mapa_com_x.Render(game_w/2-mapa_com_x.GetWidth()/2, game_h/2-mapa_com_x.GetHeight()/2, 0);
    }

    if(esta_pausado){
        pause.Render();
    }
}

TileMap* State_03_IndustriaSS::GetTileMap(){
    return (tile_map);
}

void State_03_IndustriaSS::InicializarComodo(int comodo){

    if(comodo == 12){
        int num = rand() % 4;
        //29,17  43,28
        
        Vec2 rato_pe_pos = Vec2(28, 17).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
        rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
        AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, comodo, !data.ja_pegou_chave_rato));
        
        if(num > 0){
            Vec2 rato_pe_pos = Vec2(30, 24).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
            rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
            rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
            AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, comodo, false));
        }
        if(num > 1){
            Vec2 rato_pe_pos = Vec2(37, 28).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
            rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
            rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
            AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, comodo, false));
        }
        if(num > 2){
            Vec2 rato_pe_pos = Vec2(37, 16).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
            rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
            rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
            AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, comodo, false));
        }
    }
}


void State_03_IndustriaSS::RenderArray(){
    SortArray();
    Vec2 pos;
    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
        pos.x = objectArray[i]->box.GetCenter().x;
        pos.y = objectArray[i]->box.y + objectArray[i]->box.h - objectArray[i]->GetAlturaPe();
        pos = pos.IsometricToCard(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        int info_1 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x+1, pos.y);
        int info_2 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x, pos.y+1);
        int info_3 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x+1, pos.y+1);
        int info_4 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x+2, pos.y+1);
        int info_5 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x+1, pos.y+2);
        int info_6 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x+2, pos.y+2);
        int info_7 = tile_map->GetTileInfo(data.gaia_comodo+1, pos.x+1, pos.y+1); //para o caso parede quando a gaia cai no subsolo
        //se tiver um objeto na frente do jogador renderiza o objeto
        if(info_1 != 0 || info_2 != 0 || info_3 != 0 || info_4 != 0 || info_5 != 0 || info_6 != 0){
            //se nao for esteira
            if(info_1 >= 47 || info_2 >= 47 || info_3 >= 47 || info_4 >= 47 || info_5 >= 47 || info_6 >= 47){
                tile_map->RenderLayer(data.gaia_comodo+2, pos.x, pos.y, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_objeto que estao abaixo ou na mesma linha do personagem
    //            tile_map->RenderLayer(7, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_parede_dw
            }
        }
        if(info_7!=0){
            tile_map->RenderTile(data.gaia_comodo+1, pos.x+1, pos.y+1, Camera::pos.x, Camera::pos.y);
        }
    }
}

//State_03_IndustriaSS& State_03_IndustriaSS::GetInstance(){
//    return (*instance);
//}

bool State_03_IndustriaSS::Is(std::string type){
    return(type == "State_03_IndustriaSS");
}

void State_03_IndustriaSS::Pause(){
    if(musica1.IsOpen()){
        musica1.Stop();
    }
    if(som_esteira.IsOpen()){
        som_esteira.Stop();
    }
    if(efeito.IsOpen()){ 
        efeito.Stop();
    }
    if(fala.IsOpen()){ 
        fala.Stop();
    }
    SDL_Delay(10);
}

void State_03_IndustriaSS::Resume(){
    if(!musica1.IsOpen()){
        musica1.Open("audio/02_industria/musica fase2 layer 1.ogg");
        musica1.Play(-1);
    }
    SDL_Delay(10);
}

bool State_03_IndustriaSS::Falar(float delay, std::string arquivo){

    if(tempo_falas.Get() > delay){
        if(!fala.IsOpen()){
            fala.Open(arquivo);
            fala.Play(0);
        }
        else if(!fala.IsPlaying()){
            fala.Stop();
            tempo_falas.Restart();
            return(true);
        }
    }
    return(false);
}

void State_03_IndustriaSS::TrocarDeComodo(){
    if(data.gaia_t_pos.x != data.gaia_t_pos_antiga.x || data.gaia_t_pos.y != data.gaia_t_pos_antiga.y){
        if(tile_map->GetTileInfo(data.gaia_comodo, data.gaia_t_pos.x, data.gaia_t_pos.y) == 13 || tile_map->GetTileInfo(data.gaia_comodo, data.gaia_t_pos.x, data.gaia_t_pos.y) == 14) { //tile rosa
            for(int i=0; i<tile_map->GetDepth(); i=i+4){
                if(i != data.gaia_comodo){
                    if(tile_map->GetTileInfo(i, data.gaia_t_pos.x, data.gaia_t_pos.y) != 0){
                        //se saiu do deposito pra descarga
                        if(data.gaia_comodo == 8 && i == 12){
                            tile_map->Load("map/02_industria/State_03_IndustriaSS.txt"); //recarrega o mapa pro carro e as caixas voltarem pro lugar
                        }
                        data.gaia_comodo = i;
                        data.gaia_t_pos_inicio_comodo.x = data.gaia_t_pos.x;
                        data.gaia_t_pos_inicio_comodo.y = data.gaia_t_pos.y;
                        Gaia::player->AtualizarData(data);
                        break;
                    }
                }
            }
        }
    }
}