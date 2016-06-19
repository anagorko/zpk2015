#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <iostream>
using namespace std;

/**** Plik naglowkowy klasy level ****/

class Level
{
    public:
        //Typy kwadratow
        int TYPE_EMPTY=0; //brak kwadratu
        int TYPE_METAL_BOX=1; //kwadrat metalowy, czyli sciana
        int TYPE_WOOD_BOX=2; // kwadrat drewniany
        int TYPE_PLAYER=3; // gracz
        int TYPE_POINT=4; //punkt koncowy
        int TYPE_STONE_BOX=5; // kwadrat kamienny

        Level(); // konstruktor levelu
        // drugi konstruktor, tworzy lecvel o szerokosci width, wysokosci height i specyfikacji wprowadzonej do wektora tab
        Level(int width, int height, vector<int> tab);
        int get_width(); //zwraca szerokosc levelu
        int get_height(); //zwraca wysokosc levelu
        int get_position(int x, int y); // zwraca typ w danym miejscu w wektorze
        void set_position(int x, int y, int type); // wstawia typ do danego miejsca w wektorze
        void print_level(); // dodatkowa funkcja do sprawdzenia czy level zmienia siê prawidlowo, posyla level na strumien

        bool is_null; // zmienna pomocnicza
    protected:
        //cechy levelu
        int width; //szerokosc
        int height; //wysokosc

        vector<int> tab; //wektor z informacja o cechach levelu
    private:
};

#endif // LEVEL_H
