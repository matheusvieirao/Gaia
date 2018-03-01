#include "Animation.hpp"


Animation::Animation(float x, float y, std::string spriteName){
    rotation = 0;
    sp = Sprite();
    sp.Open(spriteName);
    box = Rect(x, y, sp.GetWidth(), sp.GetHeight());
    timeLeft = -1;
    oneTimeOnly = false;
    is_dead = false;
}

Animation::Animation(std::string spriteName, bool fullScreen){
    rotation = 0;
    sp = Sprite();
    sp.Open(spriteName);
    box = Rect(0, 0, sp.GetWidth(), sp.GetHeight());
    Camera::pos.x = 0;
    Camera::pos.y = 0;

    //escalar para fullscreen
    if (fullScreen){
        game_width = Game::GetInstance().GetWindowWidth();
        game_height = Game::GetInstance().GetWindowHeight();
        float sx = (float) game_width/sp.GetWidth();
        float sy = (float) game_height/sp.GetHeight();
        sp.SetScaleX(sx);
        sp.SetScaleY(sy);
    }

    timeLeft = -1;
    oneTimeOnly = false;
    is_dead = false;
}

Animation::Animation(float x, float y, float angle, std::string spriteName, int frameCount, float frameTime, bool ends){
    sp = Sprite(spriteName, frameCount, frameTime);
    box = Rect(x, y, sp.GetWidth(), sp.GetHeight());
    rotation = angle;
    timeLeft = frameTime*frameCount;
    oneTimeOnly = ends;
    is_dead = false;
}

void Animation::Update(float dt){
    sp.Update(dt);
    if(oneTimeOnly){
        timeLeft -= dt;
    }
}

void Animation::Render(){
    printf("Animation::REnder\n");
    sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

void Animation::NotifyCollision(GameObject& other){
}

bool Animation::Is(std::string type){
    return(type == "Animation");
}

bool Animation::IsDead(){
    if(is_dead){
        return(true);
    }
    else{
        if(oneTimeOnly){
            return(timeLeft < 0);
        }
        else{
            return(false);
        }
    }
}

void Animation::Kill(){
    is_dead = true;
}

