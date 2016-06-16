#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

using namespace std;

const int X = 800, Y = 600;

int main()
{
    ALLEGRO_DISPLAY *display;

	float x = 1.00f, y = 1.00f;

	al_init();
	al_init_primitives_addon();

	display = al_create_display (X, Y);

	al_clear_to_color(al_map_rgb(255,255,255));

	for(unsigned int i = 0; i < 4294967295; i++)
	{
		if(rand()%2)
        {
			x = -0.4f*x - 1.0f;
			y = -0.4f*y + 0.1f;
		}
		else
		{
			x = 0.76f*x - 0.4f*y;
			y = 0.4f*x + 0.76f*y;
		}

		al_draw_pixel ((x+1.5f) * X/2, (y + 1.0f) * Y/2, al_map_rgb(0,0,0));
        al_flip_display();
	}

	return 0;
}
