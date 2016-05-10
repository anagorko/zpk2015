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

    int scale=50;
    double x=1;
    double y=1;
    double r=rand();
    double xp,yp;

    double re=15;
    double g=200;
    double b=50;

    for (int i = 0; i < 500000; i++) {
        xp=x;
        yp=y;
        if(r<0.01*RAND_MAX)
        {
            al_draw_pixel(scale*x+350,-scale*y+550,al_map_rgb(re,g,b));
            x=0;
            y=0.16*yp;

        }
        else if(r<=0.08*RAND_MAX)
        {
            al_draw_pixel(scale*x+350,-scale*y+550,al_map_rgb(re,g,b));
            x=0.2*xp-0.26*yp;
            y=0.23*xp+0.22*yp+1.6;
        }
        else if(r<=0.15*RAND_MAX)
        {
            al_draw_pixel(scale*x+350,-scale*y+550,al_map_rgb(re,g,b));
            x=-0.15*xp+0.28*yp;
            y=0.26*xp+0.24*yp+0.44;
        }
        else
        {
            al_draw_pixel(scale*x+350,-scale*y+550,al_map_rgb(re,g,b));
            x=0.85*xp+0.04*yp;
            y=-0.04*xp+ 0.85*yp+1.6;
        }
        r=rand();
    }

    al_flip_display();

    al_rest(5);
    al_destroy_display(display);

    return 0;
}
