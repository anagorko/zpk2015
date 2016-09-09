#ifndef AMAZING_H
#define AMAZING_H

#include "Gra.h"


class Amazing: public Gra
{
public:
    Amazing(int szerokosc, int wysokosc, int liczba_cykli);
    virtual ~Amazing();
    void wykonajCykl();
    void losujPola();
};

#endif // AMAZING_H
