#include <iostream>
#include <stdlib.h>  // random
#include <time.h>

#include "board.h"

using namespace std;

Board::Board() {
    for(int i=0; i<16; i++) {
        values[i] = -1;
    }
    srand (time(NULL));
}

int Board::get_value(int r, int c) {
    return values[r * 4 + c];
}

void Board::set_value(int r, int c, int v) {
    values[r * 4 + c] = v;
}

int Board::random_field() {
    bool isFree = false;
    for (int i=0; i<16; i++) {
        if(values[i] == -1) {
            isFree = true;
            break;
        }
    }
    if(!isFree) {
        cout<<"No more free fields!"<<endl;
        return -1;
    }

    // wylosuj wolne miejsce
    int position = rand() % 16;
    while(values[position] != -1) {
        position = rand() % 16;
    }

    // ustaw wartoœæ

    // 1/3 - ustaw 4, 2/3 - ustaw 2
    int two_or_four = rand() % 3;
    if(two_or_four == 0) {
        values[position] = 4;
    } else {
        values[position] = 2;
    }

    return 0;
}

bool Board::key_left(bool applyChanges){
    bool board_changed=false;
    for(int i = 0; i < 4; i++) {
        int new_numbers[4];
        for(int ii = 0; ii < 4; ii++) {
            new_numbers[ii] = -1;
        }

        int last_value = -1;
        int x = 0; // miejsce w tablicy new_numbers
        for(int a = 0; a < 4; a++){
            if (get_value(i,a)==-1) {
                continue;
            }
            if (last_value == -1){
                last_value = get_value(i,a);
            } else {
                if(last_value == get_value(i,a)) {
                    new_numbers[x] = 2 * last_value;
                    x++;
                    last_value = -1;
                }
                else {
                    new_numbers[x] = last_value;
                    last_value = get_value(i,a);
                    x++;
                }
            }
        }

        if(last_value != -1) {
            new_numbers[x] = last_value;
        }

        for(int ii = 0; ii < 4; ii++) {
            if(get_value(i,ii) != new_numbers[ii]) {
                board_changed=true;
            }
            if(applyChanges) {
                set_value(i, ii, new_numbers[ii]);
            }
        }
    }
    return board_changed;
}

bool Board::key_right(bool applyChanges){
    bool board_changed=false;
    for(int i = 0; i < 4; i++) {
        int new_numbers[4];
        for(int ii = 0; ii < 4; ii++) {
            new_numbers[ii] = -1;
        }

        int last_value = -1;
        int x = 3; // miejsce w tablicy new_numbers
        for(int a = 3; a >=0; a--){
            if (get_value(i,a)==-1) {
                continue;
            }
            if (last_value == -1){
                last_value = get_value(i,a);
            } else {
                if(last_value == get_value(i,a)) {
                    new_numbers[x] = 2 * last_value;
                    x--;
                    last_value = -1;
                }
                else {
                    new_numbers[x] = last_value;
                    last_value = get_value(i,a);
                    x--;
                }
            }
        }

        if(last_value != -1) {
            new_numbers[x] = last_value;
        }

        for(int ii = 3; ii >= 0; ii--) {
            if(get_value(i,ii) != new_numbers[ii]) {
                board_changed=true;
            }
            if(applyChanges) {
                set_value(i, ii, new_numbers[ii]);
            }
        }
    }
    return board_changed;
}

bool Board::key_up(bool applyChanges){
    bool board_changed=false;
    for(int i = 0; i < 4; i++) {
        int new_numbers[4];
        for(int ii = 0; ii < 4; ii++) {
            new_numbers[ii] = -1;
        }

        int last_value = -1;
        int x = 0; // miejsce w tablicy new_numbers
        for(int a = 0; a < 4; a++){
            if (get_value(a,i)==-1) {
                continue;
            }
            if (last_value == -1){
                last_value = get_value(a,i);
            } else {
                if(last_value == get_value(a,i)) {
                    new_numbers[x] = 2 * last_value;
                    x++;
                    last_value = -1;
                }
                else {
                    new_numbers[x] = last_value;
                    last_value = get_value(a,i);
                    x++;
                }
            }
        }

        if(last_value != -1) {
            new_numbers[x] = last_value;
        }

        for(int ii = 0; ii < 4; ii++) {
            if(get_value(ii,i) != new_numbers[ii]) {
                board_changed=true;
            }
            if(applyChanges) {
                set_value( ii, i, new_numbers[ii]);
            }
        }
    }
    return board_changed;
}

bool Board::key_down(bool applyChanges){
    bool board_changed=false;
    for(int i = 3; i >= 0; i--) {
        int new_numbers[4];
        for(int ii = 0; ii < 4; ii++) {
            new_numbers[ii] = -1;
        }

        int last_value = -1;
        int x = 3; // miejsce w tablicy new_numbers
        for(int a = 3; a >= 0; a--){
            if (get_value(a,i)==-1) {
                continue;
            }
            if (last_value == -1){
                last_value = get_value(a,i);
            } else {
                if(last_value == get_value(a,i)) {
                    new_numbers[x] = 2 * last_value;
                    x--;
                    last_value = -1;
                }
                else {
                    new_numbers[x] = last_value;
                    last_value = get_value(a,i);
                    x--;
                }
            }
        }

        if(last_value != -1) {
            new_numbers[x] = last_value;
        }

        for(int ii = 3; ii >= 0; ii--) {
            if(get_value(ii,i) != new_numbers[ii]) {
                board_changed=true;
            }
            if(applyChanges) {
                set_value( ii, i, new_numbers[ii]);
            }
        }
    }
    return board_changed;
}


void Board::print() {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            cout<<get_value(i, j)<<" ";
        }
        cout<<endl;
    }
}

int Board::count_points(){
    int points=0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            points += get_value(i,j);
        }
    }
    return points;
}
