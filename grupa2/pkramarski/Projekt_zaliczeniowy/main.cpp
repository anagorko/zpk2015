#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include "fparser.hh"

using namespace std;

const float FPS = 30;
const int dbx1 = 20;
const int dby1 = 20;
const int dbx2 = 600;
const int dby2 = 450;
const int NumberOfSteps = dbx2 - dbx1;

class Button
{

    unsigned char TextR, TextG, TextB, BackR, BackG, BackB;
    int TextX1, TextY1, BackX1, BackY1, BackX2, BackY2;
    int FontSize;
    const char* Text;
    const char* Font;
    ALLEGRO_COLOR colorText;
    ALLEGRO_COLOR colorBack;

public:
    void setTextR(unsigned char tr) {TextR = tr;}
    void setTextG(unsigned char tg) {TextG = tg;}
    void setTextB(unsigned char tb) {TextB = tb;}
    void setBackR(unsigned char br) {BackR = br;}
    void setBackG(unsigned char bg) {BackG = bg;}
    void setBackB(unsigned char bb) {BackB = bb;}
    void setTextX1(int tx1) {TextX1 = tx1;}
    void setTextY1(int ty1) {TextY1 = ty1;}
    void setBackX1(int bx1) {BackX1 = bx1;}
    void setBackY1(int by1) {BackY1 = by1;}
    void setBackX2(int bx2) {BackX2 = bx2;}
    void setBackY2(int by2) {BackY2 = by2;}
    void setFontSize(int fs) {FontSize = fs;}
    void setFont(const char* font) {Font = font;}
    void setText(const char* text) {Text = text;}
    void setColorText(unsigned char tr, unsigned char tg,unsigned char tb){
        colorText = al_map_rgb(TextR, TextG, TextB);
    }
    void setColorBack(unsigned char br, unsigned char bg,unsigned char bb){
        colorBack = al_map_rgb(BackR, BackG, BackB);
    }

    unsigned char getTextR() {return TextR;}
    unsigned char getTextG() {return TextG;}
    unsigned char getTextB() {return TextB;}
    unsigned char getBackR() {return BackR;}
    unsigned char getBackG() {return BackG;}
    unsigned char getBackB() {return BackB;}
    int getTextX1() const {return TextX1;}
    int getTextY1() const {return TextY1;}
    int getBackX1() const {return BackX1;}
    int getBackY1() const {return BackY1;}
    int getBackX2() const {return BackX2;}
    int getBackY2() const {return BackY2;}
    int getFontSize() const {return FontSize;}
    const char* getText() {return Text;}
    const char* getFont() {return Font;}
    ALLEGRO_COLOR getColorText() const {return colorText;}
    ALLEGRO_COLOR getColorBack() const {return colorBack;}

    void setButton(unsigned char tr, unsigned char tg, unsigned char tb, unsigned char br, unsigned char bg, unsigned char bb, int tx1, int ty1, int bx1, int by1, int bx2, int by2, int fs, const char* font, const char* text){
        setTextR(tr);
        setTextG(tg);
        setTextB(tb);
        setBackR(br);
        setBackG(bg);
        setBackB(bb);
        setTextX1(tx1);
        setTextY1(ty1);
        setBackX1(bx1);
        setBackY1(by1);
        setBackX2(bx2);
        setBackY2(by2);
        setFontSize(fs);
        setText(text);
        setFont(font);
        setColorText(tr, tg, tb);
        setColorBack(br, bg, bb);
    }
};

class Function
{
    string Formula;
    string xmin, xmax, ymin, ymax;
    int ColorStatus;
    int LineThickness;
    int Marker;
    int Scatter;
    int ChartNumber;
    string ChartName;
    FunctionParser fparser;
    vector<double> X;
    vector<double> Y;
    vector<double> X1;
    vector<double> Y1;

public:

    Function(){
        ColorStatus = 1;
        LineThickness = 1;
        Marker = 1;
        Scatter = 0;
        ChartNumber = 1;
        ChartName = "Wykres1";
    }

    double ReturnXmin(){
        return atof(xmin.c_str());
    }

    double ReturnXmax(){
        return atof(xmax.c_str());
    }

    double ReturnYmin(){
        return atof(ymin.c_str());
    }

    double ReturnYmax(){
        return atof(ymax.c_str());
    }

    void CalculateValues(){
        int res = fparser.Parse(Formula, "x");

        double RangeX = ReturnXmax() - ReturnXmin();
        double Step = RangeX/(NumberOfSteps);
        double xmin = ReturnXmin();
        double xmax = ReturnXmax();
        double step = 1;
        double x[] = { 0 };
        double y[] = { 0 };
        double x1[] = { 0 };
        double y1[] = { 0 };

        for(x[0] = xmin; x[0] <= xmax; x[0] += Step){
            X.push_back(x[0]);
            double Value = fparser.Eval(x);
            if(fparser.EvalError() == 0){
                y[0] = Value;
                Y.push_back(y[0]);
            }
            else{
                y[0] = ReturnYmin();
                Y.push_back(y[0]);
            }
        }

        for(x1[0] = xmin; x1[0] <= xmax; x1[0] += step){
            X1.push_back(x1[0]);
            double Value = fparser.Eval(x1);
            if(fparser.EvalError() == 0){
                y1[0] = Value;
                Y1.push_back(y1[0]);
            }
            else{
                y1[0] = ReturnYmin();
                Y1.push_back(y1[0]);
            }
        }
    }

    void ClearXY(){
        X.clear();
        Y.clear();
    }

    void ClearX1Y1(){
        X1.clear();
        Y1.clear();
    }

    int LengthX1(){
        X1.size();
    }

    int LengthY1(){
        Y1.size();
    }

    double ReturnY(int i){
        return Y[i];
    }

    double ReturnX(int i){
        return X[i];
    }

    double ReturnY1(int i){
        return Y1[i];
    }

    double ReturnX1(int i){
        return X1[i];
    }

    void AddSign(char Sign){
        if(Formula.length()<40)
            Formula.push_back(Sign);
    }

    void AddXmin(char SignXmin){
        if(xmin.length()<5)
            xmin.push_back(SignXmin);
    }

    void AddXmax(char SignXmax){
        if(xmax.length()<5)
            xmax.push_back(SignXmax);
    }

    void AddYmin(char SignYmin){
        if(ymin.length()<5)
            ymin.push_back(SignYmin);
    }

    void AddYmax(char SignYmax){
        if(ymax.length()<5)
            ymax.push_back(SignYmax);
    }

    void DeleteSign(){
        if(Formula.length()>0)
            Formula.pop_back();
    }

    void DeleteXmin(){
        if(xmin.length()>0)
            xmin.pop_back();
    }

    void DeleteXmax(){
        if(xmax.length()>0)
            xmax.pop_back();
    }

    void DeleteYmin(){
        if(ymin.length()>0)
            ymin.pop_back();
    }

    void DeleteYmax(){
        if(ymax.length()>0)
            ymax.pop_back();
    }

    const char* ShowChartName(){
        ChartName.append(".png");
        ChartName.c_str();
    }

    void AddChartNumber(){
        ChartNumber++;
    }

    void AddNewChartNumber(){
        string SubChartName = ChartName.substr(0,6);
        string Number = to_string(ChartNumber);
        string chartname = SubChartName.append(Number);
        ChartName = chartname;
    }

    int Length(){
        Formula.length();
    }

    int LengthXmin(){
        xmin.length();
    }

    int LengthXMax(){
        xmax.length();
    }

    int LengthYmin(){
        ymin.length();
    }

    int LengthYmax(){
        ymax.length();
    }

    const char* Show(){
        Formula.c_str();
    }

    const char* ShowXmin(){
        xmin.c_str();
    }

    const char* ShowXmax(){
        xmax.c_str();
    }

    const char* ShowYmin(){
        ymin.c_str();
    }

    const char* ShowYmax(){
        ymax.c_str();
    }

    void ChangeColorStatus(){
        if(ColorStatus == 3)
            ColorStatus = ColorStatus/3;
        else
            ColorStatus++;
    }

    void ChangeLineThickness(){
        if(LineThickness == 3)
            LineThickness = LineThickness/3;
        else
            LineThickness++;
    }

    void ChangeMarker(){
        if(Marker == 0)
            Marker++;
        else if(Scatter == 1 && Marker == 1)
            Marker = 1;
        else
            Marker = 0;
    }

    void ChangeScatter(){
        if(Scatter == 0 && Marker != 1){
            Scatter++;
            Marker++;
        }
        else if(Scatter == 0)
            Scatter++;
        else
            Scatter = 0;
    }

    int ReturnColorStatus(){
        return ColorStatus;
    }

    int ReturnLineThickness(){
        return LineThickness;
    }

    int ReturnMarker(){
        return Marker;
    }

    int ReturnScatter(){
        return Scatter;
    }
};

class Display
{
    ALLEGRO_DISPLAY     *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER       *timer = NULL;

    int width, height;

public:
    Display(){
    }

    ~Display(){
        if (display) { al_destroy_display(display); }
    }

    bool init(int w, int h) {
        width = w;
        height = h;

        al_init_font_addon();

        if (!al_init() || !al_init_primitives_addon() || !al_install_keyboard() || !al_install_mouse() || !al_init_image_addon() || !al_init_ttf_addon()) {
             return false;
        }

        al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
        al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

        display = al_create_display(width, height);
        al_set_window_title (display, "Rysowanie funkcji 2D");

        event_queue = al_create_event_queue();

        if (!event_queue) { return false; }

        timer = al_create_timer(1.0/FPS);

        if (!timer) { return false; }

        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());
        al_start_timer(timer);

        clear(); flip();
        return true;
    }

    void waitForEvent(ALLEGRO_EVENT &ev) {
        al_wait_for_event(event_queue, &ev);
    }

    bool eventQueueEmpty() {
        return al_is_event_queue_empty(event_queue);
    }

    void clear() {
        al_clear_to_color(al_map_rgb(255,255,255));
    }

    void flip() {
        al_flip_display();
    }

    int getWidth() { return width; }
    int getHeight() { return height; }

    void drawButton(Button &b){
        al_draw_filled_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack());
        al_draw_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack(),2);
        ALLEGRO_FONT* font = al_load_ttf_font(b.getFont(), b.getFontSize(),NULL);
        al_draw_text(font, b.getColorText(), b.getTextX1(), b.getTextY1(), ALLEGRO_ALIGN_CENTRE, b.getText());
        al_destroy_font(font);
    }

    void drawTextBox(Button &b){
        al_draw_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack(),2);
        ALLEGRO_FONT* font = al_load_ttf_font(b.getFont(), b.getFontSize(),NULL);
        al_draw_text(font, b.getColorText(), b.getTextX1(), b.getTextY1(), ALLEGRO_ALIGN_CENTER, b.getText());
        al_destroy_font(font);
    }

    void drawFilledTextBox(Button &b){
        al_draw_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack(),2);
        ALLEGRO_FONT* font = al_load_ttf_font(b.getFont(), b.getFontSize(),NULL);
        al_draw_text(font, b.getColorText(), b.getTextX1(), b.getTextY1(), ALLEGRO_ALIGN_LEFT, b.getText());
        al_destroy_font(font);
    }

    void drawColorButton(Button &b, Function &f){
        unsigned char red, green, blue;
        if(f.ReturnColorStatus() == 1){
            red = 255;
            green = 0;
            blue = 0;
        }
        else if(f.ReturnColorStatus() == 2){
            red = 0;
            green = 255;
            blue = 0;
        }
        else if(f.ReturnColorStatus() == 3){
            red = 0;
            green = 0;
            blue = 255;
        }

        ALLEGRO_COLOR color = al_map_rgb(red, green, blue);
        al_draw_filled_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), color);
        al_draw_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), color,2);
    }

    void drawNumberButton(Button &b, Function &f){
        const char* linethickness;
        if(f.ReturnLineThickness() == 1)
            linethickness = "1";
        if(f.ReturnLineThickness() == 2)
            linethickness = "2";
        if(f.ReturnLineThickness() == 3)
            linethickness = "3";
        al_draw_filled_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack());
        al_draw_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack(),2);
        ALLEGRO_FONT* font = al_load_ttf_font(b.getFont(), b.getFontSize(),NULL);
        al_draw_text(font, b.getColorText(), b.getTextX1(), b.getTextY1(), ALLEGRO_ALIGN_CENTRE, linethickness);
        al_destroy_font(font);
    }

    void drawCheckBoxMarker(Button &b, Function &f){
        const char* marker;
        if(f.ReturnMarker() == 1)
            marker = "X";
        if(f.ReturnMarker() == 0)
            marker = "";

        al_draw_filled_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack());
        al_draw_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack(),2);
        ALLEGRO_FONT* font = al_load_ttf_font(b.getFont(), b.getFontSize(),NULL);
        al_draw_text(font, b.getColorText(), b.getTextX1(), b.getTextY1(), ALLEGRO_ALIGN_CENTRE, marker);
        al_destroy_font(font);
    }

    void drawCheckBoxScatter(Button &b, Function &f){
        const char* scatter;
        if(f.ReturnScatter() == 1)
            scatter = "X";
        if(f.ReturnScatter() == 0)
            scatter = "";

        al_draw_filled_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack());
        al_draw_rectangle(b.getBackX1(), b.getBackY1(), b.getBackX2(), b.getBackY2(), b.getColorBack(),2);
        ALLEGRO_FONT* font = al_load_ttf_font(b.getFont(), b.getFontSize(),NULL);
        al_draw_text(font, b.getColorText(), b.getTextX1(), b.getTextY1(), ALLEGRO_ALIGN_CENTRE, scatter);
        al_destroy_font(font);
    }

    bool ButtonClicked(int mousex, int mousey, Button &b){
        if(mousex >= b.getBackX1() && mousex <= b.getBackX2() && mousey >= b.getBackY1() && mousey <= b.getBackY2())
            return true;
        else
            return false;
    }

    void DrawingBox(){
        al_draw_rectangle(dbx1-2,dby1-2,dbx2,dby2,al_map_rgb(0,0,0),2);
    }

    void SaveScreen(const char* nazwa){
        ALLEGRO_BITMAP *screen = al_create_bitmap(800, 600);
        al_set_target_bitmap(screen);
        al_draw_bitmap(al_get_backbuffer(display), 0, 0, 0);
        al_save_bitmap(nazwa, screen);
        al_destroy_bitmap(screen);
    }

    void DrawFunction(Function &f){
        double zero_x = (dbx2-dbx1) * (0 - f.ReturnXmin()) / (f.ReturnXmax() - f.ReturnXmin()) + dbx1;
        double zero_y = (dby2-dby1) * (0 - f.ReturnYmax()) / (f.ReturnYmin() - f.ReturnYmax()) + dby1;

        if(zero_x>=dbx1 && zero_x<=dbx2)
            al_draw_line(zero_x,dby1-1,zero_x, dby2, al_map_rgb(0,0,0),1);
        if(zero_y>=dby1 && zero_y<=dby2)
            al_draw_line(dbx1-1,zero_y,dbx2, zero_y, al_map_rgb(0,0,0),1);

        ALLEGRO_COLOR color;
        if(f.ReturnColorStatus() == 1)
            color = al_map_rgb(255,0,0);
        if(f.ReturnColorStatus() == 2)
            color = al_map_rgb(0,255,0);
        if(f.ReturnColorStatus() == 3)
            color = al_map_rgb(0,0,255);

        if(f.ReturnScatter() == 0){

            for(int i = 0; i < NumberOfSteps; i++){
                int x = (f.ReturnX(i) / (f.ReturnXmax()-f.ReturnXmin())*(dbx2-dbx1)+zero_x);
                int y = (f.ReturnY(i) / (f.ReturnYmin()-f.ReturnYmax())*(dby2-dby1)+zero_y);
                int x1 = (f.ReturnX(i+1) / (f.ReturnXmax()-f.ReturnXmin())*(dbx2-dbx1)+zero_x);
                int y1 = (f.ReturnY(i+1) / (f.ReturnYmin()-f.ReturnYmax())*(dby2-dby1)+zero_y);
                if(x>dbx1 && x<dbx2-1 && y>dby1 && y<dby2){
                    if(f.ReturnLineThickness() == 1){
                        al_draw_pixel(x, y, color);
                    if((x && y) != 0 && (x1 && y1) != 0 && (x1>dbx1 && x1<dbx2 && y1>dby1 && y1<dby2))
                        al_draw_line(x,y,x1,y1,color,1);
                    }
                    if(f.ReturnLineThickness() == 2){
                        if(x>dbx1 && x<dbx2 && y-1>dby1 && y-1<dby2)
                            al_draw_pixel(x, y-1, color);

                        al_draw_pixel(x, y, color);
                        if((x && y) != 0 && (x1 && y1) != 0 && (x1>dbx1 && x1<dbx2 && y1>dby1 && y1<dby2))
                            al_draw_line(x,y,x1,y1,color,3);

                        if(x>dbx1 && x<dbx2 && y+1>dby1 && y+1<dby2){
                            al_draw_pixel(x, y+1, color);
                        }
                    }
                    if(f.ReturnLineThickness() == 3){
                        if(x>dbx1 && x<dbx2 && y-2>dby1 && y-2<dby2)
                            al_draw_pixel(x, y-2, color);
                        if(x>dbx1 && x<dbx2 && y-1>dby1 && y-1<dby2)
                            al_draw_pixel(x, y-1, color);

                        al_draw_pixel(x, y, color);
                        if((x && y) != 0 && (x1 && y1) != 0 && (x1>dbx1 && x1<dbx2 && y1>dby1 && y1<dby2))
                            al_draw_line(x,y,x1,y1,color,5);

                        if(x>dbx1 && x<dbx2 && y+1>dby1 && y+1<dby2)
                            al_draw_pixel(x, y+1, color);
                        if(x>dbx1 && x<dbx2 && y+2>dby1 && y+2<dby2)
                            al_draw_pixel(x, y+2, color);
                    }
                }
            }
        }
        if(f.ReturnMarker() == 1){
            for(int i = 0; i < f.LengthX1();i++){
                int xz = (f.ReturnX1(i) / (f.ReturnXmax()-f.ReturnXmin())*(dbx2-dbx1)+zero_x);
                int yz = (f.ReturnY1(i) / (f.ReturnYmin()-f.ReturnYmax())*(dby2-dby1)+zero_y);
                if(xz>dbx1 && xz<dbx2 && yz>dby1 && yz<dby2){
                        if(f.ReturnLineThickness() == 1)
                            al_draw_filled_circle(xz,yz,3,color);
                        if(f.ReturnLineThickness() == 2)
                            al_draw_filled_circle(xz,yz,5,color);
                        if(f.ReturnLineThickness() == 3)
                            al_draw_filled_circle(xz,yz,7,color);
                }
            }
        }
    }
};

int main(int argc, char** argv){

    Display d;

    if (!d.init(800, 600)) {
        cout << "Display initialization failed." << endl; return -1;
    }

    Function f;

    Button FXstat;
    Button FX;
    Button RysujWykres;
    Button WartoscX;
    Button WartoscXOD;
    Button WartoscXODFill;
    Button WartoscXDO;
    Button WartoscXDOFill;
    Button WartoscY;
    Button WartoscYOD;
    Button WartoscYODFill;
    Button WartoscYDO;
    Button WartoscYDOFill;
    Button KolorLinii;
    Button KolorLiniiFill;
    Button GruboscLinii;
    Button GruboscLiniiFill;
    Button Znacznik;
    Button ZnacznikFill;
    Button WykresPunktowy;
    Button WykresPunktowyFill;
    Button ZapiszWykres;
    Button Zamknij;
    Button Pomoc, Pomoc2, Pomoc3, Pomoc4, Pomoc5, Pomoc6, Pomoc7, Pomoc8, Pomoc9;
    FXstat.setButton(0,0,0,
                     0,0,0,
                     45,475,
                     20,470,70,496,
                     16, "arialbd.ttf",
                     "f(x) = ");
    FX.setButton(30,90,150,
                 0,0,0,
                 85,475,
                 80,470,450,496,
                 16, "arialbd.ttf",
                 f.Show());
    RysujWykres.setButton(30,90,150,
                          150,150,150,
                          530,475,
                          460,470,600,496,
                          16, "arialbd.ttf",
                          "Rysuj wykres");
    WartoscX.setButton(0,0,0,
                     0,0,0,
                     160,521,
                     20,516,300,542,
                     16, "arialbd.ttf",
                     "Wartosc X");
    WartoscXOD.setButton(0,0,0,
                     0,0,0,
                     50,567,
                     20,562,80,588,
                     16, "arialbd.ttf",
                     "Od:");
    WartoscXODFill.setButton(30,90,150,
                     0,0,0,
                     95,567,
                     90,562,150,588,
                     16, "arialbd.ttf",
                     f.ShowXmin());
    WartoscXDO.setButton(0,0,0,
                     0,0,0,
                     200,567,
                     170,562,230,588,
                     16, "arialbd.ttf",
                     "Do:");
    WartoscXDOFill.setButton(30,90,150,
                     0,0,0,
                     245,567,
                     240,562,300,588,
                     16, "arialbd.ttf",
                     f.ShowXmax());
    WartoscY.setButton(0,0,0,
                     0,0,0,
                     460,521,
                     320,516,600,542,
                     16, "arialbd.ttf",
                     "Wartosc Y");
    WartoscYOD.setButton(0,0,0,
                     0,0,0,
                     350,567,
                     320,562,380,588,
                     16, "arialbd.ttf",
                     "Od:");
    WartoscYODFill.setButton(30,90,150,
                     0,0,0,
                     395,567,
                     390,562,450,588,
                     16, "arialbd.ttf",
                     f.ShowYmin());
    WartoscYDO.setButton(0,0,0,
                     0,0,0,
                     500,567,
                     470,562,530,588,
                     16, "arialbd.ttf",
                     "Do:");
    WartoscYDOFill.setButton(30,90,150,
                     0,0,0,
                     545,567,
                     540,562,600,588,
                     16, "arialbd.ttf",
                     f.ShowYmax());
    KolorLinii.setButton(30,90,150,
                      150,150,150,
                      700,25,
                      630,20,770,46,
                      16, "arialbd.ttf",
                      "Kolor linii");
    KolorLiniiFill.setButton(255,0,0,
                      255,0,0,
                      700,61,
                      630,56,770,66,
                      16, "arialbd.ttf",
                      "");
    GruboscLinii.setButton(30,90,150,
                      150,150,150,
                      700,91,
                      630,86,770,112,
                      16, "arialbd.ttf",
                      "Grubosc linii");
    GruboscLiniiFill.setButton(30,90,150,
                      150,150,150,
                      700,125,
                      630,122,770,144,
                      16, "arialbd.ttf",
                      "1");
    Znacznik.setButton(30,90,150,
                      150,150,150,
                      700,169,
                      630,164,770,190,
                      16, "arialbd.ttf",
                      "Znacznik");
    ZnacznikFill.setButton(30,90,150,
                      150,150,150,
                      700,200,
                      692,200,708,216,
                      16, "arialbd.ttf",
                      "X");
    WykresPunktowy.setButton(30,90,150,
                      150,150,150,
                      700,241,
                      630,236,770,262,
                      16, "arialbd.ttf",
                      "Wykres punktowy");
    WykresPunktowyFill.setButton(30,90,150,
                      150,150,150,
                      700,272,
                      692,272,708,288,
                      16, "arialbd.ttf",
                      "");
    ZapiszWykres.setButton(30,90,150,
                      150,150,150,
                      700,313,
                      630,308,770,334,
                      16, "arialbd.ttf",
                      "Zapisz wykres");
    Pomoc.setButton(0,0,0,
                      0,0,0,
                      615,359,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "Obslugiwane funkcje:");
    Pomoc2.setButton(0,0,0,
                      0,0,0,
                      615,381,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "sin(x), cos(x), tan(x), cot(x)");
    Pomoc3.setButton(0,0,0,
                      0,0,0,
                      615,398,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "exp(x), exp2(x), sqrt(x), abs(x)");
    Pomoc4.setButton(0,0,0,
                      0,0,0,
                      615,415,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "log(x), log2(x), log10(x)");
    Pomoc5.setButton(0,0,0,
                      0,0,0,
                      615,432,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "wielomiany");
    Pomoc6.setButton(0,0,0,
                      0,0,0,
                      615,454,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "Obslugiwane znaki:");
    Pomoc7.setButton(0,0,0,
                      0,0,0,
                      615,471,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "+ - / * ^ ( ) .");
    Pomoc8.setButton(0,0,0,
                      0,0,0,
                      615,488,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "cyfry");
    Pomoc9.setButton(0,0,0,
                      0,0,0,
                      615,505,
                      610,354,790,534,
                      12, "arialbd.ttf",
                      "klawiatura numeryczna");
    Zamknij.setButton(30,90,150,
                      150,150,150,
                      700,559,
                      630,554,770,580,
                      16, "arialbd.ttf",
                      "Zamknij");

    bool doexit = false;
    int textbox;
    int rshift = 0;
    bool redraw = true;
    int draw = 0;

    while(!doexit){
        ALLEGRO_EVENT ev;
        d.waitForEvent(ev);
            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                break;
            }
            else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, Zamknij))
                    break;
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, FX))
                    textbox = 1;
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, WartoscXODFill))
                    textbox = 2;
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, WartoscXDOFill))
                    textbox = 3;
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, WartoscYODFill))
                    textbox = 4;
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, WartoscYDOFill))
                    textbox = 5;
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, KolorLinii))
                    f.ChangeColorStatus();
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, GruboscLinii))
                    f.ChangeLineThickness();
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, ZnacznikFill))
                    f.ChangeMarker();
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, WykresPunktowyFill))
                    f.ChangeScatter();
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, ZapiszWykres)){
                    d.SaveScreen(f.ShowChartName());
                    f.AddChartNumber();
                    f.AddNewChartNumber();
                }
                if(d.ButtonClicked(ev.mouse.x, ev.mouse.y, RysujWykres)){
                    f.ClearXY();
                    f.ClearX1Y1();
                    f.CalculateValues();
                    draw = 1;
                }

                redraw = true;
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                if(ev.keyboard.keycode == ALLEGRO_KEY_RSHIFT)
                    rshift = 1;

                    redraw = true;
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_UP && textbox == 1){
                if(ev.keyboard.keycode == ALLEGRO_KEY_RSHIFT)
                    rshift = 0;
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    doexit = true;
                    break;
                }

                redraw = true;
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_CHAR && textbox == 1){
                if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                        f.DeleteSign();
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_FULLSTOP){
                        f.AddSign('.');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_A){
                        f.AddSign('a');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_S){
                        f.AddSign('s');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_I){
                        f.AddSign('i');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_N){
                        f.AddSign('n');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_C){
                        f.AddSign('c');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_O){
                        f.AddSign('o');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_L){
                        f.AddSign('l');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_G){
                        f.AddSign('g');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_H){
                        f.AddSign('h');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_T){
                        f.AddSign('t');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_E){
                        f.AddSign('e');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_P){
                        f.AddSign('p');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_B){
                        f.AddSign('b');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_Q){
                        f.AddSign('q');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_R){
                        f.AddSign('r');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_X){
                        f.AddSign('x');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_1 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_1){
                        f.AddSign('1');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_2 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_2){
                        f.AddSign('2');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_3 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_3){
                        f.AddSign('3');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_4 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_4){
                        f.AddSign('4');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_5 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_5){
                        f.AddSign('5');
                        FX.setText(f.Show());
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_6 && rshift == 0) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_6){
                        f.AddSign('6');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_7 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_7){
                        f.AddSign('7');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_8 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_8){
                        f.AddSign('8');
                        FX.setText(f.Show());
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_9 && rshift == 0) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_9){
                        f.AddSign('9');
                        FX.setText(f.Show());
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_0 && rshift == 0) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_0){
                        f.AddSign('0');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_9 && rshift == 1){
                        f.AddSign('(');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_0 && rshift == 1){
                        f.AddSign(')');
                        FX.setText(f.Show());
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_EQUALS && rshift == 1) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS){
                        f.AddSign('+');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_MINUS || ev.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS){
                        f.AddSign('-');
                        FX.setText(f.Show());
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_SLASH && rshift == 1) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_SLASH){
                        f.AddSign('/');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_PAD_ASTERISK){
                        f.AddSign('*');
                        FX.setText(f.Show());
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_6 && rshift == 1){
                        f.AddSign('^');
                        FX.setText(f.Show());
                }

                redraw = true;
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_CHAR && textbox >= 2 && textbox <=5){
                if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                    switch(textbox){
                        case 2:
                            f.DeleteXmin();
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.DeleteXmax();
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.DeleteYmin();
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.DeleteYmax();
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                        }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_FULLSTOP){
                    switch(textbox){
                        case 2:
                            f.AddXmin('.');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('.');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('.');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('.');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_1 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_1){
                    switch(textbox){
                        case 2:
                            f.AddXmin('1');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('1');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('1');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('1');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_2 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_2){
                    switch(textbox){
                        case 2:
                            f.AddXmin('2');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('2');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('2');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('2');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_3 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_3){
                    switch(textbox){
                        case 2:
                            f.AddXmin('3');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('3');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('3');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('3');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_4 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_4){
                    switch(textbox){
                        case 2:
                            f.AddXmin('4');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('4');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('4');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('4');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_5 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_5){
                    switch(textbox){
                        case 2:
                            f.AddXmin('5');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('5');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('5');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('5');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_6 && rshift == 0) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_6){
                    switch(textbox){
                        case 2:
                            f.AddXmin('6');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('6');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('6');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('6');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_7 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_7){
                    switch(textbox){
                        case 2:
                            f.AddXmin('7');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('7');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('7');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('7');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_8 || ev.keyboard.keycode == ALLEGRO_KEY_PAD_8){
                    switch(textbox){
                        case 2:
                            f.AddXmin('8');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('8');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('8');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('8');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_9 && rshift == 0) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_9){
                    switch(textbox){
                        case 2:
                            f.AddXmin('9');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('9');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('9');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('9');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if((ev.keyboard.keycode == ALLEGRO_KEY_0 && rshift == 0) || ev.keyboard.keycode == ALLEGRO_KEY_PAD_0){
                    switch(textbox){
                        case 2:
                            f.AddXmin('0');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('0');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('0');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('0');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }
                if(ev.keyboard.keycode == ALLEGRO_KEY_MINUS || ev.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS){
                    switch(textbox){
                        case 2:
                            f.AddXmin('-');
                            WartoscXODFill.setText(f.ShowXmin());
                            break;

                        case 3:
                            f.AddXmax('-');
                            WartoscXDOFill.setText(f.ShowXmax());
                            break;

                        case 4:
                            f.AddYmin('-');
                            WartoscYODFill.setText(f.ShowYmin());
                            break;

                        case 5:
                            f.AddYmax('-');
                            WartoscYDOFill.setText(f.ShowYmax());
                            break;
                    }
                }

                redraw = true;
            }
            if(redraw && d.eventQueueEmpty()) {
                redraw = false;
                d.clear();
                d.DrawingBox();
                d.drawFilledTextBox(FX);
                d.drawTextBox(FXstat);
                d.drawButton(RysujWykres);
                d.drawTextBox(WartoscX);
                d.drawTextBox(WartoscXOD);
                d.drawFilledTextBox(WartoscXODFill);
                d.drawTextBox(WartoscXDO);
                d.drawFilledTextBox(WartoscXDOFill);
                d.drawTextBox(WartoscY);
                d.drawTextBox(WartoscYOD);
                d.drawFilledTextBox(WartoscYODFill);
                d.drawTextBox(WartoscYDO);
                d.drawFilledTextBox(WartoscYDOFill);
                d.drawButton(KolorLinii);
                d.drawColorButton(KolorLiniiFill, f);
                d.drawButton(GruboscLinii);
                d.drawNumberButton(GruboscLiniiFill, f);
                d.drawButton(Znacznik);
                d.drawCheckBoxMarker(ZnacznikFill, f);
                d.drawButton(WykresPunktowy);
                d.drawCheckBoxScatter(WykresPunktowyFill, f);
                d.drawButton(ZapiszWykres);
                d.drawFilledTextBox(Pomoc);
                d.drawFilledTextBox(Pomoc2);
                d.drawFilledTextBox(Pomoc3);
                d.drawFilledTextBox(Pomoc4);
                d.drawFilledTextBox(Pomoc5);
                d.drawFilledTextBox(Pomoc6);
                d.drawFilledTextBox(Pomoc7);
                d.drawFilledTextBox(Pomoc8);
                d.drawFilledTextBox(Pomoc9);
                d.drawButton(Zamknij);
                if(draw == 1)
                    d.DrawFunction(f);
                d.flip();
            }
    }
};
