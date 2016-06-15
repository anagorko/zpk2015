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

class projectile
{
public:
    int x,y;
    double vx, vy;
   // double w=0.1;
    double v=20;
    double fi;
    bool fired=false;
    int f_step=0;
    ALLEGRO_BITMAP *bitmap;

    /*wierzcholki - detekcja kolizji*/
    int vertex[4][2];
    int vert_cnt;
    int czas_zycia=10;


    projectile(int _x, int _y, double _vx, double _vy, double _fi)
    {
        x=_x;
        y=_y;
        vy=_vy;
        vx=_vx;
        fi=_fi;
        //vx=-sin(fi)*vx+v;
        //vy=-cos(fi)*vy+v;
        bitmap = al_load_bitmap("data/bullet.png");
        /*maska pocisku*/
        vertex[0][0]=x+6*sin(fi)-3*cos(fi);
        vertex[0][1]=y-7*cos(fi)-3*sin(fi);
        vertex[1][0]=x+6*sin(fi)+3*cos(fi);
        vertex[1][1]=y-7*cos(fi)+3*sin(fi);
        vertex[2][0]=x-8*sin(fi)+3*cos(fi);
        vertex[2][1]=y+8*cos(fi)+3*sin(fi);
        vertex[3][0]=x-8*sin(fi)-3*cos(fi);
        vertex[3][1]=y+8*cos(fi)-3*sin(fi);
        vert_cnt=4;
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

        //magazynek wedrujacy z rakieta
      //  x=_x;
      //  y=_y;
      //  fi=_fi;

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
        vertex[0][0]=x+6*sin(fi)-3*cos(fi);
        vertex[0][1]=y-7*cos(fi)-3*sin(fi);
        vertex[1][0]=x+6*sin(fi)+3*cos(fi);
        vertex[1][1]=y-7*cos(fi)+3*sin(fi);
        vertex[2][0]=x-8*sin(fi)+3*cos(fi);
        vertex[2][1]=y+8*cos(fi)+3*sin(fi);
        vertex[3][0]=x-8*sin(fi)-3*cos(fi);
        vertex[3][1]=y+8*cos(fi)-3*sin(fi);

        vert_cnt=sizeof(vertex)/sizeof(*vertex);
     }

    void displ()
    {

        al_draw_rotated_bitmap(bitmap, 2, 6, x, y, fi, 0);
        if(x>=width) x=1;
        if(x<=0) x=width-1;
        if(y>=height) y=1;
        if(y<=0) y=height-1;
    }


};

class rocket
{
public:

    int x;
    int y;
    double fi;
    double vx;
    double vy;
    double w;
    double ax;
    double ay;
    double e;
    ALLEGRO_BITMAP *bitmap;
    int vertex[3][2];
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
             vertex[0][0]= x+32*sin(fi);
             vertex[0][1]= y-30*cos(fi);
             vertex[1][0]= x-18*sin(fi)-8*cos(fi);
             vertex[1][1]= y+18*cos(fi)-8*sin(fi);
             vertex[2][0]= x-18*sin(fi)+8*cos(fi);
             vertex[2][1]= y+18*cos(fi)+8*sin(fi);

         }

    ~rocket()
    {
        //al_destroy_bitmap(rocket);
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
             vertex[0][0]= x+32*sin(fi);
             vertex[0][1]= y-30*cos(fi);
             vertex[1][0]= x-18*sin(fi)-8*cos(fi);
             vertex[1][1]= y+18*cos(fi)-8*sin(fi);
             vertex[2][0]= x-18*sin(fi)+8*cos(fi);
             vertex[2][1]= y+18*cos(fi)+8*sin(fi);



         }

    void displ()
        {
            al_draw_rotated_bitmap(bitmap, 8, 30, x, y, fi, 0);
            if(x>=width) x=1;
            if(x<=0) x=width-1;
            if(y>=height) y=1;
            if(y<=0) y=height-1;
        }
};

class asteroid
{
    public:

    int x;
    int y;
    double fi;
    double vx;
    double vy;
    double w;
    bool visible;
    ALLEGRO_BITMAP *bitmap;
    int vertex[8][2];
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
             vertex[0][0]= x+19*sin(fi)-64*cos(fi);
             vertex[0][1]= y-19*cos(fi)-64*sin(fi);
             vertex[1][0]= x+45*sin(fi)-43*cos(fi);
             vertex[1][1]= y-45*cos(fi)-43*sin(fi);
             vertex[2][0]= x+54*sin(fi);
             vertex[2][1]= y-54*cos(fi);
             vertex[3][0]= x+37*sin(fi)+56*cos(fi);
             vertex[3][1]= y-37*cos(fi)+56*sin(fi);
             vertex[4][0]= x-11*sin(fi)+67*cos(fi);
             vertex[4][1]= y+11*cos(fi)+67*sin(fi);
             vertex[5][0]= x-52*sin(fi)+23*cos(fi);
             vertex[5][1]= y+52*cos(fi)+23*sin(fi);
             vertex[6][0]= x-48*sin(fi)-38*cos(fi);
             vertex[6][1]= y+48*cos(fi)-38*sin(fi);
             vertex[7][0]= x-21*sin(fi)-64*cos(fi);
             vertex[7][1]= y+21*cos(fi)-64*sin(fi);

             vert_cnt=sizeof(vertex)/sizeof(*vertex);
         }

    ~asteroid()
    {
        //al_destroy_bitmap(rocket);
    }

    void state_update()
         {
            //zamkniêcie swiata
            if(x>=width+25) x=1;
            if(x<=-25) x=width-1;
            if(y>=height+25) y=1;
            if(y<=-25) y=height-1;

            //aktualizacja stanu
            x=x-vx; //update pozycja x
            y=y+vy; //update pozycja y
            fi=fi+w; //update kat

            /*maska asteroidy*/
             vertex[0][0]= x+19*sin(fi)-64*cos(fi);
             vertex[0][1]= y-19*cos(fi)-64*sin(fi);
             vertex[1][0]= x+45*sin(fi)-43*cos(fi);
             vertex[1][1]= y-45*cos(fi)-43*sin(fi);
             vertex[2][0]= x+54*sin(fi);
             vertex[2][1]= y-54*cos(fi);
             vertex[3][0]= x+37*sin(fi)+56*cos(fi);
             vertex[3][1]= y-37*cos(fi)+56*sin(fi);
             vertex[4][0]= x-11*sin(fi)+67*cos(fi);
             vertex[4][1]= y+11*cos(fi)+67*sin(fi);
             vertex[5][0]= x-52*sin(fi)+23*cos(fi);
             vertex[5][1]= y+52*cos(fi)+23*sin(fi);
             vertex[6][0]= x-48*sin(fi)-38*cos(fi);
             vertex[6][1]= y+48*cos(fi)-38*sin(fi);
             vertex[7][0]= x-21*sin(fi)-64*cos(fi);
             vertex[7][1]= y+21*cos(fi)-64*sin(fi);

             vert_cnt=sizeof(vertex)/sizeof(*vertex);
         }

    void displ()
        {
            al_draw_rotated_bitmap(bitmap, 67, 55, x, y, fi, 0);
            if(x>=width) x=1;
            if(x<=0) x=width-1;
            if(y>=height) y=1;
            if(y<=0) y=height-1;
          //  if(fi>=(2*3.141592) || fi<=(-2*3.141592)) fi=0;
        }
};

class asteroid_small
{
    public:

    int x;
    int y;
    double fi;
    double vx;
    double vy;
    double w;
    bool visible;
    ALLEGRO_BITMAP *bitmap;
    int vertex[8][2];
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
             vertex[0][0]= x+19*sin(fi)-64*cos(fi);
             vertex[0][1]= y-19*cos(fi)-64*sin(fi);
             vertex[1][0]= x+45*sin(fi)-43*cos(fi);
             vertex[1][1]= y-45*cos(fi)-43*sin(fi);
             vertex[2][0]= x+54*sin(fi);
             vertex[2][1]= y-54*cos(fi);
             vertex[3][0]= x+37*sin(fi)+56*cos(fi);
             vertex[3][1]= y-37*cos(fi)+56*sin(fi);
             vertex[4][0]= x-11*sin(fi)+67*cos(fi);
             vertex[4][1]= y+11*cos(fi)+67*sin(fi);
             vertex[5][0]= x-52*sin(fi)+23*cos(fi);
             vertex[5][1]= y+52*cos(fi)+23*sin(fi);
             vertex[6][0]= x-48*sin(fi)-38*cos(fi);
             vertex[6][1]= y+48*cos(fi)-38*sin(fi);
             vertex[7][0]= x-21*sin(fi)-64*cos(fi);
             vertex[7][1]= y+21*cos(fi)-64*sin(fi);

             vert_cnt=sizeof(vertex)/sizeof(*vertex);
         }

    ~asteroid_small()
    {
        //al_destroy_bitmap(rocket);
    }

    void state_update()
         {
            //zamkniêcie swiata
            if(x>=width+25) x=1;
            if(x<=-25) x=width-1;
            if(y>=height+25) y=1;
            if(y<=-25) y=height-1;

            //aktualizacja stanu
            x=x-vx; //update pozycja x
            y=y+vy; //update pozycja y
            fi=fi+w; //update kat

            /*maska asteroidy*/
             vertex[0][0]= x+3*sin(fi)-35*cos(fi);
             vertex[0][1]= y-3*cos(fi)-35*sin(fi);
             vertex[1][0]= x+35*sin(fi)-14*cos(fi);
             vertex[1][1]= y-35*cos(fi)-14*sin(fi);
             vertex[2][0]= x+35*sin(fi)+10*cos(fi);
             vertex[2][1]= y-35*cos(fi)+10*sin(fi);
             vertex[3][0]= x+15*sin(fi)+32*cos(fi);
             vertex[3][1]= y-15*cos(fi)+32*sin(fi);
             vertex[4][0]= x-2*sin(fi)+33*cos(fi);
             vertex[4][1]= y+2*cos(fi)+33*sin(fi);
             vertex[5][0]= x-23*sin(fi)+20*cos(fi);
             vertex[5][1]= y+23*cos(fi)+20*sin(fi);
             vertex[6][0]= x-36*sin(fi)-7*cos(fi);
             vertex[6][1]= y+36*cos(fi)-7*sin(fi);
             vertex[7][0]= x-25*sin(fi)-28*cos(fi);
             vertex[7][1]= y+25*cos(fi)-28*sin(fi);

             vert_cnt=sizeof(vertex)/sizeof(*vertex);
         }

    void displ()
        {
            al_draw_rotated_bitmap(bitmap, 35, 36, x, y, fi, 0);
            if(x>=width) x=1;
            if(x<=0) x=width-1;
            if(y>=height) y=1;
            if(y<=0) y=height-1;
          //  if(fi>=(2*3.141592) || fi<=(-2*3.141592)) fi=0;
        }
};


void display_update(ALLEGRO_BITMAP *tlo, rocket r1, vector<projectile> bufor_poc, vector<asteroid> buf_asteroid, vector<asteroid_small> buf_asteroid_sm)
    {

        al_clear_to_color(al_map_rgb(0,0,0));
//        al_draw_rotated_bitmap(tlo, 0, 0, 0,0, 0, 0);
        r1.displ(); //rakieta
     //   projectile pr(50, 50, 0, 0, 1);
     //   pr.displ();
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
   // for(int k=0; k<e1;k++)
   //         cout<<"overlapping_projection x: "<<sh1[k][0]<<"    y: "<<sh1[k][1]<<endl;
   // cout<<"pocz: "<<pocz<<" kon: "<<kon<<endl;
  //  cout<<"overlapping_projection sh1 pocz x: "<<sh1[pocz][0]<<" y: "<<sh1[pocz][1]<<endl;
   // cout<<"overlapping_projection sh1 kon x: "<<sh1[kon][0]<<" y: "<<sh1[kon][1]<<endl;
  //  cout<<"overlapping_projection sh2 pocz x: "<<sh2[pocz][0]<<" y: "<<sh2[pocz][1]<<endl;
  //  cout<<"overlapping_projection sh2 kon x: "<<sh2[pocz][0]<<" y: "<<sh2[pocz][1]<<endl<<endl;


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
  //  cout<<"x1: "<<a[0]<<" y1: "<<a[1]<<" x2: "<<b[0]<<" y2: "<<b[1]<<endl;
  //  cout<<"overlapping_projection "<<sh1[pocz][0]<<space<<sh1[pocz][1]<<tab<<sh1[kon][0]<<space<<sh1[kon][1]<<endl;


    //opisanie osi za pomoca wektora osadzonego w pkt(0,0)
    a[0]=a[0]-b[0];
    a[1]=a[1]-b[1];
   // cout<<"kierunek rzutowania x: "<<a[0]<<" y: "<<a[1]<<endl;
   // al_rest(1);

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

  //  cout<<rzut_sh1[0]<<space<<rzut_sh1[1]<<tab<<rzut_sh2[0]<<space<<rzut_sh2[1]<<endl;
   // al_rest(1);

    /*czy rzuty nachodza na siebie?*/
    if (rzut_sh2[1]<rzut_sh1[0] || rzut_sh2[0]>rzut_sh1[1])
    {
        return false;
    }
    else return true;
}

bool overlapping_edges (int sh1[][2], int sh2[][2], int e1, int e2)
{
  //  cout<<"overlapping_edges "<<sh1[0][0]<<" "<<sh1[0][1]<<endl;
  //  cout<<"overlapping_edges "<<sh1[0][0]<<" "<<sh1[0][1]<<endl;
    /*bada czy następuje kolizja dwóch kształtów okreslonych tablicą wierzchołków*/

    /*jesli istnieje os dla ktorej rzuty nie nachodza na siebie wowczas nie ma kolizji!*/
    /*normalne do krawędzi sh1*/

  //   for(int k=0; k<e1;k++)
    //            cout<<"overlapping_edges x: "<<sh1[k][0]<<"    y: "<<sh1[k][1]<<endl;

    for (int i=1; i<e1; i++)
    {
      //  cout<<e1<<endl;
        if (overlapping_projection(sh1,sh2,e1,e2,i-1,i)==false)
        {
         //   cout<<"nie nachodza\n";
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
  //  cout<<"collision "<<roc.vertex[0][0]<<" "<<roc.vertex[0][1]<<endl;
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
          //  cout<<"wym "<<roc.vertex[1][0]<<" "<<roc.vertex[1][1]<<endl;
         //   for(int k=0; k<e_asteroid;k++)
             //   cout<<"x: "<<buf_asteroid[i].vertex[k][0]<<"    y: "<<buf_asteroid[i].vertex[k][1]<<endl;
           // for(int k=0; k<e_rocket;k++)
           //     cout<<"x: "<<roc.vertex[k][0]<<"    y: "<<roc.vertex[k][1]<<endl;
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
                        buf_asteroid_sm[i].visible=true;
                        buf_asteroid_sm[i].x=buf_asteroid[i].x;
                        buf_asteroid_sm[i].y=buf_asteroid[i].y;
                        buf_asteroid_sm[i+1].visible=true;
                        buf_asteroid_sm[i+1].x=buf_asteroid[i].x;
                        buf_asteroid_sm[i+1].y=buf_asteroid[i].y;
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
          //  cout<<"wym "<<roc.vertex[1][0]<<" "<<roc.vertex[1][1]<<endl;
         //   for(int k=0; k<e_asteroid;k++)
             //   cout<<"x: "<<buf_asteroid_sm[i].vertex[k][0]<<"    y: "<<buf_asteroid_sm[i].vertex[k][1]<<endl;
           // for(int k=0; k<e_rocket;k++)
           //     cout<<"x: "<<roc.vertex[k][0]<<"    y: "<<roc.vertex[k][1]<<endl;
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


    if (!al_init() || !al_install_mouse() || !al_install_keyboard()) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }

    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    event_queue = al_create_event_queue();
    timer = al_create_timer(0.001); //timer 1 ms
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    display = al_create_display(width, height);
    al_clear_to_color(al_map_rgb(0,0,0));

    /*deklaracja obiektów gry*/
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
 //   buf_asteroid_sm[0].visible=true;




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
    bool poc=false;

    ALLEGRO_EVENT ev;
    bool game_running=true;

    //kolizje
    bool asteroid_proj = false;
    bool asteroid_rocket = false;
    bool asteroid_sm_proj = false;
    bool asteroid_sm_rocket = false;

    while(game_running)
   // for (int q=0; q<10; q++)
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
            {
               // if(bufor_poc[i].visible==true)
                bufor_poc[i].state_update(r1.x, r1.y, r1.fi, r1.vx, r1.vy);
            }

            collision(bufor_poc, buf_asteroid, buf_asteroid_sm, r1, asteroid_proj, asteroid_rocket, asteroid_sm_proj,
                      asteroid_sm_rocket);
            if (asteroid_rocket==true) cout<<"kolizja";
            if (asteroid_sm_rocket==true) cout<<"kolizja_sm";

            if (asteroid_proj==true)
            {
                buf_asteroid_sm[0].visible=true;
                buf_asteroid_sm[1].visible=true;
            }
          //  if (asteroid_sm_proj==true) cout<<"kolizja_sm";

          //  buf_asteroid_sm[0].visible=true;

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

