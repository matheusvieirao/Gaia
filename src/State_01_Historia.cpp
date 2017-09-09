#include "State_01_Historia.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
//#include "StateIndustriaT.hpp"
#include "State_00_Title.hpp"

State_01_Historia::State_01_Historia(int parte){
    int game_w = Game::GetInstance().GetWindowWidth();
    int game_h = Game::GetInstance().GetWindowHeight();
    this->parte = parte;
    if(parte == 1){
        sp_1p1.Open("img/cenas/cena-1.png");
        float sx = (float) game_w/sp_1p1.GetWidth();
        float sy = (float) game_h/sp_1p1.GetHeight();
        sp_1p1.SetScaleX(sx);
        sp_1p1.SetScaleY(sy);

        sp_1p2.Open("img/cenas/cena-1-FALA.png");
        sx = (float) game_w/sp_1p2.GetWidth();
        sy = (float) game_h/sp_1p2.GetHeight();
        sp_1p2.SetScaleX(sx);
        sp_1p2.SetScaleY(sy);

        sp_2p1.Open("img/cenas/cena-2.png");
        sx = (float) game_w/sp_2p1.GetWidth();
        sy = (float) game_h/sp_2p1.GetHeight();
        sp_2p1.SetScaleX(sx);
        sp_2p1.SetScaleY(sy);

        sp_2p2.Open("img/cenas/cena-2-FALA2.png");
        sx = (float) game_w/sp_2p2.GetWidth();
        sy = (float) game_h/sp_2p2.GetHeight();
        sp_2p2.SetScaleX(sx);
        sp_2p2.SetScaleY(sy);

        sp_3p1.Open("img/cenas/cena-3.png");
        sx = (float) game_w/sp_3p1.GetWidth();
        sy = (float) game_h/sp_3p1.GetHeight();
        sp_3p1.SetScaleX(sx);
        sp_3p1.SetScaleY(sy);

        sp_4p0.Open("img/cenas/cena-4.png");
        sx = (float) game_w/sp_4p0.GetWidth();
        sy = (float) game_h/sp_4p0.GetHeight();
        sp_4p0.SetScaleX(sx);
        sp_4p0.SetScaleY(sy);

        sp_4p1.Open("img/cenas/cena-4-FALA1.png");
        sx = (float) game_w/sp_4p1.GetWidth();
        sy = (float) game_h/sp_4p1.GetHeight();
        sp_4p1.SetScaleX(sx);
        sp_4p1.SetScaleY(sy);

        sp_4p2.Open("img/cenas/cena-4-FALA2.png");
        sx = (float) game_w/sp_4p2.GetWidth();
        sy = (float) game_h/sp_4p2.GetHeight();
        sp_4p2.SetScaleX(sx);
        sp_4p2.SetScaleY(sy);

        sp_4p3.Open("img/cenas/cena-4-FALA3.png");
        sx = (float) game_w/sp_4p3.GetWidth();
        sy = (float) game_h/sp_4p3.GetHeight();
        sp_4p3.SetScaleX(sx);
        sp_4p3.SetScaleY(sy);

        sp_4p4.Open("img/cenas/cena-4-FALA4.png");
        sx = (float) game_w/sp_4p4.GetWidth();
        sy = (float) game_h/sp_4p4.GetHeight();
        sp_4p4.SetScaleX(sx);
        sp_4p4.SetScaleY(sy);

        sp_4p5.Open("img/cenas/cena-4-FALA5.png");
        sx = (float) game_w/sp_4p5.GetWidth();
        sy = (float) game_h/sp_4p5.GetHeight();
        sp_4p5.SetScaleX(sx);
        sp_4p5.SetScaleY(sy);

        sp_4p6.Open("img/cenas/cena-4-FALA6.png");
        sx = (float) game_w/sp_4p6.GetWidth();
        sy = (float) game_h/sp_4p6.GetHeight();
        sp_4p6.SetScaleX(sx);
        sp_4p6.SetScaleY(sy);

        sp_4p7.Open("img/cenas/cena-4-FALA7.png");
        sx = (float) game_w/sp_4p7.GetWidth();
        sy = (float) game_h/sp_4p7.GetHeight();
        sp_4p7.SetScaleX(sx);
        sp_4p7.SetScaleY(sy);

        sp_5p1.Open("img/cenas/cena-5.png");
        sx = (float) game_w/sp_5p1.GetWidth();
        sy = (float) game_h/sp_5p1.GetHeight();
        sp_5p1.SetScaleX(sx);
        sp_5p1.SetScaleY(sy);

        sp_5p2.Open("img/cenas/cena-5-FALA1.png");
        sx = (float) game_w/sp_5p2.GetWidth();
        sy = (float) game_h/sp_5p2.GetHeight();
        sp_5p2.SetScaleX(sx);
        sp_5p2.SetScaleY(sy);

        sp_5p3.Open("img/cenas/cena-5-FALA2.png");
        sx = (float) game_w/sp_5p3.GetWidth();
        sy = (float) game_h/sp_5p3.GetHeight();
        sp_5p3.SetScaleX(sx);
        sp_5p3.SetScaleY(sy);

        sp_5p4.Open("img/cenas/cena-5-FALA3.png");
        sx = (float) game_w/sp_5p4.GetWidth();
        sy = (float) game_h/sp_5p4.GetHeight();
        sp_5p4.SetScaleX(sx);
        sp_5p4.SetScaleY(sy);

    }

    if(parte == 2){
        sp_7.Open("img/cenas/cena-7.png");
        float sx = (float) game_w/sp_7.GetWidth();
        float sy = (float) game_h/sp_7.GetHeight();
        sp_7.SetScaleX(sx);
        sp_7.SetScaleY(sy);

        sp_8.Open("img/cenas/cena-8.png");
         sx = (float) game_w/sp_8.GetWidth();
         sy = (float) game_h/sp_8.GetHeight();
        sp_8.SetScaleX(sx);
        sp_8.SetScaleY(sy);

        sp_9.Open("img/cenas/cena-9.png");
         sx = (float) game_w/sp_9.GetWidth();
        sy = (float) game_h/sp_9.GetHeight();
        sp_9.SetScaleX(sx);
        sp_9.SetScaleY(sy);

        sp_10.Open("img/cenas/cena-10.png");
        sx = (float) game_w/sp_10.GetWidth();
        sy = (float) game_h/sp_10.GetHeight();
        sp_10.SetScaleX(sx);
        sp_10.SetScaleY(sy);
    }
    track = 0;
    tempo_falas.Restart();
}

State_01_Historia::~State_01_Historia(){
    fala.Stop();
    //dtor
}

void State_01_Historia::Update(float dt){
    InputManager& In = InputManager::GetInstance();

    tempo_falas.Update(dt);


    if(In.KeyPress(SDLK_ESCAPE)){
        popRequested = true;
        Game::GetInstance().Push(new State_00_Title());
    }

    if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
        track++;
    }


    if(In.KeyPress(SDLK_SPACE)){
        if(fala.IsOpen()){
            fala.Stop();
        }
        track++;
    }
}

void State_01_Historia::Render(){

    if(parte == 1){
        switch(track){
            case 0:
                sp_1p1.Render(0,0,0);

                if(Falar(0.1, "audio/fase1/001A - bocejo.wav")){
                    track = 1;
                }
                break;

            case 1:
                sp_1p2.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/002A - ai que fome.wav")){
                    track = 2;
                }
                break;

            case 2:
                sp_2p1.Render(0,0,0);
                if(tempo_falas.Get() > 0.3){
                    track = 4;
                    tempo_falas.Restart();
                }
                break;

            case 3:
                sp_2p2.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/004A - puts.wav")){
                    track = 5;
                }
                break;

            case 4:
                sp_3p1.Render(0,0,0);
                if(tempo_falas.Get() > 1.5){
                    track = 6;
                    tempo_falas.Restart();
                }
                break;



            //sp_4p0.Open("img/cenas/cena-4.png");
            case 5:
                sp_4p0.Render(0,0,0);
                if(tempo_falas.Get() > 0.5){
                    track = 7;
                    tempo_falas.Restart();
                }
                break;

            case 6:
                sp_4p1.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/005A - iae seu gg.wav")){
                    track = 8;
                }
                break;

            case 7:
                sp_4p2.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/006G - bom dia.wav")){
                    track = 9;
                }
                break;

            //sp_4p3.Open("img/cenas/cena-4-FALA3.png");
            case 8:
                sp_4p3.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/007A - me ve um cafe.wav")){
                    track = 10;
                }
                break;

            case 9:
                sp_4p4.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/008G - eh pra ja.wav")){
                    track = 11;
                }
                break;

            //sp_4p5.Open("img/cenas/cena-4-FALA5.png");
            case 10:
                sp_4p5.Render(0,0,0);
                if(Falar(0.6, "audio/fase1/009X - dia foi puxado.wav")){
                    track = 12;
                }
                break;

            case 11:
                sp_4p6.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/010Ya - puts serio como foi.wav")){
                    track = 13;
                }
                break;

            //sp_4p7.Open("img/cenas/cena-4-FALA7.png");
            case 12:
                sp_4p7.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/011X - mo correria.wav")){
                    track = 14;
                }
                break;

            case 13:
                sp_5p1.Render(0,0,0);
                if(tempo_falas.Get() > 0.5){
                    track = 15;
                    tempo_falas.Restart();
                }
                break;

            case 14:
                sp_5p2.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/012Y - e agora jose.wav")){
                    track = 16;
                }
                break;

            case 15:
                sp_5p3.Render(0,0,0);
                if(Falar(0.1, "audio/fase1/013X - ja aconteceu antes.wav")){
                    track = 17;
                }
                break;

            case 16:
                sp_5p4.Render(0,0,0);
                if(Falar(1, "audio/fase1/014A - que loucura.wav")){
                    track = 18;
                }
                break;

            case 17:
                if(tempo_falas.Get() > 1){
                    track = 19;
                }

            case 18:
                // data.gaia_t_pos_inicio_comodo = Vec2(47, 15);
                // data.gaia_comodo = 4;
                // data.gaia_hp = 10;
                // data.corre = true;
                // data.ja_ficou_encurralada = 0;
                // data.fala_velho = false;
                // data.pegou_chave_rato = false;
                // data.ja_pressionou_f = 0;
                // data.esteira = false;
                // data.p_corredor2 = false;
                // data.p_deposito = false;
                // data.pegou_chicote = false;
                // Game::GetInstance().Push(new StateIndustriaT(data));

                popRequested = true;
                break;

            case 19:
                break;

        }
    }


    if(parte == 2){
        switch(track){
            case 0:
                sp_7.Render(0,0,0);
                break;

            case 1:
                sp_8.Render(0,0,0);
                break;

            case 2:
                sp_9.Render(0,0,0);
                break;

            case 3:
                sp_10.Render(0,0,0);
                break;
            case 4:
                sp_10.Render(0,0,0);
                break;

        }
    }
}

void State_01_Historia::Pause(){
    fala.Stop();
}

void State_01_Historia::Resume(){
    //music.Play(-1);
}

bool State_01_Historia::Is(std::string type){
    return(type == "State_01_Historia");
}

bool State_01_Historia::Falar(float delay, std::string arquivo){

    if(tempo_falas.Get() > delay){
        if(!fala.IsOpen()){
            fala.Open(arquivo);
            fala.Play(0);
        }
        if(!fala.IsPlaying()){
            fala.Stop();
            tempo_falas.Restart();
            return(true);
        }
    }
    return(false);
}
