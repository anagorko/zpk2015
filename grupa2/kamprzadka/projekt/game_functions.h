#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

int display_update(ALLEGRO_BITMAP *tlo, rocket r1, vector<projectile> bufor_poc, vector<asteroid> buf_asteroid, vector<asteroid_small> buf_asteroid_sm)
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
        return 0;
    }



int logic_update(rocket& r1, vector<asteroid_small>& buf_asteroid_sm, vector<asteroid>& buf_asteroid,
                 vector<projectile>& bufor_poc, bool& asteroid_proj, bool& asteroid_rocket, bool& asteroid_sm_proj,
                 bool& asteroid_sm_rocket, bool up, bool left, bool right)
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
    return 0;
}

void get_keys(ALLEGRO_EVENT ev, bool& up, bool& left, bool& right, int& ctr_d, int& ctr_l,
              vector<projectile>& bufor_poc, int bul_nmb)
{
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
}




#endif // GAME_FUNCTIONS_H_INCLUDED
