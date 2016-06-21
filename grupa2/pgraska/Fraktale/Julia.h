#pragma once

#include "Fraktal.h"

class Julia : public Fraktal
{
public:
	Julia(int sx, int sy, ALLEGRO_FONT* font8);
	~Julia();

	int Click(int x, int y);
	int Obliczaj(double x, double y, int maxIteracje);

	void Draw(ALLEGRO_USTR* str);
	void Generate();
};
