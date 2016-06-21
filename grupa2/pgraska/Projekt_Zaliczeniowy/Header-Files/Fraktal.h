#pragma once

#include <math.h>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <complex>

#include "Przycisk.h"
#include "Okno.h"

class Fraktal : public Okno
{
protected:
	double startMinR, startMaxR, startMinI, startMaxI;
	double minR, maxR, minI, maxI;
	double sR, sI;
	int liczbaIteracji;
	ALLEGRO_FONT* font8;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_COLOR kolorCzcionki;

public:
	bool czyBylZaladowany;

	Fraktal(int sx, int sy, ALLEGRO_FONT* font8);
	~Fraktal();

	virtual int Click(int x, int y) = 0;
	virtual void Generate() = 0;
	virtual int Obliczaj(double x, double y, int maxIteracje) = 0;

	void Powieksz(int lx, int rx, int gy, int dy);
	void Resetuj();
	void Draw(ALLEGRO_USTR* str);
	void SetLiczbaIteracji(int iteracje);

	ALLEGRO_BITMAP* CreateBitmap(int w, int h);
};
