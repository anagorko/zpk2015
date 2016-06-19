#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <sstream>

using namespace std;

enum ruchtool {gora, dol, prawo, lewo};

class glowna
{
    bool przegrana, wygrana, done;
    int t[4][4],u[4][4],spr=1,wynik=0,stop=0;
    ALLEGRO_FONT *font = al_load_ttf_font("FreeMono.ttf",35,0);
    ALLEGRO_FONT *font1 = al_load_ttf_font("FreeMono.ttf",65,0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("FreeMono.ttf",14,0);

    public:

    glowna(): przegrana(false), wygrana(false), done(false){}

    void start();

    private:

    void pierwsze_losowanie();

    void rys();

    void losowanie();

    void game_over();

    void przepisanie_u();

    void strzalki();

    void ruch(ruchtool );

    ALLEGRO_COLOR wybor_kol(int );

    ALLEGRO_COLOR wybor_kol_czcionka(int );

    string to_string(int );
};

    void glowna :: start()
    {
        pierwsze_losowanie();
        rys();
        int m=0,mm=1;
        while(przegrana==FALSE)
        {
            while(mm==1)
            {
                strzalki();
                if(wygrana==TRUE)
                    wygrana=FALSE;

                if(stop==0)
                {
                    for(int i=0;i<4;i++)
                        for(int j=0;j<4;j++)
                        {
                            if(t[i][j]==2048)
                            {
                                wygrana=TRUE;
                                stop=1;
                            }
                        }
                }

                if(done==TRUE)
                    break;

                rys();
                for(int i=0;i<4;i++)
                    for(int j=0;j<4;j++)
                    {
                        if(u[i][j]!=t[i][j])
                            mm=0;
                    }
            }

            if(done==TRUE)
                break;

            mm=1;

            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    if(t[i][j]==0)
                    {
                        losowanie();
                        rys();
                        i=4;
                        j=4;
                    }
                }

            game_over();
            if(spr==0)
            {
                przegrana=TRUE;
                rys();
                al_rest(3.0f);
            }

            przepisanie_u();
       }
    }

    void glowna :: pierwsze_losowanie()
    {
        for( int i = 0; i < 4; i++ )
            for( int j = 0; j < 4; j++ )
                t[i][j]=0;

        int a,b,r,s,rr,ss;
        a=2;
        b=rand()%4;
        if(b<=2)
            b=2;
        else
            b=4;
        r=rand()%4;
        s=rand()%4;
        t[r][s]=a;
        do
        {
            rr=rand()%4;
            ss=rand()%4;
            t[rr][ss]=b;
        }while(r==rr&s==ss);

        for( int i = 0; i < 4; i++ )
            for( int j = 0; j < 4; j++ )
                u[i][j]=t[i][j];
    }

    void glowna :: rys()
    {
        al_clear_to_color(al_map_rgb(140,140,140));

        al_draw_filled_rectangle(10,10 ,100, 100,wybor_kol(t[0][0]));
        al_draw_text(font, wybor_kol_czcionka(t[0][0]), 55, 25,ALLEGRO_ALIGN_CENTRE, to_string(t[0][0]).c_str());

        al_draw_filled_rectangle(110,10 ,200, 100,wybor_kol(t[1][0]));
        al_draw_text(font, wybor_kol_czcionka(t[1][0]), 155, 25,ALLEGRO_ALIGN_CENTRE, to_string(t[1][0]).c_str());

        al_draw_filled_rectangle(210,10 ,300, 100,wybor_kol(t[2][0]));
        al_draw_text(font, wybor_kol_czcionka(t[2][0]), 255, 25,ALLEGRO_ALIGN_CENTRE, to_string(t[2][0]).c_str());

        al_draw_filled_rectangle(310,10 ,400, 100,wybor_kol(t[3][0]));
        al_draw_text(font, wybor_kol_czcionka(t[3][0]), 355, 25,ALLEGRO_ALIGN_CENTRE, to_string(t[3][0]).c_str());


        al_draw_filled_rectangle(10,110 ,100, 200,wybor_kol(t[0][1]));
        al_draw_text(font, wybor_kol_czcionka(t[0][1]), 55, 125,ALLEGRO_ALIGN_CENTRE, to_string(t[0][1]).c_str());

        al_draw_filled_rectangle(110,110 ,200, 200,wybor_kol(t[1][1]));
        al_draw_text(font, wybor_kol_czcionka(t[1][1]), 155, 125,ALLEGRO_ALIGN_CENTRE, to_string(t[1][1]).c_str());

        al_draw_filled_rectangle(210,110 ,300, 200,wybor_kol(t[2][1]));
        al_draw_text(font, wybor_kol_czcionka(t[2][1]), 255, 125,ALLEGRO_ALIGN_CENTRE, to_string(t[2][1]).c_str());

        al_draw_filled_rectangle(310,110 ,400, 200,wybor_kol(t[3][1]));
        al_draw_text(font, wybor_kol_czcionka(t[3][1]), 355, 125,ALLEGRO_ALIGN_CENTRE, to_string(t[3][1]).c_str());


        al_draw_filled_rectangle(10,210 ,100, 300,wybor_kol(t[0][2]));
        al_draw_text(font, wybor_kol_czcionka(t[0][2]), 55, 225,ALLEGRO_ALIGN_CENTRE, to_string(t[0][2]).c_str());

        al_draw_filled_rectangle(110,210 ,200, 300,wybor_kol(t[1][2]));
        al_draw_text(font, wybor_kol_czcionka(t[1][2]), 155, 225,ALLEGRO_ALIGN_CENTRE, to_string(t[1][2]).c_str());

        al_draw_filled_rectangle(210,210 ,300, 300,wybor_kol(t[2][2]));
        al_draw_text(font, wybor_kol_czcionka(t[2][2]), 255, 225,ALLEGRO_ALIGN_CENTRE, to_string(t[2][2]).c_str());

        al_draw_filled_rectangle(310,210 ,400, 300,wybor_kol(t[3][2]));
        al_draw_text(font, wybor_kol_czcionka(t[3][2]), 355, 225,ALLEGRO_ALIGN_CENTRE, to_string(t[3][2]).c_str());


        al_draw_filled_rectangle(10,310 ,100, 400,wybor_kol(t[0][3]));
        al_draw_text(font, wybor_kol_czcionka(t[0][3]), 55, 325,ALLEGRO_ALIGN_CENTRE, to_string(t[0][3]).c_str());

        al_draw_filled_rectangle(110,310 ,200, 400,wybor_kol(t[1][3]));
        al_draw_text(font, wybor_kol_czcionka(t[1][3]), 155, 325,ALLEGRO_ALIGN_CENTRE, to_string(t[1][3]).c_str());

        al_draw_filled_rectangle(210,310 ,300, 400,wybor_kol(t[2][3]));
        al_draw_text(font, wybor_kol_czcionka(t[2][3]), 255, 325,ALLEGRO_ALIGN_CENTRE, to_string(t[2][3]).c_str());

        al_draw_filled_rectangle(310,310 ,400, 400,wybor_kol(t[3][3]));
        al_draw_text(font, wybor_kol_czcionka(t[3][3]), 355, 325,ALLEGRO_ALIGN_CENTRE, to_string(t[3][3]).c_str());


        al_draw_filled_rectangle(10,410 ,245, 500,al_map_rgb(238,228,218));
        al_draw_filled_rectangle(255,410 ,400, 500,al_map_rgb(238,228,218));

        al_draw_text(font, al_map_rgb(0,0,0), 325, 405,ALLEGRO_ALIGN_CENTRE, "SCORE");
        al_draw_text(font, al_map_rgb(0,0,0), 325, 440,ALLEGRO_ALIGN_CENTRE, to_string(wynik).c_str());

        if(przegrana==TRUE)
        {
            al_draw_text(font1, al_map_rgb(0,0,0), 200, 155,ALLEGRO_ALIGN_CENTRE, "GAME OVER");
        }

        if(wygrana==TRUE)
        {
            al_draw_text(font1, al_map_rgb(0,0,0), 200, 155,ALLEGRO_ALIGN_CENTRE, "YOU WIN!");
        }

        al_draw_text(font2, al_map_rgb(0,0,0), 15, 405,ALLEGRO_ALIGN_LEFT, "Use your arrow keys to move");
        al_draw_text(font2, al_map_rgb(0,0,0), 15, 420,ALLEGRO_ALIGN_LEFT, "the tiles. When two tiles");
        al_draw_text(font2, al_map_rgb(0,0,0), 15, 435,ALLEGRO_ALIGN_LEFT, "with the same number touch,");
        al_draw_text(font2, al_map_rgb(0,0,0), 15, 450,ALLEGRO_ALIGN_LEFT, "they merge into one!");
        al_draw_text(font2, al_map_rgb(0,0,0), 15, 465,ALLEGRO_ALIGN_LEFT, "Get to the 2048 tile.");
        al_draw_text(font2, al_map_rgb(0,0,0), 15, 480,ALLEGRO_ALIGN_LEFT, "Press Esc to exit.");

        al_flip_display();
    }

    void glowna :: losowanie()
    {
        int i,j,a;
        i=rand()%4;
        j=rand()%4;
        while(t[i][j]!=0)
        {
            i=rand()%4;
            j=rand()%4;
        }
        a=rand()%4;
        if(a<=2)
            a=2;
        else
            a=4;
        t[i][j]=a;
    }

    void glowna :: game_over()
    {
        spr=0;
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            {
                if(t[i][j]==0)
                {
                spr=1;
                break;
                }
            }

        if(spr==0)
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    if(i+1<4 & j+1<4)
                    {
                        if(t[i][j]==t[i+1][j])
                        {
                            spr=1;
                            break;
                        }
                        else if(t[i][j]==t[i][j+1])
                        {
                            spr=1;
                            break;
                        }
                    }
                    else if(j==3 & i+1<4)
                    {
                        if(t[i][j]==t[i+1][j])
                        {
                            spr=1;
                            break;
                        }
                    }
                    else if(i==3 & j+1<4)
                    {
                        if(t[i][j]==t[i][j+1])
                        {
                            spr=1;
                            break;
                        }
                    }
                }
    }

    void glowna :: przepisanie_u()
    {
        for( int i = 0; i < 4; i++ )
            for( int j = 0; j < 4; j++ )
                u[i][j]=t[i][j];
    }

    void glowna :: strzalki()
    {
        ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
        al_register_event_source(event_queue, al_get_keyboard_event_source());

        bool nie_bylo_strzalki = true;

        while (nie_bylo_strzalki)
        {
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP: ruch(gora); nie_bylo_strzalki = false; break;
                    case ALLEGRO_KEY_LEFT: ruch(lewo); nie_bylo_strzalki = false; break;
                    case ALLEGRO_KEY_DOWN: ruch (dol); nie_bylo_strzalki = false; break;
                    case ALLEGRO_KEY_RIGHT: ruch (prawo);  nie_bylo_strzalki = false; break;
                    case ALLEGRO_KEY_ESCAPE: done = TRUE; nie_bylo_strzalki = false;
                }
            }
        }
    }

    void glowna :: ruch(ruchtool v)
    {
        switch(v)
        {
        case gora:

        //PRZESUNIĘCIE W GÓRĘ WSZYSTKICH ELEMENTÓW !=0
        for(int i=0;i<4;i++)
            for(int j=3;j>0;j--)
            {
                if(t[i][j-1]==0)
                {
                    for(int k=j;k<4;k++)
                    {
                        t[i][k-1]=t[i][k];
                        t[i][k]=0;
                    }
                }
            }
        //SUMOWANIE
        for(int i=0;i<4;i++)
            for(int j=0;j<3;j++)
            {
                if(t[i][j]==t[i][j+1])
                {
                    t[i][j]=t[i][j]+t[i][j+1];
                    wynik=wynik+t[i][j];
                    t[i][j+1]=0;
                }
            }
        //PRZESUNIĘCIE W GÓRĘ RAZ JESZCZE
        for(int i=0;i<4;i++)
            for(int j=3;j>0;j--)
            {
                if(t[i][j-1]==0)
                {
                    for(int k=j;k<4;k++)
                    {
                        t[i][k-1]=t[i][k];
                        t[i][k]=0;
                    }
                }
            }
        break;

        case dol:

        //PRZESUNIĘCIE W DÓŁ WSZYSTKICH ELEMENTÓW !=0
        for(int i=0;i<4;i++)
            for(int j=0;j<3;j++)
            {
                if(t[i][j+1]==0)
                {
                    for(int k=j;k>=0;k--)
                    {
                        t[i][k+1]=t[i][k];
                        t[i][k]=0;
                    }
                }
            }
        //SUMOWANIE
        for(int i=0;i<4;i++)
            for(int j=3;j>0;j--)
            {
                if(t[i][j]==t[i][j-1])
                {
                    t[i][j]=t[i][j]+t[i][j-1];
                    wynik=wynik+t[i][j];
                    t[i][j-1]=0;
                }
            }
        //PRZESUNIĘCIE W DÓŁ RAZ JESZCZE
        for(int i=0;i<4;i++)
            for(int j=0;j<3;j++)
            {
                if(t[i][j+1]==0)
                {
                    for(int k=j;k>=0;k--)
                    {
                        t[i][k+1]=t[i][k];
                        t[i][k]=0;
                    }
                }
            }
        break;

        case prawo:

        //PRZESUNIĘCIE W PRAWO WSZYSTKICH ELEMENTÓW !=0
        for(int j=0;j<4;j++)
            for(int i=0;i<3;i++)
            {
                if(t[i+1][j]==0)
                {
                    for(int k=i;k>=0;k--)
                    {
                        t[k+1][j]=t[k][j];
                        t[k][j]=0;
                    }
                }
            }
        //SUMOWANIE
        for(int j=0;j<4;j++)
            for(int i=3;i>0;i--)
            {
                if(t[i][j]==t[i-1][j])
                {
                    t[i][j]=t[i][j]+t[i-1][j];
                    wynik=wynik+t[i][j];
                    t[i-1][j]=0;
                }
            }
        //PRZESUNIĘCIE W PRAWO RAZ JESZCZE
        for(int j=0;j<4;j++)
            for(int i=0;i<3;i++)
            {
                if(t[i+1][j]==0)
                {
                    for(int k=i;k>=0;k--)
                    {
                        t[k+1][j]=t[k][j];
                        t[k][j]=0;
                    }
                }
            }
        break;

        case lewo:

        //PRZESUNIĘCIE W LEWO WSZYSTKICH ELEMENTÓW !=0
        for(int j=0;j<4;j++)
            for(int i=3;i>0;i--)
            {
                if(t[i-1][j]==0)
                {
                    for(int k=i;k<4;k++)
                    {
                        t[k-1][j]=t[k][j];
                        t[k][j]=0;
                    }
                }
            }
        //SUMOWANIE
        for(int j=0;j<4;j++)
            for(int i=0;i<4;i++)
            {
                if(t[i][j]==t[i+1][j])
                {
                    t[i][j]=t[i][j]+t[i+1][j];
                    wynik=wynik+t[i][j];
                    t[i+1][j]=0;
                }
            }
        //PRZESUNIĘCIE W LEWO RAZ JESZCZE
        for(int j=0;j<4;j++)
            for(int i=3;i>0;i--)
            {
                if(t[i-1][j]==0)
                {
                    for(int k=i;k<4;k++)
                    {
                        t[k-1][j]=t[k][j];
                        t[k][j]=0;
                    }
                }
            }
            };
    }

    ALLEGRO_COLOR glowna :: wybor_kol(int tab)
    {

        ALLEGRO_COLOR kolor;
        if(tab==0) kolor = al_map_rgb(238,228,218);
        else if(tab==2) kolor = al_map_rgb(216,212,208);
        else if(tab==4) kolor = al_map_rgb(237,224,200);
        else if(tab==8) kolor = al_map_rgb(242,177,121);
        else if(tab==16) kolor = al_map_rgb(245,149,99);
        else if(tab==32) kolor = al_map_rgb(246,124,95);
        else if(tab==64) kolor = al_map_rgb(246,94,59);
        else if(tab==128) kolor = al_map_rgb(237,207,114);
        else if(tab==256) kolor = al_map_rgb(237,204,97);
        else if(tab==512) kolor = al_map_rgb(237,200,80);
        else if(tab==1024) kolor = al_map_rgb(237,197,63);
        else if(tab==2048) kolor = al_map_rgb(237,194,46);
        else kolor = al_map_rgb(60,58,50);
        return kolor;
    }

    ALLEGRO_COLOR glowna :: wybor_kol_czcionka(int tab)
    {
        ALLEGRO_COLOR kolor_czcionki;

        if(tab==2||tab==4) kolor_czcionki = al_map_rgb(0,0,0);
        else if (tab==0) kolor_czcionki = al_map_rgb(238,228,218);
        else kolor_czcionki = al_map_rgb(255,255,255);
        return kolor_czcionki;
    }

    string glowna :: to_string(int t)
    {
        stringstream ss;
        ss << t;
        return ss.str();
    }



int main(int argc, char **argv)
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    ALLEGRO_KEYBOARD_STATE klawiatura;
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *okno = al_create_display(410,510);
    al_init_font_addon();
    al_init_ttf_addon();

    glowna gra;
    gra.start();
    al_rest(0.5f);

    al_destroy_display(okno);
}
