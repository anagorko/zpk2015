#include<iostream>
using namespace std;
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <cstdlib>

const int ScreenWeight = 800;
const int ScreenHeight = 600;

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(ScreenWeight, ScreenHeight);

    al_clear_to_color(al_map_rgb(0,0,0));

    float x=600;
    float y=300;
    for(int i=0;i<10000;i++){
        if(rand()%2+1==1)
        {
            x=-0.4*x-1;
            y=-0.4*y+0.1;
        }
        else{
            x=0.76*x-0.4*y;
            y=0.4*x+0.76*y;
        }
        al_draw_pixel(x*400 + 400 , y*300+300, al_map_rgb(0,255,0));
    }
    al_flip_display();
    al_rest(10);
    al_destroy_display(display);
    return 0;
}
