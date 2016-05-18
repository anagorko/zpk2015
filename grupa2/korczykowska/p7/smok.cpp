#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const int w = 1000;
const int h = 800;

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(0,0,0));


    double x = 10;
    double y = 10;
    double x_p, y_p; //wartosci x prim, y prim
    double pstwo;    //prawdopodobienstwo, czy 1 rownanie czy drugie
//wybieranie dowolnego rownania
//z jednakowym prawdopodobieństwem obu
//liczb parzystych jest tylko samo co parzystych, więc
//losuje liczbe z rand() i sprawdzam, czy podzielna przez 2

    for (int i = 0; i < 10000; i++) {

        pstwo = rand()

        if (if pstwo % 2 ==0){
            x_p = -0.4 * x - 1;
            y_p = -0.4 * y + 0.1;
            al_draw_pixel(x_p + 300, y_p + 500, al_map_rgb(120,0,120));
            x = x_p;
            y = y_p;
        }
        else {
            x_p = 0.76 * x - 0.4 * y;
            y_p = 0.4 * x + 0.76 * y;
            al_draw_pixel(x_p + 300, y_p + 500, al_map_rgb(120,0,120));
            x = x_p;
            y = y_p;
        }

    }

    al_flip_display();

    al_rest(15);
    al_destroy_display(display);

    return 0;
}
