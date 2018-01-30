#ifndef PAUSE2_H
#define PAUSE2_H

#include <fstream>

#include "Game.hpp"
#include "InputManager.hpp"
#include "Sprite.hpp"
#include "StateData.hpp"

class Pause2{
	public:
		Pause2();
		void Update(StateData data); //se o jogo ainda esta pausado, retorna true
		void Render();
		bool IsPaused();
		void SetPause();
		bool QuitRequested();

	private:
		bool esta_pausado;

		int opcao1;
		int opcao2;
		int opcao2_antiga;
		bool menu_continua;
		bool quit;

		Sprite sp_pause0;
		Sprite sp_pause1;
		Sprite sp_pause2;
		Sprite sp_pause3;
		Sprite sp_pausecont1;
		Sprite sp_pausecont2;
		Sprite sp_pausecont3;
		Sprite sp_pausecont4;
		Sprite sp_pausecont5;
};

#endif