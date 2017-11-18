#include "Celula.hpp"

Celula::Celula(){

}

Celula::Celula(int x, int y, Celula* ptr_cel_antiga){
        this->x = x;
        this->y = y;
        this->ptr_cel_antiga = ptr_cel_antiga;
}
