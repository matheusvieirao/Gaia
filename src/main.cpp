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
                getchar();
                break;
            case(2):
                getchar();
                break;
            case(3):
                
                getchar();
                break;
            case(4):
                 //Game::Game
                getchar();
                break;
            case(5):
                 //Game::Game
                getchar();
                break;
            case(6):
                 // Game::Game
                getchar();
                break;
            case(7):
                 // Game::Game
                getchar();
                break;
            case(8):
                getchar();
                break;
            case(9):
                 //InputManager::Update
                getchar();
                break;
            case(10):
                 //InputManager::KeyPress || InputManager::KeysPress || InputManager::KeyRelease ||
                getchar();
                break;
            case(11):
                 //
                getchar();
                break;
            case(12):
                std::cout << "t_map não pode ser nullptr. "  << std::endl; //(Gaia::Andar || Gaia::TrocarDeComodo || Guarda::AcharComodo ...
                getchar();
                break;
            case(13):
                std::cout << "TileMap esta tentando renderizar uma camada de tile que nao existe (TileMap::RenderLayer) " << std::endl;
                getchar();
                break;
           case(14):
               std::cout << "State == nullptr. State nao foi carregado. - "  << std::endl; //Guarda::AcharComodo ...
               getchar();
               break;
       }
 
   }

    return 0;
}
