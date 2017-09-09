#ifndef SPRITE_H
#define SPRITE_H


#include <string>

#include "SDL2/SDL.h"
#include "Timer.hpp"

/**
* Sprite::Sprite: Instancializa a textura e chama Open. obs: dentro da classe Sprite o primeiro frame da animação é tratado como 0 mas nas classes a quais ele é referenciado o primeiro frame é tratado como 1.
*   @param std::string file: String com o caminho relativo da imagem no computador.
*   @param int frame_total: Número total de frames na imagem.
*   @param int frame_animation: Número de frames que pertecem a uma animação.
*   @param int frame_start: Número do primeiro frame a ser renderizado (esse número vai de 1 até n, sendo n o número total de frames na imagem).
*   @param int frame_time: Tempo de exposição de cada frame.
*   @param int repetitions: numero de repeticoes da animacao, se nulo a sprite nao tem animacao e se negativo a sprite tem loop infinito.
*
* Sprite::~Sprite: Destroi a textura.
*
* Sprite::Open: Abre a texture, descobre sua altura e largura e chama SetClip.
*   @param std::string file: String com o caminho relativo da imagem no computador.
*
* Sprite::SetClip: Seta clipRect.
*   @param int x: Posição latitudinal para posicionar o canto superior esquerdo do clip.
*   @param int y: Posição longitudinal para posicionar o canto superior esquerdo do clip.
*   @param int w: Largura do clip.
*   @param int h: Altura do clip.
*
* Sprite::Update: .
*
* Sprite::Render: Renderiza na posição (x,y) o que da imagem estiver dentro de clipRect.
*   @param int x: posição latitudinal de onde se deseja renderizar o canto superior esquerdo da imagem.
*   @param int y: Posição longitudinal de onde se deseja renderizar o canto superior esquerdo da imagem.
*
* Sprite::GetWidth: Retorna a largura da textura.
*   @return int: largura da textura.
*
* Sprite::GetHeight: Retorna a altura da textura.
*   @return int: altura da textura.
*
* Sprite::GetFrameStart: Retorna o primeiro frame da animação.
*   @return int: Primeiro frame da animação de 1 a n, sendo n o total de frames da animação.
*
* Sprite::GetFrame: Retorna o frame atual.
*   @return int: Frame atual da animação de 1 a n, sendo n o total de frames da animação.
*
* Sprite::GetAnimationDur: Retorna quantos frames tem em uma animação.
*   @return int: Quantos frames tem na animação de 1 a n, sendo n o total de frames da animação.
*
* Sprite::IsOpen: Verifica se a textura está aberta.
*   @return bool: Retorna true se a textura está aberta e false se não
*
* Sprite::SetScaleX:
*   @param int frame:
*
* Sprite::SetScaleY:
*   @param int frame:
*
* Sprite::SetFrame: Seta o frame a ser utilizado
*   @param int frame: Frame a ser utilizado, esse número vai de 1 até n, sendo n o número total de frames na imagem.
*
* Sprite::SetFrameTotal: Seta o número total de frames na imagem.
*   @param int frame_total: Número total de frames na imagem.
*
* Sprite::SetFrameAnimation: Seta a duração da animação em frames
*   @param int frame_animation: Número de frames em uma animação.
*
* Sprite::SetFrameStart: Seta o primeiro frame da animação
*   @param int frame_start: Número do primeiro frame da animação, esse número vai de 1 até n, sendo n o número total de frames na imagem.
*
* Sprite::SetFrameTime: Seta o tempo de cada frame da animação
*   @param int frame_time: Tempo em segundos de duração de cada frame.
*
* Sprite::SetRepetitions: Seta a variavel repetitions da classe.
*   @param int repetitions: numero de repeticoes da animacao, se nulo a sprite nao tem animacao e se negativo a sprite tem loop infinito.
*
*
* @var SDL_Texture* texture: Textura da imagem.
* @var int frame_width: Largura de um frame da imagem.
* @var int width: Largura da imagem.
* @var int height: Altura da imagem.
* @var SDL_Rect* clipRect: recorte quadrado de texture.
* @var float scale_x: Escala em x.
* @var float scale_y: Escala em y.
* @var int frame_total: Número total de frames na imagem.
* @var int frame_animation: Número do ultimo frame da animação (pode ser o mesmo numero do frame_start se não houver animação).
* @var int frame_start: Número do primeiro frame da animação, esse número vai de 0 até n-1, sendo n o número total de frames na imagem
* @var float frame_time: Tempo em segundos de duração de cada frame.
* @var int frame_current: Frame atual que está sendo renderizado.
* @var Timer timer: Timer utilizado para controlar a duração das animações.
* @var int repetitions: numero de repeticoes da animacao, se nulo a sprite nao tem animacao e se negativo a sprite tem loop infinito.
* @var bool pause: se true a sprite nao eh animada se false sim.
**/

class Sprite {
    public:
        Sprite();
        Sprite(std::string file, int frame_total = 1, int frame_start = 1, int frame_animation = 1, float frame_time = 1, int repetitions = -1);
        virtual ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Update(float dt);
        void Render(int x, int y, float angle = 0);
        int GetWidth();
        int GetHeight();
        int GetFrameStart();
        int GetFrame();
        int GetAnimationDur();
        float GetFrameTime();
        bool IsOpen();
        void SetScaleX(float scale);
        void SetScaleY(float scale);
        void SetFrame(int frame);
        void SetFrameTotal(int frame_total);
        void SetFrameAnimation(int frame_animation);
        void SetFrameStart(int frame_start);
        void SetFrameTime(float frame_time);
        void SetRepetitions(int repetitions);
        void PauseAnimation();
        void ResumeAnimation();

    private:
        SDL_Texture* texture;
        int frame_width;
        int width;
        int height;
        SDL_Rect clip_rect;
        float scale_x;
        float scale_y;
        int frame_total;
        int frame_animation;
        int frame_animation_dur;
        int frame_start;
        float frame_time;
        int frame_current;
        Timer timer;
        int repetitions;
        bool pause;
};


#endif // SPRITE_H
