#include "board.h"

Board::Board(int w, int h) {
    width = w;
    height = h;

    // inicjalizacja bird
    bird = new Bird();
    bird -> y = height / 2;

    // inicjalizacja obstacles
    for(int i=0; i<4; i++) {
        obstacles[i] = new Obstacle();
        obstacles[i] -> x = (i+1) * width/4;
        obstacles[i] -> screenHeight = height;
        obstacles[i] -> randomize_up_down();
    }
}

void Board::increase_bird_v() {
    bird -> velocity -= BIRD_INCREASE_V;
}

int Board::move_objects() {
    // czy dodac punkt?
    int point = 0;
    // grawitacja i polozenie ptaka
    bird -> velocity += GRAVITY;
    bird -> y += bird -> velocity;
    // polozenie przeszkod
    for(int i=0; i<4; i++) {
        if(obstacles[i] -> x <= 0) {
            obstacles[i] -> x = width;
            point = 1;
        } else {
            obstacles[i] -> x-= OBSTACLE_SPEED;
        }
    }
    return point;
}

bool Board::check_collision() {
    // do gory
    if((bird -> y) <= 0) {
        return true;
    }
    // do dolu
    if((bird -> y) >= height) {
        return true;
    }
    // z przeszkodami
    for(int i=0; i<4; i++) {
        if(((obstacles[i] -> x) >= 7) && ((obstacles[i] -> x) <= 13) ) {
            if((bird -> y) >= (obstacles[i] -> down) || (bird -> y) <= (obstacles[i] -> up) ) {
                return true;
            }
        }
    }
    return false;
}
