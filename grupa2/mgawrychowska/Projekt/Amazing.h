#ifndef AMAZING_H
#define AMAZING_H

#include "Gra.h"


class Amazing: public Gra
{
public:
    Amazing(int szerokosc, int wysokosc, int liczba_cykli = 0);
    virtual ~Amazing();
    void wykonajCykl();
    void losujPola();
};

#endif // AMAZING_H
