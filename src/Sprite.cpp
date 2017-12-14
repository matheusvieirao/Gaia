#include "SDL2/SDL_image.h"
#include "Sprite.hpp"
#include "Game.hpp"
#include "iostream"
#include "Resources.hpp"

Sprite::Sprite() {
    texture = nullptr;
    frame_total = 1;
    frame_start = 0;
    frame_animation = 0;
    frame_animation_dur = 1;
    frame_time = 1;
    frame_current = 0;
    scale_x = 1;
    scale_y = 1;
    pause = false;
    timer.Restart();
    repetitions = -1;
}

Sprite::Sprite(std::string file, int frame_total, int frame_start, int frame_animation, float frame_time, int repetitions){
    texture = nullptr;
    this->frame_total = frame_total;
    this->frame_start = frame_start-1;
    this->frame_animation = frame_animation-1 + frame_start;
    frame_animation_dur = frame_animation;
    this->frame_time = frame_time;
    frame_current = 0;
    scale_x = 1;
    scale_y = 1;
    timer.Restart();
    this->repetitions = repetitions;
    if (repetitions == 0){
        pause = true;
    }
    else{
        pause = false;
    }

    Open(file);
}

Sprite::~Sprite() {
    //SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    if (texture != nullptr) {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        frame_width = width/frame_total;
        SetFrame(frame_start+1);
    }
    else {
        std::cout << "IMG_LoadTexture não conseguiu abrir " << file << " - Sprite::Open " << SDL_GetError() << std::endl;
        exit(1); 
    }
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clip_rect.x = x;
    clip_rect.y = y;
    clip_rect.w = w;
    clip_rect.h = h;
}


void Sprite::Update(float dt) {
    if(!pause){
        timer.Update(dt);
        if(timer.Get() > frame_time){
            frame_current++;
            if(frame_current>frame_animation){
                if(repetitions > 0){
                    repetitions--;
                }
                if(repetitions == 0){
                    pause = true;
                    frame_current--;
                }
                else{
                    frame_current=frame_start;
                }
            }
            SetFrame(frame_current+1);
            timer.Restart();
        }
    }
}

void Sprite::Render(int x, int y, float angle) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clip_rect.w * scale_x;
    dstrect.h = clip_rect.h * scale_y;
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clip_rect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}

void Sprite::PauseAnimation(){
    pause = true;
}

void Sprite::ResumeAnimation(){
    pause = false;
}


int Sprite::GetWidth() {
    return(frame_width*scale_x);
}

int Sprite::GetHeight() {
    return(height*scale_y);
}

int Sprite::GetFrameStart() {
    return(frame_start+1);
}

int Sprite::GetFrame() {
    return(frame_current+1);
}

int Sprite::GetAnimationDur() {
    return(frame_animation_dur);
}

float Sprite::GetFrameTime() {
    return(frame_time);
}

bool Sprite::IsOpen() {
    return(texture != nullptr);
}

void Sprite::SetScaleX(float scale){
    scale_x = scale;
}

void Sprite::SetScaleY(float scale){
    scale_y = scale;
}

void Sprite::SetFrame(int frame){
    frame--;
    if(frame == frame_total){ //if que da um desconto se o programa mandar um valor de frame 1 numero maior do que o normal, mas se aparecer, corrigir no codigo o local aonde isso está sendo chamado.
        printf("Não deveria estar entrando aqui, de uma olhadinha em Sprite::SetFrame\n");
        frame = frame_start;
    }

    if(frame < frame_total){
        frame_current = frame;
        SetClip(frame*frame_width, 0, frame_width, height);
    }
    else{
        printf("Erro. %d é um valor de frame impossivel (o valor de frame deve estar entre 1 e n, sendo n o numero total de frames) (Srite::SetFrame)\n",frame);
    }
}

void Sprite::SetFrameTotal(int frame_total){
    this->frame_total = frame_total;
    frame_width = width/frame_total;
    SetFrame(frame_start+1);
}

void Sprite::SetFrameAnimation(int frame_animation){
    frame_animation_dur = frame_animation;
    this->frame_animation = frame_start + frame_animation-1;
    SetFrame(frame_start+1);
}

void Sprite::SetFrameStart(int novo_frame_start){
    int duracao_animacao = frame_animation - frame_start+1;
    int frame_relativo = frame_current - frame_start; //frame relativo é a posicao (0 = primeiro, 1 = segundo...) do frame atual em relacao ao primeiro frame da animacao (frame_start)

    frame_start = novo_frame_start - 1;
    frame_animation = frame_start + duracao_animacao-1;

    SetFrame(frame_start+frame_relativo+1);
    timer.Restart();
}

void Sprite::SetFrameTime(float frame_time){
    this->frame_time = frame_time;
}

void Sprite::SetRepetitions(int repetitions){
    this->repetitions = repetitions;
    if(repetitions==0){
        pause = true;
    }
    else{
        pause = false;
    }
    SetFrame(frame_start+1);
}
