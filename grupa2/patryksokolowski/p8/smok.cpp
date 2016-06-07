#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const int w = 800;
const int h = 600;
const int n = 1000000;



int main()
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(255,255,255));

    double x, y;
    x = 1;
    y = 1;

    for (int i=0; i< n; i++) {
        if ((rand() % 2) == 0) {
            x = -0.4*x - 1;
            y = -0.4*y + 0.1;
            al_draw_pixel(x*w/4 + w/2,y*h/4 + h/2, al_map_rgb(255,0,0));
        }
        else {
            x = 0.76*x - 0.4*y;
            y = 0.4*x + 0.76*y;
            al_draw_pixel(x*w/4 + w/2,y*h/4 + h/2, al_map_rgb(255,0,0));
        }

    }

    al_flip_display();

    al_rest(10);
    al_destroy_display(display);

    return 0;
}
