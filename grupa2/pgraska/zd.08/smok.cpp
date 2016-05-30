#include<iostream>
#include <fstream>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const int w = 800;
const int h = 600;


int main(int argc, char** argv)
{
	ALLEGRO_DISPLAY       *display = NULL;

	al_init();
	al_init_primitives_addon();

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	display = al_create_display(w, h);



	al_clear_to_color(al_map_rgb(0, 0, 0));

	fstream plik;
	plik.open("zad_4_a.txt",ios::out);

	double x = 1.0;
	double y = 1.0;

	double suma_x = 0.0;
	double suma_y = 0.0;
	plik << "Podpunkt a)\n\n";

	double min_x = 99999999;
	double max_x = -99999999;
	double min_y = 99999999;
	double max_y = -99999999;

	for (int i = 0; i < 5000; i++) {

		plik << "x = " << x << "   y = " << y <<"\n";

		if (rand()%2 == 0) {
			x = -0.4 * x - 1;
			y = -0.4 * y + 0.1;
		}
		else {
			x = 0.76 * x - 0.4 * y;
			y = 0.4 * x + 0.76 * y;
		}

		if (i >= 100) {
			if (x < min_x) {
				min_x = x;
			}
			if (x > max_x) {
				max_x = x;
			}
			if (y < min_y) {
				min_y = y;
			}
			if (y > max_y) {
				max_y = y;
			}
			suma_x += x;
			suma_y += y;
			al_draw_pixel(500 * (x + 1.2), 500 * (y + 0.5), al_map_rgb(255, 255, 255));
		}
	}

	double srednia_x = suma_x / 5000;
	double srednia_y = suma_y / 5000;

	plik << "\n\nPodpunkt c) \n\n";
	plik << "srednia x = " << srednia_x << "\n" << "srednia_y = " << srednia_y << "\n\n";

	plik << "\n\nPodpunkt d) \n\n";

	plik << "Max x = " << max_x << "   Min x = " << min_x << "\n";
	plik << "Max y = " << max_y << "   Min y = " << min_y << "\n";

	plik.close();

	al_flip_display();
	al_save_bitmap(".bmp", al_get_backbuffer(display));
	al_rest(4);
	al_destroy_display(display);

	return 0;
}
