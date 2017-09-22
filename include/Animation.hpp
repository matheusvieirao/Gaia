#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Game.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"

#define PI 3.14159265359
#define PI2 6.28318530718

class Animation : public GameObject{
    public:
        Animation(float x, float y, std::string spriteName);
        Animation(std::string spriteName, bool fullScreen); //renderiza com x e y na origem. se full screen for true em fullscreen
        Animation(float x, float y, float angle, std::string spriteName, int frameCount, float frameTime, bool ends);
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
        bool IsDead();
        void Kill();
    private:
        float timeLeft;
        bool oneTimeOnly;
        Sprite sp;
        bool is_dead;
        bool fullScreen;
        int game_width;
        int game_height;
};

#endif // ANIMATION_HPP
