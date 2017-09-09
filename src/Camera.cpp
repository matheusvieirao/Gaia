#include <iostream>
#include "SDL2/SDL.h"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"

Vec2 Camera::pos(0,0);
Vec2 Camera::speed(0,0);
GameObject* Camera::focus = nullptr;

Camera::Camera(){
    focus = nullptr;
    speed.x = 0;
    speed.y = 0;
}

Camera::~Camera(){
}

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    float vel_limite = 0.7;
    if(focus != nullptr) {
        pos.x = focus->box.GetCenter().x - Game::GetInstance().GetWindowWidth()/2;
        pos.y = focus->box.GetCenter().y - Game::GetInstance().GetWindowHeight()/2;
    }
    else{
        if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)) {
            if(speed.x < 0) {
                speed.x = 0;
            }
            if(speed.y > 0) {
                speed.x = speed.y;
            }
            if(speed.y < 0) {
                speed.x = -speed.y;
            }
            if(speed.x < vel_limite){
                speed.x += dt;
            }
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT)) {
            if(speed.x > 0) {
                speed.x = 0;
            }
            if(speed.y > 0) {
                speed.x = -speed.y;
            }
            if(speed.y < 0) {
                speed.x = speed.y;
            }
            if(speed.x > -vel_limite){
                speed.x -= dt;
            }
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_UP)) {
            if(speed.y > 0) {
                speed.y = 0;
            }
            if (speed.x > 0) {
                speed.y = -speed.x;
            }
            if (speed.x < 0) {
                speed.y = speed.x;
            }
            if(speed.y > -vel_limite){
                speed.y -= dt;
            }
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_DOWN)) {
            if(speed.y < 0) {
                speed.y = 0;
            }
            if (speed.x > 0) {
                speed.y = speed.x;
            }
            if (speed.x < 0) {
                speed.y = -speed.x;
            }
            if(speed.y < vel_limite){
                speed.y += dt;
            }
        }
        if(InputManager::GetInstance().KeyRelease(SDLK_RIGHT)) {
            speed.x = 0;
        }
        if(InputManager::GetInstance().KeyRelease(SDLK_LEFT)) {
            speed.x = 0;
        }
        if(InputManager::GetInstance().KeyRelease(SDLK_UP)) {
            speed.y = 0;
        }
        if(InputManager::GetInstance().KeyRelease(SDLK_DOWN)) {
            speed.y = 0;
        }

        if(speed.x < 200){
            pos.x = pos.x + speed.x*50;
        }
        if(speed.y < 200){
            pos.y = pos.y + speed.y*50;
        }


    }
}
