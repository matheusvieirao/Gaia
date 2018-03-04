#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SDL2/SDL_ttf.h"
#include "Rect.hpp"
#include "Color.hpp"

enum TextStyle{SOLID, SHADED, BLENDED};

class Text{
    public:
        //Text();
        Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x = 0, int y = 0);
        Text();
        virtual ~Text();
        void Open(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x = 0, int y = 0);
        void Render(int cameraX = 0, int cameraY = 0);
        void SetPos(int x, int y, bool centerX = false, bool centerY = false);
        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontSize(int fontSize);
        void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        int GetHeight();
        int GetWidth();
        void RemakeTexture();
    private:
        TTF_Font* font;
        SDL_Texture* texture;
        std::string text;
        TextStyle style;
        int fontSize;
        SDL_Color color;
        SDL_Color bgColor;
        Rect box;
};

#endif // TEXT_H
