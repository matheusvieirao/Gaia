#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <stack>
#include "SDL2/SDL.h"
#include "State.hpp"

/**
* Game::Game: Recebe o titulo do jogo, a largura e a altura da janela do jogo e inicializa as bibliotecas do SDL.
*   @param title: Titulo do jogo.
*   @param width: Largura da janela do jogo.
*   @param height: Altura da tela do jogo.
* Game::~Game: Destroi State, renderer, a janela e sai do SDL.
* Game::Run: Atualiza o State, renderiza o State, faz um delay (30fps) enquanto não é solicitado sair do jogo.
* Game::GetInstance: Retorna a instancia de Game.
*   @return instance.
* Game::GetState: Retorna o state.
*   @return state.
* Game::GetRenderer: Retorna renderer.
*   @return renderer.
*
* @var erro: std::vector<int> Responsavel por armazenar os erros em pilha.
* @var instance: static Game* Responsavel por armazenar a unica instância de Game.
* @var window: SDL_Window* Janela do jogo.
* @var renderer: SDL_Renderer* Renderizador SDL.
* @var state: State* Estado do jogo.
**/

class Game {
    public:
        Game(std::string title, int width, int height);
        Game(Game&&) = default;
        Game& operator=(Game&&) = default;
        ~Game();
        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();
        void Push(State* state);
        void Run();
        float GetDeltaTime();
        int GetWindowWidth();
        int GetWindowHeight();
        bool IsStateStackEmpty();
        void AddErro(int num, std::string local);

        std::vector<std::pair<int, std::string>> erro;

    private:
        void CalculateDeltaTime();

        int width;
        int height;
        int frameStart;
        float dt;
        static Game* instance;
        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::stack<std::unique_ptr<State>> stateStack;

};

#endif // GAME_H
