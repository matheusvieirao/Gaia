#include "Sound.hpp"
#include "Resources.hpp"

bool Sound::finished = false;

Sound::Sound(){
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
    if(IsOpen()){
        Mix_HaltChannel(channel);
        finished = true;
        chunk = nullptr;
    }
}

void Sound::Stop(int ms){
    if(IsOpen()){
        Mix_FadeOutChannel(channel, ms);
        Mix_HaltChannel(channel);
        finished = true;
        chunk = nullptr;
    }
}

void Sound::Open(std::string file){
    chunk = Resources::GetSound(file);
    finished = false;
}

bool Sound::IsOpen(){
    return(chunk != nullptr);
}

bool Sound::IsPlaying(){
    return(!finished);
}

void Sound::Finished(int channel){
    finished = true;
}
