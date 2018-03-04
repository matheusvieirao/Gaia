#include "Text.hpp"
#include "Resources.hpp"
#include "Game.hpp"

//Text::Text(){}

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y){
    font = Resources::GetFont(fontFile, fontSize);
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    box.x = x;
    box.y = y;
    texture = nullptr;
    SetBackgroundColor(0x00, 0x00, 0x00, 128);
    if(font != nullptr){
        RemakeTexture();
    }
}

Text::Text(){
    font = Resources::GetFont("font/URW Gothic L Demi.ttf", 50);
    fontSize = 50;
    style = BLENDED;
    text = "";
    color = Color::white;
    box.x = 0;
    box.y = 0;
    texture = nullptr;
    SetBackgroundColor(0x00, 0x00, 0x00, 128);
    if(font != nullptr){
 //       RemakeTexture();
    }
}

Text::~Text(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Text::Open(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y){
    font = Resources::GetFont(fontFile, fontSize);
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    box.x = x;
    box.y = y;
    texture = nullptr;
    SetBackgroundColor(0x00, 0x00, 0x00, 128);
    if(font != nullptr){
        RemakeTexture();
    }
}

void Text::Render(int cameraX, int cameraY){
    if(texture != nullptr){
        SDL_Rect dstrect, cliprect;
        cliprect.x = 0;
        cliprect.y = 0;
        cliprect.w = box.w;
        cliprect.h = box.h;

        dstrect.x = box.x-cameraX;
        dstrect.y = box.y-cameraY;
        dstrect.w = box.w;
        dstrect.h = box.h;
        SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &cliprect, &dstrect);
    }
}

void Text::SetPos(int x, int y, bool centerX, bool centerY){
    if(centerX){
        box.x = x - box.w/2;
    }
    else{
        box.x = x;
    }
    if(centerY){
        box.y = y - box.h/2;
    }
    else{
        box.y = y;
    }
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    bgColor.r = r;
    bgColor.g = g;
    bgColor.b = b;
    bgColor.a = a;
}

int Text::GetHeight(){
    return(box.h);
}

int Text::GetWidth(){
    return(box.w);
}

void Text::RemakeTexture(){
    SDL_Surface* surface;

    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }

    if(style == SOLID){
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
    }
    else if(style == SHADED){
        surface = TTF_RenderText_Shaded(font, text.c_str(), color, bgColor);
    }
    else if(style == BLENDED){
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
    }

    if(surface != nullptr){
        box.w = surface->w;
        box.h = surface->h;
        texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
        SDL_FreeSurface(surface);
    }
}
