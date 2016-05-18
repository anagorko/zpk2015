#include<algorithm>
#include<iomanip>
#include<iostream>
#include<random>
#include<vector>
using namespace std;

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

const int szerokosc = { 1280 };
const int wysokosc = { 720 };

const double dx = { 1.25 };
const double dy = { 0.5 };
const int skalujX = { 800 };
const int skalujY = { 800 };

void generujSmoka(double, double, vector <float> &, vector <float> &, int n = 5000);
void obliczSrodekMasySmoka(const vector <float> &, const vector <float> &, const double, const double, const int, const int);
void obliczRozmiarySmoka(vector <float>, vector <float>, const double, const double, const int, const int);

int main() {
	vector <float> smok_x, smok_y;
	generujSmoka(1, 1, smok_x, smok_y);

	cout << setprecision(1) << fixed;

	obliczSrodekMasySmoka(smok_x, smok_y, dx, dy, skalujX, skalujY);
	obliczRozmiarySmoka(smok_x, smok_y, dx, dy, skalujX, skalujY);

	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	 
	ALLEGRO_DISPLAY * okno = al_create_display(szerokosc, wysokosc);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	// zgodnie z trescia zadania pomijam pierwsze 100 obserwacji
	for (int i = 100; i < smok_x.size(); ++i)
		al_draw_pixel((smok_x.at(i) + dx) * skalujX, (smok_y.at(i) + dy) * skalujY, al_map_rgb(255, 255, 255));

	al_flip_display();
	al_save_bitmap("iteracje.bmp", al_get_backbuffer(okno));
	al_rest(7);
	al_destroy_display(okno);
}

void generujSmoka(double x, double y, vector <float> & xv, vector <float> & yv, int n) {
	// na podstawie: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3551.pdf
	random_device rd{};
	mt19937 mt(rd());
	uniform_int_distribution <int> du(0, 1);

	for (int i = 0; i < n; ++i) {
		if (0 == du(mt)) {
			x = -0.4 * x - 1;
			y = -0.4 * y + 0.1;
		}
		else {
			x = 0.76 * x - 0.4 * y;
			y = 0.4 * x + 0.76 * y;
		}
		xv.push_back(x);
		yv.push_back(y);
	}
}

void obliczSrodekMasySmoka(const vector <float> & xv, const vector <float> & yv, const double dx, const double dy, const int skalujX, const int skalujY) {
	int sumaX = { 0 }, sumaY = { 0 }, n = { int(xv.size()) };

	// zgodnie z trescia zadania pomijam pierwsze 100 obserwacji
	for (int i = 100; i < n; ++i) {
		sumaX += ((xv.at(i) + dx) * skalujX);
		sumaY += ((yv.at(i) + dy) * skalujY);
	}

	cout << "Srodek masy smoka (po przeskalowaniu) to: " << endl;
	cout << "(x_avg, y_avg) = (" << double( sumaX / (n - 100) ) << ", " << double( sumaY / (n - 100) ) << ")." << endl;
}

void obliczRozmiarySmoka(vector <float> xv, vector <float> yv, const double dx, const double dy, const int skalujX, const int skalujY) {
	// zgodnie z trescia zadania pomijam pierwsze 100 obserwacji
	sort(xv.begin() + 100, xv.end());
	sort(yv.begin() + 100, yv.end());

	cout << "Wymiary smoka (po przeskalowaniu) to: " << endl;
	cout << "(x_min, x_max) = (" << (xv.at(100) + dx) * skalujX << ", " << (xv.at(xv.size() - 1) + dx) * skalujX << ")," << endl;
	cout << "(y_min, y_max) = (" << (yv.at(100) + dy) * skalujY << ", " << (yv.at(yv.size() - 1) + dy) * skalujY << ")." << endl;
}
