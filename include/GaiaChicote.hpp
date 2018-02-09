#ifndef GAIACHICOTE_HPP
#define GAIACHICOTE_HPP

#include "GameObject.hpp"

class GaiaChicote : public GameObject{
    public:
        GaiaChicote(float x, float y);
        virtual ~GaiaChicote();
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
        bool IsDead();
        bool is_dead;
    private:

};

#endif // GAIACHICOTE_HPP
