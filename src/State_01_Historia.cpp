#include "State_01_Historia.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
//#include "StateIndustriaT.hpp"
#include "State_00_Title.hpp"

State_01_Historia::State_01_Historia(int parte){
    this->parte = parte;
    if(parte == 1){
        // indices de 0 a 16
        AddObject(new Animation("img/cenas/cena-1.png", true));
        AddObject(new Animation("img/cenas/cena-1-FALA.png", true));
        AddObject(new Animation("img/cenas/cena-2.png", true));
        AddObject(new Animation("img/cenas/cena-2-FALA2.png", true));
        AddObject(new Animation("img/cenas/cena-3.png", true));
        AddObject(new Animation("img/cenas/cena-4.png", true));
        AddObject(new Animation("img/cenas/cena-4-FALA1.png", true));
        AddObject(new Animation("img/cenas/cena-4-FALA2.png", true));
        AddObject(new Animation("img/cenas/cena-4-FALA3.png", true));
        AddObject(new Animation("img/cenas/cena-4-FALA4.png", true));
        AddObject(new Animation("img/cenas/cena-4-FALA5.png", true));
        AddObject(new Animation("img/cenas/cena-4-FALA6.png", true));
        AddObject(new Animation("img/cenas/cena-4-FALA7.png", true));
        AddObject(new Animation("img/cenas/cena-5.png", true));
        AddObject(new Animation("img/cenas/cena-5-FALA1.png", true));
        AddObject(new Animation("img/cenas/cena-5-FALA2.png", true));
        AddObject(new Animation("img/cenas/cena-5-FALA3.png", true));
    }

    if(parte == 2){
        //indices de 0 a 4
        AddObject(new Animation("img/cenas/cena-7.png", true));
        AddObject(new Animation("img/cenas/cena-8.png", true));
        AddObject(new Animation("img/cenas/cena-9.png", true));
        AddObject(new Animation("img/cenas/cena-10.png", true));
    }
    track = 0;
    tempo_falas.Restart();
}

State_01_Historia::~State_01_Historia(){
    fala.Stop();
    objectArray.clear();
}

void State_01_Historia::Update(float dt){
    InputManager& In = InputManager::GetInstance();

    tempo_falas.Update(dt);

    if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
        if(fala.IsOpen()){
            fala.Stop();
            tempo_falas.Restart();
        }
        track++;
    }
    if(In.KeyPress(SDLK_ESCAPE)){
        popRequested = true;
        Resources::ClearResources();
        Game::GetInstance().Push(new State_00_Title());
    }
    if(In.QuitRequested()){
        quitRequested = true;
    }
}

void State_01_Historia::Render(){

    if(parte == 1){
        
        if (track < 17){
            objectArray[track]->Render();
        }
        else {
            objectArray[16]->Render();
        }

        switch(track){
            case 0:
                if(Falar(0.1, "audio/fase1/001A - bocejo.wav")){
                    track = 1;
                }
                break;

            case 1:
                if(Falar(0.1, "audio/fase1/002A - ai que fome.wav")){
                    track = 2;
                }
                break;

            case 2:
                if(tempo_falas.Get() > 0.3){
                    track = 3;
                    tempo_falas.Restart();
                }
                break;

            case 3:
                if(Falar(0.1, "audio/fase1/004A - puts.wav")){
                    track = 4;
                }
                break;

            case 4:
                if(tempo_falas.Get() > 1.5){
                    track = 5;
                    tempo_falas.Restart();
                }
                break;
            case 5:
                if(tempo_falas.Get() > 0.5){
                    track = 6;
                    tempo_falas.Restart();
                }
                break;

            case 6:
                if(Falar(0.1, "audio/fase1/005A - iae seu gg.wav")){
                    track = 7;
                }
                break;

            case 7:
                if(Falar(0.1, "audio/fase1/006G - bom dia.wav")){
                    track = 8;
                }
                break;

            case 8:
                if(Falar(0.1, "audio/fase1/007A - me ve um cafe.wav")){
                    track = 9;
                }
                break;

            case 9:
                if(Falar(0.1, "audio/fase1/008G - eh pra ja.wav")){
                    track = 10;
                }
                break;

            case 10:
                if(Falar(0.6, "audio/fase1/009X - dia foi puxado.wav")){
                    track = 11;
                }
                break;

            case 11:
                if(Falar(0.1, "audio/fase1/010Ya - puts serio como foi.wav")){
                    track = 12;
                }
                break;

            case 12:
                if(Falar(0.1, "audio/fase1/011X - mo correria.wav")){
                    track = 13;
                }
                break;

            case 13:
                if(tempo_falas.Get() > 0.5){
                    track = 14;
                    tempo_falas.Restart();
                }
                break;

            case 14:
                if(Falar(0.1, "audio/fase1/012Y - e agora jose.wav")){
                    track = 15;
                }
                break;

            case 15:
                if(Falar(0.1, "audio/fase1/013X - ja aconteceu antes.wav")){
                    track = 16;
                }
                break;

            case 16:
                if(Falar(1, "audio/fase1/014A - que loucura.wav")){
                    track = 17;
                }
                break;

            case 17:
                if(tempo_falas.Get() > 1){
                    track = 18;
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
        if (track < 4){
            objectArray[track]->Render();
        }
        else {
            objectArray[3]->Render();
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
