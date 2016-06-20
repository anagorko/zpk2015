#ifndef COLLISION_DETECTION_H_INCLUDED
#define COLLISION_DETECTION_H_INCLUDED

bool overlapping_projection(int sh1[][2], int sh2[][2], int e1, int e2, int pocz, int kon)
{
    /*bada czy rzuty na dowolny wyznaczony dwoma wierzcholkami kierunek pokrywaja sie
    rzuty odbywaj¹ sie na kierunek normalny do wyznaczonego przez punkty sh1[pocz], sz1[kon]*/
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
    /*bada czy wystêpuje kolizja dwóch kszta³tów okreslonych tablic¹ wierzcho³ków*/

    /*jesli istnieje os dla ktorej rzuty nie nachodza na siebie wowczas nie ma kolizji!*/
    /*normalne do krawêdzi sh1*/

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
    /*normalne do krawêdzi sh2*/
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

    //kolizja rakieta - asteroida ma³a
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

    //kolizja pocisk - asteroida ma³a
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

#endif // COLLISION_DETECTION_H_INCLUDED
