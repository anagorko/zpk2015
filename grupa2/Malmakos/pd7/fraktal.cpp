
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

const int WYSOKOSC  = 600;
const int SZEROKOSC = 600;
double x=300;
double y=400;

double get_x1(double _x, double _y){
    x=-0.4*_x -1 +300;
    return x;
    }

double get_x2(double _x, double _y){
    x=0.76*_x -0.4*_y+300;
    return x;
    }
double get_y1(double _x, double _y){
    y=-0.4*_y +0.1+300;
    return y;
    }

double get_y2(double _x, double _y){
    y=0.4*_x +0.76*_y+300;
    return y;
    }
Int main(){
int los;
    ALLEGRO_DISPLAY *display = NULL;

    al_init();
    al_init_primitives_addon();
    srand (time(NULL));

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(SZEROKOSC, WYSOKOSC);

    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_line(0, WYSOKOSC/2, SZEROKOSC, WYSOKOSC/2, al_map_rgb(255,255,255), 2);
    al_draw_line(SZEROKOSC/2,0, SZEROKOSC/2, WYSOKOSC, al_map_rgb(255,255,255), 2);

        for(int i=0; i<70000;i++){
         los = rand() % 10 + 1;
            if(los<6){
            al_draw_pixel(get_x1(x,y), -get_y1(x,y)+300, al_map_rgb(255,255,255));
            }else{
            al_draw_pixel(get_x2(x,y), -get_y2(x,y)+300, al_map_rgb(255,255,255));
            }

        }

    al_flip_display();

    al_rest(20);
    al_destroy_display(display);

    return 0;
}
