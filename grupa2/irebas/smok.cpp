#include<iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

using namespace std;

const int w = 800;
const int h = 600;
const int n = 10000;

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY*display = NULL;

    al_init();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(0,0,0));

    double x, y;
    x = 1;
    y = 1;
    // punkt startowy


    double xmin = 100, xmax = -100, ymin = 100, ymax = -100;
    // maksymalne i minimalne wartosci

    for (int i = 0; i < n; i++) {

        if (if rand() % 2 ==0){
            x = -0.4 * x - 1;
            y = -0.4 * y + 0.1;
    // jezeli parzysta to modyfikuje
        }
        else {
            x = 0.76 * x - 0.4 * y;
            y = 0.4 * x + 0.76 * y;
        }

    if (i >= 100) {

            sum_x += x;
            sum_y += y;

            if (x > xmax)
                xmax = x;
            else if (x < xmin)
                xmin = x;
            if (y > ymax)
                ymax = y;
            else if (y < ymin)
                ymin = y;

            al_draw_pixel(400 * (x + 1), 500 * (y + 0.5), al_map_rgb(255,255,255));
        }

    }

    al_flip_display();
    al_rest(10);
    al_destroy_display(display);

    cout << "Srodek masy smoka:" << endl;
    cout << "X = " << sum_x / 4900 << endl;
    cout << "Y = " << sum_y / 4900 << endl;
    cout << endl;

    cout << "Rozmiary smoka:" << endl;
    cout << "X min = " << xmin << endl;
    cout << "Y min = " << ymin << endl;
    cout << "X max = " << xmax << endl;
    cout << "Y max = " << ymax << endl;
}
