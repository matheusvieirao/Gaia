#include "State_00_Title.hpp"
#include "Game.hpp"
//#include "StateIndustriaT.hpp"
//#include "StateIndustriaSS.hpp"
#include "InputManager.hpp"
#include "Color.hpp"
#include "Game.hpp"
#include "Resources.hpp"
//#include "StateData.hpp"
#include "State_01_Historia.hpp"

//ç = \u00e7
State_00_Title::State_00_Title():pressSpace("font/URW Gothic L Demi.ttf", 50, BLENDED, "Pressione espaco para jogar", Color::white, 0, 0){
    int game_w = Game::GetInstance().GetWindowWidth();
    int game_h = Game::GetInstance().GetWindowHeight();

    pressSpace.SetPos(game_w/2, game_h-(game_h/7.5), true, true);

    menu.Open("img/telas/menu1.png");

    int w = menu.GetWidth();
    int h = menu.GetHeight();
    float scale_x = (float) game_w/w;
    float scale_y = (float) game_h/h;

    menu.SetScaleX(scale_x);
    menu.SetScaleY(scale_y);

    menu1.Open("img/telas/menu2.png");
    menu1.SetScaleX(scale_x);
    menu1.SetScaleY(scale_y);

    menu2.Open("img/telas/menu3.png");
    menu2.SetScaleX(scale_x);
    menu2.SetScaleY(scale_y);

    menu3.Open("img/telas/menu4.png");
    menu3.SetScaleX(scale_x);
    menu3.SetScaleY(scale_y);

    cont.Open("img/telas/cont.png");
    cont.SetScaleX(scale_x);
    cont.SetScaleY(scale_y);

    cont1.Open("img/telas/cont1.png");
    cont1.SetScaleX(scale_x);
    cont1.SetScaleY(scale_y);

    cont2.Open("img/telas/cont2.png");
    cont2.SetScaleX(scale_x);
    cont2.SetScaleY(scale_y);

    cont3.Open("img/telas/cont3.png");
    cont3.SetScaleX(scale_x);
    cont3.SetScaleY(scale_y);

    cont4.Open("img/telas/cont4.png");
    cont4.SetScaleX(scale_x);
    cont4.SetScaleY(scale_y);

    cont5.Open("img/telas/cont5.png");
    cont5.SetScaleX(scale_x);
    cont5.SetScaleY(scale_y);

    timer.Restart();
    if(!music.IsOpen()){
        music.Open("audio/00_title/musica title theme.ogg");
        music.Play(-1);
    }

    opcao1 = 1;
    opcao2 = 1;
    opcao2_antiga = 1;
    menu_continua = false;
}

State_00_Title::~State_00_Title(){
    objectArray.clear();
}

void State_00_Title::Update(float dt){
    InputManager& In = InputManager::GetInstance();

    //SELECT
    if(In.KeyPress(SDLK_DOWN)){
        opcao1++;
        if(opcao1>3){
            opcao1 = 1;
        }

        if(menu_continua){
            if(opcao2 == 1 || opcao2 == 2){
                opcao2_antiga = opcao2;
                opcao2 = 3;
            }
            else if(opcao2 == 3) {
                if (opcao2_antiga == 1 || opcao2_antiga == 5){
                    opcao2_antiga = opcao2;
                    opcao2 = 4;
                }
                else {
                    opcao2_antiga = opcao2;
                    opcao2 = 5;
                }
            }
            else { // 4 ou 5
                opcao2_antiga = opcao2;
                opcao2 = opcao2 - 3;
            }
        }
    }

    if(In.KeyPress(SDLK_UP)){
        opcao1--;
        if(opcao1<1){
            opcao1 = 3;
        }

        if(menu_continua){
            if(opcao2 == 1 || opcao2 == 2){
                opcao2_antiga = opcao2;
                opcao2 = opcao2 + 3;
            }
            else if(opcao2 == 3) {
                if (opcao2_antiga == 1 || opcao2_antiga == 5){
                    opcao2_antiga = opcao2;
                    opcao2 = 2;
                }
                else {
                    opcao2_antiga = opcao2;
                    opcao2 = 1;
                }
            }
            else { // 4 ou 5
                opcao2_antiga = opcao2;
                opcao2 = 3;
            }
        }
    }

    if(In.KeyPress(SDLK_RIGHT)){
        opcao1++;
        if(opcao1>3){
            opcao1 = 1;
        }

        if(menu_continua){
            if(opcao2 == 1 || opcao2 == 4){
                opcao2_antiga = opcao2;
                opcao2 = 3;
            }
            else if(opcao2 == 3) {
                if (opcao2_antiga == 1 || opcao2_antiga == 5){
                    opcao2_antiga = opcao2;
                    opcao2 = 2;
                }
                else {
                    opcao2_antiga = opcao2;
                    opcao2 = 5;
                }
            }
            else { // 2 ou 5
                opcao2_antiga = opcao2;
                opcao2--;
            }
        }
    }

    if(In.KeyPress(SDLK_LEFT)){
        opcao1--;
        if(opcao1<1){
            opcao1 = 3;
        }

        if(menu_continua){
            if(opcao2 == 1 || opcao2 == 4){
                opcao2_antiga = opcao2;
                opcao2++;
            }
            else if(opcao2 == 3) {
                if (opcao2_antiga == 2 || opcao2_antiga == 4){
                    opcao2_antiga = opcao2;
                    opcao2 = 1;
                }
                else {
                    opcao2_antiga = opcao2;
                    opcao2 = 4;
                }
            }
            else { // 2 ou 5
                opcao2_antiga = opcao2;
                opcao2 = 3;
            }
        }
    }

    timer.Update(dt);
    if(timer.Get() > 4){
        timer.Restart();
    }

    //ACTION
    if(!menu_continua){
        if(opcao1 == 1 || opcao1 == 0){
            if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                //inicio fase
                Resources::ClearResources();
                data.s1_num_historia = 1;
                Game::GetInstance().Push(new State_01_Historia(data));
                popRequested=true;
            }
        }
        else if(opcao1 == 2){
            if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                opcao1 = -1;
                if(!menu_continua){
                    menu_continua = true;
                }
            }
        }
        else if(opcao1 == 3){
            if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                quitRequested = true;
            }
        }
        if(In.KeyPress(SDLK_ESCAPE) || In.QuitRequested()){
            quitRequested = true;
        }
    }
    else {
        if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
            std::ifstream file_save;
            std::string string_aux;
            
            if(opcao2 == 1){
                file_save.open("save/save1.txt");
            }
            else if(opcao2 == 2){
                file_save.open("save/save2.txt");
            }
            else if(opcao2 == 3){
                file_save.open("save/save3.txt");
            }
            else if(opcao2 == 4){
                file_save.open("save/save4.txt");
            }
            else if(opcao2 == 5){
                file_save.open("save/save5.txt");
            }

            file_save >> string_aux >> data.s1_num_historia;
            file_save >> string_aux >> data.state_atual;
            file_save >> string_aux >> data.gaia_comodo;
            file_save >> string_aux >> data.gaia_t_pos.x >> data.gaia_t_pos.y;
            file_save >> string_aux >> data.gaia_t_pos_antiga.x >> data.gaia_t_pos_antiga.y;
            file_save >> string_aux >> data.gaia_t_pos_inicio_comodo.x >> data.gaia_t_pos_inicio_comodo.y;
            file_save >> string_aux >> data.gaia_hp;
            file_save >> string_aux >> data.gaia_poderes;

            file_save >> string_aux >> data.p_deposito;
            file_save >> string_aux >> data.p_corredor2;

            file_save >> string_aux >> data.esteira_ligada;
            
            file_save >> string_aux >> data.ja_mostrou_corre;
            file_save >> string_aux >> data.ja_mostrou_f_esteira;
            file_save >> string_aux >> data.ja_mostrou_f_chicote;

            file_save >> string_aux >> data.ja_ficou_encurralada;
            file_save >> string_aux >> data.ja_falou_velho;
            file_save >> string_aux >> data.ja_pegou_chave_rato;
            file_save >> string_aux >> data.ja_pegou_chicote;
            file_save.close();

            if(data.state_atual == 1){
                Game::GetInstance().Push(new State_01_Historia(data));
            }
            else if(data.state_atual == 2){
                Game::GetInstance().Push(new State_02_IndustriaT(data));
            }
            else if(data.state_atual == 3){
                Game::GetInstance().Push(new State_03_IndustriaSS(data));
            }
            popRequested = true;
        }
        if(In.QuitRequested()){
            quitRequested = true;
        }
        if(In.KeyPress(SDLK_ESCAPE)){
            opcao1 = 2;
            opcao2_antiga = 1;
            opcao2 = 1;
            menu_continua = false;
        }
    }
}

void State_00_Title::Render(){
    if(!menu_continua){
        if(opcao1 == 1){
            menu1.Render(0,0,0);
        }
        else if(opcao1 == 2){
            menu2.Render(0,0,0);
        }
        else if(opcao1 == 3){
            menu3.Render(0,0,0);
        }
        else{
            menu.Render(0,0,0);
        }
        if(timer.Get() < 2){
            pressSpace.Render(0,0);
        }
    }
    else{
        if(opcao2 == 1){
            cont1.Render(0,0,0);
        }
        else if(opcao2 == 2){
            cont2.Render(0,0,0);
        }
        else if(opcao2 == 3){
            cont3.Render(0,0,0);
        }
        else if(opcao2 == 4){
            cont4.Render(0,0,0);
        }
        else if(opcao2 == 5){
            cont5.Render(0,0,0);
        }
        else{
            cont.Render(0,0,0);
        }
    }
}

void State_00_Title::Pause(){
    music.Stop();
}

void State_00_Title::Resume(){
    //music.Play(-1);
}

bool State_00_Title::Is(std::string type){
    return (type == "State_00_Title");
}
