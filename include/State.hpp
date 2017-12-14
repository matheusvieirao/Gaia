#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>
#include <string>
#include "GameObject.hpp"
#include "TileMap.hpp"
//#include "StateData.hpp"

class State{
    public:
        State();
        virtual ~State();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        virtual bool Is(std::string type) = 0;
        //virtual void State_00_Title(StateData::Item item);
        virtual void AddObject(GameObject* ptr);
        void PushInventario(StateData::Item item);
        virtual TileMap* GetTileMap();
        bool PopRequested();
        void PopRequest();
        bool QuitRequested();
    protected:
        virtual void UpdateArray(float dt);
        virtual void RenderArray();
        virtual void SortArray();

        bool popRequested;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif // STATE_H
