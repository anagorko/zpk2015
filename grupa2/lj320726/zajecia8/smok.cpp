#include<iostream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>

const int w = 800;
const int h = 600;
const int n = 120000;
double sup, inf;

int main(int argc, char** argv)
{

    sup = -1000000;
    inf = 1000000;
    int m = n+100;
    double tx[m];
    double ty[m];
    tx[0]=1;
    ty[0]=1;
    srand(time( NULL ));
    for (int i=1;i<m;i++)
    {
        double prawd = double(rand()) / (RAND_MAX);;
        if (prawd>=0.5){
            tx[i] = -0.4*tx[i-1]-1;
            ty[i]= -0.4*ty[i-1]+0.1;
        }
        else {
            tx[i] = 0.76*tx[i-1]-0.4*ty[i-1];
            ty[i]= 0.4*tx[i-1]+0.76*ty[i-1];
        }
        if (tx[i] > sup)  sup = tx[i];
        if (ty[i] > sup)  sup = ty[i];
        if (tx[i] < inf)  inf = tx[i];
        if (ty[i] < inf)  inf = ty[i];
    }
    ALLEGRO_DISPLAY       *display = NULL;

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(w, h);

    al_clear_to_color(al_map_rgb(0,0,0));

    double srx=0;
    double sry=0;
    double maxx, maxy,minx,miny;
    maxx=-10000;
    maxy=-10000;
    minx=10000;
    miny=10000;


    for (int i = 100; i < m; i++) {
        al_draw_pixel(2*w/3 + (tx[i] / (sup - inf) * w), h/2 - (ty[i] / (sup - inf) * h), al_map_rgb(255,255,255));
        if (tx[i]>maxx) maxx=tx[i];
        if (ty[i]>maxy) maxy=ty[i];
        if (tx[i]<minx) minx=tx[i];
        if (ty[i]<miny) miny=ty[i];
        srx=tx[i]+srx;
        sry=ty[i]+sry;
    }
    srx=srx/n;
    sry=sry/n;
    cout.precision(1 + 1);
    cout<<endl<< "Maksymalna wartosc x wynosi: "; printf( "%.1f", maxx );
    cout<<endl<< "Maksymalna wartosc y wynosi: "; printf( "%.1f", maxy );
    cout<<endl<< "Minimalna wartosc x wynosi: "; printf( "%.1f", minx );
    cout<<endl<< "Minimalna wartosc y wynosi: "; printf( "%.1f", miny );
    cout<<endl<< "Srodek ciezkosci smoka(x:y) to: "<<"("; printf( "%.1f", srx ); cout<<":"; printf( "%.1f", sry); cout<<")";

    al_flip_display();


    ALLEGRO_BITMAP *bitmap=al_get_backbuffer(display);

    al_save_bitmap("smok.bmp", bitmap);
    al_rest(5);
    al_destroy_display(display);

    return 0;
}
