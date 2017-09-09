#ifndef STATE_01_HISTORIA_H
#define STATE_01_HISTORIA_H

#include "State.hpp"
#include "Sprite.hpp"
//#include "StateData.hpp"
#include "Sound.hpp"
#include "Timer.hpp"
#include <string>

class State_01_Historia : public State{
    public:
        State_01_Historia(int parte);
        virtual ~State_01_Historia();
        void Update(float dt);
        void Render();
        void Pause();
        void Resume();
        bool Is(std::string type);
        bool Falar(float delay, std::string arquivo);

    private:
        Sprite sp_1p1;
        Sprite sp_1p2;
        Sprite sp_2p1;
        Sprite sp_2p2;
        Sprite sp_3p1;
        Sprite sp_4p0;
        Sprite sp_4p1;
        Sprite sp_4p2;
        Sprite sp_4p3;
        Sprite sp_4p4;
        Sprite sp_4p5;
        Sprite sp_4p6;
        Sprite sp_4p7;
        Sprite sp_5p1;
        Sprite sp_5p2;
        Sprite sp_5p3;
        Sprite sp_5p4;
        Sprite sp_7;
        Sprite sp_8;
        Sprite sp_9;
        Sprite sp_10;
        Timer tempo_falas;
        Sound fala;
        int track = 0;
        //StateData data;
        int parte;

};

#endif // STATEHISTORIA_H
