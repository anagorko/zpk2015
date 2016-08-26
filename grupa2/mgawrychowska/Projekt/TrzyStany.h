#ifndef TRZYSTANY_H
#define TRZYSTANY_H

#include "Gra.h"

class TrzyStany: public Gra
{
public:
    TrzyStany(int szerokosc, int wysokosc, int liczba_cykli = 0);
    virtual ~TrzyStany();
    void wykonajCykl();
    void losujPola();
};

#endif // TRZYSTANY_H
