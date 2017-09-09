#ifndef CAMERA_H
#define CAMERA_H
#include "Vec2.hpp"
#include "GameObject.hpp"

class Camera{
    public:
        Camera();
        virtual ~Camera();
        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);
        static Vec2 pos;
        static Vec2 speed;
    private:
        static GameObject* focus;
};

#endif // CAMERA_H
