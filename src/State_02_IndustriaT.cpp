#include "State_02_IndustriaT.hpp"

//State_02_IndustriaT* State_02_IndustriaT::instance = nullptr;

State_02_IndustriaT::State_02_IndustriaT(StateData data):bg("img/telas/background.jpg"){
    //if(instance == nullptr){ //da erro se fizer isso
    //instance = this;

    num_fala = 0;
    track = 0;
    estado = JOGO;
    esta_pausado = false;

    bg.SetScaleX((float)Game::GetInstance().GetWindowWidth()/bg.GetWidth());
    bg.SetScaleY((float)Game::GetInstance().GetWindowHeight()/bg.GetHeight());
    tile_set = new TileSet(12, 11, 152, "img/tiles/tile_set.png");
    tile_map = new TileMap("map/02_industria/State_02_IndustriaT.txt", tile_set);

    sp_press_d.Open("img/teclas/tecla_d.png");
    float scale = (float)(Game::GetInstance().GetWindowWidth()/1.5)/sp_press_d.GetWidth();
    sp_press_d.SetScaleX(scale);
    sp_press_d.SetScaleY(scale);

    sp_corre.Open("img/teclas/tecla_corre.png");
    scale = (float)(Game::GetInstance().GetWindowWidth()/2)/sp_corre.GetWidth();
    sp_corre.SetScaleX(scale);
    sp_corre.SetScaleY(scale);

    this->data.Atribuir(data); 
    this->data.state_atual = 2;

    Vec2 gaia_pe_pos = data.gaia_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
    AddObject(new Gaia(gaia_pe_pos.x, gaia_pe_pos.y, data));

    Camera::Follow(Gaia::player);
    quitRequested = false;

    data.gaia_comodo = data.gaia_comodo;
    comodo_jogador_antigo = data.gaia_comodo;

    tempo_esteira.Restart();
    estado_esteira = 0;
    data.ja_ficou_encurralada = data.ja_ficou_encurralada;

    InicializarComodo(data.gaia_comodo);

}

State_02_IndustriaT::~State_02_IndustriaT(){
    objectArray.clear();
    //Resources::ClearResources(); ?
}

void State_02_IndustriaT::Update(float dt){
    InputManager& In = InputManager::GetInstance();
    Vec2 gaia_pos(0,0);
    if(Gaia::player != nullptr){
        gaia_pos = Gaia::player->GetPos();
    }

    data.gaia_t_pos_antiga.x = data.gaia_t_pos.x;
    data.gaia_t_pos_antiga.y = data.gaia_t_pos.y;
    data.gaia_t_pos = tile_map->FindTile(gaia_pos.x, gaia_pos.y);

    comodo_jogador_antigo = data.gaia_comodo;
    TrocarDeComodo(data.gaia_t_pos, data.gaia_t_pos_antiga);


    Camera::Update(dt);
    tempo_encurralada.Update(dt);
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


    if(In.QuitRequested()){
        quitRequested = true;
    }

    ////pause
    if(!esta_pausado){
        if(In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
            pause.SetPause();
        }
    }
    if(esta_pausado){ //esse if tem que estar depois do if passado.
        pause.Update(data);
    }
    if(pause.QuitRequested()){
        Game::GetInstance().Push(new State_00_Title());
        PopRequest();
    }
    esta_pausado = pause.IsPaused();


    ////jogo
    if(estado == JOGO && !esta_pausado){

        UpdateArray(dt); /////////////TEM UM ERRO AQUI QUANDO COMECA UM NOVO JOGO (com guarda)

        if(data.gaia_t_pos.x != data.gaia_t_pos_antiga.x || data.gaia_t_pos.y != data.gaia_t_pos_antiga.y){

            //pegou cartao
            if(tile_map->GetTileInfo(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y) == 87){
                tile_map->ChangeTile(data.gaia_comodo+2, data.gaia_t_pos.x, data.gaia_t_pos.y, 0);
                data.p_deposito = true;
                if(!efeito.IsOpen())
                    efeito.Open("audio/sons/got item.ogg");
                efeito.Play(0);
            }
            int tile_info = tile_map->GetTileInfo(data.gaia_comodo, data.gaia_t_pos.x, data.gaia_t_pos.y);

            //piso roxo, mudar de comodo
            if(tile_info == 13){
                //tubo de ar
                if(tile_map->GetTileInfo(data.gaia_comodo+1, data.gaia_t_pos.x, data.gaia_t_pos.y+1) == 5){
                    data.gaia_hp = Gaia::player->GetHP();
                    data.gaia_comodo = 4; //corredor do subsolo
                    data.gaia_t_pos_inicio_comodo = Vec2(4,14);
                    data.gaia_t_pos = Vec2(4,14);
                    Game::GetInstance().Push(new State_03_IndustriaSS(data));
                    PopRequest();
                    }
            }

            //piso azul, descer esteira
            if(tile_info == 15 ){
                data.gaia_hp = Gaia::player->GetHP();
                data.gaia_t_pos_inicio_comodo.x = data.gaia_t_pos.x;
                data.gaia_t_pos_inicio_comodo.y = data.gaia_t_pos.y+2;
                data.gaia_t_pos.y = data.gaia_t_pos.y+2;
                data.gaia_comodo = 12;
                Game::GetInstance().Push(new State_03_IndustriaSS(data));
                PopRequest();
            }
        }

        //som e animaçao esteira
        if(data.esteira_ligada && data.gaia_comodo == 0){
            if(!som_esteira.IsOpen()){
                som_esteira.Open("audio/sons/esteira loop.ogg");
                som_esteira.Play(-1);
            }
            int tile_info;
            tempo_esteira.Update(dt);
            if(tempo_esteira.Get() > 0.1){
                tempo_esteira.Restart();
                for(int j = 0; j < tile_map->GetHeight(); j++){
                    for(int i = 0; i < tile_map->GetWidth(); i++){
                        tile_info = tile_map->GetTileInfo(2,i,j);
                        if(tile_info >= 25 && tile_info <= 52){
                            if(tile_info == 27 || tile_info == 30 || tile_info == 33 || tile_info == 36 ||
                            tile_info == 43 || tile_info == 46 || tile_info == 49 || tile_info == 52){
                                tile_map->ChangeTile(2, i, j, tile_info-2);
                            }
                            else{
                                tile_map->ChangeTile(2, i, j, tile_info+1);
                            }
                        }
                    }
                }
            }
        }
        else{
            if(som_esteira.IsOpen()){
                som_esteira.Stop();
            }
        }

        if(data.gaia_comodo == 8){
            if(!som_ronco.IsOpen()){
                som_ronco.Open("audio/sons/ronco guarda.ogg");
                som_ronco.Play(-1);
            }
        }
        else{
            if(som_ronco.IsOpen()){ 
                som_ronco.Stop();
            }
        }

        //se apertar esquerda e S para de mostrar "corre"
        if(!data.ja_mostrou_corre){
            if(In.KeysPress(SDLK_LEFT, SDLK_s)){
                data.ja_mostrou_corre = true;
            }
        }

        //abrir ou fechar porta do corredor 2
        if(!data.p_corredor2){
            tile_map->ChangeTile(16, 52, 18, 0);
        }
        else{
            tile_map->ChangeTile(16, 52, 18, 13);
        }
        if(data.gaia_comodo == 12){
            data.p_corredor2 = true;
        }


        //parte que a gaia entra no lugar de ficar encurralada
        if(data.ja_ficou_encurralada < 3){
            TratarEncurralamento();
        }
    }

    else if(estado == FALA && !esta_pausado){
        if(In.KeyPress(SDLK_SPACE)){
            if(fala.IsOpen()){
                fala.Stop();
            }
            track++;
        }

        //Gaia eh encurralada e fica transparente
        if(num_fala == 1){
            if(track == 0){
                if(tempo_falas.Get() > 0.3){
                    if(!fala.IsOpen()){
                        fala.Open("audio/02_industria/001 - nossa o que foi isso.ogg");
                        fala.Play(0);
                    }
                    else if(!fala.IsPlaying()){
                        fala.Stop();
                        track = 1 ;
                        tempo_falas.Restart();
                    }
                }
            }
            if(track == 1){
                if(tempo_falas.Get() > 0.2){
                    if(!fala.IsOpen() ){
                        fala.Open("audio/02_industria/002 - ta mas agora pra onde ir.ogg");
                        fala.Play(0);
                    }
                    else if(!fala.IsPlaying()){
                        fala.Stop();
                        track = 2;
                    }
                }
            }
            if(track == 2){
                if(tempo_falas.Get() > 0.5){
                    if(!fala.IsOpen() ){
                        fala.Open("audio/02_industria/003 - o duto de ar.ogg");
                        fala.Play(0);
                    }
                    else if(!fala.IsPlaying()){
                        fala.Stop();
                        track = 3;
                    }
                }
            }
            if(track == 3){
                if(tempo_falas.Get() > 0.5){
                    if(!fala.IsOpen() ){
                        fala.Open("audio/02_industria/004 - mais perigoso do que aqui nao deve ser.ogg");
                        fala.Play(0);
                    }
                    else if(!fala.IsPlaying()){
                        fala.Stop();
                        track = 4;
                    }
                }
            }
            if(track > 3){
                num_fala = 0;
                estado = JOGO;
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
                if(fala.IsOpen()){
                    fala.Stop();
                }
                int r = rand() % 347;
                if(r<160){
                    fala.Open("audio/sons/morte1.ogg");
                }
                else if (r<305){
                    fala.Open("audio/sons/morte2.ogg");
                }
                else{
                    fala.Open("audio/sons/morri.ogg");
                }
                fala.Play(0);
                SDL_Delay(1800);
                data.gaia_hp = 10;
                data.gaia_t_pos = data.gaia_t_pos_inicio_comodo;
                //data.comecou_jogo = true;
                Game::GetInstance().Push(new State_02_IndustriaT(data));
                PopRequest();
            }
            //realmente é necessário apagar a gaia aqui? #Verdps
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State_02_IndustriaT::Render(){
    int game_w = Game::GetInstance().GetWindowWidth();
    int game_h = Game::GetInstance().GetWindowHeight();

    //Renderiza o Background
    bg.Render(0, 0, 0);

    tile_map->RenderLayer(data.gaia_comodo, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_piso_producao
    tile_map->RenderLayer(data.gaia_comodo+1, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_parede_up_producao
    tile_map->RenderLayer(data.gaia_comodo+2, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_objeto_producao

    //Renderiza Objetos
    RenderArray();

    //Desenha caixas de colisao
//    for (unsigned i = 0; i < objectArray.size(); i++) {
//        Rect box2 = objectArray[i]->GetBoxColisao();
//        box2.x -= Camera::pos.x;
//        box2.y -= Camera::pos.y;
//        Collision::DrawHitbox(box2);
//    }

    if(data.ja_ficou_encurralada == 2){
        sp_press_d.Render(game_w/2-sp_press_d.GetWidth()/2, game_h/4, 0);
    }

    if(!data.ja_mostrou_corre){
        sp_corre.Render(game_w/2-sp_corre.GetWidth()/2, game_h/2-sp_corre.GetHeight()/2, 0);
    }

    if(esta_pausado){
        pause.Render();
    }
}

void State_02_IndustriaT::TratarEncurralamento(){

    if( (data.ja_ficou_encurralada==0) && (data.gaia_t_pos.x == 12 && data.gaia_t_pos.y == 16 && (data.gaia_t_pos_antiga.x != 12 || data.gaia_t_pos_antiga.y != 16))){
        data.ja_ficou_encurralada = 1; //para ela poder pisar nesse espaço depois sem andar automaticamente de novo

        Gaia::player->PushMovimento(PARADO);
        Gaia::player->PushMovimento(PARADO);
        Gaia::player->PushMovimento(PARADO);
        Gaia::player->PushMovimento(PARADO);
        Gaia::player->PushMovimento(PARADO);
        Gaia::player->PushMovimento(PARADO);
        Gaia::player->PushMovimento(NO);
        Gaia::player->PushMovimento(NO);
        Gaia::player->PushMovimento(NO);
        Gaia::player->PushMovimento(NO);
        for(unsigned i=0; i < objectArray.size(); i++){
            if(objectArray[i]->Is("b2")){
                objectArray[i]->PushMovimento(NE);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
            }
            else if(objectArray[i]->Is("b1")){
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(SO);
                objectArray[i]->PushMovimento(NO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
            }
            else if(objectArray[i]->Is("c2")){
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(NE);
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
            }
            else if(objectArray[i]->Is("c1")){
                objectArray[i]->PushMovimento(SO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(SE);
                objectArray[i]->PushMovimento(PARADO);
                objectArray[i]->PushMovimento(PARADO);
            }
        }
    }
    if(data.ja_ficou_encurralada == 1){

        data.ja_ficou_encurralada = 2;
        tempo_encurralada.Restart();
    }
    if(data.ja_ficou_encurralada == 2){
        data.gaia_poderes = 1;
        Gaia::player->AtualizarData(data);
        if (Gaia::player->EstaTransparente() && tempo_encurralada.Get() > 1){
            tempo_encurralada.Restart();
            data.ja_ficou_encurralada = 3;
            estado = FALA;
            num_fala = 1;
            tempo_falas.Restart();
        }
    }
}

void State_02_IndustriaT::InicializarComodo(int comodo){
    if(comodo == 4) { //corredor
        Vec2 guarda_t_pos = Vec2(50, 17);
        Vec2 guarda_pe_pos = guarda_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        AddObject(new Guarda(guarda_pe_pos.x, guarda_pe_pos.y, Guarda::PERSEGUINDO, comodo, "a1"));

        guarda_t_pos = Vec2(48, 16);
        guarda_pe_pos = guarda_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        AddObject(new Guarda(guarda_pe_pos.x, guarda_pe_pos.y, Guarda::PERSEGUINDO, comodo, "a2"));

        guarda_t_pos = Vec2(50, 15);
        guarda_pe_pos = guarda_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        AddObject(new Guarda(guarda_pe_pos.x, guarda_pe_pos.y, Guarda::PERSEGUINDO, comodo, "a3"));

        Guarda::GuardaEstado estado_guarda;
        if(!data.ja_ficou_encurralada){
            estado_guarda = Guarda::PARADO_AUTOMATICO;
        }
        else{
            estado_guarda = Guarda::DESCANSANDO_PARADO;
        }

        guarda_t_pos = Vec2(11, 15);
        guarda_pe_pos = guarda_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        AddObject(new Guarda(guarda_pe_pos.x, guarda_pe_pos.y, estado_guarda, comodo, "b1"));

        guarda_t_pos = Vec2(11, 17);
        guarda_pe_pos = guarda_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        AddObject(new Guarda(guarda_pe_pos.x, guarda_pe_pos.y, estado_guarda, comodo, "b2"));

        guarda_t_pos = Vec2(3, 15);
        guarda_pe_pos = guarda_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        AddObject(new Guarda(guarda_pe_pos.x, guarda_pe_pos.y, estado_guarda, comodo, "c1"));

        guarda_t_pos = Vec2(3, 17);
        guarda_pe_pos = guarda_t_pos.CardToIsometricCenter(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        AddObject(new Guarda(guarda_pe_pos.x, guarda_pe_pos.y, estado_guarda, comodo, "c2"));
    }
    else if(comodo == 16) { //refeitorio
        std::vector<Vec2> v_guarda_t_pos;

        v_guarda_t_pos.push_back(Vec2(54,18));
        v_guarda_t_pos.push_back(Vec2(54,26));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(50,23));
        v_guarda_t_pos.push_back(Vec2(50,21));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(54,28));
        v_guarda_t_pos.push_back(Vec2(50,28));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(45,21));
        v_guarda_t_pos.push_back(Vec2(45,27));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(42,27));
        v_guarda_t_pos.push_back(Vec2(42,21));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

    }
    else if(comodo == 8){ //dormitorio
        std::vector<Vec2> v_guarda_t_pos;

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(33,27));
        v_guarda_t_pos.push_back(Vec2(33,22));
        v_guarda_t_pos.push_back(Vec2(28,22));
        v_guarda_t_pos.push_back(Vec2(28,27));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(28,22));
        v_guarda_t_pos.push_back(Vec2(28,27));
        v_guarda_t_pos.push_back(Vec2(33,27));
        v_guarda_t_pos.push_back(Vec2(33,22));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(15,24));
        v_guarda_t_pos.push_back(Vec2(24,24));
        v_guarda_t_pos.push_back(Vec2(15,24));
        v_guarda_t_pos.push_back(Vec2(15,22));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));

        v_guarda_t_pos.clear();
        v_guarda_t_pos.push_back(Vec2(24,27));
        v_guarda_t_pos.push_back(Vec2(17,27));
        AddObject(new GuardaObservador(v_guarda_t_pos, comodo, tile_map));
    }
}

bool State_02_IndustriaT::EstaZonaF(){
    Vec2 t_pos = Gaia::player->GetTPos();
    int direcao = Gaia::player->GetDirecao();
    int comodo_atual = Gaia::player->GetComodoAtual();

    if(tile_map->GetTileInfo(comodo_atual+2, t_pos.x, t_pos.y) == 11 ){
        return (true);
    }
    else if(direcao == NE && tile_map->GetTileInfo(comodo_atual+2, t_pos.x, t_pos.y-1) == 11){
        return (true);
    }
    return(false);
}

void State_02_IndustriaT::ZonaF(){
    Vec2 t_pos = Gaia::player->GetTPos();
    int direcao = Gaia::player->GetDirecao();
    int comodo_atual = Gaia::player->GetComodoAtual();

    if((tile_map->GetTileInfo(comodo_atual+2, t_pos.x, t_pos.y) == 11 ) ||
    (direcao == NE && tile_map->GetTileInfo(comodo_atual+2, t_pos.x, t_pos.y-1) == 11)){
        data.esteira_ligada = !data.esteira_ligada;
    }
}

void State_02_IndustriaT::RenderArray(){
    Vec2 pos;
    int info_1, info_2, info_3;
    SortArray();

    for (unsigned i = 0; i < objectArray.size(); i++) {

        objectArray[i]->Render();
        pos.x = objectArray[i]->box.GetCenter().x;
        pos.y = objectArray[i]->box.y + objectArray[i]->box.h - objectArray[i]->GetAlturaPe();
        pos = pos.IsometricToCard(tile_set->GetTileWidth(), tile_set->GetTileHeight());
        info_1 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x+1, pos.y);
        info_2 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x, pos.y+1);
        info_3 = tile_map->GetTileInfo(data.gaia_comodo+2, pos.x+1, pos.y+1);
        //se tiver um objeto na frente do jogador renderiza o objeto
        if(info_1 != 0 || info_2 != 0 || info_3 != 0 ){
            //se nao for esteira
            if(!((info_1 >= 25 && info_1 <= 52)||(info_2 >= 25 && info_2 <= 52)||(info_3 >= 25 && info_3 <= 52))){
                tile_map->RenderLayer(data.gaia_comodo+2, pos.x, pos.y, Camera::pos.x, Camera::pos.y); //Renderiza a camada t_objeto que estao abaixo ou na mesma linha do personagem
            }
        }
    }
}

bool State_02_IndustriaT::Is(std::string type){
    return(type == "State_02_IndustriaT");
}

void State_02_IndustriaT::Pause(){
    musica1.Stop(0);
    musica2.Stop(0);
    if(data.ja_pegou_chave_rato) {
        musica3.Stop(0);
    }
}

void State_02_IndustriaT::Resume(){
    if(!musica1.IsOpen()){
        musica1.Open("audio/02_industria/musica fase2 layer 1.ogg");
    }
    if(!musica2.IsOpen()){
        musica2.Open("audio/02_industria/musica fase2 layer 2.ogg");
    }
    if(!musica3.IsOpen()){
        musica3.Open("audio/02_industria/musica fase2 layer 3.ogg");
    }
    musica1.Play(-1);
    musica2.Play(-1);
    if(data.ja_pegou_chave_rato){
        musica3.Play(-1);
    }
}

TileMap* State_02_IndustriaT::GetTileMap(){
    return (tile_map);
}

void State_02_IndustriaT::TrocarDeComodo(Vec2 t_pos, Vec2 t_pos_antiga){
    if(t_pos.x != t_pos_antiga.x || t_pos.y != t_pos_antiga.y){
        if(tile_map->GetTileInfo(data.gaia_comodo, t_pos.x, t_pos.y) == 13 || tile_map->GetTileInfo(data.gaia_comodo, t_pos.x, t_pos.y) == 14) { //tile rosa ou vermelho
            for(int i=0; i<tile_map->GetDepth(); i=i+4){
                if(i != data.gaia_comodo){
                    if(tile_map->GetTileInfo(i, t_pos.x, t_pos.y) != 0){
                        data.gaia_comodo = i;
                        data.gaia_t_pos_inicio_comodo.x = t_pos.x;
                        data.gaia_t_pos_inicio_comodo.y = t_pos.y;
                        Gaia::player->AtualizarData(data);
                        break;
                    }
                }
            }
        }
    }
}
