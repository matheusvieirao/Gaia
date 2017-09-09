#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>

class Sound{
    public:
        Sound();
        Sound(std::string file);
        void Play(int times); //numero de vezes que a musica repete. se times == -1 a musica se repete indefinitivamente
        void Stop(); //para a musica abruptamente
        void Stop(int ms); //para a musica com um fadeout de ms milisegundos
        void Open(std::string file); //se mal sucedido music == nullptr
        bool IsOpen();
        bool IsPlaying();
    private:
        static void Finished(int channel);
        static bool finished;
        Mix_Chunk* chunk;
        int channel;
};

#endif // SOUND_H
