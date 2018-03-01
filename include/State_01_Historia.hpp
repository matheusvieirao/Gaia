#ifndef STATE_01_HISTORIA_H
#define STATE_01_HISTORIA_H

#include "InputManager.hpp"
#include "Game.hpp"
#include "State.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "Timer.hpp"
#include "Resources.hpp"
#include "StateData.hpp"
#include "State_00_Title.hpp"
#include "State_02_IndustriaT.hpp"
#include <string>
#include <vector>

class State_01_Historia : public State{
    public:
        State_01_Historia(StateData data);
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
        StateData data;
        int num_historia;

        std::vector<Animation> vet_anim;

};

#endif // STATEHISTORIA_H
