#pragma once

#include "Fraktal.h"

class Mandelbrot : public Fraktal
{
public:
	Mandelbrot(int sx, int sy, ALLEGRO_FONT* font8);
	~Mandelbrot();

	int Click(int x, int y);
	int Obliczaj(double x, double y, int maxIteracje);

	void Generate();
	void Draw(ALLEGRO_USTR* str);
};
