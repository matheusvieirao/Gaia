#include "Gaia.hpp"

Gaia* Gaia::player;

Gaia::Gaia(float x, float y, int hp, int comodo){
    player = this;
    pause = false;

    sp_andando.Open("img/gaia_andando.png");
    sp_andando.SetFrameTotal(24);
    sp_andando.SetFrameStart(1);
    sp_andando.SetFrameAnimation(6);
    sp_andando.SetFrameTime(0.2);
    sp_andando.SetScaleX(0.9);
    sp_andando.SetScaleY(0.9);

    sp_correndo.Open("img/gaia_correndo.png");
    sp_correndo.SetFrameTotal(16);
    sp_correndo.SetFrameStart(1);
    sp_correndo.SetFrameAnimation(4);
    sp_correndo.SetFrameTime(0.15);
    sp_correndo.SetScaleX(1);
    sp_correndo.SetScaleY(1);

    sp_chicote.Open("img/gaia_chicote.png");
    sp_chicote.SetFrameTotal(40);
    sp_chicote.SetFrameStart(1);
    sp_chicote.SetFrameAnimation(10);
    sp_chicote.SetFrameTime(0.15);
    sp_chicote.SetScaleX(1.5);
    sp_chicote.SetScaleY(1.5);

    sp_carro.Open("img/gaia_carro.png");
    sp_carro.SetFrameTotal(36);
    sp_carro.SetFrameStart(1);
    sp_carro.SetFrameAnimation(9);
    sp_carro.SetFrameTime(0.2);
    sp_carro.SetScaleX(1.2);
    sp_carro.SetScaleY(1.2);

    sp_transparente.Open("img/gaia_transparente.png");
    sp_transparente.SetFrameTotal(24);
    sp_transparente.SetFrameStart(1);
    sp_transparente.SetFrameAnimation(6);
    sp_transparente.SetFrameTime(0.05);
    sp_transparente.SetRepetitions(1);

    m_dur = sp_andando.GetAnimationDur(); //quantos frames de animaçao tem em cada movimento
    m_sudeste = 1; //primeiro sprite em direçao ao movimento
    m_nordeste = 1+m_dur;
    m_noroeste = 1+m_dur*2;
    m_sudoeste = 1+m_dur*3;

    sprite_atual = ANDANDO;

    altura_pe = 30;
    altura_box_col = 60;
    largura_box_col = 80;

    box.x = x - sp_andando.GetWidth()/2;
    box.y = y - sp_andando.GetHeight() + altura_pe;
    box.w = sp_andando.GetWidth();
    box.h = sp_andando.GetHeight();

    box_anterior.x = box.x;
    box_anterior.y = box.y;
    box_anterior.w = box.w;
    box_anterior.h = box.h;

    modo_manual = true;
    primeiro_mov_modo_manual = false;
    dur_movimento.Restart();
    this->hp = hp;
//    AcharComodo();
//    printf("%d",GetComodoAtual());//nao funciona pq o ponteiro de tile map ainda nao ta pronto
    comodo_atual = comodo;
    pos_antiga = Vec2(x, y);
    pos_inicio_comodo = Vec2(x, y);
    //TrocarDeComodo(); //nao funciona pq o ponteiro de tile map ainda nao ta pronto
    ataque_chicote=-1;
    direcao = SE;

}

Gaia::~Gaia(){
    //dtor
}

void Gaia::Update(float dt){

    float vel = 500 * dt;// * em pixel por segundo
    InputManager& In = InputManager::GetInstance();
    dur_movimento.Update(dt);
    tempo_chicote.Update(dt);
    pos_antiga = Vec2(box.GetCenter().x, box.y+box.h-altura_pe);
    sprite_anterior = sprite_atual;




    if(!pause){
        if(!modo_manual){
            if(primeiro_mov_modo_manual){
                mov_atual = vet_mov.back();
                if(dur_movimento.Get() > (float)(76/((vel/dt))*0.973)){
                    dur_movimento.Restart();
                    primeiro_mov_modo_manual = false;
                }
            }
            if(dur_movimento.Get() > ((float)(76/((vel/dt)*0.5)*0.973))){ //sendo 0.5 o seno do angulo da inclinacao do tile e 72 a metade de sua altura.
                if(!vet_mov.empty()){
                    mov_atual = vet_mov.back();
                    vet_mov.pop_back();
                    dur_movimento.Restart();
                }
                else{
                    modo_manual = true;
                }
            }

            if(mov_atual == S){
                Andar(S, vel, dt);
                direcao = S;
            }
            else if(mov_atual == SE){
                Andar(SE, vel, dt);
                direcao = SE;
            }
            else if(mov_atual == L){
                Andar(L, vel, dt);
                direcao = L;
            }
            else if(mov_atual == NE){
                Andar(NE, vel, dt);
                direcao = NE;
            }
            else if(mov_atual == N){
                Andar(N, vel, dt);
                direcao = N;
            }
            else if(mov_atual == NO){
                Andar(NO, vel, dt);
                direcao = NO;
            }
            else if(mov_atual == O){
                Andar(O, vel, dt);
                direcao = O;
            }
            else if(mov_atual == SO){
                Andar(SO, vel, dt);
                direcao = SO;
            }
            else if(mov_atual == PARADO){
                Parar();
                if(In.IsKeyDown(SDLK_d)){
                    sprite_atual = TRANSPARENTE;
                    modo_manual = true;
                }

            }
        }

        if (modo_manual) {

            //alterar sprite
            if(sprite_atual == ANDANDO || sprite_atual == CORRENDO){
                if(In.IsKeyDown(SDLK_s)){
                    sprite_atual = CORRENDO;
                }
                else{
                    sprite_atual = ANDANDO;
                }
                if(In.KeyPress(SDLK_d)){
                    sprite_atual = TRANSPARENTE;
                }
                if(In.KeyPress(SDLK_f)){
                    sprite_atual = CHICOTE;
                    ataque_chicote = 0;
                }
            }
            if(sprite_atual == TRANSPARENTE){
                if(In.IsKeyDown(SDLK_d)){
                    sprite_atual = TRANSPARENTE;
                }
                if(In.KeyRelease(SDLK_d)){
                    sprite_atual = ANDANDO;
                }
            }
            if(sprite_atual == CHICOTE){
                float temp = sp_chicote.GetFrameTime();
                if(ataque_chicote==0){
                    som_chicote.Open("audio/sons/chicote doesnt hit.ogg");
                    som_chicote.Play(0);
                    ataque_chicote = 1;
                    tempo_chicote.Restart();
                }
                if(ataque_chicote == 1 || ataque_chicote == 2){
                    if(tempo_chicote.Get() < temp*2){
                        if(In.KeyPress(SDLK_f)){
                            ataque_chicote = 2;
                        }
                    }
                    else {
                        if(ataque_chicote == 2){
                            som_chicote.Open("audio/sons/chicote doesnt hit.ogg");
                            som_chicote.Play(0);
                            ataque_chicote = 3;
                            tempo_chicote.Restart();
                        }
                        else{
                            ataque_chicote = -1;
                            sprite_atual = ANDANDO;
                        }
                    }
                }
                if(ataque_chicote == 3 || ataque_chicote == 4) {
                    if(tempo_chicote.Get() < temp*2){
                        if(In.KeyPress(SDLK_f)){
                            ataque_chicote = 4;
                        }
                    }
                    else {
                        if(ataque_chicote == 4){
                            som_chicote.Open("audio/sons/chicote doesnt hit.ogg");
                            som_chicote.Play(0);
                            ataque_chicote = 5;
                            tempo_chicote.Restart();
                        }
                        else{
                            ataque_chicote = -1;
                            sprite_atual = ANDANDO;
                        }
                    }
                }
                if(ataque_chicote == 5 || ataque_chicote == 6){
                    if(tempo_chicote.Get() < temp*5){
                        if(In.KeyPress(SDLK_f)){
                            ataque_chicote = 6;
                        }
                    }
                    else {
                        if(ataque_chicote == 6){
                            som_chicote.Open("audio/sons/chicote doesnt hit.ogg");
                            som_chicote.Play(0);
                            ataque_chicote = 1;
                            tempo_chicote.Restart();
                        }
                        else{
                            ataque_chicote = -1;
                            sprite_atual = ANDANDO;
                        }
                    }
                }
            }


            if(sprite_atual == CARRO){
                if(comodo_atual != 8){
                    sprite_atual = ANDANDO;
                }
            }

            if(sprite_atual == ANDANDO){
                if(sprite_anterior != sprite_atual){
                    int centro_x = box.GetCenter().x;
                    int centro_y = box.GetCenter().y;
                    box.w = sp_andando.GetWidth();
                    box.h = sp_andando.GetHeight();
                    box.x = centro_x-box.w/2;
                    box.y = centro_y-box.h/2;
                    altura_pe = 30;
                    altura_box_col = 60;
                    largura_box_col = 80;
                    m_dur = sp_andando.GetAnimationDur();
                    m_sudeste = 1; //primeiro sprite em direçao ao movimento
                    m_nordeste = 1+m_dur;
                    m_noroeste = 1+m_dur*2;
                    m_sudoeste = 1+m_dur*3;
                }
                vel = 300 * dt;
            }
            else if(sprite_atual == CORRENDO){
                if(sprite_anterior != sprite_atual){
                    int centro_x = box.GetCenter().x;
                    int centro_y = box.GetCenter().y;
                    box.w = sp_correndo.GetWidth();
                    box.h = sp_correndo.GetHeight();
                    box.x = centro_x-box.w/2;
                    box.y = centro_y-box.h/2;
                    altura_pe = 50;
                    altura_box_col = 60;
                    largura_box_col = 80;
                    m_dur = sp_correndo.GetAnimationDur();
                    m_sudeste = 1; //primeiro sprite em direçao ao movimento
                    m_nordeste = 1+m_dur;
                    m_noroeste = 1+m_dur*2;
                    m_sudoeste = 1+m_dur*3;
                }
                vel = 500 * dt;
            }
            else if(sprite_atual == CHICOTE){
                if(sprite_anterior != sprite_atual){
                    int centro_x = box.GetCenter().x;
                    int centro_y = box.GetCenter().y;
                    box.w = sp_chicote.GetWidth();
                    box.h = sp_chicote.GetHeight();
                    box.x = centro_x-box.w/2;
                    box.y = centro_y-box.h/2;
                    altura_pe = 50;
                    altura_box_col = 60;
                    largura_box_col = 80;
                    m_dur = sp_chicote.GetAnimationDur();
                    m_sudeste = 1; //primeiro sprite em direçao ao movimento
                    m_nordeste = 1+m_dur;
                    m_noroeste = 1+m_dur*2;
                    m_sudoeste = 1+m_dur*3;
                }
            }
            else if(sprite_atual == TRANSPARENTE){
                if(sprite_anterior != sprite_atual){
                    som_transparente.Open("audio/sons/ficando invisivel.ogg");
                    som_transparente.Play(0);
                    int centro_x = box.GetCenter().x;
                    int centro_y = box.GetCenter().y;
                    box.w = sp_transparente.GetWidth();
                    box.h = sp_transparente.GetHeight();
                    box.x = centro_x-box.w/2;
                    box.y = centro_y-box.h/2;
                    altura_pe = 30;
                    altura_box_col = 60;
                    largura_box_col = 80;
                    m_dur = sp_transparente.GetAnimationDur();
                    m_sudeste = 1; //primeiro sprite em direçao ao movimento
                    m_nordeste = 1+m_dur;
                    m_noroeste = 1+m_dur*2;
                    m_sudoeste = 1+m_dur*3;
                }
            }
            else if(sprite_atual == CARRO){
                if(sprite_anterior != sprite_atual){
                    int centro_x = box.GetCenter().x;
                    int centro_y = box.GetCenter().y;
                    box.w = sp_carro.GetWidth();
                    box.h = sp_carro.GetHeight();
                    box.x = centro_x-box.w/2;
                    box.y = centro_y-box.h/2;
                    altura_pe = 50;
                    altura_box_col = 60;
                    largura_box_col = 80;
                }
                m_dur = sp_carro.GetAnimationDur();
                m_sudeste = 1; //primeiro sprite em direçao ao movimento
                m_nordeste = 1+m_dur;
                m_noroeste = 1+m_dur*2;
                m_sudoeste = 1+m_dur*3;
                vel = 800 * dt;
            }



            if(sprite_atual == ANDANDO || sprite_atual == CORRENDO){
                //se parar
                if(!In.IsKeyDown(SDLK_DOWN) && !In.IsKeyDown(SDLK_RIGHT) && !In.IsKeyDown(SDLK_UP) && !In.IsKeyDown(SDLK_LEFT)){
                    mov_anterior = PARADO;
                    Parar();
                }
                else{
                //se estiver em movimento obs:: os movimentos combinados (duas teclas, NE, NO, SE, SO) devem ser implementados antes dos movimentos simples (uma tecla, N, S, L, O)
                    if(In.IsKeysDown(SDLK_DOWN, SDLK_RIGHT)){
                        Andar(SE, vel, dt);
                        direcao = SE;
                    }
                    else if(In.IsKeysDown(SDLK_RIGHT, SDLK_UP)){
                        Andar(NE, vel, dt);
                        direcao = NE;
                    }
                    else if(In.IsKeysDown(SDLK_UP, SDLK_LEFT)){
                        Andar(NO, vel, dt);
                        direcao = NO;
                    }
                    else if(In.IsKeysDown(SDLK_LEFT, SDLK_DOWN)){
                        Andar(SO, vel, dt);
                        direcao = SO;
                    }
                    else if(In.IsKeyDown(SDLK_DOWN)){
                        Andar(SO, vel, dt);
                        direcao = SO;
                    }
                    else if(In.IsKeyDown(SDLK_RIGHT)){
                        Andar(SE, vel, dt);
                        direcao = SE;
                    }
                    else if(In.IsKeyDown(SDLK_UP)){
                        Andar(NE, vel, dt);
                        direcao = NE;
                    }
                    else if(In.IsKeyDown(SDLK_LEFT)){
                        Andar(NO, vel, dt);
                        direcao = NO;
                    }
                }
            }

            if(sprite_atual == CHICOTE){
                if(sprite_anterior != sprite_atual){
                    if(direcao == SE){
                        sp_chicote.SetFrameStart(m_sudeste);
                        sp_chicote.SetFrame(m_sudeste);
                    }
                    else if(direcao == NE){
                        sp_chicote.SetFrameStart(m_nordeste);
                        sp_chicote.SetFrame(m_nordeste);
                    }
                    else if(direcao == NO){
                        sp_chicote.SetFrameStart(m_noroeste);
                        sp_chicote.SetFrame(m_noroeste);
                    }
                    else if(direcao == SO){
                        sp_chicote.SetFrameStart(m_sudoeste);
                        sp_chicote.SetFrame(m_sudoeste);
                    }
                    else {
                        printf("erro em escolher a direcao do chicote de Gaia\n");
                    }
                }
            }

            if(sprite_atual == TRANSPARENTE){
                if(sprite_anterior != sprite_atual){
                    sp_transparente.SetRepetitions(1);
                    if(direcao == SE){
                        sp_transparente.SetFrameStart(m_sudeste);
                        sp_transparente.SetFrame(m_sudeste);
                    }
                    else if(direcao == NE){
                        sp_transparente.SetFrameStart(m_nordeste);
                        sp_transparente.SetFrame(m_nordeste);
                    }
                    else if(direcao == NO){
                        sp_transparente.SetFrameStart(m_noroeste);
                        sp_transparente.SetFrame(m_noroeste);
                    }
                    else if(direcao == SO){
                        sp_transparente.SetFrameStart(m_sudoeste);
                        sp_transparente.SetFrame(m_sudoeste);
                    }
                    else {
                        printf("Erro em escolher a direcao de ficar transparente\n");
                    }
                }
            }

            if(sprite_atual == CARRO){
                if(In.IsKeysDown(SDLK_DOWN, SDLK_RIGHT)){
                    Andar(SE, vel, dt);
                    direcao = SE;
                }
                else if(In.IsKeysDown(SDLK_RIGHT, SDLK_UP)){
                    Andar(NE, vel, dt);
                    direcao = NE;
                }
                else if(In.IsKeysDown(SDLK_UP, SDLK_LEFT)){
                    Andar(NO, vel, dt);
                    direcao = NO;
                }
                else if(In.IsKeysDown(SDLK_LEFT, SDLK_DOWN)){
                    Andar(SO, vel, dt);
                    direcao = SO;
                }
                else if(In.IsKeyDown(SDLK_DOWN)){
                    Andar(SO, vel, dt);
                    direcao = SO;
                }
                else if(In.IsKeyDown(SDLK_RIGHT)){
                    Andar(SE, vel, dt);
                    direcao = SE;
                }
                else if(In.IsKeyDown(SDLK_UP)){
                    Andar(NE, vel, dt);
                    direcao = NE;
                }
                else if(In.IsKeyDown(SDLK_LEFT)){
                    Andar(NO, vel, dt);
                    direcao = NO;
                }
            }
        }
    }

    if(sprite_atual == ANDANDO){
        sp_andando.Update(dt);
    }
    else if(sprite_atual == CORRENDO){
        sp_correndo.Update(dt);
    }
    else if(sprite_atual == CHICOTE){
        sp_chicote.Update(dt);
    }
    else if(sprite_atual == TRANSPARENTE){
        sp_transparente.Update(dt);
    }
    else if(sprite_atual == CARRO){
        sp_carro.Update(dt);
    }
}

void Gaia::Render(){
    if(sprite_atual == ANDANDO){
        sp_andando.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
    }
    else if(sprite_atual == CORRENDO){
        sp_correndo.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
    }
    else if(sprite_atual == CHICOTE){
        sp_chicote.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
    }
    else if(sprite_atual == TRANSPARENTE){
        sp_transparente.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
    }
    else if(sprite_atual == CARRO){
        sp_carro.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation);
    }
}

void Gaia::Andar(int mov, float vel, float dt){
    float cos_angulo = 0.866025403784438646763723170752936183471402626905190314027; //30º
    float sen_angulo = 0.5; //30º
    float tg_angulo = 0.577350269189625764509148780501957455647601751270126876018 ;// 30º
    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    int t_info;


    box_anterior.x = box.x;
    box_anterior.y = box.y;
    box_anterior.w = box.w;
    box_anterior.h = box.h;

    if(t_map == nullptr){
        Game::GetInstance().AddErro(12, "Gaia::Andar");
    }

    if(sprite_atual == ANDANDO){
        sp_andando.ResumeAnimation();
        if(mov == SE){
            if(mov_anterior != SE || sprite_anterior != sprite_atual){
                sp_andando.SetFrameStart(m_sudeste);
                sp_andando.SetFrameAnimation(m_dur);
                mov_anterior = SE;
            }
            box.x += cos_angulo * vel;
            box.y += sen_angulo* vel;
            //se andar em tiles vazios voltar o movimento feito (ficar parado)
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x -= cos_angulo * vel;
                box.y -= sen_angulo* vel;
                sp_andando.SetFrame(m_sudeste+1);
                sp_andando.PauseAnimation();
            }
        }
        else if(mov == NE){
            if(mov_anterior != NE || sprite_anterior != sprite_atual){
                sp_andando.SetFrameStart(m_nordeste);
                sp_andando.SetFrameAnimation(m_dur);
                mov_anterior = NE;
            }
            box.x += cos_angulo * vel;
            box.y -= sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x -= cos_angulo * vel;
                box.y += sen_angulo* vel;
                sp_andando.SetFrame(m_nordeste+1);
                sp_andando.PauseAnimation();
            }
        }
        else if(mov == NO){
            if(mov_anterior != NO || sprite_anterior != sprite_atual){
                sp_andando.SetFrameStart(m_noroeste);
                sp_andando.SetFrameAnimation(m_dur);
                mov_anterior = NO;
            }
            box.x -= cos_angulo * vel;
            box.y -= sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x += cos_angulo * vel;
                box.y += sen_angulo* vel;
                sp_andando.SetFrame(m_noroeste+1);
                sp_andando.PauseAnimation();
            }
        }
        else if(mov == SO){
            if(mov_anterior != SO || sprite_anterior != sprite_atual){
                sp_andando.SetFrameStart(m_sudoeste);
                sp_andando.SetFrameAnimation(m_dur);
                mov_anterior = SO;
            }
            box.x -= cos_angulo * vel;
            box.y += sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x += cos_angulo * vel;
                box.y -= sen_angulo* vel;
                sp_andando.SetFrame(m_sudoeste+1);
                sp_andando.PauseAnimation();
            }
        }
        else if(mov == PARADO){
            mov_anterior = PARADO;
            Parar();
        }
    }
    else if(sprite_atual == CORRENDO){
        sp_correndo.ResumeAnimation();
        if(mov == SE){
            if(mov_anterior != SE || sprite_anterior != sprite_atual){
                sp_correndo.SetFrameStart(m_sudeste);
                sp_correndo.SetFrameAnimation(m_dur);
                mov_anterior = SE;
            }
            box.x += cos_angulo * vel;
            box.y += sen_angulo* vel;
            //se andar em tiles vazios voltar o movimento feito (ficar parado)
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x -= cos_angulo * vel;
                box.y -= sen_angulo* vel;
                sp_correndo.SetFrame(m_sudeste+1);
                sp_correndo.PauseAnimation();
            }
        }
        else if(mov == NE){
            if(mov_anterior != NE || sprite_anterior != sprite_atual){
                sp_correndo.SetFrameStart(m_nordeste);
                sp_correndo.SetFrameAnimation(m_dur);
                mov_anterior = NE;
            }
            box.x += cos_angulo * vel;
            box.y -= sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x -= cos_angulo * vel;
                box.y += sen_angulo* vel;
                sp_correndo.SetFrame(m_nordeste+1);
                sp_correndo.PauseAnimation();
            }
        }
        else if(mov == NO){
            if(mov_anterior != NO || sprite_anterior != sprite_atual){
                sp_correndo.SetFrameStart(m_noroeste);
                sp_correndo.SetFrameAnimation(m_dur);
                mov_anterior = NO;
            }
            box.x -= cos_angulo * vel;
            box.y -= sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x += cos_angulo * vel;
                box.y += sen_angulo* vel;
                sp_correndo.SetFrame(m_noroeste+1);
                sp_correndo.PauseAnimation();
            }
        }
        else if(mov == SO){
            if(mov_anterior != SO || sprite_anterior != sprite_atual){
                sp_correndo.SetFrameStart(m_sudoeste);
                sp_correndo.SetFrameAnimation(m_dur);
                mov_anterior = SO;
            printf("2\n");
            }
            box.x -= cos_angulo * vel;
            box.y += sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x += cos_angulo * vel;
                box.y -= sen_angulo* vel;
                sp_correndo.SetFrame(m_sudoeste+1);
                sp_correndo.PauseAnimation();
            }
        }
        else if(mov == PARADO){
            mov_anterior = PARADO;
            Parar();
        }
    }
    else if(sprite_atual == CARRO){
        sp_carro.ResumeAnimation();
        if(mov == SE){
            if(mov_anterior != SE || sprite_anterior != sprite_atual){
                sp_carro.SetFrameStart(m_sudeste);
                sp_carro.SetFrameAnimation(m_dur);
                mov_anterior = SE;
            }
            box.x += cos_angulo * vel;
            box.y += sen_angulo* vel;
            //se andar em tiles vazios voltar o movimento feito (ficar parado)
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x -= cos_angulo * vel;
                box.y -= sen_angulo* vel;
                sp_carro.SetFrame(m_sudeste+1);
                sp_carro.PauseAnimation();
            }
        }
        else if(mov == NE){
            if(mov_anterior != NE || sprite_anterior != sprite_atual){
                sp_carro.SetFrameStart(m_nordeste);
                sp_carro.SetFrameAnimation(m_dur);
                mov_anterior = NE;
            }
            box.x += cos_angulo * vel;
            box.y -= sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x -= cos_angulo * vel;
                box.y += sen_angulo* vel;
                sp_carro.SetFrame(m_nordeste+1);
                sp_carro.PauseAnimation();
            }
        }
        else if(mov == NO){
            if(mov_anterior != NO || sprite_anterior != sprite_atual){
                sp_carro.SetFrameStart(m_noroeste);
                sp_carro.SetFrameAnimation(m_dur);
                mov_anterior = NO;
            }
            box.x -= cos_angulo * vel;
            box.y -= sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x += cos_angulo * vel;
                box.y += sen_angulo* vel;
                sp_carro.SetFrame(m_noroeste+1);
                sp_carro.PauseAnimation();
            }
        }
        else if(mov == SO){
            if(mov_anterior != SO || sprite_anterior != sprite_atual){
                sp_carro.SetFrameStart(m_sudoeste);
                sp_carro.SetFrameAnimation(m_dur);
                mov_anterior = SO;
            printf("2\n");
            }
            box.x -= cos_angulo * vel;
            box.y += sen_angulo* vel;
            Vec2 t_pos = GetTPos();
            t_info = t_map->GetTileInfo(comodo_atual, t_pos.x, t_pos.y);
            if(t_info == 0 || t_info ==  18 || t_info ==  19){
                box.x += cos_angulo * vel;
                box.y -= sen_angulo* vel;
                sp_carro.SetFrame(m_sudoeste+1);
                sp_carro.PauseAnimation();
            }
        }
        else if(mov == PARADO){
            mov_anterior = PARADO;
            Parar();
        }
    }

}
//
//void Gaia::Transparente(){
//    InputManager& In = InputManager::GetInstance();
//
//    if(In.KeyPress(SDLK_d)){
//        sp_transparente.SetRepetitions(1);
//        if(mov_anterior == SE){
//            sp_transparente.SetFrameStart(m_sudeste);
//        }
//        else if(mov_anterior == NE){
//            sp_transparente.SetFrameStart(m_nordeste);
//        }
//        else if(mov_anterior == NO){
//            sp_transparente.SetFrameStart(m_noroeste);
//        }
//        else if(mov_anterior == SO){
//            sp_transparente.SetFrameStart(m_sudoeste);
//            printf("3\n");
//        }
//        else {
//            printf("e\n");
//            sp_transparente.SetFrameStart(sp_andando.GetFrameStart());
//        }
//    }
//    if(In.IsKeyDown(SDLK_d)){
//        sprite_atual = TRANSPARENTE;
//    }
//    if(In.KeyRelease(SDLK_d)){
//        sprite_atual = ANDANDO;
//    }
//}

bool Gaia::EstaTransparente(){
    bool terminou_animacao=false;

    if(sp_transparente.GetFrame() > sp_transparente.GetFrameStart()+1){
        terminou_animacao = true;
    }

    return(sprite_atual==TRANSPARENTE && terminou_animacao);
}

void Gaia::Parar(){
    mov_anterior = PARADO;
    int mov = GetDirecao();

    if(sprite_atual == ANDANDO){
        if(mov == SE){
            sp_andando.SetFrame(m_sudeste+1);
            sp_andando.PauseAnimation();
        }
        else if(mov == NE){
            sp_andando.SetFrame(m_nordeste+1);
            sp_andando.PauseAnimation();
        }
        else if(mov == NO){
            sp_andando.SetFrame(m_noroeste+1);
            sp_andando.PauseAnimation();
        }
        else if(mov == SO){
            sp_andando.SetFrame(m_sudoeste+1);
            sp_andando.PauseAnimation();
        }
    }
    else if(sprite_atual == CORRENDO){
        if(mov == SE){
            sp_correndo.SetFrame(m_sudeste+1);
            sp_correndo.PauseAnimation();
        }
        else if(mov == NE){
            sp_correndo.SetFrame(m_nordeste+1);
            sp_correndo.PauseAnimation();
        }
        else if(mov == NO){
            sp_correndo.SetFrame(m_noroeste+1);
            sp_correndo.PauseAnimation();
        }
        else if(mov == SO){
            sp_correndo.SetFrame(m_sudoeste+1);
            sp_correndo.PauseAnimation();
        }
    }
    else if(sprite_atual == CHICOTE){
        if(mov == SE){
            sp_chicote.SetFrame(m_sudeste+1);
            sp_chicote.PauseAnimation();
        }
        else if(mov == NE){
            sp_chicote.SetFrame(m_nordeste+1);
            sp_chicote.PauseAnimation();
        }
        else if(mov == NO){
            sp_chicote.SetFrame(m_noroeste+1);
            sp_chicote.PauseAnimation();
        }
        else if(mov == SO){
            sp_chicote.SetFrame(m_sudoeste+1);
            sp_chicote.PauseAnimation();
        }
    }
    else if(sprite_atual == TRANSPARENTE){
        if(mov == SE){
            sp_transparente.SetFrame(m_sudeste+1);
            sp_transparente.PauseAnimation();
        }
        else if(mov == NE){
            sp_transparente.SetFrame(m_nordeste+1);
            sp_transparente.PauseAnimation();
        }
        else if(mov == NO){
            sp_transparente.SetFrame(m_noroeste+1);
            sp_transparente.PauseAnimation();
        }
        else if(mov == SO){
            sp_transparente.SetFrame(m_sudoeste+1);
            sp_transparente.PauseAnimation();
        }
    }
    else if(sprite_atual == CARRO){
        if(mov == SE){
            sp_carro.SetFrame(m_sudeste+1);
            sp_carro.PauseAnimation();
        }
        else if(mov == NE){
            sp_carro.SetFrame(m_nordeste+1);
            sp_carro.PauseAnimation();
        }
        else if(mov == NO){
            sp_carro.SetFrame(m_noroeste+1);
            sp_carro.PauseAnimation();
        }
        else if(mov == SO){
            sp_carro.SetFrame(m_sudoeste+1);
            sp_carro.PauseAnimation();
        }
    }
}

void Gaia::SetSpriteAtual(SpritesGaia sprite){
    sprite_atual = sprite;
}


Vec2 Gaia::GetPos(){
    return(Vec2(box.GetCenter().x, box.y+box.h-altura_pe));
}

Vec2 Gaia::GetTPos(){
    TileMap* t_map = Game::GetInstance().GetCurrentState().GetTileMap();
    Vec2 t_pos(0,0);

    if(t_map == nullptr){
        Game::GetInstance().AddErro(12, "Gaia::GetTPos");
    }
    else{
        t_pos = t_map->FindTile(box.GetCenter().x, box.y+box.h-altura_pe);
    }
    return(t_pos);
}

int Gaia::GetDirecao(){
    int frame_start;

    if(sprite_atual == ANDANDO){
        frame_start = sp_andando.GetFrameStart();
    }
    else if(sprite_atual == CORRENDO){
        frame_start = sp_correndo.GetFrameStart();
    }
    else if(sprite_atual == CHICOTE){
        frame_start = sp_chicote.GetFrameStart();
    }
    else if(sprite_atual == TRANSPARENTE){
        frame_start = sp_transparente.GetFrameStart();
    }
    else if(sprite_atual == CARRO){
        frame_start = sp_carro.GetFrameStart();
    }

    if(frame_start == m_nordeste){
        return(NE);
    }
    else if(frame_start == m_noroeste){
        return(NO);
    }
    else if(frame_start == m_sudeste){
        return(SE);
    }
    else if(frame_start == m_sudoeste){
        return(SO);
    }
    else {
        return(direcao);
    }
}

int Gaia::GetHP(){
    return(hp);
}

void Gaia::PushMovimento(int mov){
    vet_mov.push_back(mov);
    modo_manual = false;
    primeiro_mov_modo_manual = true;
    dur_movimento.Restart();
}

void Gaia::NotifyCollision(GameObject& other){
    if(other.Is("Guarda")){
        hp = -1;
    }
    if(other.Is("Velhor")){
        box.x = box_anterior.x;
        box.y = box_anterior.y;
    }
}

bool Gaia::Is(std::string type){
    return(type == "Gaia");
}

bool Gaia::IsDead(){
    if(hp <= 0){
        return (true);
    }
    else{
        return(false);
    }
}
