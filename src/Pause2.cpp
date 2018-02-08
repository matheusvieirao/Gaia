#include "Pause2.hpp"

Pause2::Pause2() {
	opcao1 = 1;
	opcao2 = 1;
	opcao2_antiga = 1;
	menu_continua = false;
    esta_pausado = false;
    quit = false;

    sp_pause0.Open("img/telas/pause0.png");
    sp_pause0.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pause0.GetWidth());
    sp_pause0.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pause0.GetHeight());

    sp_pause1.Open("img/telas/pause1.png");
    sp_pause1.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pause1.GetWidth());
    sp_pause1.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pause1.GetHeight());

    sp_pause2.Open("img/telas/pause2.png");
    sp_pause2.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pause2.GetWidth());
    sp_pause2.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pause2.GetHeight());

    sp_pause3.Open("img/telas/pause3.png");
    sp_pause3.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pause3.GetWidth());
    sp_pause3.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pause3.GetHeight());

    sp_pausecont1.Open("img/telas/pausecont1.png");
    sp_pausecont1.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pausecont1.GetWidth());
    sp_pausecont1.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pausecont1.GetHeight());

    sp_pausecont2.Open("img/telas/pausecont2.png");
    sp_pausecont2.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pausecont2.GetWidth());
    sp_pausecont2.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pausecont2.GetHeight());

    sp_pausecont3.Open("img/telas/pausecont3.png");
    sp_pausecont3.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pausecont3.GetWidth());
    sp_pausecont3.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pausecont3.GetHeight());

    sp_pausecont4.Open("img/telas/pausecont4.png");
    sp_pausecont4.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pausecont4.GetWidth());
    sp_pausecont4.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pausecont4.GetHeight());

    sp_pausecont5.Open("img/telas/pausecont5.png");
    sp_pausecont5.SetScaleX((float)Game::GetInstance().GetWindowWidth()/sp_pausecont5.GetWidth());
    sp_pausecont5.SetScaleY((float)Game::GetInstance().GetWindowHeight()/sp_pausecont5.GetHeight());
}


void Pause2::Update(StateData data) {
    if(esta_pausado){

    	InputManager& In = InputManager::GetInstance();

    	esta_pausado = true;


        //SELECTION
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




        //ACTION
    	if(!menu_continua){
            if(opcao1 == 1 || opcao1 == 0){
                if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                    //retorna para a fase
                    esta_pausado = false;
                }
            }
            else if(opcao1 == 2){
                if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                	//entrar no menu continua
                    opcao1 = -1;
                    if(!menu_continua){
                        menu_continua = true;
                    }
                }
            }
            else if(opcao1 == 3){
                if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                    //opcao sair do menu
                    quit = true;
                }
            }
            if(In.KeyPress(SDLK_ESCAPE)){
                //sair do pause
                esta_pausado = false;
            }
        }
        else { //menu continua
            if(In.KeyPress(SDLK_SPACE) || In.KeyPress(SDLK_RETURN) || In.KeyPress(SDLK_RETURN2)){
                
                std::ofstream file_save;
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

                file_save << "s1_num_historia " << data.s1_num_historia << std::endl;
                file_save << "state_atual " << data.state_atual << std::endl;
                file_save << "gaia_comodo " << data.gaia_comodo << std::endl;
                file_save << "gaia_t_pos " << data.gaia_t_pos.x << " " << data.gaia_t_pos.y << std::endl;
                file_save << "gaia_t_pos_antiga " << data.gaia_t_pos_antiga.x << " "  << data.gaia_t_pos_antiga.y << std::endl;
                file_save << "gaia_t_pos_inicio_comodo " << data.gaia_t_pos_inicio_comodo.x << " "  << data.gaia_t_pos_inicio_comodo.y << std::endl;
                file_save << "gaia_hp " << data.gaia_hp << std::endl;

                file_save << "p_deposito " << data.p_deposito << std::endl;
                file_save << "p_corredor2 " << data.p_corredor2 << std::endl;

                file_save << "esteira_ligada " << data.esteira_ligada << std::endl;
                
                file_save << "ja_mostrou_corre " << data.ja_mostrou_corre << std::endl;
                file_save << "ja_mostrou_f_esteira " << data.ja_mostrou_f_esteira << std::endl;
                file_save << "ja_mostrou_f_chicote " << data.ja_mostrou_f_chicote << std::endl;

                file_save << "ja_ficou_encurralada " << data.ja_ficou_encurralada << std::endl;
                file_save << "ja_falou_velho " << data.ja_falou_velho << std::endl;
                file_save << "ja_pegou_chave_rato " << data.ja_pegou_chave_rato << std::endl;
                file_save << "ja_pegou_chicote " << data.ja_pegou_chicote << std::endl;

                std::cout << "Salvo com sucesso!" << std::endl;
                file_save.close();
                menu_continua = false;
                opcao1 = 1;
            }
            if(In.KeyPress(SDLK_ESCAPE)){
                opcao1 = 2;
                opcao2_antiga = 1;
                opcao2 = 1;
                menu_continua = false;
            }
        }
    }
}

void Pause2::Render() {
	sp_pause0.Render(0,0,0);

    if(!menu_continua){
        if(opcao1 == 1){
            sp_pause1.Render(0,0,0);
        }
        else if(opcao1 == 2){
            sp_pause2.Render(0,0,0);
        }
        else if(opcao1 == 3){
            sp_pause3.Render(0,0,0);
        }
    }
    else{
        if(opcao2 == 1){
            sp_pausecont1.Render(0,0,0);
        }
        else if(opcao2 == 2){
            sp_pausecont2.Render(0,0,0);
        }
        else if(opcao2 == 3){
            sp_pausecont3.Render(0,0,0);
        }
        else if(opcao2 == 4){
            sp_pausecont4.Render(0,0,0);
        }
        else if(opcao2 == 5){
            sp_pausecont5.Render(0,0,0);
        }
    }
}

bool Pause2::IsPaused(){
	return(esta_pausado);
}

void Pause2::SetPause(){
    esta_pausado = true;
}

bool Pause2::QuitRequested(){
    return (quit);
}