#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <iostream>
#include <cstdlib>

#ifndef _mrowka_h

#define	_mrowka_h

using namespace std;

//#define VERSION "1.0"


namespace Mrowka {

    const int SZER = 800;

    const int WYS = 600;

    enum kierunek {
        N = 0,
        E= 1,
        S = 2,
        W = 3};

    class pole{

    private:

        int pozX, pozY;
        int rozmiar;
        int kolor;

    public:


    pole()
    {
        pozX=0;
        pozY=0;
        rozmiar=1;
        kolor= 1;   //kolory : 1- czarny, 2-niebieski 3- czerwony
    }


        pole(int x, int y, int rozmiar);
        unsigned int getX();
        unsigned int getY();
        int getKolor();
        void setKolor(int k);
        unsigned int getRozmiar();
        void setX(unsigned int x);
        void setY(unsigned int y);
        void setRozmiar(unsigned int rozmiar);

    };


    class mrowa{

    private:
        int pozX, pozY;
        int rozmiar;
        kierunek zwrot;
        ALLEGRO_BITMAP *obrazek;

    public:

    mrowa()
    {
        pozX=0;
        pozY=0;
        rozmiar=1;
        zwrot = N;
    }


        mrowa(int x, int y, int z);
        void ruch();
        void rysujMr();
        void lewo();
        void prawo();
        void setX(unsigned int x);
        void setY(unsigned int y);
        unsigned int getX();
        unsigned int getY();
        ALLEGRO_BITMAP *getBMP();
        unsigned int getRozmiar();
        void setRozmiar(unsigned int x);
        kierunek getZwrot();
        void setZwrot(kierunek zwrot);
        void pomaluj(vector <pole> &NieBiale, int kolory);
        void skret(vector <pole> &NieBiale);
        int czySieZmiesci(vector <pole> &NieBiale);
        /*int kolor(vector <pole> &NieBiale);*/// sprawdza czy pozycje mrowki pokrywaja sie z ktoryms z czarnych pol przechowywanych w vectorze 'czarnepole' klasy pole


    };


};




#endif	/* _MROWKA_H */




