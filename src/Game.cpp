#include <iostream>
#include <string>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "Game.hpp"
#include "StateIndustriaT.hpp"
#include "InputManager.hpp"
#include "Resources.hpp"
#include "Color.hpp"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
    this->width = width;
    this->height = height;
	if (instance == nullptr) {
			instance = this;
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == 0){
				if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
                    frameStart = 0;
                    dt = 0;
                    window = nullptr;
                    renderer = nullptr;
					window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
					renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
					if ((window != nullptr) && (renderer != nullptr)){
                        storedState = nullptr;
                        Color();
					}
					else {
						if (window == nullptr) {
							AddErro(4, "Game::Game");
						}
						else {
							AddErro(5, "Game::Game");
						}
					}
				}
				else {
					AddErro(3, "Game::Game");
				}
				if(Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) != 0){
                    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == 0){
                        //musica aberta com sucesso
                    }
                    else{
                        AddErro(7, ": Mix_OpenAudio falhou. - Game::Game");
                    }
				}
				else {
                    AddErro(6, "Game::Game");
				}
				if(TTF_Init() == 0){
                    //sucess
				}
				else{
                    AddErro(7, ": TTF_Init falhou. - Game::Game");
				}
			}
			else{
				AddErro(2, "Game::Game");
			}
	}
	else {
		AddErro(1, "Game::Game");
	}
}

Game::~Game() {
    if(storedState != nullptr){
        delete storedState;
    }
    for(unsigned i = 0; i < stateStack.size(); i++){
       stateStack.pop();
    }
    instance = nullptr;
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Game& Game::GetInstance(){
	return(*instance);
}

SDL_Renderer* Game::GetRenderer(){
    return(renderer);
}

State& Game::GetCurrentState(){
    if(storedState == nullptr){
        return(*stateStack.top().get());
    }
    else{
        return(*storedState);
    }
}

void Game::Push(State* state){
    storedState = state;
}

void Game::Run(){
    if(storedState != nullptr){
        stateStack.emplace(storedState);
        storedState = nullptr;
        while(!stateStack.empty() && !stateStack.top()->QuitRequested()) {
            CalculateDeltaTime();
            //std::cout << "______________\n"<<dt<<std::endl;

            if(stateStack.top()->PopRequested()){
                stateStack.top()->Pause();
                stateStack.pop();
                if(storedState != nullptr){
                    stateStack.emplace(storedState);
                    storedState = nullptr;
                }
                stateStack.top()->Resume();
            }
            else{
                InputManager::GetInstance().Update();
                stateStack.top()->Update();
                stateStack.top()->Render();
                SDL_RenderPresent(renderer);
            }

            int dt_mili = SDL_GetTicks() - frameStart;
            if(dt_mili < 33){
                SDL_Delay(33-dt_mili);
            }
        }
    }
    else {
        Resources::ClearImages();
    }
}

void Game::CalculateDeltaTime() {
    unsigned ticks = SDL_GetTicks();
    dt = ((float)ticks - (float)frameStart) / 1000;
    frameStart = ticks;
}

float Game::GetDeltaTime(){
    return(dt);
}

int Game::GetWindowWidth(){
    return(width);
}

int Game::GetWindowHeight(){
    return(height);
}

bool Game::IsStateStackEmpty(){
    return(stateStack.empty() || (stateStack.size()==1 && stateStack.top()->PopRequested()));
}

void Game::AddErro(int num, std::string local){
    erro.push_back(std::make_pair(num, local));
}



