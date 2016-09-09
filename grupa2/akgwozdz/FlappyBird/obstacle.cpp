#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "obstacle.h"

using namespace std;

void Obstacle::randomize_up_down() {
    // wielkosc otworu w przeszkodzie (150 - 250)
    int holeSize = rand() % 150 + 100;
    // gorny brzeg otworu
    up = rand() % (screenHeight - holeSize);
    // dolny brzeg otworu
    down = up + holeSize;
}
