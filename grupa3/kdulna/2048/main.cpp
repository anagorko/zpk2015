#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

const int w = 6;
const int h = 11;

const int t_w = 60;
const int t_h = 60;

const float FPS = 60;

const int screen_w = t_w * w;
const int screen_h = t_h * h;

bool quit = false;

ALLEGRO_BITMAP* bitmapa[16];
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT_QUEUE *event_queue2 = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *font2 = NULL;
ALLEGRO_FONT *font3 = NULL;
ALLEGRO_FONT *font4 = NULL;

int init()
{
    srand(time(NULL));

    if(!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        return -1;
    }

    if (!al_init_primitives_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }

    if(!al_init_image_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'image'." << endl;
        return -1;
    }

    if(!al_install_keyboard()) {
        cerr << "Błąd podczas inicjalizacji klawiatury." << endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        cerr << "Błąd podczas inicjalizacji zegara." << endl;
        return -1;
    }

    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "Błąd podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cerr << "Błąd podczas inicjalizacji kolejki zdarzeń." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_init_font_addon();
    al_init_ttf_addon();



    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();
    al_start_timer(timer);

    return 0;
}

const string kafelki[16] =
{
    "kafelki/pusty.png",
    "kafelki/dwa.png",
    "kafelki/cztr.png",
    "kafelki/osm.png",
    "kafelki/szsn.png",
    "kafelki/trzd.png",
    "kafelki/szcz.png",
    "kafelki/stdwo.png",
    "kafelki/dwpsz.png",
    "kafelki/pcsdw.png",
    "kafelki/tsdcz.png",
    "kafelki/dwtczo.png",
    "kafelki/left.png",
    "kafelki/right.png",
    "kafelki/up.png",
    "kafelki/down.png"
};

bool set_bitmaps(){
    for (int i = 0; i < 16; i++) {
        bitmapa[i] = al_load_bitmap(kafelki[i].c_str());

        if (!bitmapa[i]) {
            cerr << "Błąd podczas wczytywania bitmapy " << kafelki[i] << "." << endl;
            return false;
        }
    }

    return true;
}

class Player
{
    string Name;
    int Score, rank;

public:
    Player(){
    }
    ~Player(){
    }

    string getName() const{
        return Name;
    }
    int getScore() const{
        return Score;
    }
    int getrank() const{
        return rank;
    }
    void setName(string N){
        Name = N;
    }
    void setScore(int S){
        Score = S;
    }
    void setrank(int r){
        rank = r;
    }

    friend ostream& operator<<(ostream& os, Player& p);
    friend istream& operator>>(istream& is, Player& p);
};

ostream& operator<<(ostream& os, Player& p){
    return os << p.rank << " " << p.Name << "   " <<  p.Score<< endl;
}

istream& operator>>(istream& is, Player& p){
    is >> p.rank;
    is >> p.Name;
    is >> p.Score;
    return is;
}

class Leaderboard
{
    vector<Player> lb;

public:
    Leaderboard(){
    }
    ~Leaderboard(){
    }

    void read(){
        ifstream board;
        board.open("mainboard");

        string player;

        while(getline(board, player)){
            Player p;
            istringstream iss(player);
            iss >> p;
            lb.push_back(p);
        }
        board.close();
    }
    void write(string boardname){
        ofstream board;
        board.open(boardname, ios::trunc);

        for (Player& p: lb) {
            board << p;
        }
        board.close();
    }
    vector<Player> getPlayers(){
        return lb;
    }
    void setPlayer(Player& p){
        lb.push_back(p);
    }
    void add(string name, int score){
        sort(lb.begin(), lb.end(), [] (const Player& lhs, const Player& rhs) { return lhs.getScore() > rhs.getScore(); });

        int r = 1;

        for (Player& p: lb){
            if (p.getScore() >= score){
                r++;
            }
        }
        if (r <= 20){
            for (Player& p: lb){
                if (p.getrank() >= r){
                    p.setrank(p.getrank() + 1);
                }
                if (p.getrank() > 20){
                    lb.erase(lb.begin() + p.getrank() - 1);
                }
            }

            Player p;
            p.setName(name);
            p.setScore(score);
            p.setrank(r);

            setPlayer(p);
            sort(lb.begin(), lb.end(), [] (const Player& lhs, const Player& rhs) { return lhs.getScore() > rhs.getScore(); });
            write("mainboard");
        }
    }
};

class Game{

    int grid[4][4];


    public:
    Game(){
    }
    ~Game(){
    }

    int score = 0;
    int win = 0; //1 jesli wygrana, -1 jesli przegrana
    string name = "";

    void set_grid(int j, int i, int n){
        grid[j][i] = n;
    }

    int get_tile(int j, int i){
        return grid[j][i];
    }

    void init_grid(){
        for (int j = 0; j < 4; j++){
            for (int i = 0; i < 4; i++){
                grid[j][i] = 0;
            }
        }
        for (int t = 0; t < 2; t++){
            while(true){
                int i = rand() % 4;
                int j = rand() % 4;
                int k = rand() % 10;
                if (k < 2 && grid[j][i] == 0){
                    set_grid(j, i, 4);
                    break;
                }else if (grid[j][i] == 0){
                    set_grid(j, i, 2);
                    break;
                }
            }
        }
    }

    void move_up(){
        for (int i = 0; i < 4; i++){
            int j = 0;
            int l = 1;
            while (j < 4){
                if (j > 0 && grid[j - 1][i] == 0){
                    for (int k = j - 1; k < 3; k++){
                        set_grid(k, i, grid[k + 1][i]);
                    }
                    set_grid(3, i, 0);
                    l++;
                    if (l > 4){
                        j++;
                    }
                }else if (grid[j][i] == 0){
                    for (int k = j; k < 3; k++){
                    set_grid(k, i, grid[k + 1][i]);
                    }
                    set_grid(3, i, 0);
                    l++;
                    if (l > 4){
                        j++;
                    }
                }else if (j > 0 && grid[j - 1][i] == grid[j][i]){
                    set_grid(j - 1, i, 2 * grid[j][i]);
                    score = score + grid[j - 1][i];
                    for (int k = j; k < 3; k++){
                        set_grid(k, i, grid[k + 1][i]);
                    }
                    set_grid(3, i, 0);
                    if (grid[j - 1][i] == 2048){
                        win = 1;
                    }
                    j++;
                }else{
                    j++;
                }
            }
        }
    }

    void move_down(){
        for (int i = 0; i < 4; i++){
            int j = 3;
            int l = 1;
            while (j >= 0){
                if (j < 3 && grid[j + 1][i] == 0){
                    for (int k = j + 1; k > 0; k--){
                        set_grid(k, i, grid[k - 1][i]);
                    }
                    set_grid(0, i, 0);
                    l++;
                    if (l > 4){
                        j--;
                    }
                }else if (grid[j][i] == 0){
                    for (int k = j; k > 0; k--){
                    set_grid(k, i, grid[k - 1][i]);
                    }
                    set_grid(0, i, 0);
                    l++;
                    if (l > 4){
                        j--;
                    }
                }else if (j < 3 && grid[j + 1][i] == grid[j][i]){
                    set_grid(j + 1, i, 2 * grid[j + 1][i]);
                    score = score + grid[j + 1][i];
                    if (grid[j + 1][i] == 2048){
                        win = 1;
                    }
                    for (int k = j; k > 0; k--){
                        set_grid(k, i, grid[k - 1][i]);
                    }
                    set_grid(0, i, 0);
                    j--;
                }else{
                    j--;
                }
            }
        }
    }

    void move_right(){
        for (int j = 0; j < 4; j++){
            int i = 3;
            int l = 1;
            while (i >= 0){
                if (i < 3 && grid[j][i + 1] == 0){
                    for (int k = i + 1; k > 0; k--){
                        set_grid(j, k, grid[j][k - 1]);
                    }
                    set_grid(j, 0, 0);
                    l++;
                    if (l > 4){
                        i--;
                    }
                }else if (grid[j][i] == 0){
                    for (int k = i; k > 0; k--){
                    set_grid(j, k, grid[j][k - 1]);
                    }
                    set_grid(j, 0, 0);
                    l++;
                    if (l > 4){
                        i--;
                    }
                }else if (i < 3 && grid[j][i + 1] == grid[j][i]){
                    set_grid(j, i + 1, 2 * grid[j][i + 1]);
                    score = score + grid[j][i + 1];
                    if (grid[j][i + 1] == 2048){
                        win = 1;
                    }
                    for (int k = i; k > 0; k--){
                        set_grid(j, k, grid[j][k - 1]);
                    }
                    set_grid(j, 0, 0);
                    i--;
                }else{
                    i--;
                }
            }
        }
    }

    void move_left(){
        for (int j = 0; j < 4; j++){
            int i = 0;
            int l = 1;
            while (i < 4){
                if (i > 0 && grid[j][i - 1] == 0){
                    for (int k = i - 1; k < 3; k++){
                        set_grid(j, k, grid[j][k + 1]);
                    }
                    set_grid(j, 3, 0);
                    l++;
                    if (l > 4){
                        i++;
                    }
                }else if (grid[j][i] == 0){
                    for (int k = i; k < 3; k++){
                    set_grid(j, k, grid[j][k + 1]);
                    }
                    set_grid(j, 3, 0);
                    l++;
                    if (l > 4){
                        i++;
                    }
                }else if (i > 0 && grid[j][i - 1] == grid[j][i]){
                    set_grid(j, i - 1, 2 * grid[j][i - 1]);
                    score = score + grid[j][i - 1];
                    if (grid[j][i - 1] == 2048){
                        win = 1;
                    }
                    for (int k = i; k < 3; k++){
                        set_grid(j, k, grid[j][k + 1]);
                    };
                    set_grid(j, 3, 0);
                    i++;
                }else{
                    i++;
                }
            }
        }
    }

    void add(){
        while(true){
            int i = rand() % 4;
            int j = rand() % 4;
            int k = rand() % 10;
            if (grid[j][i] == 0){
                if (k < 2){
                    set_grid(j, i, 4);
                }else{
                    set_grid(j, i, 2);
                }
                break;
            }
        }
    }

    int empties_count(){ //ilosc wolnych pol
        int e_c = 0;
        for (int j = 0; j < 4; j++){
                for (int i = 0; i < 4; i++){
                    if (grid[j][i] > 0){
                        e_c = e_c + 1;
                    }
                }
        }
        return e_c;
    };

    int any_moves(){ //0 = nie ma ruchu, 1 = jest ruch

        if (!is_move_l() && !is_move_r() && !is_move_u() && !is_move_d()){
            return 0;
        }
        return 1;
    };

    int is_move_r(){
       for (int j = 0; j < 4; j++){
            for (int i = 0; i < 3; i++){
                if (grid[j][i] == grid[j][i + 1] && grid[j][i] > 0){
                    return 1;
                }
                if (grid[j][i] > 0 && grid[j][i + 1] == 0){
                    return 1;
                }
            }
       }
       return 0;
    }

    int is_move_l(){
       for (int j = 0; j < 4; j++){
            for (int i = 1; i < 4; i++){
                if (grid[j][i] == grid[j][i - 1] && grid[j][i] > 0){
                    return 1;
                }
                if (grid[j][i] > 0 && grid[j][i - 1] == 0){
                    return 1;
                }
            }
       }
       return 0;
    }

    int is_move_d(){
       for (int i = 0; i < 4; i++){
            for (int j = 0; j < 3; j++){
                if (grid[j][i] == grid[j + 1][i] && grid[j][i] > 0){
                    return 1;
                }
                if (grid[j][i] > 0 && grid[j + 1][i] == 0){
                    return 1;
                }
            }
       }
       return 0;
    }

    int is_move_u(){
       for (int i = 0; i < 4; i++){
            for (int j = 1; j < 4; j++){
                if (grid[j][i] == grid[j - 1][i] && grid[j][i] > 0){
                    return 1;
                }
                if (grid[j][i] > 0 && grid[j - 1][i] == 0){
                    return 1;
                }
            }
       }
       return 0;
    }
};

Game game;

    void draw_board(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        int numer;

        for (int i = 1; i < 5; i++){
            for (int j = 3; j < 7; j++){
                if (game.get_tile(j - 3, i - 1) == 0){
                    numer = 0;
                }else if (game.get_tile(j - 3, i - 1) == 2){
                    numer = 1;
                }else if (game.get_tile(j - 3, i - 1) == 4){
                    numer = 2;
                }else if (game.get_tile(j - 3, i - 1) == 8){
                    numer = 3;
                }else if (game.get_tile(j - 3, i - 1) == 16){
                    numer = 4;
                }else if (game.get_tile(j - 3, i - 1) == 32){
                    numer = 5;
                }else if (game.get_tile(j - 3, i - 1) == 64){
                    numer = 6;
                }else if (game.get_tile(j - 3, i - 1) == 128){
                    numer = 7;
                }else if (game.get_tile(j - 3, i - 1) == 256){
                    numer = 8;
                }else if (game.get_tile(j - 3, i - 1) == 512){
                    numer = 9;
                }else if (game.get_tile(j - 3, i - 1) == 1024){
                    numer = 10;
                }else if (game.get_tile(j - 3, i - 1) == 2048){
                    numer = 11;
                }
                al_draw_bitmap_region(bitmapa[numer], 0, 0, t_w, t_h, i * t_w, j * t_h, 0);
            }
        }

        al_draw_bitmap_region(bitmapa[12], 0, 0, t_w / 12, 4 * t_w + t_w / 12, (11 * t_w / 12), (35 * t_h / 12), 0);
        al_draw_bitmap_region(bitmapa[13], 0, 0, t_w / 12, 4 * t_w + t_w / 12, (60 * t_w / 12), (36 * t_h / 12), 0);
        al_draw_bitmap_region(bitmapa[14], 0, 0, 4 * t_w + t_w / 12, t_w / 12, (12 * t_w / 12), (35 * t_h / 12), 0);
        al_draw_bitmap_region(bitmapa[15], 0, 0, 4 * t_w + t_w / 12, t_w / 12, (11 * t_w / 12), (84 * t_h / 12), 0);

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");

        al_draw_text(font2, al_map_rgb(0, 0, 0), screen_w / 2, screen_h / 6, ALLEGRO_ALIGN_CENTER, "score: ___________");
        al_draw_textf(font2, al_map_rgb(0, 0, 0), (screen_w * 2) / 3, screen_h / 6, ALLEGRO_ALIGN_CENTER, "%d", game.score);

        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 20) / 24, ALLEGRO_ALIGN_LEFT, "Restart game [R]");
        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 21) / 24, ALLEGRO_ALIGN_LEFT, "Menu [M]");
        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 22) / 24, ALLEGRO_ALIGN_LEFT, "Quit [Q]");
    }

    void draw_menu(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");
        al_draw_text(font, al_map_rgb(0, 0, 0), screen_w / 2, 80, ALLEGRO_ALIGN_CENTER, "MENU");

        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 9) / 24, ALLEGRO_ALIGN_CENTER, "Continue game [C]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 11) / 24, ALLEGRO_ALIGN_CENTER, "New game [N]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 13) / 24, ALLEGRO_ALIGN_CENTER, "Leaderboard [L]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 15) / 24, ALLEGRO_ALIGN_CENTER, "Quit [Q]");
    }

    void draw_menu1(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");
        al_draw_text(font, al_map_rgb(0, 0, 0), screen_w / 2, 80, ALLEGRO_ALIGN_CENTER, "MENU");

        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 9) / 24, ALLEGRO_ALIGN_CENTER, "New game [N]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 11) / 24, ALLEGRO_ALIGN_CENTER, "Leaderboard [L]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 13) / 24, ALLEGRO_ALIGN_CENTER, "Quit [Q]");
    }

    void draw_win(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");

        al_draw_text(font2, al_map_rgb(0, 0, 0), screen_w / 2, screen_h / 2 - 40, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS !!!");
        al_draw_textf(font2, al_map_rgb(0, 0, 0), screen_w / 2, screen_h / 2, ALLEGRO_ALIGN_CENTER, "Your score is %d", game.score);

        al_draw_text(font3, al_map_rgb(105, 105, 105), screen_w / 2, (screen_h * 22) / 24, ALLEGRO_ALIGN_CENTER, "Press SPACE to continue");
    }

    void draw_lose(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");

        al_draw_text(font2, al_map_rgb(0, 0, 0), screen_w / 2, screen_h / 2 - 40, ALLEGRO_ALIGN_CENTER, "SORRY, YOU LOST");
        al_draw_textf(font2, al_map_rgb(0, 0, 0), screen_w / 2, screen_h / 2, ALLEGRO_ALIGN_CENTER, "Your score is %d", game.score);

        al_draw_text(font3, al_map_rgb(105, 105, 105), screen_w / 2, (screen_h * 22) / 24, ALLEGRO_ALIGN_CENTER, "Press SPACE to continue");
    }

    void draw_name(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");

        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, screen_h / 2 - 40, ALLEGRO_ALIGN_CENTER, "Type your name and press ENTER");
        al_draw_filled_rectangle(screen_w / 10, screen_h / 2 + 5, (screen_w * 9)/ 10, screen_h / 2 + 45, al_map_rgb(255, 255, 255));
    }

    void draw_start(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");

        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 9) / 24, ALLEGRO_ALIGN_CENTER, "Start game [S]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 12) / 24, ALLEGRO_ALIGN_CENTER, "Instructions [I]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 15) / 24, ALLEGRO_ALIGN_CENTER, "Leaderboard [L]");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 18) / 24, ALLEGRO_ALIGN_CENTER, "Quit [Q]");
    }

    void draw_leaderboard(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");
        al_draw_text(font2, al_map_rgb(0, 0, 0), screen_w / 2, 80, ALLEGRO_ALIGN_CENTER, "Leaderboard");

        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 21) / 24, ALLEGRO_ALIGN_LEFT, "Menu [M]");
        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 22) / 24, ALLEGRO_ALIGN_LEFT, "Quit [Q]");

        ifstream board;
        board.open("mainboard");

        string player;
        int i = 0;

        while(getline(board, player)){
            al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 5, screen_h / 4 + 20 * (i - 1), ALLEGRO_ALIGN_LEFT, player.c_str());
            i++;
        }

        board.close();
    }

    void draw_leaderboard1(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");
        al_draw_text(font2, al_map_rgb(0, 0, 0), screen_w / 2, 80, ALLEGRO_ALIGN_CENTER, "Leaderboard");

        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 21) / 24, ALLEGRO_ALIGN_LEFT, "Back [B]");
        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 22) / 24, ALLEGRO_ALIGN_LEFT, "Quit [Q]");

        ifstream board;
        board.open("mainboard");

        string player;
        int i = 0;

        while(getline(board, player)){
            al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 5, screen_h / 4 + 20 * (i - 1), ALLEGRO_ALIGN_LEFT, player.c_str());
            i++;
        }

        board.close();
    }

    void draw_instructions(){
        al_clear_to_color(al_map_rgb(233 ,150, 123));

        al_draw_text(font, al_map_rgb(255, 255, 255), screen_w - 20, 0, ALLEGRO_ALIGN_RIGHT, "2048");
        al_draw_text(font2, al_map_rgb(0, 0, 0), screen_w / 2, 80, ALLEGRO_ALIGN_CENTER, "Instructions"); //original instructions from 2048 app

        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 6) / 24, ALLEGRO_ALIGN_CENTER, "Use arrow keys to move tiles.");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 8) / 24, ALLEGRO_ALIGN_CENTER, "When two tiles with");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 10) / 24, ALLEGRO_ALIGN_CENTER, "the same number touch,");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 12) / 24, ALLEGRO_ALIGN_CENTER, "they merge into one.");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 14) / 24, ALLEGRO_ALIGN_CENTER, "Join the numbers and get to");
        al_draw_text(font3, al_map_rgb(0, 0, 0), screen_w / 2, (screen_h * 16) / 24, ALLEGRO_ALIGN_CENTER, "the 2048 tile!");

        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 21) / 24, ALLEGRO_ALIGN_LEFT, "Back [B]");
        al_draw_text(font3, al_map_rgb(105, 105, 105), 20, (screen_h * 22) / 24, ALLEGRO_ALIGN_LEFT, "Quit [Q]");
    }

int main()
{

    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    if (!set_bitmaps()) {
        return -1;
    }

    font = al_load_ttf_font("FreeMono.ttf", 60, 0);

    if (!font){
      fprintf(stderr, "Could not load 'FreeMono.ttf'.\n");
      return -1;
    }

    font2 = al_load_ttf_font("FreeMono.ttf", 30, 0);

    if (!font2){
      fprintf(stderr, "Could not load 'FreeMono.ttf'.\n");
      return -1;
    }

    font3 = al_load_ttf_font("FreeMono.ttf", 18, 0);

    if (!font3){
      fprintf(stderr, "Could not load 'FreeMono.ttf'.\n");
      return -1;
    }

    font4 = al_load_ttf_font("FreeMono.ttf", 45, 0);

    if (!font4){
      fprintf(stderr, "Could not load 'FreeMono.ttf'.\n");
      return -1;
    }

    int state = 0;
    draw_start();
    al_flip_display();

    bool redraw = true;

    while(!quit){
    ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_UP) {

            if (ev.keyboard.keycode == ALLEGRO_KEY_Q && state != 8) {
                quit = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_L && state == 0) {
                state = 5;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_B && (state == 4 || state == 5)) {
                state = 0;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_I && state == 0) {
                state = 4;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_S && state == 0) {
                state = 8;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER && state == 8){
                state = 1;
                game.init_grid();
                redraw = true;
                break;
            }
        }

        if (ev.type == ALLEGRO_EVENT_KEY_CHAR && state == 8){
            game.name.push_back(ev.keyboard.unichar);
            redraw = true;
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            if (state == 0) {
                draw_start();
                al_flip_display();
            } else if (state == 1) {
                draw_board();
                al_flip_display();
            } else if (state == 4) {
                draw_instructions();
                al_flip_display();
            } else if (state == 5) {
                draw_leaderboard1();
                al_flip_display();
            } else if (state == 8) {
                draw_name();
                al_draw_text(font2, al_map_rgb(0, 0, 0), screen_w / 2, screen_h / 2, ALLEGRO_ALIGN_CENTER, game.name.c_str());
                al_flip_display();
            }
        }
    }

    redraw = true;
    int s = 0;

    while(!quit)
    {
        if (game.win != 0 && s == 0){
            Leaderboard leaderboard;
            leaderboard.read();
            leaderboard.add(game.name, game.score);

            if (game.win == 1){

                draw_board();
                al_draw_text(font4, al_map_rgb(255, 0, 0), screen_w / 2, screen_h / 2, ALLEGRO_ALIGN_CENTER, "YOU WON");
                al_flip_display();
                al_rest(3);

                draw_win();
                al_flip_display();

            } else if (game.win == -1){

                draw_board();
                al_draw_text(font4, al_map_rgb(255, 0, 0), screen_w / 2, screen_h / 2, ALLEGRO_ALIGN_CENTER, "NO MORE MOVES");
                al_flip_display();
                al_rest(3);

                draw_lose();
                al_flip_display();

            }

            s++;

            while(!quit){
                ALLEGRO_EVENT ev;

                al_wait_for_event(event_queue, &ev);

                if (ev.type == ALLEGRO_EVENT_KEY_UP) {

                    if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                        state = 3;
                        draw_leaderboard();
                        al_flip_display();
                    }
                    if (ev.keyboard.keycode == ALLEGRO_KEY_Q && (state == 3 || state == 6)) {
                        quit = true;
                    }
                    if (ev.keyboard.keycode == ALLEGRO_KEY_M && (state == 3 || state == 7)) {
                        state = 6;
                        draw_menu1();
                        al_flip_display();
                    }
                    if (ev.keyboard.keycode == ALLEGRO_KEY_L && state == 6) {
                        state = 7;
                        redraw = true;
                        break;
                    }
                    if (ev.keyboard.keycode == ALLEGRO_KEY_N && state == 6) {
                        state = 1;
                        game.init_grid();
                        game.win = 0;
                        game.score = 0;
                        s = 0;
                        redraw = true;
                        break;
                    }
                }
            }
        }


        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_UP) {

            if (ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                quit = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_S && state == 0) {
                game.init_grid();
                state = 1;
                s = 0;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_R && state == 1) {
                game.init_grid();
                game.score = 0;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_M && (state == 1 || state == 3)) {
                state = 2;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_M && state == 7) {
                state = 6;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_C && state == 2) {
                state = 1;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_N && (state == 2 || state == 6)) {
                state = 1;
                game.init_grid();
                game.win = 0;
                game.score = 0;
                s = 0;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_L && state == 2) {
                state = 3;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_L && state == 6) {
                state = 7;
                redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_UP && state == 1) {
                if (game.is_move_u() == 1){
                    game.move_up();
                    game.add();
                    redraw = true;
                }
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN && state == 1) {
                if (game.is_move_d() == 1){
                    game.move_down();
                    game.add();
                    redraw = true;
                }
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT && state == 1) {
                if (game.is_move_l() == 1){
                    game.move_left();
                    game.add();
                    redraw = true;
                }
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT && state == 1) {
                if (game.is_move_r() == 1){
                    game.move_right();
                    game.add();
                    redraw = true;
                }
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            if (state == 1) {
                draw_board();
                al_flip_display();
                if (game.any_moves() == 0){
                    game.win = -1;
                }
            } else if (state == 2) {
                draw_menu();
                al_flip_display();
            } else if (state == 3 || state == 7) {
                draw_leaderboard();
                al_flip_display();
            } else if (state == 6) {
                draw_menu1();
                al_flip_display();
            }
        }
    }
}
