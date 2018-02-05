#include "State_01_Historia.hpp"

State_01_Historia::State_01_Historia(StateData data){
    num_historia = data.s1_num_historia;
    data.state_atual = 1;
    if(num_historia == 1){
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

    if(num_historia == 2){
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
    if(fala.IsOpen())
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

    if(num_historia == 1){
        
        if (track < 17){
            objectArray[track]->Render();
        }
        else {
            objectArray[16]->Render();
        }

        switch(track){
            case 0:
                if(Falar(0.1, "audio/01_historia/001A - bocejo.wav")){
                    track = 1;
                }
                break;

            case 1:
                if(Falar(0.1, "audio/01_historia/002A - ai que fome.wav")){
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
                if(Falar(0.1, "audio/01_historia/004A - puts.wav")){
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
                if(Falar(0.1, "audio/01_historia/005A - iae seu gg.wav")){
                    track = 7;
                }
                break;

            case 7:
                if(Falar(0.1, "audio/01_historia/006G - bom dia.wav")){
                    track = 8;
                }
                break;

            case 8:
                if(Falar(0.1, "audio/01_historia/007A - me ve um cafe.wav")){
                    track = 9;
                }
                break;

            case 9:
                if(Falar(0.1, "audio/01_historia/008G - eh pra ja.wav")){
                    track = 10;
                }
                break;

            case 10:
                if(Falar(0.6, "audio/01_historia/009X - dia foi puxado.wav")){
                    track = 11;
                }
                break;

            case 11:
                if(Falar(0.1, "audio/01_historia/010Ya - puts serio como foi.wav")){
                    track = 12;
                }
                break;

            case 12:
                if(Falar(0.1, "audio/01_historia/011X - mo correria.wav")){
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
                if(Falar(0.1, "audio/01_historia/012Y - e agora jose.wav")){
                    track = 15;
                }
                break;

            case 15:
                if(Falar(0.1, "audio/01_historia/013X - ja aconteceu antes.wav")){
                    track = 16;
                }
                break;

            case 16:
                if(Falar(1, "audio/01_historia/014A - que loucura.wav")){
                    track = 17;
                }
                break;

            case 17:
                if(tempo_falas.Get() > 1){
                    track = 18;
                }

            case 18:
                data.Carregar("inicio jogo");
                Game::GetInstance().Push(new State_02_IndustriaT(data));

                popRequested = true;
                break;

            case 19:
                break;

        }
    }


    if(num_historia == 2){
        if (track < 4){
            objectArray[track]->Render();
        }
        else {
            objectArray[3]->Render();
        }
    }
}

void State_01_Historia::Pause(){
    if(fala.IsOpen())
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
        else if(!fala.IsPlaying()){
            fala.Stop();
            tempo_falas.Restart();
            return(true);
        }
    }
    return(false);
}
