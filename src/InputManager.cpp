#include <iostream>
#include "InputManager.hpp"
#include "Game.hpp"
#include "SDL2/SDL.h"

//InputManager& InputManager::GetInstance;

InputManager& InputManager::GetInstance(){
    static InputManager instancia;
    return(instancia);
}

InputManager::InputManager() {
    int i;

    for(i=0; i<6; i++){
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
    for(i=0; i<354; i++) {
        keyState[i] = false;
        keyUpdate[i] = 0;
    }
    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
}

bool InputManager::ValidatesKeyInput(int* key) {
    if (*key > 0x40000038) {
        *key =  *key - 0x3FFFFFB9;

    }
    if(*key >= 0 && *key < 354){
        return(true);
    }
    else{
        return(false);
    }
}

bool InputManager::ValidatesMouseInput(int button){
    if(button >= 0 && button < 6) {
        return(true);
    }
    else {
        return(false);
    }
}

void InputManager::Update() {
    SDL_Event event;
    int key_aux, mouse_aux;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

    while (SDL_PollEvent(&event)) {

        switch(event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;

            case (SDL_MOUSEBUTTONDOWN):
                mouse_aux = event.button.button;

                if (ValidatesMouseInput(mouse_aux)) {
                    mouseState[mouse_aux] = true;
                    mouseUpdate[mouse_aux] = updateCounter;
                }
                else {
                    std::cout << "Um botão do mouse fora do range foi detectada. - InputManager::Update "  << std::endl;
                }
                break;

            case (SDL_MOUSEBUTTONUP):
                mouse_aux = event.button.button;

                if (ValidatesMouseInput(mouse_aux)) {
                    mouseState[mouse_aux] = false;
                    mouseUpdate[mouse_aux] = updateCounter;
                }
                else {
                    std::cout << "Um botão do mouse fora do range foi detectada. - InputManager::Update "  << std::endl;
                }
                break;

            case (SDL_KEYDOWN):
                key_aux = event.key.keysym.sym;
                //se o evento nao for repetido, registra ele
                if(!event.key.repeat) {

                    if(ValidatesKeyInput(&key_aux)) {
                        keyState[key_aux] = true;
                        keyUpdate[key_aux] = updateCounter;
                    }
                    else {
                        std::cout << "Uma tecla do teclado fora do range foi detectada. - InputManager::Update "  << std::endl;
                    }
                }
                break;

            case (SDL_KEYUP):
                key_aux = event.key.keysym.sym;
                //se o evento nao for repetido, registra ele
                if(!event.key.repeat) {

                    if(ValidatesKeyInput(&key_aux)) {
                        keyState[key_aux] = false;
                        keyUpdate[key_aux] = updateCounter;
                    }
                    else {
                        std::cout << "Uma tecla do teclado fora do range foi detectada. - InputManager::Update "  << std::endl;
                    }
                }
                break;
        }
    }
}

bool InputManager::KeyPress(int key){
    if(ValidatesKeyInput(&key)){
        if(updateCounter == keyUpdate[key]) {
            return(keyState[key]);
        }
        else {
            return(false);
        }
    }
    else {
        std::cout << "Uma tecla fora do alcance do teclado foi solicitada. - InputManager::KeyPress(int)"  << std::endl;
        return(false);
    }
}

bool InputManager::KeysPress(int key1, int key2){
    if(ValidatesKeyInput(&key1) && ValidatesKeyInput(&key2)){
        if(updateCounter == keyUpdate[key1] || updateCounter == keyUpdate[key2]) {
            return(keyState[key1] && keyState[key2]);
        }
        else {
            return(false);
        }
    }
    else {
        std::cout << "Uma tecla fora do alcance do teclado foi solicitada. - InputManager::KeysPress(int int)"  << std::endl;
        return(false);
    }
}

bool InputManager::KeyRelease(int key){
    if(ValidatesKeyInput(&key)){
        if(updateCounter == keyUpdate[key]) {
            return(!keyState[key]);
        }
        else {
            return(false);
        }
    }
    else {
        std::cout << "Uma tecla fora do alcance do teclado foi solicitada. - InputManager::KeyRelease"  << std::endl;
        return(false);
    }
}

bool InputManager::IsKeyDown(int key){
    if (ValidatesKeyInput(&key)) {
        return(keyState[key]);
    }
    else{
        return(false);
    }
}

bool InputManager::IsKeysDown(int key1, int key2){
    if (ValidatesKeyInput(&key1) && ValidatesKeyInput(&key2)) {
        return(keyState[key1]&& keyState[key2]);
    }
    else{
        return(false);
    }
}

bool InputManager::MousePress(int button){
    if(updateCounter == mouseUpdate[button]){
        return(mouseState[button]);
    }
    else{
        return(false);
    }
}

bool InputManager::MouseRelease(int button){
    if(updateCounter == mouseUpdate[button]){
        return(!mouseState[button]);
    }
    else{
        return(false);
    }
}

bool InputManager::IsMouseDown(int button){
    return(mouseState[button]);
}

int InputManager::GetMouseX(){
    return(mouseX);
}

int InputManager::GetMouseY(){
    return(mouseY);
}

bool InputManager::QuitRequested(){
    return(quitRequested);
}


InputManager::~InputManager(){
}
