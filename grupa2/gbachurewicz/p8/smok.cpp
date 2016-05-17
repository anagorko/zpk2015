#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const int w = 800;
const int h = 600;
const int N = 100000; //N to liczba iteracji



int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(255,255,255)); //ustawiamy biale tlo

    double x, y;
    x = 1;
    y = 1; //punkt startowy dla (x,y) to (1,1)
    for (int i=0; i< N; i++) {
        if ((rand() % 2) == 0) { //gdy losowa jest parzysta to pierwsze przeksztalcenie ukladu
            x = -0.4*x - 1; //modyfikacja wspolrzednych
            y = -0.4*y + 0.1;
            al_draw_pixel(x*w/4 + w/2,y*h/4 + h/2, al_map_rgb(0,0,0)); //rozpoczynamy rysowanie od srodka ekranu (w/2,h/2)
        }
        else {
            x = 0.76*x - 0.4*y;
            y = 0.4*x + 0.76*y;
            al_draw_pixel(x*w/4 + w/2,y*h/4 + h/2, al_map_rgb(0,0,0)); //oddalenia punktow od siebie skalujemy przez wektor (w/4,h/4)
        }

    }

    al_flip_display();

    al_rest(5);
    al_destroy_display(display);

    return 0;
}
