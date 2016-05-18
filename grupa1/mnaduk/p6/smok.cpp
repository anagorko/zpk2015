#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
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

    float x=0, y=0;
    
    for(int i=0;i<5000;i++)
    {
        if(rand()%2==1)
        {
            x = -0.4*x -1;
            y = -0.4*y +0.1;
        }
        else
        {
            x= 0.76*x - 0.4*y;
            y= 0.4*x + 0.76*y;
        }
        al_draw_pixel((x+1.5)*400 , (y+0.6)*600, al_map_rgb(255,255,255));
    }
    al_flip_display();

    al_rest(3);
    al_destroy_display(display);

    return 0;
}
