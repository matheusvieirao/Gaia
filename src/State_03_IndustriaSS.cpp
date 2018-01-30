#include "State_03_IndustriaSS.hpp"

//State_03_IndustriaSS* State_03_IndustriaSS::instance = nullptr;

State_03_IndustriaSS::State_03_IndustriaSS(StateData data):bg("img/telas/background.jpg"){
    if(!musica1.IsOpen()){
        musica1.Open("audio/02_industria/musica fase2 layer 1.ogg");
        musica1.Play(-1);
    }

    pause1.Open("img/telas/pause1.png");
    pause1.SetScaleX((float)Game::GetInstance().GetWindowWidth()/pause1.GetWidth());
    pause1.SetScaleY((float)Game::GetInstance().GetWindowHeight()/pause1.GetHeight());

    //if(instance == nullptr) //da erro se fizer isso ----------
    //instance = this;
    num_fala = 0;
    track = 0;
    estado = JOGO;
    pause = false;

    bg.SetScaleX((float)Game::GetInstance().GetWindowWidth()/bg.GetWidth());
    bg.SetScaleY((float)Game::GetInstance().GetWindowHeight()/bg.GetHeight());
    tile_set = new TileSet(12, 11, 152, "img/tiles/tile_set.png");
    tile_map = new TileMap("map/02_industria/State_03_IndustriaSS.txt", tile_set);

    press_f.Open("img/teclas/tecla_f.png");
    float scale = (float)(Game::GetInstance().GetWindowWidth()/3)/press_f.GetWidth();
    press_f.SetScaleX(scale);
    press_f.SetScaleY(scale);

    this->data.Atribuir(data);
    
    Vec2 gaia_pe_pos = this->data.gaia_t_pos.CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
    gaia_pe_pos.x = gaia_pe_pos.x + tile_set->GetTileWidth()/2;
    gaia_pe_pos.y = gaia_pe_pos.y + tile_set->GetTileHeight()/2;
    AddObject(new Gaia(gaia_pe_pos.x, gaia_pe_pos.y, data.gaia_hp, data.gaia_comodo));

    Camera::Follow(Gaia::player);
    quitRequested = false;

    entrou_no_comodo = true;
}

State_03_IndustriaSS::~State_03_IndustriaSS(){
    objectArray.clear();
}

void State_03_IndustriaSS::Update(float dt){
    InputManager& In = InputManager::GetInstance();
    Vec2 gaia_pos(0,0);
    if(Gaia::player != nullptr){
        gaia_pos = Gaia::player->GetPos();
    }

    //data.PrintData();

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
    if(entrou_no_comodo){
        entrou_no_comodo = false;
        InicializarComodo(data.gaia_comodo);
    }
    if(data.gaia_comodo != comodo_jogador_antigo){
        entrou_no_comodo = true;
        for(unsigned i = 0; i < objectArray.size(); i++){
            if(objectArray[i]->GetComodoAtual() == comodo_jogador_antigo){
                objectArray.erase(objectArray.begin() + i);
                i--;
            }
        }
    }

    //input
    if(In.KeyPress(SDLK_ESCAPE)){
        Game::GetInstance().Push(new State_00_Title());
        PopRequest();
    }

    if(In.QuitRequested()){
        quitRequested = true;
    }

    if(In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
        pause = !pause;
    }

    //jogo
    if(estado == JOGO && !pause){
        UpdateArray(Game::GetInstance().GetDeltaTime());

        if(data.gaia_t_pos.x != data.gaia_t_pos_antiga.x || data.gaia_t_pos.y != data.gaia_t_pos_antiga.y){
            //subir esteira
            if(tile_info == 15 ){
                data.gaia_hp = Gaia::player->GetHP();
                data.gaia_t_pos_inicio_comodo.x = data.gaia_t_pos.x;
                data.gaia_t_pos_inicio_comodo.y = data.gaia_t_pos.y-2;
                data.gaia_comodo = 0;
                Game::GetInstance().Push(new State_02_IndustriaT(data));
                PopRequest();
            }

            //fala com velhinho
            if(!data.fala_velho && data.gaia_t_pos.x == 16){
                Vec2 velho_t_pos(17,15);
                Vec2 velho_pe_pos = velho_t_pos.CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
                velho_pe_pos.x = velho_pe_pos.x + tile_set->GetTileWidth()/2;
                velho_pe_pos.y = velho_pe_pos.y + tile_set->GetTileHeight()/2;
                AddObject(new Velhor(velho_pe_pos.x, velho_pe_pos.y, data.gaia_comodo));
                estado = FALA;
                tempo_falas.Restart();
            }

            //bebidinha
            if(tile_map->GetTileInfo(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y) == 89){
                tile_map->ChangeTile(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y, 0);
                efeito.Open("audio/sons/got item.ogg");
                efeito.Play(0);
                data.inventario.push_back(StateData::BEBIDINHA);

            }

            //carrinho
            if(tile_map->GetTileInfo(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y) == 90){
                tile_map->ChangeTile(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y, 0);
                Gaia::player->SetSpriteAtual(Gaia::CARRO);
            }
        }

        if(data.esteira && data.gaia_comodo == 12){
            som_esteira.Open("audio/sons/esteira loop.ogg");
            som_esteira.Play(-1);
            int tile_info;
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

        //verifica inventario
        for(unsigned i = 0; i< data.inventario.size(); i++){
            if(data.inventario[i] == StateData::CARTAO_ACESSO){
                data.p_deposito = true;
            }
            if(data.inventario[i] == StateData::CHAVE_ENERGIA){
                data.pegou_chave_rato = true;
            }
        }

        if(gaia_direcao == NE){ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
        //esta atras do controle da esteira
        if(gaia_direcao == NE && tile_map->GetTileInfo(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y-1) == 88){
            printa_f = true;
            if(In.KeyPress(SDLK_f)){
                if(data.pegou_chave_rato == true){
                    if(data.esteira == true){
                        efeito.Open("audio/sons/desliga esteira.ogg");
                        data.esteira = false;
                    }
                    else{
                        efeito.Open("audio/sons/liga esteira.ogg");
                        data.esteira = true;
                    }
                    efeito.Play(0);
                }
                data.ja_pressionou_f = true;
                printa_f = false;
            }
        }
        else{
            printa_f = false;
        }

        if(!data.esteira){
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
    else if(estado == FALA && !pause){
        if(In.KeyPress(SDLK_SPACE)){
            if(fala.IsOpen()){
                fala.Stop();
            }
            track++;
        }

        if(!data.fala_velho){
            switch(track){
                case 0:
                    if(Falar(0.1, "audio/02_industria/003.wav")){
                        track = 1;
                    }
                    break;

                case 1:
                    if(Falar(0.2, "audio/02_industria/004.wav")){
                        track = 2;
                    }
                    break;

                case 2:
                    if(Falar(0.4, "audio/02_industria/005V - velho demais.wav")){
                        track = 3;
                    }
                    break;

                case 3:
                    if(Falar(0.5, "audio/02_industria/006G - tentou fugir.wav")){
                        track = 4;
                    }
                    break;

                case 4:
                    if(Falar(0.5, "audio/02_industria/007V - varias.wav")){
                        track = 5;
                    }
                    break;

                case 5:
                    if(Falar(0.5, "audio/02_industria/008G - algum plano.wav")){
                        track = 6;
                    }
                    break;

                case 6:
                    if(Falar(0.5, "audio/02_industria/009V - mapa na cabeca.wav")){
                        track = 7;
                    }
                    break;

                case 7:
                    if(Falar(0.5, "audio/02_industria/010G - como assim.wav")){
                        track = 8;
                    }
                    break;

                case 8:
                    if(Falar(0.5, "audio/02_industria/011V - com ctz vc vai.wav")){
                        track = 9;
                    }
                    break;

                case 9:
                    if(Falar(0.05, "audio/sons/ficando invisivel.ogg")){
                        track = 10;
                    }
                    break;

                case 10:
                    if(Falar(0.05, "audio/02_industria/012G - ler a mente.wav")){
                        track = 11;
                    }
                    break;

                case 11:
                    if(Falar(0.5, "audio/02_industria/013V - eu abrindo a mente.wav")){
                        track = 12;
                    }
                    break;

                case 12:
                    estado = JOGO;
                    track = 0;
                    data.fala_velho = true;
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
//    for (unsigned i = 0; i < objectArray.size(); i++) {
//        Rect box2 = objectArray[i]->GetBoxColisao();
//        box2.x -= Camera::pos.x;
//        box2.y -= Camera::pos.y;
//        Collision::DrawHitbox(box2);
//    }

    if(printa_f && data.ja_pressionou_f == false){
        press_f.Render(game_w/2-press_f.GetWidth()/2, game_h/4, 0);
    }

    if(pause){
        pause1.Render(0,0,0);
    }
}

void State_03_IndustriaSS::InicializarComodo(int comodo){

    if(comodo == 12){
        int num = rand() % 4;
        //29,17  43,28
        if(data.pegou_chave_rato==false){
            Vec2 rato_pe_pos = Vec2(28, 17).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
            rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
            rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
            AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, true));
        }
        if(num > 0){
            int x = (rand() % 15) + 29; // 29 <= x <= 43
            int y = (rand() % 12) + 17; // 17 <= y <= 28
            Vec2 rato_pe_pos = Vec2(x, y).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
            rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
            rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
            AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, false));
        }
        if(num > 1){
            int x = ((rand()*7) % 15) + 29; // 29 <= x <= 43
            int y = ((rand()*7) % 12) + 17; // 17 <= y <= 28
            Vec2 rato_pe_pos = Vec2(x, y).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
            rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
            rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
            AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, false));
        }
        if(num > 2){
            int x = ((rand()*17) % 15) + 29; // 29 <= x <= 43
            int y = ((rand()*17) % 12) + 17; // 17 <= y <= 28
            Vec2 rato_pe_pos = Vec2(x, y).CardToIsometric(tile_set->GetTileWidth(), tile_set->GetTileHeight());
            rato_pe_pos.x = rato_pe_pos.x + tile_set->GetTileWidth()/2;
            rato_pe_pos.y = rato_pe_pos.y + tile_set->GetTileHeight()/2;
            AddObject(new Rato(rato_pe_pos.x, rato_pe_pos.y, false));
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
        //se tiver um objeto na frente do jogador renderiza o objeto
        if(info_1 != 0 || info_2 != 0 || info_3 != 0 ){
            //se nao for esteira
            if(!((info_1 >= 25 && info_1 <= 52)||(info_2 >= 25 && info_2 <= 52)||(info_3 >= 25 && info_3 <= 52))){
                tile_map->RenderLayer(data.gaia_comodo+2, pos.x, pos.y, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_objeto que estao abaixo ou na mesma linha do personagem
    //            tile_map->RenderLayer(7, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_parede_dw
            }
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
}

void State_03_IndustriaSS::Resume(){

}

TileMap* State_03_IndustriaSS::GetTileMap(){
    return (tile_map);
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
                        data.gaia_comodo = i;
                        data.gaia_t_pos_inicio_comodo.x = data.gaia_t_pos.x;
                        data.gaia_t_pos_inicio_comodo.y = data.gaia_t_pos.y;
                        Gaia::player->SetComodoAtual(i);
                        break;
                    }
                }
            }
        }
    }
}

void State_03_IndustriaSS::PushInventario(StateData::Item item){
    data.inventario.push_back(item);
}