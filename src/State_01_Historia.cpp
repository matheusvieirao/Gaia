#include "State_01_Historia.hpp"

State_01_Historia::State_01_Historia(StateData data){
    num_historia = data.s1_num_historia;
    data.state_atual = 1;

    if(num_historia == 1){
        // indices de 0 a 16
        vet_anim.push_back(Animation("img/cenas/cena-1.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-1-FALA.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-2.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-2-FALA2.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-3.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4-FALA1.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4-FALA2.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4-FALA3.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4-FALA4.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4-FALA5.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4-FALA6.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-4-FALA7.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-5.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-5-FALA1.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-5-FALA2.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-5-FALA3.png", true));
    }

    fim_jogo.Open("font/URW Gothic L Demi.ttf", 77, BLENDED, "Fim", Color::white, 0, 0);
    press_space.Open("font/URW Gothic L Demi.ttf", 50, BLENDED, "Pressione espaco para retornar ao menu", Color::white, 0, 0);
    int game_w = Game::GetInstance().GetWindowWidth();
    int game_h = Game::GetInstance().GetWindowHeight();

    fim_jogo.SetPos(game_w-fim_jogo.GetWidth()-35, game_h-(game_h/7.5)-press_space.GetHeight()-fim_jogo.GetHeight());
    press_space.SetPos(game_w/2, game_h-(game_h/7.5), true, true);
    if(num_historia == 2){
        //indices de 0 a 4
        vet_anim.push_back(Animation("img/cenas/cena-7.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-8.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-9.png", true));
        vet_anim.push_back(Animation("img/cenas/cena-10.png", true));
    }
    track = 0;
    tempo_falas.Restart();
}

State_01_Historia::~State_01_Historia(){
    if(fala.IsOpen())
        fala.Stop();
    vet_anim.clear();
}

void State_01_Historia::Update(float dt){
    InputManager& In = InputManager::GetInstance();

    tempo_falas.Update(dt);

    if(In.KeyPress(SDLK_m)){ // #verdps só coloquei isso aqui pra debugar e pular a animacao
        track = 16;
    }

    if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
        if(fala.IsOpen()){
            fala.Stop();
        }
        tempo_falas.Restart();
        track++;
    }
    if(In.KeyPress(SDLK_ESCAPE)){
        popRequested = true;
        Game::GetInstance().Push(new State_00_Title());
    }
    if(In.QuitRequested()){
        quitRequested = true;
    }

    if(num_historia == 1){
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
    else if(num_historia == 2){
        if(tempo_falas.Get() > 2.2){
            track++;
            tempo_falas.Restart();
        }
        if(track > 4){
            if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                popRequested = true;
                Game::GetInstance().Push(new State_00_Title());
            }
        }
    }
}

void State_01_Historia::Render(){

    if(num_historia == 1){
        
        if (track < 17){
            vet_anim[track].Render();
        }
        else {
            vet_anim[16].Render();
        }
    }


    if(num_historia == 2){
        if (track < 4){
            vet_anim[track].Render();
        }
        else if(track == 4){
            vet_anim[3].Render();
            fim_jogo.Render(0,0);
        }
        else if(track == 5){
            vet_anim[3].Render();
            fim_jogo.Render(0,0);
            press_space.Render(0,0);
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
