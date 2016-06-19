#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;


const int width = 800;
const int height = 600;
const int n_bf=25; //pociski w buforze

struct Point
{
    int x,y;
};

class game_object
{
    public:
    int x,y;
    double vx, vy;
    double v;
    double fi;
    bool fired;
    int f_step;
    double w;
    double ax;
    double ay;
    double e;
    bool visible;
    int x_mid, y_mid; //srodek figury
    ALLEGRO_BITMAP *bitmap;

    void displ()
    {
        al_draw_rotated_bitmap(bitmap, x_mid, y_mid, x, y, fi, 0);
        if(x>=width) x=1;
        if(x<=0) x=width-1;
        if(y>=height) y=1;
        if(y<=0) y=height-1;
    }

    protected:
    void rotate_mask(Point wierz[], int vertex[][2], int vert_cnt)
    {
        for (int i=0;i<vert_cnt;i++)
            {
                vertex[i][0]=x-wierz[i].y*sin(fi)+wierz[i].x*cos(fi);
                vertex[i][1]=y+wierz[i].y*cos(fi)+wierz[i].x*sin(fi);
            }
    }
};

class aster : public game_object //opis asteroid
{
    public:
    int vertex[8][2];//wspolrzedne bezwzgledne (dynamiczne) wierzcholkow maski
    Point wierz[8]; //wspolrzedne wzgledne (statyczne) wierzcholkow maski
    void state_update()
         {
            //zamkniecie swiata
            if(x>=width+25) x=1;
            if(x<=-25) x=width-1;
            if(y>=height+25) y=1;
            if(y<=-25) y=height-1;

            //aktualizacja stanu
            x=x-vx; //update pozycja x
            y=y+vy; //update pozycja y
            fi=fi+w; //update kat

            /*maska asteroidy*/
            rotate_mask(wierz, vertex, 8);
         }
};

class projectile : public game_object
{
public:
    /*wierzcholki - detekcja kolizji*/
    int vertex[4][2]; //wspolrzedne bezwzgledne (dynamiczne) wierzcholkow maski
    Point wierz[4]; //wspolrzedne wzgledne (statyczne) wierzcholkow maski
    int vert_cnt;
    int czas_zycia;

    projectile(int _x, int _y, double _vx, double _vy, double _fi)
    {
        f_step=0;
        v=20;
        fired=false;
        x=_x;
        y=_y;
        vy=_vy;
        vx=_vx;
        fi=_fi;
        bitmap = al_load_bitmap("data/bullet.png");

        /*maska pocisku*/
        wierz[0].x=-3; wierz[0].y=-7;
        wierz[1].x=3; wierz[1].y=-7;
        wierz[2].x=3; wierz[2].y=7;
        wierz[3].x=-3; wierz[3].y=7;
        vert_cnt=sizeof(vertex)/sizeof(*vertex);

        x_mid=2;
        y_mid=7;
        czas_zycia=10;
    }

    ~projectile()
    {

    }

    void state_update(int _x, int _y, double _fi, double _vx, double _vy)
     {
        //zamkniecie swiata
        if(x>=width) x=30;
        if(x<=0) x=width-1;
        if(y>=height) y=1;
        if(y<=0) y=height-1;

        //gdy wystrzelony
        if (fired==true)
        {
            if (f_step==0)
            {
                x=_x;
                y=_y;
                fi=_fi;
                vx=-sin(_fi)*v+_vx;
                vy=-cos(_fi)*v+_vy;
            }
            f_step++;

            if(f_step==czas_zycia) //czas zycia pocisku = 10
            {
                fired=false;
                vx=0;
                vy=0;
                f_step=0;
            }
        }

        //aktualizacja stanu
        x=x-vx; //update pozycja x
        y=y+vy; //update pozycja y
        /*maska pocisku*/
        rotate_mask(wierz, vertex, vert_cnt);
     }
};

class rocket : public game_object
{
public:

    int vertex[3][2];//wspolrzedne bezwzgledne (dynamiczne) wierzcholkow maski
    Point wierz[3]; //wspolrzedne wzgledne (statyczne) wierzcholkow maski
    int vert_cnt;

    rocket(int _x, int _y, double _fi, double _vx, double _vy, double _w,
             double _ax, double _ay, double _e, string _path)
         {
             x=_x;
             y=_y;
             fi=_fi;
             vx=_vx;
             vy=_vy;
             w=_w;
             ax=_ax;
             ay=_ay;
             e=_e;
             bitmap = al_load_bitmap("data/rocket.png");

             vert_cnt=sizeof(vertex)/sizeof(*vertex);

             /*maska rakiety*/
             wierz[0].x=0; wierz[0].y=-32;
             wierz[1].x=18; wierz[1].y=30;
             wierz[2].x=-18; wierz[2].y=30;

             x_mid=8;
             y_mid=30;
         }

    ~rocket()
    {
    }

    void state_update(bool up, bool left, bool right)
         {

            if (up==true)
            {
                ax=-sin(fi)*0.5;
                ay=-cos(fi)*0.5;
            }

            if (left==true) e=-0.01;
            if (right==true) e=0.01;

            //zamkniêcie swiata
            if(x>=width) x=1;
            if(x<=0) x=width-1;
            if(y>=height) y=1;
            if(y<=0) y=height-1;

            //aktualizacja stanu
            vx=vx+ax; //update predkosc x
            vy=vy+ay; //update predkosc y
            w=w+e; //update predkosc obrotowa
            x=x-vx; //update pozycja x
            y=y+vy; //update pozycja y
            fi=fi+w; //update kat
            ax=0;
            ay=0;
            e=0;

            vert_cnt=sizeof(vertex)/sizeof(*vertex);

            /*maska rakiety*/
            rotate_mask(wierz, vertex, vert_cnt);
         }
};

class asteroid : public aster
{
    public:
    int vert_cnt;

    asteroid(int _x, int _y, double _fi, double _vx, double _vy, double _w)
         {
             x=_x;
             y=_y;
             fi=_fi;
             vx=_vx;
             vy=_vy;
             w=_w;
             bitmap = al_load_bitmap("data/asteroid.png");
             visible=false;

             /*maska asteroidy*/
             wierz[0].x=-64; wierz[0].y=-19;
             wierz[1].x=-43; wierz[1].y=-45;
             wierz[2].x=0; wierz[2].y=-54;
             wierz[3].x=56; wierz[3].y=-37;
             wierz[4].x=67; wierz[4].y=11;
             wierz[5].x=23; wierz[5].y=52;
             wierz[6].x=-38; wierz[6].y=48;
             wierz[7].x=-64; wierz[7].y=21;

             vert_cnt=sizeof(vertex)/sizeof(*vertex);

             x_mid=67;
             y_mid=55;
         }

    ~asteroid()
    {
    }
};

class asteroid_small : public aster
{
    public:
    int vert_cnt;

    asteroid_small(int _x, int _y, double _fi, double _vx, double _vy, double _w)
         {
             x=_x;
             y=_y;
             fi=_fi;
             vx=_vx;
             vy=_vy;
             w=_w;
             bitmap = al_load_bitmap("data/asteroid2.png");
             visible=false;

             /*maska asteroidy*/
             wierz[0].x=-35; wierz[0].y=-3;
             wierz[1].x=-14; wierz[1].y=-35;
             wierz[2].x=10; wierz[2].y=-35;
             wierz[3].x=32; wierz[3].y=-37;
             wierz[4].x=33; wierz[4].y=11;
             wierz[5].x=20; wierz[5].y=52;
             wierz[6].x=-7; wierz[6].y=48;
             wierz[7].x=-28; wierz[7].y=21;
             vert_cnt=sizeof(vertex)/sizeof(*vertex);

             x_mid=35;
             y_mid=36;
         }

    ~asteroid_small()
    {
    }
};


void display_update(ALLEGRO_BITMAP *tlo, rocket r1, vector<projectile> bufor_poc, vector<asteroid> buf_asteroid, vector<asteroid_small> buf_asteroid_sm)
    {

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_rotated_bitmap(tlo, 0, 0, 0,0, 0, 0);
        r1.displ(); //rakieta
        for(int i=0;i<n_bf;i++)
        {
            if(bufor_poc[i].fired==true)
                bufor_poc[i].displ();
        }

        for(int i=0; i<3; i++)
        {
            if (buf_asteroid[i].visible==true)
                buf_asteroid[i].displ();
        }

        for(int i=0; i<6; i++)
        {
            if (buf_asteroid_sm[i].visible==true)
                buf_asteroid_sm[i].displ();
        }

        al_flip_display();
    }

bool overlapping_projection(int sh1[][2], int sh2[][2], int e1, int e2, int pocz, int kon)
{
    /*bada czy rzuty na dowolny wyznaczony dwoma wierzcholkami kierunek pokrywaja sie
    rzuty odbywają sie na kierunek normalny do wyznaczonego przez punkty sh1[pocz], sz1[kon]*/
    //a,b - punkty wyznaczajace kierunek normalny do krawedzi
    int a[2],b[2];
    int rzut_sh1[2], rzut_sh2[2];
    rzut_sh1[0]=1000000, rzut_sh2[0]=1000000; //na pozycji 0 - minimum, na pozycji 1 - maksimum
    rzut_sh1[1]=0, rzut_sh2[1]=0;
    int k;

    string space=" ";
    string tab="    ";

    /*wyznaczenie kierunku normalnego do krawedzi*/
    a[0]=-sh1[pocz][1];
    a[1]=sh1[pocz][0];
    b[0]=-sh1[kon][1];
    b[1]=sh1[kon][0];


    //opisanie osi za pomoca wektora osadzonego w pkt(0,0)
    a[0]=a[0]-b[0];
    a[1]=a[1]-b[1];

    /*rzuty kolejnych puntow sh1*/
    for (int j=1; j<e1; j++)
    {
        k=sh1[j][0]*a[0]+sh1[j][1]*a[1];
        if (k<rzut_sh1[0]) rzut_sh1[0]=k;
        if (k>rzut_sh1[1]) rzut_sh1[1]=k;
    }

    /*rzuty kolejnych puntow sh2*/
    for (int j=1; j<e2; j++)
    {
        k=sh2[j][0]*a[0]+sh2[j][1]*a[1];
        if (k<rzut_sh2[0]) rzut_sh2[0]=k;
        if (k>rzut_sh2[1]) rzut_sh2[1]=k;
    }

    /*czy rzuty nachodza na siebie?*/
    if (rzut_sh2[1]<rzut_sh1[0] || rzut_sh2[0]>rzut_sh1[1])
    {
        return false;
    }
    else return true;
}

bool overlapping_edges (int sh1[][2], int sh2[][2], int e1, int e2)
{
    /*bada czy występuje kolizja dwóch kształtów okreslonych tablicą wierzchołków*/

    /*jesli istnieje os dla ktorej rzuty nie nachodza na siebie wowczas nie ma kolizji!*/
    /*normalne do krawędzi sh1*/

    for (int i=1; i<e1; i++)
    {
        if (overlapping_projection(sh1,sh2,e1,e2,i-1,i)==false)
        {
            return false;
        }

    }

    //ostania krawedz
    if (overlapping_projection(sh1,sh2,e1,e2,0,e1-1)==false)
            return false;
    /*normalne do krawędzi sh2*/
    for (int i=1; i<e2; i++)
    {
        if (overlapping_projection(sh2,sh1,e2,e1,i-1,i)==false)
            return false;
    }
    //ostania krawedz
    if (overlapping_projection(sh2,sh1,e2,e1,0,e2-1)==false)
            return false;
    return true;
}


void collision(vector<projectile>& bufor_poc, vector<asteroid>& buf_asteroid, vector<asteroid_small>& buf_asteroid_sm,
               rocket& roc, bool& asteroid_proj, bool& asteroid_rocket, bool& asteroid_sm_proj, bool& asteroid_sm_rocket)
{
    /*bada czy nastapila kolizja kluczowych obiektow na mapie*/
    asteroid_proj=false;
    asteroid_rocket=false;
    asteroid_sm_proj=false;
    asteroid_sm_rocket=false;
    int e_rocket=roc.vert_cnt;
    int e_asteroid=buf_asteroid[0].vert_cnt;
    int e_projectile=bufor_poc[0].vert_cnt;

    //kolizja rakieta - asteroida
    for (int i=0; i<buf_asteroid.size(); i++)
    {
        /*widoczne asteroidy*/
        if (buf_asteroid[i].visible==true)
        {
            if(overlapping_edges (roc.vertex, buf_asteroid[i].vertex, e_rocket, e_asteroid)==true)
            {
                asteroid_rocket=true;
                roc.x=0;
                roc.y=0;
                roc.vx=0;
                roc.vy=0;
                roc.w=0;
                i=buf_asteroid.size();
            }

        }
    }

    //kolizja pocisk - asteroida
    for (int i=0; i<buf_asteroid.size(); i++)
    {
        /*widoczne asteroidy*/
        if (buf_asteroid[i].visible==true)
        {
            for (int j=0; j<bufor_poc.size();j++)
            {
                if (bufor_poc[j].fired==true)
                {
                    if(overlapping_edges (bufor_poc[j].vertex, buf_asteroid[i].vertex, e_rocket, e_asteroid)==true)
                    {
                        asteroid_proj=true;
                        buf_asteroid[i].visible=false;
                        bufor_poc[j].fired=false;
                        bufor_poc[j].vx=0;
                        bufor_poc[j].vy=0;
                        bufor_poc[j].f_step=0;
                        buf_asteroid_sm[2*i].visible=true;
                        buf_asteroid_sm[2*i].x=buf_asteroid[i].x;
                        buf_asteroid_sm[2*i].y=buf_asteroid[i].y;
                        buf_asteroid_sm[2*i+1].visible=true;
                        buf_asteroid_sm[2*i+1].x=buf_asteroid[i].x;
                        buf_asteroid_sm[2*i+1].y=buf_asteroid[i].y;
                        j=bufor_poc.size();
                    }
                }

            }
        }
    }

    //kolizja rakieta - asteroida mała
    for (int i=0; i<buf_asteroid_sm.size(); i++)
    {
        /*widoczne asteroidy*/
        if (buf_asteroid_sm[i].visible==true)
        {
            if(overlapping_edges (roc.vertex, buf_asteroid_sm[i].vertex, e_rocket, e_asteroid)==true)
            {
                roc.x=0;
                roc.y=0;
                roc.vx=0;
                roc.vy=0;
                roc.w=0;
                asteroid_sm_rocket=true;
                i=buf_asteroid_sm.size();
            }

        }
    }

    //kolizja pocisk - asteroida mała
    for (int i=0; i<buf_asteroid_sm.size(); i++)
    {
        /*widoczne asteroidy*/
        if (buf_asteroid_sm[i].visible==true)
        {
            for (int j=0; j<bufor_poc.size();j++)
            {
                if (bufor_poc[j].fired==true)
                {
                    if(overlapping_edges (bufor_poc[j].vertex, buf_asteroid_sm[i].vertex, e_rocket, e_asteroid)==true)
                    {
                        asteroid_sm_proj=true;
                        bufor_poc[j].fired=false;
                        bufor_poc[j].vx=0;
                        bufor_poc[j].vy=0;
                        bufor_poc[j].f_step=0;
                        buf_asteroid_sm[i].visible=false;
                        j=bufor_poc.size();
                    }
                }

            }
        }
    }
}

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
  //  bool poc=false;

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

        if(ev.type==ALLEGRO_EVENT_TIMER)
        {
            ctr_d++;
            ctr_l++;
        }
        else if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    up=true;
                break;
                case ALLEGRO_KEY_LEFT:
                    left=true;
                break;
                case ALLEGRO_KEY_RIGHT:
                    right=true;
                break;
                case ALLEGRO_KEY_SPACE:
                    for(int i=n_bf;i>=0;i--)
                    {
                        if (bufor_poc[i].fired==false)
                        bul_nmb=i;
                    }
                    bufor_poc[bul_nmb].fired=true;
                break;
            }
        }
        else if(ev.type==ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    up=false;
                    break;
                break;
                case ALLEGRO_KEY_LEFT:
                    left=false;
                break;
                case ALLEGRO_KEY_RIGHT:
                    right=false;
                break;
            }
        }

        if (ctr_l==logic_period)
        {
            r1.state_update(up, left, right);
            for (int i=0; i<6; i++)
                buf_asteroid_sm[i].state_update();
            for (int i=0; i<3; i++)
                buf_asteroid[i].state_update();

            for(int i=0;i<n_bf;i++)
                bufor_poc[i].state_update(r1.x, r1.y, r1.fi, r1.vx, r1.vy);

            collision(bufor_poc, buf_asteroid, buf_asteroid_sm, r1, asteroid_proj, asteroid_rocket, asteroid_sm_proj,
                      asteroid_sm_rocket);
            ctr_l=0;
        }

        if (ctr_d==display_period)
        {
            display_update(tlo,r1,bufor_poc,buf_asteroid,buf_asteroid_sm);
            ctr_d=0;
        }
    }

    al_destroy_display(display);

    return 0;
}
