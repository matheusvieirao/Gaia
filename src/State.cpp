#include "State.hpp"

State::State(){
    popRequested = false;
    quitRequested = false;
}

State::State(StateData data){
    popRequested = false;
    quitRequested = false;
    this->data = data;
}

State::~State(){
    objectArray.clear();
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

void State::SetData(std::string var, int value) {
    printf("entrou\n");
        if(var == "gaia_hp"){
            data.gaia_hp = value;
        }
        else if(var == "p_deposito"){
            data.p_deposito = value;
        }
        else if(var == "p_corredor2"){
            data.p_corredor2 = value;
        }
        else if(var == "esteira_ligada"){
            data.esteira_ligada = value;
        }
        else if(var == "ja_mostrou_corre"){
            data.ja_mostrou_corre = value;
        }
        else if(var == "ja_mostrou_f_esteira"){
            data.ja_mostrou_f_esteira = value;
        }
        else if(var == "ja_mostrou_f_chicote"){
            data.ja_mostrou_f_chicote = value;
        }
        else if(var == "ja_ficou_encurralada"){
            data.ja_ficou_encurralada = value;
        }
        else if(var == "ja_falou_velho"){
            data.ja_falou_velho = value;
        }
        else if(var == "ja_pegou_chave_rato"){
            printf("ja_pegou_chave_rato\n");
            data.ja_pegou_chave_rato = value;
        }
        else if(var == "ja_pegou_chicote"){
            data.ja_pegou_chicote = value;
        }
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

//void State::State_00_Title(StateData::Item item){
//
//}

