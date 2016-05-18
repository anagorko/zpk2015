#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<math.h>
#include<iomanip>

using namespace std;

const int w = 800;
const int h = 600;

const int iteracje = 5000;

double xmin = 1;
double xmax = -1;
double ymin = 1;
double ymax = -1;
double xsum = 0;
double ysum = 0;
double xmean;
double ymean;

int x0 = 1;
int y0 = 1;

double x[iteracje], y[iteracje];

int zero_x(){
    return w * (0 - xmin) / (xmax - xmin);
}

int zero_y(){
    return h * (0 - ymin) / (ymax - ymin);
}

void smok(int x0, int y0, int iteracje){

    x[0] = x0;
    y[0] = y0;

    for(int i = 1;i < iteracje;i++){
        int los = rand();
            if(los % 2 == 0){
                x[i] = -0.4 * x[i-1] - 1;
                y[i] = -0.4 * y[i-1] + 0.1;
            }
            else{
                x[i] =  0.76 * x[i-1] - 0.40 * y[i-1];
                y[i] =  0.40 * x[i-1] + 0.76 * y[i-1];
            }
            if(i >= 100){
                xsum += x[i];
            }
            if(i >= 100){
                ysum += y[i];
            }
            if(i >= 100 && x[i] > xmax){
                xmax = x[i];
            }
            if(i >= 100 && x[i] < xmin){
                xmin = x[i];
            }
            if(i >= 100 && y[i] > ymax){
                ymax = y[i];
            }
            if(i >= 100 && y[i] < ymin){
                ymin = y[i];
            }
    }
    xmean = xsum / (iteracje - 100);
    ymean = ysum / (iteracje - 100);
}

int main(int argc, char** argv){
    ALLEGRO_DISPLAY *display = NULL;

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(0,0,0));

    smok(x0, y0, iteracje);

    for (int i = 100; i < iteracje; i++)
        al_draw_pixel((x[i] / (xmax - xmin) * w + zero_x()), (y[i] / (ymax - ymin) * h + zero_y()), al_map_rgb(255,255,255));

    al_flip_display();

    al_save_bitmap("smok.bmp", al_get_backbuffer(display));

    cout << setprecision(1) << fixed;
    cout << "Srednia wartosc x: " << xmean << endl;
    cout << "Srednia wartosc y: " << ymean << endl;
    cout << "Maksymalna wartosc x: " << xmax << endl;
    cout << "Minimalna wartosc x: " << xmin << endl;
    cout << "Maksymalna wartosc y: " << ymax << endl;
    cout << "Minimalna wartosc y: " << ymin << endl;

    al_rest(5);
    al_destroy_display(display);
}
