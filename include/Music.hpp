#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SDL2/SDL_mixer.h>

class Music{
    public:
        Music();
        Music(std::string file);
        void Play(int times); //numero de vezes que a musica repete. se times == -1 a musica se repete indefinitivamente
        void Stop(); //para a musica abruptamente
        void Stop(int ms); //para a musica com um fadeout de ms milisegundos
        void Open(std::string file); //se mal sucedido music == nullptr
        bool IsOpen();
    private:
        Mix_Music* music;
};

#endif // MUSIC_H
