#ifndef AMOEBA_H
#define AMOEBA_H

#include "Gra.h"

class Amoeba: public Gra
{
public:
    Amoeba(int szerokosc, int wysokosc, int liczba_cykli = 0);
    virtual ~Amoeba();
    void wykonajCykl();
    void losujPola();

};

#endif // AMOEBA_H
