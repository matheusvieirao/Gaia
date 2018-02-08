#include "Rato.hpp"
#include "Game.hpp"
#include "Gaia.hpp"
#include "Camera.hpp"

Rato::Rato(float x, float y, bool chave):sp("img/personagens/lularanha.png", 12, 1, 3, 0.2){
    altura_pe = 49;
    largura_box_col = 54;
    altura_box_col = 42;
    box.x = x - sp.GetWidth()/2;
    box.y = y - sp.GetHeight() + altura_pe;
    box.w = sp.GetWidth();
    box.h = sp.GetHeight();
    som.Open("audio/sons/rato.ogg");

    if(chave){
        sp_chave.Open("img/itens/chave.png");
    }

    AcharComodo();

    hp = 1;
    andar_n_tiles = 1;
    estado_atual = DESCANSANDO_PARADO;
    tempo_estado.Restart();
    movimento_atual = PARADO;
    this->chave = chave;
}

Rato::~Rato(){

}

void Rato::Update(float dt){
    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    int tile_width = t_map->GetTileWidth();
    int tile_height = t_map->GetTileHeight();
    Vec2 gaia_pos = Gaia::player->GetPos();
    Vec2 gaia_t_pos = gaia_pos.IsometricToCard(tile_width, tile_height);
    Vec2 rato_pos = Vec2(box.GetCenter().x, box.y+box.h-altura_pe);
    Vec2 rato_t_pos = rato_pos.IsometricToCard(tile_width, tile_height);
    float vel_devagar = 200*dt;
    float vel_rapido = 500*dt;
    float tempo_devagar = (float)tile_width/(vel_devagar/dt);//tempo de andar um tile na velocidade devagar
    float tempo_rapido = (float)tile_width/(vel_rapido/dt);//tempo de andar um tile na velocidade rapido
    int mod_maior_distancia;
    int estado_fulga = 0; //0 andar / 1 espreita

    tempo_estado.Update(dt);
    tempo_som.Update(dt);

    sp.Update(dt);

    if(estado_atual == DESCANSANDO_PARADO){
        mod_maior_distancia = MaiorDistancia(rato_t_pos, gaia_t_pos);
        if(tempo_estado.Get() > tempo_devagar){
            andar_n_tiles = AndarAleatorio(dt*vel_devagar, rato_t_pos, t_map);
            estado_atual = DESCANSANDO_ANDANDO;
            tempo_estado.Restart();
        }
        if(mod_maior_distancia < 3){
            estado_atual = FUGINDO;
            estado_fulga = CalcularFulga(rato_t_pos, gaia_t_pos, t_map);
            tempo_estado.Restart();
        }
    }
    else if(estado_atual == DESCANSANDO_ANDANDO){
        mod_maior_distancia = MaiorDistancia(rato_t_pos, gaia_t_pos);

        Andar(vel_devagar, t_map);

        if(tempo_estado.Get() > 2*andar_n_tiles*tempo_devagar){
            estado_atual = DESCANSANDO_PARADO;
            tempo_estado.Restart();
        }
        if(mod_maior_distancia < 3){
            estado_atual = FUGINDO;
            estado_fulga = CalcularFulga(rato_t_pos, gaia_t_pos, t_map);
            tempo_estado.Restart();
        }
    }
    else if(estado_atual == ESPREITA){
        mod_maior_distancia = MaiorDistancia(rato_t_pos, gaia_t_pos);

        PararParaTras();

        if(mod_maior_distancia < 4){
            estado_atual = FUGINDO;
            estado_fulga = CalcularFulga(rato_t_pos, gaia_t_pos, t_map);
            tempo_estado.Restart();
        }
        else if(mod_maior_distancia > 5 || tempo_estado.Get() > 3){
            estado_atual = DESCANSANDO_ANDANDO;
            tempo_estado.Restart();
        }
    }
    else if(estado_atual == FUGINDO){
        if(tempo_estado.Get() > tempo_rapido){
            estado_fulga = CalcularFulga(rato_t_pos, gaia_t_pos, t_map);
            tempo_estado.Restart();
        }

        if(estado_fulga == 1){
            estado_atual = ESPREITA;
            tempo_estado.Restart();
        }
        else {
            Andar(vel_rapido, t_map);
        }

         if(tempo_som.Get() > 1.5 && movimento_anterior != movimento_atual){
            som.Play(1);
            tempo_som.Restart();
        }
    }

    if(t_map == nullptr){
        std::cout << "t_map não pode ser nullptr. Rato::Update"  << std::endl;
    }
}

int Rato::AndarAleatorio(float vel, Vec2 rato_t_pos, TileMap* t_map){
    int direcao;
    int i = 0;
    bool direcao_errada = true;
    int modulo = rand() % 12; //(0,3,4,5,8,9) = 1 tile | (1,2,6,10) = 2 tiles| (7,11) = 3 tiles

    if(modulo == 7|| modulo == 11){
        modulo = 3;
    }
    else if(modulo == 1 || modulo == 2 || modulo == 6 || modulo == 10){
        modulo = 2;
    }
    else{ // modulo == (0,3,4,5,8,9)
        modulo = 1;
    }

    while(direcao_errada && i < 10) {
        i++;
        direcao = rand() % 16;
        if(direcao == 0 || direcao == 9 || direcao == 11 || direcao == 15){ //SE
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x+1, rato_t_pos.y) != 0 ){
                    movimento_atual = SE;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x+1, rato_t_pos.y) != 0  &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x+2, rato_t_pos.y) != 0 ){
                    movimento_atual = SE;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x+1, rato_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x+2, rato_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x+3, rato_t_pos.y) != 0 ){
                    movimento_atual = SE;
                    direcao_errada = false;
                }
            }
        }
        else if(direcao == 1 || direcao == 3 || direcao == 7 || direcao == 14) { //NE
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y-1) != 0 ){
                    movimento_atual = NE;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y-1) != 0  &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y-2) != 0 ){
                    movimento_atual = NE;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y-1) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y-2) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y-3) != 0 ){
                    movimento_atual = NE;
                    direcao_errada = false;
                }
            }
        }
        else if(direcao == 2 || direcao == 5 || direcao == 10 || direcao == 13) { //NO
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x-1, rato_t_pos.y) != 0 ){
                    movimento_atual = NO;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x-1, rato_t_pos.y) != 0  &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x-2, rato_t_pos.y) != 0 ){
                    movimento_atual = NO;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x-1, rato_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x-2, rato_t_pos.y) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x-3, rato_t_pos.y) != 0 ){
                    movimento_atual = NO;
                    direcao_errada = false;
                }
            }
        }
        else { //SO (direcao == 4 || direcao == 6 || direcao == 8 || direcao == 12)
            if(modulo == 1){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y+1) != 0 ){
                    movimento_atual = SO;
                    direcao_errada = false;
                }
            }
            else if(modulo == 2){
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y+1) != 0  &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y+2) != 0 ){
                    movimento_atual = SO;
                    direcao_errada = false;
                }
            }
            else{
                if(t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y+1) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y+2) != 0 &&
                   t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y+3) != 0 ){
                    movimento_atual = SO;
                    direcao_errada = false;
                }
            }
        }
    }

    //se nao achou lugar vazio aleatoriamente nas i t
    if(direcao_errada && t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y+1) != 0 ){
        movimento_atual = SO;
        modulo = 1;
        direcao_errada = false;
    }
    if(direcao_errada && t_map->GetTileInfo(comodo_atual, rato_t_pos.x, rato_t_pos.y-1) != 0 ){
        movimento_atual = NE;
        modulo = 1;
        direcao_errada = false;
    }
    if(direcao_errada && t_map->GetTileInfo(comodo_atual, rato_t_pos.x+1, rato_t_pos.y) != 0 ){
        movimento_atual = SE;
        modulo = 1;
        direcao_errada = false;
    }
    if(direcao_errada && t_map->GetTileInfo(comodo_atual, rato_t_pos.x-1, rato_t_pos.y) != 0 ){
        movimento_atual = NO;
        modulo = 1;
        direcao_errada = false;
    }
    if(direcao_errada){
        movimento_atual = NO;
        modulo = 1;
        direcao_errada = false;
    }

    return(modulo);
}

int Rato::MaiorDistancia(Vec2 rato_t_pos, Vec2 gaia_t_pos){
    int dif_x = (int)rato_t_pos.x - (int)gaia_t_pos.x;
    int dif_y = (int)rato_t_pos.y - (int)gaia_t_pos.y;
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

void Rato::PararParaTras(){
    int m_dur = sp.GetAnimationDur();
    int m_sudeste = 1;
    int m_nordeste = 1+m_dur;
    int m_noroeste = 1+m_dur*2;
    int m_sudoeste = 1+m_dur*3;

    if(movimento_atual == SE){
        sp.SetFrame(m_noroeste+1);
        sp.PauseAnimation();
    }
    else if(movimento_atual == NE){
        sp.SetFrame(m_sudoeste+1);
        sp.PauseAnimation();
    }
    else if(movimento_atual == NO){
        sp.SetFrame(m_sudeste+1);
        sp.PauseAnimation();
    }
    else if(movimento_atual == SO){
        sp.SetFrame(m_nordeste+1);
        sp.PauseAnimation();
    }

    movimento_atual = PARADO;
}

int Rato::CalcularFulga(Vec2 rato_t_pos, Vec2 gaia_t_pos, TileMap* t_map){
    int dir_oposta_jogador;
    int chance_aleatoria = rand() % 100;
    Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
    int info_tile_se = t_map->GetTileInfo(comodo_atual, t_pos.x+1, t_pos.y);
    int info_tile_ne = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y-1);
    int info_tile_no = t_map->GetTileInfo(comodo_atual, t_pos.x-1, t_pos.y);
    int info_tile_so = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y+1);
    int info_tile_2se = t_map->GetTileInfo(comodo_atual, t_pos.x+2, t_pos.y);
    int info_tile_2ne = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y-2);
    int info_tile_2no = t_map->GetTileInfo(comodo_atual-2, t_pos.x, t_pos.y);
    int info_tile_2so = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y+2);

    int dif_x = (int)rato_t_pos.x - (int)gaia_t_pos.x;
    int dif_y = (int)rato_t_pos.y - (int)gaia_t_pos.y;
    int mod_dif_x = dif_x;
    if(dif_x < 0){
        mod_dif_x = -dif_x;
    }
    int mod_dif_y = dif_y;
    if(dif_y < 0){
        mod_dif_y = -dif_y;
    }
    if(mod_dif_x > mod_dif_y){
        if(mod_dif_x < 4){ //distancia maxima que o rato pode fugir da gaia
            if(dif_x > 0){
                dir_oposta_jogador = SE;
            }
            else if (dif_x <= 0){
                dir_oposta_jogador = NO;
            }
        }
        else{
            return(1);
        }
    }
    else{
        if(mod_dif_y < 4){ //distancia maxima que o rato pode fugir da gaia
            if(dif_y > 0){
                dir_oposta_jogador = SO;
            }
            else if(dif_y <= 0){
                dir_oposta_jogador = NE;
            }
        }
        else{
            return(1);
        }
    }

    if(dif_x == 0){
        if (info_tile_no == 0 || info_tile_2no == 0){
            dif_x++;
            dir_oposta_jogador = SE;
        }
        else if (info_tile_se == 0 || info_tile_2se == 0){
            dif_x--;
            dir_oposta_jogador = NO;
        }
    }
    if(dif_y == 0){
        if (info_tile_ne == 0 || info_tile_2ne == 0){
            dif_y++;
            dir_oposta_jogador = SO;
        }
        else if (info_tile_so == 0 || info_tile_2so == 0){
            dif_y--;
            dir_oposta_jogador = NO;
        }
    }

    movimento_anterior = movimento_atual;

    if(dir_oposta_jogador == SE){
        if (info_tile_se == 0){
            if(dif_y > 0){
                movimento_atual = SO;
            }
            else{
                movimento_atual = NE;
            }
        }
        else if(info_tile_so == 0){ //tem uma parede ao sudoeste
            if(info_tile_se == 0 || mod_dif_x < 3){ //encurralado no sul || jogador ta chegando perto
                movimento_atual = NE;
            }
        }
        else if(info_tile_ne == 0){ //tem uma parede ao nordeste
            if(info_tile_se == 0 ||  mod_dif_x < 3){ //encurralado no leste || jogador ta chegando perto
                movimento_atual = SO;
            }
        }
        else if(chance_aleatoria > 90){ //uma chance aleatoria do inimigo mudar de rota mesmo nao estando sendo encurralado
            if(dif_y > 0){
                movimento_atual = SO;
            }
            else{
                movimento_atual = NE;
            }
        }
        else{
            movimento_atual = dir_oposta_jogador;
        }
    }

    if(dir_oposta_jogador == NO){
        if (info_tile_no == 0){
            if(dif_y > 0){
                movimento_atual = SO;
            }
            else{
                movimento_atual = NE;
            }
        }
        else if(info_tile_so == 0){ //tem uma parede ao sudoeste
            if(info_tile_no == 0 || mod_dif_x < 3){ // encurralado no oeste || jogador ta chegando perto
                movimento_atual = NE;
            }
        }
        else if(info_tile_ne == 0){ //tem uma parede ao nordeste
            if(info_tile_no == 0 || mod_dif_x < 3){ //encurralado no norte || jogador ta chegando perto
                movimento_atual = SO;
            }
        }
        else if(chance_aleatoria > 90){ //uma chance aleatoria do inimigo mudar de rota mesmo nao estando sendo encurralado
            if(dif_y > 0){
                movimento_atual = SO;
            }
            else{
                movimento_atual = NE;
            }
        }
        else{
            movimento_atual = dir_oposta_jogador;
        }
    }

    else if(dir_oposta_jogador == SO) {
        if(info_tile_so == 0){
            if(dif_x > 0){
                movimento_atual = SE;
            }
            else{
                movimento_atual = NO;
            }
        }
        if(info_tile_se == 0){ //tem uma parede ao sudeste
            if(info_tile_so == 0 || mod_dif_y < 3){ //encurralado no sul || jogador ta chegando perto
                movimento_atual = NO;
            }
        }
        else if(info_tile_no == 0){ //tem uma parede ao noroeste
            if(info_tile_so == 0 || mod_dif_y < 3){ //encurralado no oeste || jogador ta chegando perto
                movimento_atual = SE;
            }
        }
        else if(chance_aleatoria > 90){ //uma chance aleatoria do inimigo mudar de rota mesmo nao estando sendo encurralado
            if(dif_x > 0){
                movimento_atual = SE;
            }
            else{
                movimento_atual = NO;
            }
        }
        else{
            movimento_atual = dir_oposta_jogador;
        }
    }

    else if(dir_oposta_jogador == NE) {
        if(info_tile_ne == 0){
            if(dif_x > 0){
                movimento_atual = SE;
            }
            else{
                movimento_atual = NO;
            }
        }
        else if(info_tile_se == 0){ //tem uma parede ao sudeste
            if(info_tile_ne == 0 || mod_dif_y < 3){ // encurralado no leste || jogador ta chegando perto
                movimento_atual = NO;
            }
        }
        else if(info_tile_no == 0){ //tem uma parede ao noroeste
            if(info_tile_ne == 0 || mod_dif_y < 3){ // encurralado no norte || jogador ta chegando perto
                movimento_atual = SE;
            }
        }
        else if(chance_aleatoria > 90){ //uma chance aleatoria do inimigo mudar de rota mesmo nao estando sendo encurralado
            if(dif_x > 0){
                movimento_atual = SE;
            }
            else{
                movimento_atual = NO;
            }
        }
        else{
            movimento_atual = dir_oposta_jogador;
        }
    }

    return(0);
}

void Rato::Andar(float vel, TileMap* t_map){

    float cos_angulo = 0.866025404; //30º
    float sen_angulo = 0.5; //30º
    int m_dur = sp.GetAnimationDur(); //quantos frames de animaçao tem em cada movimento
    int m_sudeste = 1;
    int m_nordeste = 1+m_dur;
    int m_noroeste = 1+m_dur*2;
    int m_sudoeste = 1+m_dur*3;
    int tile_info;

    sp.ResumeAnimation();

    if(movimento_atual == SE){
        if(movimento_anterior != SE){
            sp.SetFrameStart(m_sudeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = SE;
        }
        box.x += cos_angulo * vel;
        box.y += sen_angulo* vel;
        //se andar em tiles vazios voltar o movimento feito (ficar parado)
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x -= cos_angulo * vel;
            box.y -= sen_angulo* vel;
            sp.SetFrame(m_sudeste+1);
            sp.PauseAnimation();
        }
    }
    else if(movimento_atual == NE){
        if(movimento_anterior != NE){
            sp.SetFrameStart(m_nordeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = NE;
        }
        box.x += cos_angulo * vel;
        box.y -= sen_angulo* vel;
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x -= cos_angulo * vel;
            box.y += sen_angulo* vel;
            sp.SetFrame(m_nordeste+1);
            sp.PauseAnimation();
        }
    }
    else if(movimento_atual == NO){
        if(movimento_anterior != NO){
            sp.SetFrameStart(m_noroeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = NO;
        }
        box.x -= cos_angulo * vel;
        box.y -= sen_angulo* vel;
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x += cos_angulo * vel;
            box.y += sen_angulo* vel;
            sp.SetFrame(m_noroeste+1);
            sp.PauseAnimation();
        }
    }
    else if(movimento_atual == SO){
        if(movimento_anterior != SO){
            sp.SetFrameStart(m_sudoeste);
            sp.SetFrameAnimation(m_dur);
            movimento_anterior = SO;
        }
        box.x -= cos_angulo * vel;
        box.y += sen_angulo* vel;
        Vec2 t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
        tile_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
        if(tile_info == 0 || tile_info == 13 || tile_info == 14 || tile_info == 18 || tile_info == 19){
            box.x += cos_angulo * vel;
            box.y -= sen_angulo* vel;
            sp.SetFrame(m_sudoeste+1);
            sp.PauseAnimation();
        }
    }
    else if(movimento_atual == PARADO){
        if(movimento_anterior != PARADO){
            movimento_anterior = PARADO;
        }
    }
}

void Rato::Render(){
    int x = box.x-Camera::pos.x;
    int y = box.y-Camera::pos.y;

    sp.Render(x, y, rotation);
    if(chave){
        int x_chave = x + box.w/2 - sp_chave.GetWidth()/2;
        int y_chave = y + box.h/2 - sp_chave.GetHeight()/2;
        sp_chave.Render(x_chave, y_chave, 0);
    }
}

int Rato::GetAlturaPe(){
    return(altura_pe);
}

void Rato::PushMovimento(int mov){

}


void Rato::NotifyCollision(GameObject& other){
    if(other.Is("Gaia")){
        if(chave==true){
            chave = false;
            Game::GetInstance().GetCurrentState().SetData("ja_pegou_chave_rato", true);
            if(!som_item.IsOpen())
                som_item.Open("audio/sons/got item.ogg");
            som_item.Play(0);
        }
    }
}

bool Rato::Is(std::string type){
    return(type=="Rato");
}

bool Rato::IsDead(){
    return(false);
}
