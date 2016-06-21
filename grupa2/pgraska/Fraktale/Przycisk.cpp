#include "Przycisk.h"

#include "Window.h"

Przycisk::Przycisk(int id, int x, int y, Actions_t action, char* file)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->action = action;

	bitmap = al_load_bitmap(file);

	if (!bitmap)
	{
		printf("Nie mozna zaladowac pliku!");
	}

	this->sizeX = al_get_bitmap_width(bitmap);
	this->sizeY = al_get_bitmap_height(bitmap);

	this->lx = x - sizeX / 2;
	this->px = x + sizeX / 2;

	this->gy = y - sizeY / 2;
	this->dy = y + sizeY / 2;
}

Przycisk::~Przycisk()
{
}

bool Przycisk::IsClicked(int x, int y)
{
	if (x > this->lx && x < this->px && y > this->gy && y < this->dy)
		return true;
	return false;
}

void Przycisk::Draw()
{
	al_draw_bitmap(bitmap, x - sizeX / 2, y - sizeY / 2, 0);
}
