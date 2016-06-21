#include "Julia.h"
#include "Window.h"


Julia::Julia(int sx, int sy, ALLEGRO_FONT* font8) : Fraktal(sx, sy, font8)
{
	startMinR = -2.5, startMaxR = 2.5;
	minR = startMinR, maxR = startMaxR;
	sR = maxR - minR;
	double t = screenRatio * sR;
	minI = -t / 2.0;
	maxI = t / 2.0;
	startMinI = minI, startMaxI = maxI;
	sI = maxI - minI;
	liczbaIteracji = 30;

	czyBylZaladowany = false;
	bitmap = CreateBitmap(sx, sy);
}


Julia::~Julia()
{
}

int Julia::Click(int x, int y)
{
	return RESPOND_CLICKED;
}

void Julia::Draw(ALLEGRO_USTR* str)
{
	Fraktal::Draw(str);
}

void Julia::Generate()
{
	double maxN = (double)liczbaIteracji;

	ALLEGRO_BITMAP* old_target = al_get_target_bitmap();

	al_set_target_bitmap(bitmap);
	for (int y = 0; y < screenY; ++y)
	{
		for (int x = 0; x < screenX; ++x)
		{
			int n = Obliczaj(x, y, maxN);
			double nn = n;

			int r = (1.0 - nn / maxN) * 256;
			int g = (1.0 - nn / maxN) * 256;
			int b = (1.0 - nn / maxN) * 256;

			al_put_pixel(x, y, al_map_rgb(r, g, b));
		}
	}

	al_set_target_bitmap(old_target);
}

int Julia::Obliczaj(double x, double y, int maxIteracje)
{
	std::complex<double> p(minR + x / (screenX - 1.0) * sR, minI + y / (screenY - 1.0) * sI);
	std::complex<double> c(-0.1, 0.65);
	std::complex<double> z = p;
	unsigned int iteracje;

	for (iteracje = 0; iteracje < maxIteracje && std::abs(z) < 2.0; ++iteracje)
		z = z*z + c;

	return iteracje;
}
