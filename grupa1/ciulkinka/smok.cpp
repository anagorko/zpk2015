#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <cstdlib>

const int w = 800;
const int h = 600;

int losuj()
{
    int r = rand() % 4 + 1;
    return r;
}

float oblicz_x(float x, float y, int r)
{
    /*r z przedzialu 1:4*/
    float x_;

    if (r < 3)
    {
        x_ = - (0.4 * x) - 1;
    } else
    {
        x_ = (0.76 * x) - (0.4 * y);
    }
    return x_;
}

double oblicz_y(float x, float y, int r)
{
    /*r z przedzialu 1:4*/
    float y_;

    if (r < 3)
    {
        y_ = - (0.4 * y) + 0.1;
    } else
    {
        y_ = (0.4 * x) + (0.76 * y);
    }
    return y_;
}

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    float x = 1;
    float y = 1;

    int los;

    for (int i = 1; i < 500000; i++)
    {
        los = losuj();

        x = oblicz_x(x, y, los);
        y = oblicz_y(x, y, los);

        al_draw_pixel((x * 300 + w/2),
                      (y * 300 + h/2),
                      al_map_rgb(255, 255, 255));
    }

    al_flip_display();

    al_rest(3);
    al_destroy_display(display);

    return 0;
}

