#ifndef ARTIST_H
#define ARTIST_H

#include "Gra.h"


class Artist : public Gra
{
public:
    Artist(int szerokosc, int wysokosc, int liczba_cykli = 0);
    virtual ~Artist();
    void wykonajCykl();
    void losujPola();

};

#endif // ARTIST_H
