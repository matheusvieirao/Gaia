#include <iostream>
#include <SDL2/SDL.h>

#include "Game.hpp"
#include "State_00_Title.hpp"

int main(int argc,char *argv[]){
    unsigned erro_aux;
    //Game *game = new Game("Gaia", 1280, 720);
    Game game = Game("Gaia", 1280, 720);
    game.Push(new State_00_Title());
    game.Run();
    for(erro_aux = 0; erro_aux < game.erro.size(); erro_aux++){
        switch(game.erro[erro_aux].first){
            case(0):
                break;
            case(1):
                std::cout << erro_aux << ": A instancia inicial do jogo é diferente de null. O jogo ta tentando instanciar duas vezes. - " << game.erro[erro_aux].second << std::endl; //Game::Game
                getchar();
                break;
            case(2):
                std::cout << erro_aux << ": SDL_Init falhou. - " << game.erro[erro_aux].second << SDL_GetError() << std::endl; //Game::Game
                getchar();
                break;
            case(3):
                std::cout << erro_aux << ": IMG_Init falhou. - " << game.erro[erro_aux].second << SDL_GetError() << std::endl; //Game::Game
                getchar();
                break;
            case(4):
                std::cout << erro_aux << ": SDL_CreateWindow falhou. - " << game.erro[erro_aux].second << SDL_GetError() << std::endl; //Game::Game
                getchar();
                break;
            case(5):
                std::cout << erro_aux << ": SDL_CreateRenderer falhou. - " << game.erro[erro_aux].second << SDL_GetError() << std::endl; //Game::Game
                getchar();
                break;
            case(6):
                std::cout << erro_aux << ": Mix_Init falhou. - " << game.erro[erro_aux].second << std::endl; // Game::Game
                getchar();
                break;
            case(7):
                std::cout << erro_aux << game.erro[erro_aux].second << std::endl; // Game::Game
                getchar();
                break;
            case(8):
                std::cout << erro_aux << ": IMG_LoadTexture falhou. - " << game.erro[erro_aux].second << SDL_GetError() << std::endl; //Sprite::Open
                getchar();
                break;
            case(9):
                std::cout << erro_aux << ": Uma tecla do teclado fora do range foi detectada. - " << game.erro[erro_aux].second << std::endl; //InputManager::Update
                getchar();
                break;
            case(10):
                std::cout << erro_aux << ": Uma tecla fora do alcance do teclado foi solicitada. - " << game.erro[erro_aux].second << std::endl; //InputManager::KeyPress || InputManager::KeysPress || InputManager::KeyRelease ||
                getchar();
                break;
            case(11):
                std::cout << erro_aux << ": Um botão do mouse fora do range foi detectada. - " << game.erro[erro_aux].second << std::endl; //InputManager::Update
                getchar();
                break;
            case(12):
                std::cout << erro_aux << ": t_map não pode ser nullptr. Provavelmente a personagem Gaia está sendo criada em uma fase sem um tile map. - " << game.erro[erro_aux].second << std::endl; //(Gaia::Andar || Gaia::TrocarDeComodo || Guarda::AcharComodo ...
                getchar();
                break;
            case(13):
                std::cout << erro_aux << ": TileMap esta tentando renderizar uma camada de tile que nao existe (TileMap::RenderLayer) " << game.erro[erro_aux].second << std::endl;
                getchar();
                break;
           case(14):
               std::cout << erro_aux << ": State == nullptr. State nao foi carregado. - " << game.erro[erro_aux].second << std::endl; //Guarda::AcharComodo ...
               getchar();
               break;
       }
 
   }

    return 0;
}
