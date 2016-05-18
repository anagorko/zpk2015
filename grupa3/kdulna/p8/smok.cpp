#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include<iomanip>

const int w = 800;
const int h = 600;

double xmax = -100, ymax = -100, xmin = 100, ymin = 100;


double f1x(double x)
{
    return -0.4 * x - 1;
}

double f1y(double y)
{
    return -0.4 * y + 0.1;
}

double f2x(double x, double y)
{
    return 0.76 * x - 0.4 * y;
}

double f2y(double x, double y)
{
    return 0.4 * x + 0.76 * y;
}

int zero_x()
{
    return w * (0 - xmin) / (xmax - xmin);
}

int zero_y()
{
    return h * (0 - ymin) / (ymax - ymin);
}

int main()
{
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(0,0,0));

    double x[5000], y[5000];
    x[0] = 1;
    y[0] = 1;

    double xmax = -1, ymax = -1, xmin = 1, ymin = 1;

    for (int i = 1; i < 5000; i++){
        int a = rand();
        if (a % 2 == 0){
            x[i] = f1x(x[i - 1]);
            y[i] = f1y(y[i - 1]);
        } else{
            x[i] = f2x(x[i - 1], y[i - 1]);
            y[i] = f2y(x[i - 1], y[i - 1]);
        }
        if (i >= 100 && x[i] > xmax){
            xmax = x[i];
        }
        if (i >= 100 && x[i] < xmin){
            xmin = x[i];
        }
        if (i >= 100 && y[i] > ymax){
            ymax = y[i];
        }
        if (i >= 100 && y[i] < ymin){
            ymin = y[i];
        }
    }

    double avgx = 0, avgy = 0;
    for (int i = 100; i < 5000 ; i++){
        avgx = avgx + x[i];
        avgy = avgy + y[i];
    }
    avgx = avgx / 4900;
    avgy = avgy / 4900;

    cout << setprecision(1) << fixed;
    cout << "wartosc minimalna x: " << xmin << endl;
    cout << "wartosc maksymalna x: " << xmax << endl;
    cout << "wartosc minimalna y: " << ymin << endl;
    cout << "wartosc maksymalna y: " << ymax << endl;
    cout << "srodek ciezkosci: (" << avgx << " , " << avgy << ")" << endl;

    for (int i = 100; i < 5000; i++){
        al_draw_pixel(w - (x[i] / (xmax - xmin + 1) * w + zero_x() ), h - (y[i] / (ymax - ymin + 1) * h + zero_y() ), al_map_rgb(255,255,255));
    }

    al_flip_display();

    ALLEGRO_BITMAP *bitmap=al_get_backbuffer(display);

    al_save_bitmap("smok.bmp", bitmap);

    al_rest(5);
    al_destroy_display(display);

    return 0;
}
