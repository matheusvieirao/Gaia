#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include "SDL2/SDL.h"

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT

/**
* Update
* KeyPress
*   @param key int
*   @return bool
* KeysPress Se as duas teclas estiverem sendo pressionadas e for o primeiro frame de pelo menos uma delas sendo pressionada retorna true.
*   @param key int
*   @return bool
* KeyRelease
*   @param key int
*   @return bool
* IsKeyDown
*   @param key int
*   @return bool
* MousePress
*   @param button int
*   @return bool
* MouseRelease
*   @param button int
*   @return bool
* IsMouseDown
*   @param button int
*   @return bool
* GetMouseX
*   @return int
* GetMouseY
*   @return int
* QuitRequested
*   @return bool
* GetInstance
*   @return InputManager&
* InputManager
* ValidadesKeyInput bool
* ~InputManager
*
* @var mouseState bool[6]
* @var mouseUpdate int[6] SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT, SDL_BUTTON_X1, SDL_BUTTON_X2
* @var keyState bool[416]
* @var keyUpdate int[416]
* @var quitRequested bool
* @var updateCounter int
* @var mouseX int
* @var mouseY int
*/
class InputManager {
    public:
        static InputManager& GetInstance();
        void Update();
        bool KeyPress(int key);
        bool KeysPress(int key1, int key2);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool IsKeysDown(int key1, int key2);
        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();
    private:
        InputManager();
        bool ValidatesKeyInput(int *key);
        bool ValidatesMouseInput(int button);
        virtual ~InputManager();
        bool mouseState[6];
        int mouseUpdate[6];
        bool keyState[354];
        int keyUpdate[354];
        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;
};

#endif // INPUTMANAGER_H
