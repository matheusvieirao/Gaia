#ifndef STATE_01_HISTORIA_H
#define STATE_01_HISTORIA_H

#include "State.hpp"
#include "Animation.hpp"
//#include "StateData.hpp"
#include "Sound.hpp"
#include "Timer.hpp"
#include "Resources.hpp"
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
        Timer tempo_falas;
        Sound fala;
        int track = 0;
        //StateData data;
        int parte;

};

#endif // STATEHISTORIA_H
