
#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h> //podstawowe funkcje geometryczne
#include <math.h>
#include <cstdlib>
#include <vector>

const int w = 800;
const int h = 600;

vector <double> wektor_x;
vector <double> wektor_y;

double x=1;
double y=1;


void calculate()
{

    wektor_x.push_back(1);
    wektor_y.push_back(1);

    int losowa;
    double x2;
    double y2;
    for (int i=1; i<10000; i++)
    {

        losowa = (rand() % 2);

        if (losowa == 0)
        {
            x2 = - 0.4*x - 1;
            y2 = - 0.4*y + 0.1;

            x=x2;
            y=y2;
        }

        else
        {
            x2 = 0.76*x - 0.4*y;
            y2 = 0.4*x + 0.76*y;

            x=x2;
            y=y2;
        }

        wektor_x.push_back(x);
        wektor_y.push_back(y);
    }
}

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY       *display = NULL;
    al_init();
    al_init_primitives_addon();
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    display = al_create_display(w, h);

    calculate();

    al_clear_to_color(al_map_rgb(0,0,0));

    for (int i = 0; i < wektor_x.size(); i++)
    {
        al_draw_pixel( wektor_x[i], wektor_y[i], al_map_rgb(255,255,255));
    }

    al_flip_display();

    al_rest(30);
    al_destroy_display(display);

    return 0;
}
