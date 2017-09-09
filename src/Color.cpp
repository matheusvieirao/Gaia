#include "Color.hpp"

SDL_Color Color::black;
SDL_Color Color::white;
SDL_Color Color::azulGelo;

Color::Color(){
    black.r = 0x00;
    black.g = 0x00;
    black.b = 0x00;
    black.a = 128;

    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 128;

    azulGelo.r = 0x16;
    azulGelo.g = 0xe5;
    azulGelo.b = 0x77;
    azulGelo.a = 128;
}
