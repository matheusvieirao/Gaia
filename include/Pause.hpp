#ifndef PAUSE_H
#define PAUSE_H

#include "InputManager.hpp"
#include "Sprite.hpp"

class Pause{
	public:
		Pause();
		bool Update(); //se o jogo ainda esta pausado, retorna true
		void Render();
		bool IsPaused();

	private:
		bool esta_pausado;

		int opcao1;
		int opcao2;
		int opcao2_antiga;
		bool menu_continua;

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