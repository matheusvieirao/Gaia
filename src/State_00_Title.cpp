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

    menu.Open("img/menu_title/menu1.png");

    int w = menu.GetWidth();
    int h = menu.GetHeight();
    float scale_x = (float) game_w/w;
    float scale_y = (float) game_h/h;

    menu.SetScaleX(scale_x);
    menu.SetScaleY(scale_y);


    menu1.Open("img/menu_title/menu2.png");
    menu1.SetScaleX(scale_x);
    menu1.SetScaleY(scale_y);

    menu2.Open("img/menu_title/menu3.png");
    menu2.SetScaleX(scale_x);
    menu2.SetScaleY(scale_y);

    menu3.Open("img/menu_title/menu4.png");
    menu3.SetScaleX(scale_x);
    menu3.SetScaleY(scale_y);

    cont.Open("img/menu_title/cont.png");
    cont.SetScaleX(scale_x);
    cont.SetScaleY(scale_y);

    cont1.Open("img/menu_title/cont1.png");
    cont1.SetScaleX(scale_x);
    cont1.SetScaleY(scale_y);

    cont2.Open("img/menu_title/cont2.png");
    cont2.SetScaleX(scale_x);
    cont2.SetScaleY(scale_y);

    cont3.Open("img/menu_title/cont3.png");
    cont3.SetScaleX(scale_x);
    cont3.SetScaleY(scale_y);

    cont4.Open("img/menu_title/cont4.png");
    cont4.SetScaleX(scale_x);
    cont4.SetScaleY(scale_y);

    cont5.Open("img/menu_title/cont5.png");
    cont5.SetScaleX(scale_x);
    cont5.SetScaleY(scale_y);



    timer.Restart();
    if(!music.IsOpen()){
        music.Open("audio/musicas/musica title theme.ogg");
        music.Play(-1);
    }

    opcao1 = 0;
    opcao2 = 0;
    menu_continua = false;
}

void State_00_Title::Update(float dt){
    InputManager& In = InputManager::GetInstance();

    if(In.KeyPress(SDLK_DOWN)){
        opcao1++;
        opcao2++;
        if(opcao1>3){
            opcao1 = 1;
        }
        if(opcao2>5){
            opcao2 = 1;
        }
    }
    if(In.KeyPress(SDLK_UP)){
        opcao1--;
        opcao2--;
        if(opcao1<1){
            opcao1 = 3;
        }
        if(opcao2<1){
            opcao2 = 5;
        }
    }

    timer.Update(dt);
    if(timer.Get() > 4){
        timer.Restart();
    }

    if(In.KeyPress(SDLK_ESCAPE) || In.QuitRequested()){
        quitRequested = true;
    }
    if(opcao1 == 1 || opcao1 == 0){
        if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
            //inicio fase
            Game::GetInstance().Push(new State_01_Historia(1));
            popRequested=true;
        }
    }
    if(menu_continua){
        if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
            if(opcao2 == 1){
                //antes do encurralamento
/////////////////////////////                Game::GetInstance().Push(new State_01_Historia(2));

                popRequested = true;
            }
            else if(opcao2 == 2){
/////////////////////////////                //antes da fala corredor SS
                // data.gaia_t_pos_inicio_comodo = Vec2(14, 16);
                // data.gaia_comodo = 4;
                // data.gaia_hp = 10;
                // data.p_deposito = false;
                // data.p_corredor2 = false;
                // data.esteira = false;
                // data.pegou_chave_rato = false;
                // data.ja_ficou_encurralada = 3;
                // data.corre = false;
                // data.ja_pressionou_f = false;
                // data.pegou_chicote = false;
                // data.fala_velho = false;
                // Game::GetInstance().Push(new StateIndustriaSS(data));

                popRequested = true;
            }
            else if(opcao2 == 3){
   /////////////////////////////             //depois de pegar o cartao
                // data.gaia_t_pos_inicio_comodo = Vec2(25, 16);
                // data.gaia_comodo = 4;
                // data.gaia_hp = 10;
                // data.corre = false;
                // data.ja_ficou_encurralada = 3;
                // data.fala_velho = true;
                // data.pegou_chave_rato = true;
                // data.ja_pressionou_f = true;
                // data.esteira = true;
                // data.p_deposito = true;
                // data.p_corredor2 = true;
                // data.pegou_chicote = false;
                // data.inventario.push_back(StateData::CHAVE_ENERGIA);
                // data.inventario.push_back(StateData::CARTAO_ACESSO);
                // Game::GetInstance().Push(new StateIndustriaSS(data));

                popRequested = true;
            }
            else if(opcao2 == 4){
   /////////////////////////////             //antes do encurralamento
                // data.gaia_t_pos_inicio_comodo.x = 15;
                // data.gaia_t_pos_inicio_comodo.y = 15;
                // data.gaia_comodo = 4;
                // data.gaia_hp = 10;
                // data.corre = false;
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

            }
            else if(opcao2 == 5){
                //depois da fala corredor SS
 /////////////////////////////               // data.gaia_t_pos_inicio_comodo = Vec2(25, 16);
                // data.gaia_comodo = 4;
                // data.gaia_hp = 10;
                // data.p_deposito = false;
                // data.p_corredor2 = true;
                // data.esteira = true;
                // data.pegou_chave_rato = true;
                // data.ja_ficou_encurralada = 3;
                // data.ja_pressionou_f = false;
                // data.corre = false;
                // data.pegou_chicote = false;
                // data.fala_velho = true;
                // data.inventario.push_back(StateData::CHAVE_ENERGIA);
                // data.inventario.push_back(StateData::CARTAO_ACESSO);
                // Game::GetInstance().Push(new StateIndustriaSS(data));

                popRequested = true;
            }
        }
    }

    else if(opcao1 == 2){
        if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
            opcao1 = -1;
            if(!menu_continua){
                opcao2 = 0;
                menu_continua = true;
            }
        }
    }

    else if(opcao1 == 3){
        if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
            quitRequested = true;
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
