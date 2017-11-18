//feita para auxiliar na busca do A*

#ifndef CELULA_H
#define CELULA_H


class Celula{
    public:
        Celula();
        Celula(int x, int y, Celula* ptr_cel_antiga);
        int x;
        int y;
        Celula* ptr_cel_antiga;
        float custo_ate_agora;
        float custo_total;
};

#endif // CELULA_H
