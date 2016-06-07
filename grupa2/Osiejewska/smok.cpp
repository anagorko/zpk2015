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

    double x = 1, y=1;
    double x_s=0, y_s=0;
    double x_min = 100, x_max = -100, y_min = 100, y_max = -100; //min i max

    for (int i = 0; i < 5000; i++) {

       int pr = rand();

        if (if pr % 2 ==0){
            x_s = -0.4 * x - 1;
            y_s = -0.4 * y + 0.1;
            x = x_s;
            y = y_s;
        }
        else {
            x_s = 0.76 * x - 0.4 * y;
            y_s = 0.4 * x + 0.76 * y;
            x = x_s;
            y = y_s;
        }

    if (i >= 100) {

            suma_x += x;
            suma_y += y;

            if (x > max_x)
                max_x = x;
            else if (x < min_x)
                min_x = x;
            if (y > max_y)
                max_y = y;
            else if (y < min_y)
                min_y = y;

            al_draw_pixel(300 * (x_s + 300), 500 * (y_s + 500), al_map_rgb(255,255,255));
        }

    }

    al_flip_display();

    al_rest(15);
    al_destroy_display(display);

    cout << "Srodek masy:" << endl;
    cout << "x = " << x_s / 4900 << endl;
    cout << "y = " << y_s / 4900 << endl;
    cout << endl;

    cout << "Rozmiary:" << endl;
    cout << "x_min = " << x_min << endl;
    cout << "y_min = " << min_y << endl;
    cout << "x_max = " << x_max << endl;
    cout << "y_max = " << max_y << endl;
}
