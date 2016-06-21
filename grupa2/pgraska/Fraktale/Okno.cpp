#include "Okno.h"

#include "Window.h"
#include "Przycisk.h"

Okno::Okno(int sx, int sy)
{
	this->screenX = sx;
	this->screenY = sy;
	screenRatio = static_cast<double>(sy) / static_cast<double>(sx);
}

Okno::~Okno()
{
}
