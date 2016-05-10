#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const int w = 800;
const int h = 600;

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(0,0,0));

    int scale=300;
    double x=1;
    double y=1;
    double xp, yp;
    double r=rand();

    for (int i = 0; i < 10000000; i++) {
        xp=x;
        yp=y;
        if(r>16383.5)
        {
            al_draw_pixel(scale*x+500,scale*y+300,al_map_rgb(255,0,0));
            x=-0.4*xp-1;
            y=-0.4*yp+0.1;

        }
        else
        {
            al_draw_pixel(scale*x+500,scale*y+300,al_map_rgb(0,0,255));
            x=0.76*xp-0.4*yp;
            y=0.4*xp+0.76*yp;

        }
        r=rand();
    }

    al_flip_display();

    al_rest(10);
    al_destroy_display(display);

    return 0;
}
