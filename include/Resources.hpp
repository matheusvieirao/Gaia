#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

class Resources
{
    public:
        static SDL_Texture* GetImage(std::string file);
        static Mix_Music* GetMusic(std::string file);
        static Mix_Chunk* GetSound(std::string file);
        static TTF_Font* GetFont(std::string file, int fontSize);
        static void ClearImages();
        static void ClearMusic();
        static void ClearSounds();
        static void ClearFonts();
    private:
        static std::unordered_map<std::string, SDL_Texture*> imageTable;
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
        static std::unordered_map<std::string, TTF_Font*> fontTable;
};

#endif // RESOURCES_H
