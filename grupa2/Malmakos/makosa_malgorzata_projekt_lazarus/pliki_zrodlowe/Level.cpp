#include "Level.h"

/**** Definicje skladnikow klasy level ****/

Level::Level() {
    is_null = true;
}

Level::Level(int w, int h, vector<int> t) {
    width = w;
    height = h;

    tab = t;
}

int Level::get_width() {
    return width;
}

int Level::get_height() {
    return height;
}

//vector<int> Level::get_tab() {
 //   return tab;
//}

int Level::get_position(int x, int y) {
    return tab[y*width+x]; //zwraca typ kwadratu z miejsca y*width+x
}

void Level::set_position(int x, int y, int type) {
    tab[y*width+x] = type; // przypisuje typ na miejsce y*width+x
}

//Funkcja pomocnicza
void Level::print_level() {
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            cout << get_position(j,i);
        }
        cout << endl;
    }
}
