#ifndef CORAL_H
#define CORAL_H

#include "Gra.h"


class Coral: public Gra
{
public:
    Coral(int szerokosc, int wysokosc, int liczba_cykli = 0);
    virtual ~Coral();

    void wykonajCykl();
    void losujPola();

};

#endif // CORAL_H
