#include "Sound.hpp"
#include "Resources.hpp"
#include <iostream>

bool Sound::finished = false;

Sound::Sound(){
    channel = -1;
    chunk = nullptr;
}

Sound::Sound(std::string file){
    chunk = nullptr;
    Open(file);
}

void Sound::Play(int times){
    if(IsOpen()){
        channel = Mix_PlayChannel(-1, chunk, times);
        Mix_ChannelFinished(Finished);
    }
}

void Sound::Stop(){
    if(channel >= 0 && channel < 32){
        Mix_HaltChannel(channel);
    }
    finished = true;
    chunk = nullptr;
}

void Sound::Stop(int ms){
    if(channel >= 0 && channel < 32){
        Mix_FadeOutChannel(channel, ms);
        Mix_HaltChannel(channel);
    }
    finished = true;
    chunk = nullptr;
}

void Sound::Open(std::string file){
    chunk = Resources::GetSound(file);
    finished = false;
}

bool Sound::IsOpen(){
    return(chunk != nullptr);
}

bool Sound::IsPlaying(){ //como é usa Finished que é estatica só funciona quando só existe 1 som de cada vez
    return(!finished);
}

void Sound::Finished(int channel){
    finished = true;
}
