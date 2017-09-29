#include "Resources.hpp"
#include "SDL2/SDL_image.h"
#include "Game.hpp"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

SDL_Texture* Resources::GetImage(std::string file){
    SDL_Texture* texture;

    auto it = imageTable.find(file);

    if (it != imageTable.end()){
            texture = it->second;
            return(texture);
    }
    else{
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture != nullptr) {
            imageTable.emplace(file, texture);
            return(texture);
        }
        else{
            return(nullptr);
        }
    }
}

Mix_Music* Resources::GetMusic(std::string file){
    Mix_Music* music;

    auto it = musicTable.find(file);

    if (it != musicTable.end()){
            music = it->second;
            return(music);
    }
    else{
        music = Mix_LoadMUS(file.c_str());
        if (music != nullptr) {
            musicTable.emplace(file, music);
            return(music);
        }
        else{
            return(nullptr);
        }
    }
}

Mix_Chunk* Resources::GetSound(std::string file){
    Mix_Chunk* sound;

    auto it = soundTable.find(file);

    if (it != soundTable.end()){
            sound = it->second;
            return(sound);
    }
    else{
        sound = Mix_LoadWAV(file.c_str());
        if (sound != nullptr) {
            soundTable.emplace(file, sound);
            return(sound);
        }
        else{
            return(nullptr);
        }
    }
}

TTF_Font* Resources::GetFont(std::string file, int fontSize){
    TTF_Font* font;
    std::string key = file + std::to_string(fontSize);

    auto it = fontTable.find(key);

    if (it != fontTable.end()){
            font = it->second;
            return(font);
    }
    else{
        font = TTF_OpenFont(file.c_str(), fontSize);
        if (font != nullptr) {
            fontTable.emplace(key, font);
            return(font);
        }
        else{
            return(nullptr);
        }
    }
}

void Resources::ClearImages(){
    for (auto& x: imageTable) {
        SDL_DestroyTexture(x.second);
    }
    imageTable.clear();
}

void Resources::ClearMusic(){
    for (auto& x: musicTable) {
        Mix_FreeMusic(x.second);
    }
    musicTable.clear();
}

void Resources::ClearSounds(){
    for (auto& x: soundTable) {
        Mix_FreeChunk(x.second);
    }
    soundTable.clear();
}

void Resources::ClearFonts(){
    for (auto& x: fontTable) {
        TTF_CloseFont(x.second);
    }
    fontTable.clear();
}

void Resources::ClearResources(){
    ClearImages();
    ClearMusic();
    ClearSounds();
    ClearFonts();
}