#ifndef HIGHLIFE_H
#define HIGHLIFE_H

#include "Gra.h"

class HighLife: public Gra
{
    public:
        HighLife(int szerokosc, int wysokosc, int liczba_cykli);
        virtual ~HighLife();
        void wykonajCykl();
        void losujPola();

};

#endif // HIGHLIFE_H

