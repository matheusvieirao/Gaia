#ifndef STATETITLE_H
#define STATETITLE_H

#include "State.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "Music.hpp"
#include "StateData.hpp"

class StateTitle : public State{
    public:
        StateTitle();
        void Update();
        void Render();
        void Pause();
        void Resume();
        bool Is(std::string type);
    private:
        Sprite menu;
        Sprite menu1;
        Sprite menu2;
        Sprite menu3;
        Sprite cont;
        Sprite cont1;
        Sprite cont2;
        Sprite cont3;
        Sprite cont4;
        Sprite cont5;
        int opcao1;
        int opcao2;
        bool menu_continua;
        Text pressSpace;
        Timer timer;
        Music music;
        StateData data;
};


#endif // STATETITLE_H
