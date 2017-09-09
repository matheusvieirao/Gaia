#include "Music.hpp"
#include "Resources.hpp"

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    Open(file);
}

void Music::Play(int times){
    Mix_PlayMusic(music, times);
}

void Music::Stop(){
    Mix_FadeOutMusic(0);
}

void Music::Stop(int ms){
    Mix_FadeOutMusic(ms);
}

void Music::Open(std::string file){
    music = Resources::GetMusic(file);
}

bool Music::IsOpen(){
    return(music != nullptr);
}
