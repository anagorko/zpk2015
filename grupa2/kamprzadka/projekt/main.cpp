#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "classes.h"
#include "collision_detection.h"
#include "game_functions.h"

using namespace std;


int main(int argc, char** argv)
{
    srand(time(0));
    ALLEGRO_DISPLAY *display = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;


    if (!al_init() || !al_install_mouse() || !al_install_keyboard() || !al_init_image_addon() ||
            !al_init_primitives_addon() ) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    event_queue = al_create_event_queue();
    timer = al_create_timer(0.001); //timer 1 ms
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    display = al_create_display(width, height);
    al_clear_to_color(al_map_rgb(0,0,0));

    /*inicjalizacja obiektów gry*/
    al_start_timer(timer); //timer
    rocket r1(400,300,0,0,0,0,0,0,0,"data\rocket.png"); //rakieta

    vector<asteroid> buf_asteroid; //asteroidy
    double v,vxa,vya,xa,ya,fia;
    for (int i=0;i<3;i++)
    {
        v=3;
        fia=(static_cast<double>(rand())/RAND_MAX*3)*12;
        xa=(static_cast<double>(rand())/RAND_MAX)*width;
        ya=(static_cast<double>(rand())/RAND_MAX)*height;
        vxa=v*sin(fia);
        vya=v*cos(fia);
        asteroid ast(xa,ya,0,vxa,vya,0.01);
        buf_asteroid.push_back(ast);
    }
    buf_asteroid[0].visible=true;
    buf_asteroid[1].visible=true;
    buf_asteroid[2].visible=true;


    vector<asteroid_small> buf_asteroid_sm; //asteroidy
    for (int i=0;i<6;i++)
    {
        v=9;
        fia=(static_cast<double>(rand())/RAND_MAX*3)*12;
        xa=(static_cast<double>(rand())/RAND_MAX)*width;
        ya=(static_cast<double>(rand())/RAND_MAX)*height;
        vxa=v*sin(fia);
        vya=v*cos(fia);
        asteroid_small ast_sm(xa,ya,0,vxa,vya,0.01);
        buf_asteroid_sm.push_back(ast_sm);
    }

    vector<projectile> bufor_poc; //pociski
    for(int i=0;i<n_bf;i++)
    {
        projectile poc(300,500,0,0,0);
        bufor_poc.push_back(poc);
    }
    int bul_nmb; //biezacy pocisk w buforze

    ALLEGRO_BITMAP *tlo;
    tlo = al_load_bitmap("data/background.jpg");

    int FPS=60;
    int LPS=25;
    int ctr_d=0; // licznik milisekund
    int ctr_l=0;
    int display_period=1000/FPS;
    int logic_period=1000/LPS;

    bool up=false;
    bool left=false;
    bool right=false;

    ALLEGRO_EVENT ev;
    bool game_running=true;

    //kolizje
    bool asteroid_proj = false;
    bool asteroid_rocket = false;
    bool asteroid_sm_proj = false;
    bool asteroid_sm_rocket = false;

    while(game_running)
    {
        al_wait_for_event(event_queue, &ev);
        get_keys(ev, up, left, right, ctr_l, ctr_d, bufor_poc, bul_nmb);

        if (ctr_l==logic_period)
            ctr_l=logic_update(r1,buf_asteroid_sm,buf_asteroid,bufor_poc,asteroid_proj, asteroid_rocket,
                            asteroid_sm_proj, asteroid_sm_rocket, up, left, right);

        if (ctr_d==display_period)
            ctr_d=display_update(tlo,r1,bufor_poc,buf_asteroid,buf_asteroid_sm);
    }

    al_destroy_display(display);

    return 0;
}
