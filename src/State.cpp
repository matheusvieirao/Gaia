#include "State.hpp"

State::State(){
    popRequested = false;
    quitRequested = false;
}

State::~State(){
    objectArray.clear();
}

void State::Update(){

}

void State::Render(){

}

void State::AddObject(GameObject* ptr) {
    objectArray.emplace_back(ptr);
}

bool State::Is(std::string type){
    return(type == "State");
}

TileMap* State::GetTileMap(){
    return (nullptr);
}

bool State::PopRequested(){
    return(popRequested);
}

void State::PopRequest(){
    popRequested = true;
}

bool State::QuitRequested(){
    return(quitRequested);
}

void State::UpdateArray(float dt){
    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray(){
    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }

}

void State::SortArray(){
    bool repetir = true;
    int altura1, altura2;

    while(repetir){
        repetir = false;
        for (unsigned i = 0; i < objectArray.size()-1; i++) {
            altura1 = objectArray[i]->box.y + objectArray[i]->box.h - objectArray[i]->GetAlturaPe();
            altura2 = objectArray[i+1]->box.y + objectArray[i+1]->box.h - objectArray[i+1]->GetAlturaPe();
            if(altura1 > altura2){
                std::swap(objectArray[i], objectArray[i+1]);
                repetir = true;
                break;
            }
        }
    }
}


//void State::PushInventario(StateData::Item item){
//
//}

