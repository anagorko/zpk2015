#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <cstdlib>

const int w = 1000;
const int h = 1000;

int main(int argc, char** argv)
{
    int los;
    double x, x1, y, y1;

    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    display = al_create_display(w, h); //wielkosc okienka

    al_clear_to_color(al_map_rgb(0,0,0)); //wyczyszcza okienko ze smieci i daje kolor 0 0 0 czarny


x=1;
y=1;
los =( rand() % 2 );

  for (int i = 0; i < 5000; i++) {


        cout<<"x="<<ceil(x*500+600)<<"  y="<<ceil(y*500+400)<<endl;
        los =( rand() % 2 );
        if (los==0) {x=-0.4*x-1; y=-0.4*y+0.1;}
        else {x1= x; y1=y; x=0.76*x1-0.4*y1; y=0.4*x+0.76*y1;}
        //al_draw_pixel(ceil(x*500+600),ceil(y*500+400), al_map_rgb(255, 0, 0));
        //rysowanie nie dziala
    }
    al_flip_display();

    al_rest(3);
    al_destroy_display(display);

    return 0;
}
