#include<iostream>

#include "bird.h"
#include "obstacle.h"

using namespace std;

const double BIRD_INCREASE_V = 0.8;
const double GRAVITY = 0.2;
const double OBSTACLE_SPEED = 2;

class Board {

public:
    int width;
    int height;
    Obstacle* obstacles[4];
    Bird* bird;

    Board(int w, int h);

    void increase_bird_v();
    int move_objects();
    bool check_collision();
};
