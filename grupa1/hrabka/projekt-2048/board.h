
class Board {

private:
    int values[16];

public:
    Board();

    int get_value(int r, int c);
    void set_value(int r, int c, int v);

    int random_field();
    bool key_left(bool applyChanges = true);
    bool key_right(bool applyChanges = true);
    bool key_up(bool applyChanges = true);
    bool key_down(bool applyChanges = true);
    int count_points();
    void print();
};
