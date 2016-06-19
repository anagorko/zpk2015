#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include <cmath>
#include <vector>
#include <cstdlib>
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


#endif // CLASSES_H_INCLUDED
