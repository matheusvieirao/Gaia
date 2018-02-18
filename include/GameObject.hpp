#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include "Rect.hpp"

/**
* GameObject::~GameObject: Destrutor de GameObject.
* GameObject::GameObject: Atualiza GameObject.
* GameObject::Render: Renderiza GameObject.
* GameObject::NotifyCollision: Verifica se houve colisão.
* GameObject::Is: Verifica o tipo do objeto (recebe uma string com o nome da classe e retorna true se for o mesmo nome da classe e false se nao).
* GameObject::IsDead: GameObject verifica se o objeto ou personagem está morto.
* GameObject::GetAlturaPe: Retorna a distancia entre o pe do personagem e o final da imagem no eixo y.
* GameObject::AcharComodo: Acha o comodo que o objeto esta incerido. para a funçao funcionar box deve ja estar setado.
*
* @var box Rect Retangulo com as dimensoes do objeto.
* @var rotation float com o angulo de rotacao em radianos
**/

class GameObject {
    public:
        GameObject();
        virtual ~GameObject();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual void NotifyCollision(GameObject& other) = 0;
        virtual bool Is(std::string type) = 0;
        virtual bool IsDead() = 0;
        virtual Rect GetBoxColisao();
        virtual void PushMovimento(int mov);
        void SetPause(bool pausar);
        void AcharComodo();
        int GetAlturaPe();
        int GetComodoAtual();
        Rect box;
        int comodo_atual;
        float rotation;
        int altura_pe;
        int largura_box_col;
        int altura_box_col;
        bool pause;
};

#endif // GAMEOBJECT_H
