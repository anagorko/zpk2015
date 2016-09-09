#ifndef WIREWORLD_H
#define WIREWORLD_H

#include "Gra.h"

class WireWorld : public Gra
{
public:
    WireWorld(int szerokosc, int wysokosc, int liczba_cykli);
    virtual ~WireWorld();
    void wykonajCykl();
    void losujPola();

};

#endif // WIREWORLD_H
