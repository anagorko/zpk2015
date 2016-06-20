#include "classes.cpp"
#include "collision_detection.cpp"
#include "game_functions.cpp"

using namespace std;


int main(int argc, char** argv)
{
    srand(time(0));

    /*deklaracja wyswietlacza i timera*/
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_COLOR color = al_map_rgba_f(1.0, 0.4, 0.6, 0);
    ALLEGRO_BITMAP *tlo;
    al_init_font_addon();

    if (!al_init() || !al_install_mouse() || !al_install_keyboard() || !al_init_image_addon()
        || !al_init_primitives_addon()
        || !al_init_ttf_addon()
        ) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }

    /*inicjalizacja obiektow allegro*/
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    event_queue = al_create_event_queue();
    timer = al_create_timer(0.001); //timer 1 ms
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    display = al_create_display(width, height);
    font=al_load_ttf_font("data/earthorbiterpunch.ttf",72,0 );
    al_clear_to_color(al_map_rgb(0,0,0));
    al_start_timer(timer); //timer
    ALLEGRO_EVENT ev;

    /*inicjalizacja obiektów gry*/
    rocket r1(400,300,0,0,0,0,0,0,0,"data\rocket.png"); //rakieta
    tlo = al_load_bitmap("data/background.jpg");
    vector<asteroid> buf_asteroid; //asteroidy duze
    double v,vxa,vya,xa,ya,fia;
    v=3;
    for (int i=0;i<3;i++)
    {
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

    vector<asteroid_small> buf_asteroid_sm; //asteroidy male
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

    /*parametry gry*/
    int FPS=60;
    int LPS=25;
    int ctr_d=0; // licznik milisekund
    int ctr_l=0;
    int display_period=1000/FPS;
    int logic_period=1000/LPS;
    int lifes=2;
    bool game_running=true;

    bool up=false;
    bool left=false;
    bool right=false;

    /*kolizje*/
    bool asteroid_proj = false;
    bool asteroid_rocket = false;
    bool asteroid_sm_proj = false;
    bool asteroid_sm_rocket = false;

    /*wygrana*/
    bool win=false;

    /*ekran powitalny*/
    while (up!=true)
            {
                al_draw_text(font, color, 170, 125, NULL, "asteroids");
                al_draw_text(font, color, 150, 300, NULL, "to start");
                al_draw_text(font, color, 210, 370, NULL, "Press UP");
                al_flip_display();
                al_wait_for_event(event_queue, &ev);
                get_keys(ev, up, left, right, ctr_l, ctr_d, bufor_poc, bul_nmb);
            }
    ctr_l=0;
    ctr_d=0;

    /*wlasciwa petla gry*/
    while(game_running)
    {
        /*eventy*/
        al_wait_for_event(event_queue, &ev);
        /*zebranie stanu klawiatury*/
        get_keys(ev, up, left, right, ctr_l, ctr_d, bufor_poc, bul_nmb);

        /*odswiezenie logiki gry*/
        if (ctr_l==logic_period)
        {

            ctr_l=logic_update(r1,buf_asteroid_sm,buf_asteroid,bufor_poc,asteroid_proj, asteroid_rocket,
                            asteroid_sm_proj, asteroid_sm_rocket, up, left, right);
            if (asteroid_sm_rocket==true || asteroid_rocket==true)
                lifes--;

            win = check_win(buf_asteroid,buf_asteroid_sm);
        }

        /*odswiezenie ekranu*/
        if (ctr_d==display_period)
            ctr_d=display_update(tlo,r1,bufor_poc,buf_asteroid,buf_asteroid_sm, lifes);

        /*gdy wygrana - tu to samo co w przy przegranej (zgodnie z ustaleniami brak kolejnych poziomow)*/
        if(win==true)
        {
            game_running = false;
            up=false;
            while (up!=true && left!=true)
            {
                al_flip_display();
                al_draw_text(font, color, 170, 75, NULL, "you won!");
                al_draw_text(font, color, 150, 200, NULL, "to retry");
                al_draw_text(font, color, 210, 280, NULL, "Press UP");
                al_draw_text(font, color, 150, 400, NULL, "to abort");
                al_draw_text(font, color, 210, 480, NULL, "Press LEFT");
                al_flip_display();
                al_wait_for_event(event_queue, &ev);
                get_keys(ev, up, left, right, ctr_l, ctr_d, bufor_poc, bul_nmb);
            }
            if(up==true) //gdy restart
            {
                al_clear_to_color(al_map_rgb(0,0,0));
                reinit(buf_asteroid, buf_asteroid_sm, r1, lifes, ctr_l, ctr_d, game_running);
                win=false;
            }

            if (left==true)
            {
                game_running=false;
            }
        }

        /*gdy przegrana*/
        if (lifes==0)
        {
            game_running = false;
            up=false;
            while (up!=true && left!=true)
            {
                al_flip_display();
                al_draw_text(font, color, 170, 75, NULL, "GAME OVER");
                al_draw_text(font, color, 150, 200, NULL, "to retry");
                al_draw_text(font, color, 210, 280, NULL, "Press UP");
                al_draw_text(font, color, 150, 400, NULL, "to abort");
                al_draw_text(font, color, 210, 480, NULL, "Press LEFT");
                al_flip_display();
                al_wait_for_event(event_queue, &ev);
                get_keys(ev, up, left, right, ctr_l, ctr_d, bufor_poc, bul_nmb);
            }
            if(up==true) //gdy restart
            {
                al_clear_to_color(al_map_rgb(0,0,0));
                reinit(buf_asteroid, buf_asteroid_sm, r1, lifes, ctr_l, ctr_d, game_running);
            }

            if (left==true)
            {
                game_running=false;
            }
        }
    }


    al_destroy_display(display);

    return 0;
}
