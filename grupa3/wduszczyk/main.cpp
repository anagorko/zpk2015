#include <iostream>
#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h> //Header for dialogue boxes
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <typeinfo>


//--- muparserx framework -------------------------------------------------------------------------
#include "mpParser.h"
#include "mpDefines.h"
#include "mpTest.h"
//--- other includes ------------------------------------------------------------------------------
#include "timer.h"

using namespace std;
using namespace mup;
//poczatek miejsca na zmienne globalne ******************************************************
const int w = 500;
const int width = 500;
const int h = 500;
const int hight = 500;
const double PI = 3.1415926535897932;

#define RUNDA cout<<"Podaj wzor funkcji"<<endl
#define BLUE 240, 248, 255
#define RED 255, 0 , 0
#define YELLOW 255, 250, 5
#define GREEN 0, 150, 0
#define WHITE 255, 255, 255
#define SRODEK 200,200
#define GREY al_map_rgb(100,100,100)

int no_of_players = 1;


//koniec miejsca na zmienne globalne ******************************************************



//poczatek miejsca na klasy******************************************************
class punkt{
double x, y;
public:
    Point() {}
   void Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
};

class Player{
 private:
 int id, score; //definiuje zmienne dla klasy ktore beda obliczane wewnatrz programu
 //chce aby tego uzytkownik nie mogl zmieniac
 punkt x,y;

 public:
 string plname; // imie dla zawodnika uzytkownik moze nadac i wywolac

 Player() {
     id=0;
     score=0;
     plname="gracz";
 }

 Player(int _id, int _score, string _name) {
     id=_id;
     score=_score;
     plname=_name;
 }

Player (string name) {
    id=no_of_players;
new Player(id,0,name);
}

string getName(int id) {
return plname;}
 //Player(Point(int a, int b)) { //wspolrzedne gracza}

};


class Goal{

};

class przeszkoda{
    float x, y, r;
public:
    przeszkoda(float _x, float _y, float _r){
        x = _x;
        y = _y;
        r = _r;
    }
    void obstacle(){
        al_draw_filled_circle(x, y, r, GREY);
    }
 bool czy_zderzenie(float x1, float y1){
        if((x1-x)*(x1-x) + (y1-y)*(y1-y) < r*r)
            return TRUE;
        else
            return FALSE;
    }

    float get_x() {return x;}
    float get_y() {return y;}
    float get_r() {return r;}
    void set_x(float _x) {x = _x;}
};



//koniec miejsca na klasy******************************************************



//pocz�tek miejsca na funkcje ******************************************************
void DODAWANIE ()
{
    string ans;
    cout<<"Czy dodac gracza? T/N"<<endl;
    cin>>ans;

        if (ans == "T" || ans == "t" || ans=="y" || ans=="Y" || ans=="tak" or ans=="Tak") {
            if (no_of_players >4){ cout<<"osiagnieto maksymalna liczbe graczy";}
            else{
        cout<<"Podaj nazwe dla gracza "<<no_of_players<<endl;
        no_of_players+=1;

        cin>>ans;

        Player(ans);
        DODAWANIE();
        }
        }


}

 bool kraniec(float x, float y){
        if (x < w && y > 0 && y < h)
            return FALSE;
        else
            return TRUE;
    }


void wykres () {
//rysowanie podstawowego wykresu funkcji
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_line(50,200,350,200,al_map_rgb(WHITE), 2);
        al_draw_line(345,195,350,200,al_map_rgb(WHITE), 2);
        al_draw_line(345,205,350,200,al_map_rgb(WHITE), 2);

    al_draw_line(200,50,200,350,al_map_rgb(WHITE), 2);
        al_draw_line(195,55,200,50,al_map_rgb(WHITE), 2);
        al_draw_line(205,55,200,50,al_map_rgb(WHITE), 2);
}


//double na string
string d2string(const double x){
    ostringstream stream;
    stream << x;
    return stream.str();
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



const string_type sPrompt = _T("muparserx> ");

//-------------------------------------------------------------------------------------------------
// The following classes will be used to list muParserX variables, constants
// from this console application
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class FunPrint : public ICallback
{
public:
  FunPrint() : ICallback(cmFUNC, _T("print"), 1)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)
  {
    console() << a_pArg[0].Get()->ToString() << _T("\n");
    *ret = (float_type)0.0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("");
  }

  virtual IToken* Clone() const
  {
    return new FunPrint(*this);
  }
}; // class FunPrint

//-------------------------------------------------------------------------------------------------
class FunTest0 : public ICallback
{
public:
  FunTest0() : ICallback(cmFUNC, _T("test0"), 0)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type * /*a_pArg*/, int /*a_iArgc*/)
  {
    *ret = (float_type)0.0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("");
  }

  virtual IToken* Clone() const
  {
    return new FunTest0(*this);
  }
}; // class FunTest0

//-------------------------------------------------------------------------------------------------
class FunListVar : public ICallback
{
public:

  FunListVar() : ICallback(cmFUNC, _T("list_var"), 0)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type * /*a_pArg*/, int /*a_iArgc*/)
  {
    ParserXBase &parser = *GetParent();

    console() << _T("\nParser variables:\n");
    console() << _T(  "-----------------\n");

    // Query the used variables (must be done after calc)
    var_maptype vmap = parser.GetVar();
    if (!vmap.size())
    {
      console() << _T("Expression does not contain variables\n");
    }
    else
    {
      var_maptype::iterator item = vmap.begin();
      for (; item!=vmap.end(); ++item)
      {
        // You can dump the token into a stream via the "<<" operator
        console() << _T("  ") << item->first << _T(" =  ") << *(item->second)/* << _T("\n")*/;

        // If you need more specific information cast the token to a variable object
        Variable &v = (Variable&)(*(item->second));
        console() << _T("  (type=\"") << v.GetType() << _T("\"; ptr=0x") << hex << v.GetPtr() << _T(")\n");
      }
    }

    *ret = (float_type)vmap.size();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("list_var() - List all variables of the parser bound to this function and returns the number of defined variables.");
  }

  virtual IToken* Clone() const
  {
    return new FunListVar(*this);
  }
}; // class FunListVar


//-------------------------------------------------------------------------------------------------
class FunListConst : public ICallback
{
public:

  FunListConst() : ICallback(cmFUNC, _T("list_const"), 0)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type * /*a_pArg*/, int /*a_iArgc*/)
  {
    ParserXBase &parser = *GetParent();

    console() << _T("\nParser constants:\n");
    console() << _T(  "-----------------\n");

    val_maptype cmap = parser.GetConst();
    if (!cmap.size())
    {
      console() << _T("No constants defined\n");
    }
    else
    {
      val_maptype::iterator item = cmap.begin();
      for (; item!=cmap.end(); ++item)
        console() << _T("  ") << item->first << _T(" =  ") << (Value&)(*(item->second)) << _T("\n");
    }

    *ret = (float_type)cmap.size();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("list_const() - List all constants of the parser bound to this function and returns the number of defined constants.");
  }

  virtual IToken* Clone() const
  {
    return new FunListConst(*this);
  }
}; // class FunListConst


//-------------------------------------------------------------------------------------------------
class FunBenchmark : public ICallback
{
public:
  FunBenchmark() : ICallback(cmFUNC, _T("bench"), 0)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type * /*a_pArg*/, int /*a_iArgc*/)
  {
    char outstr[200];
    time_t t = time(nullptr);

    #ifdef _DEBUG
    strftime(outstr, sizeof(outstr), "Result_%Y%m%d_%H%M%S_dbg.txt", localtime(&t));
    #else
    strftime(outstr, sizeof(outstr), "Result_%Y%m%d_%H%M%S_release.txt", localtime(&t));
    #endif

    const char_type* sExpr[] = {
                                 _T("sin(a)"),
                                 _T("cos(a)"),
                                 _T("tan(a)"),
                                 _T("sqrt(a)"),
                                 _T("(a+b)*3"),
                                 _T("a^2+b^2"),
                                 _T("a^3+b^3"),
                                 _T("a^4+b^4"),
                                 _T("a^5+b^5"),
                                 _T("a*2+b*2"),
                                 _T("-(b^1.1)"),
                                 _T("a + b * c"),
                                 _T("a * b + c"),
                                 _T("a+b*(a+b)"),
                                 _T("(1+b)*(-3)"),
                                 _T("e^log(7*a)"),
                                 _T("10^log(3+b)"),
                                 _T("a+b-e*pi/5^6"),
                                 _T("a^b/e*pi-5+6"),
                                 _T("sin(a)+sin(b)"),
                                 _T("(cos(2.41)/b)"),
                                 _T("-(sin(pi+a)+1)"),
                                 _T("a-(e^(log(7+b)))"),
                                 _T("sin(((a-a)+b)+a)"),
                                 _T("((0.09/a)+2.58)-1.67"),
                                 _T("abs(sin(sqrt(a^2+b^2))*255)"),
                                 _T("abs(sin(sqrt(a*a+b*b))*255)"),
                                 _T("cos(0.90-((cos(b)/2.89)/e)/a)"),
                                 _T("(1*(2*(3*(4*(5*(6*(a+b)))))))"),
                                 _T("abs(sin(sqrt(a^2.1+b^2.1))*255)"),
                                 _T("(1*(2*(3*(4*(5*(6*(7*(a+b))))))))"),
                                 _T("1/(a*sqrt(2*pi))*e^(-0.5*((b-a)/a)^2)"),
                                 _T("1+2-3*4/5^6*(2*(1-5+(3*7^9)*(4+6*7-3)))+12"),
                                 _T("1+b-3*4/5^6*(2*(1-5+(3*7^9)*(4+6*7-3)))+12*a"),
                                 _T("(b+1)*(b+2)*(b+3)*(b+4)*(b+5)*(b+6)*(b+7)*(b+8)*(b+9)*(b+10)*(b+11)*(b+12)"),
                                 _T("(a/((((b+(((e*(((((pi*((((3.45*((pi+a)+pi))+b)+b)*a))+0.68)+e)+a)/a))+a)+b))+b)*a)-pi))"),
                                 _T("(((-9))-e/(((((((pi-(((-7)+(-3)/4/e))))/(((-5))-2)-((pi+(-0))*(sqrt((e+e))*(-8))*(((-pi)+(-pi)-(-9)*(6*5))/(-e)-e))/2)/((((sqrt(2/(-e)+6)-(4-2))+((5/(-2))/(1*(-pi)+3))/8)*pi*((pi/((-2)/(-6)*1*(-1))*(-6)+(-e)))))/((e+(-2)+(-e)*((((-3)*9+(-e)))+(-9)))))))-((((e-7+(((5/pi-(3/1+pi)))))/e)/(-5))/(sqrt((((((1+(-7))))+((((-e)*(-e)))-8))*(-5)/((-e)))*(-6)-((((((-2)-(-9)-(-e)-1)/3))))/(sqrt((8+(e-((-6))+(9*(-9))))*(((3+2-8))*(7+6+(-5))+((0/(-e)*(-pi))+7)))+(((((-e)/e/e)+((-6)*5)*e+(3+(-5)/pi))))+pi))/sqrt((((9))+((((pi))-8+2))+pi))/e*4)*((-5)/(((-pi))*(sqrt(e)))))-(((((((-e)*(e)-pi))/4+(pi)*(-9)))))))+(-pi)"),
                                 0 };



    ParserX  parser;
    Value a((float_type)1.0);
    Value b((float_type)2.0);
    Value c((float_type)3.0);

    parser.DefineVar(_T("a"),  Variable(&a));
    parser.DefineVar(_T("b"),  Variable(&b));
    parser.DefineVar(_T("c"),  Variable(&c));
    parser.DefineConst(_T("pi"), (float_type)M_PI);
    parser.DefineConst(_T("e"), (float_type)M_E);

    FILE *pFile = fopen(outstr, "w");
    int iCount = 400000;

    #ifdef _DEBUG
    string_type sMode = _T("# debug mode\n");
    #else
    string_type sMode = _T("# release mode\n");
    #endif

    fprintf(pFile, "%s; muParserX V%s\n", sMode.c_str(), ParserXBase::GetVersion().c_str());
    fprintf(pFile, "\"Eqn no.\", \"number\", \"result\", \"time in ms\", \"eval per second\", \"expr\"\n");

    printf("%s", sMode.c_str());
    printf("\"Eqn no.\", \"number\", \"result\", \"time in ms\", \"eval per second\", \"expr\"\n");

    double avg_eval_per_sec = 0;
    int ct=0;
    for (int i=0; sExpr[i]; ++i)
    {
      ct++;
      StartTimer();
      Value val;
      parser.SetExpr(sExpr[i]);

      // implicitely create reverse polish notation
      parser.Eval();

      for (int n=0; n<iCount; ++n)
      {
        val = parser.Eval();
      }

      double diff = StopTimer();

      double eval_per_sec = (double)iCount*1000.0/diff;
      avg_eval_per_sec += eval_per_sec;

      #if !defined _UNICODE
      fprintf(pFile, "Eqn_%d, %d, %lf, %lf, %lf, %s\n", i, iCount, (double)val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      printf("Eqn_%d, %d, %lf, %lf, %lf, %s\n"        , i, iCount, (double)val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      #else
      fwprintf(pFile, _T("Eqn_%d, %d, %lf, %lf, %lf, %s\n"), i, iCount, (double)val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      wprintf(_T("Eqn_%d, %d, %lf, %lf, %lf, %s\n")        , i, iCount, (double)val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      #endif
    }

    avg_eval_per_sec /= (double)ct;

    fprintf(pFile, "# Eval per s: %ld", (long)avg_eval_per_sec);

    fflush(pFile);
    *ret = (float_type)avg_eval_per_sec;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("bench() - Perform a benchmark with a set of standard functions.");
  }

  virtual IToken* Clone() const
  {
    return new FunBenchmark(*this);
  }
}; // class FunBenchmark


//-------------------------------------------------------------------------------------------------
class FunListFunctions : public ICallback
{
public:
  FunListFunctions() : ICallback(cmFUNC, _T("list_fun"), 0)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type * /*a_pArg*/, int /*a_iArgc*/)
  {
    ParserXBase &parser = *GetParent();

    console() << _T("\nParser functions:\n");
    console() << _T(  "----------------\n");

    fun_maptype fmap = parser.GetFunDef();
    if (!fmap.size())
    {
      console() << _T("No functions defined\n");
    }
    else
    {
      val_maptype::iterator item = fmap.begin();
      for (; item!=fmap.end(); ++item)
      {
        ICallback *pFun = (ICallback*)item->second.Get();
        console() << pFun->GetDesc() << _T("\n");
      }
    }

    *ret = (float_type)fmap.size();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("list_fun() - List all parser functions and returns the total number of defined functions.");
  }

  virtual IToken* Clone() const
  {
    return new FunListFunctions(*this);
  }
}; // class FunListFunctions


//-------------------------------------------------------------------------------------------------
class FunEnableOptimizer : public ICallback
{
public:
  FunEnableOptimizer() : ICallback(cmFUNC, _T("enable_optimizer"), 1)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)
  {
    ParserXBase &parser = *GetParent();
    parser.EnableOptimizer(a_pArg[0]->GetBool());
    *ret = a_pArg[0]->GetBool();
  }
  virtual const char_type* GetDesc() const
  {
    return _T("enable_optimizer(bool) - Enables the parsers built in expression optimizer.");
  }

  virtual IToken* Clone() const
  {
    return new FunEnableOptimizer(*this);
  }
}; // class FunListFunctions


//-------------------------------------------------------------------------------------------------
class FunSelfTest : public ICallback
{
public:
  FunSelfTest() : ICallback(cmFUNC, _T("test"), 0)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type * /*a_pArg*/, int /*a_iArgc*/)
  {
    ParserXBase::EnableDebugDump(0, 0);
    ParserTester pt;
    pt.Run();
    *ret = (float_type)0.0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("test() - Runs the unit test of muparserx.");
  }

  virtual IToken* Clone() const
  {
    return new FunSelfTest(*this);
  }
}; // class FunSelfTest

//-------------------------------------------------------------------------------------------------
class FunEnableDebugDump : public ICallback
{
public:
  FunEnableDebugDump() : ICallback(cmFUNC, _T("debug"), 2)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)
  {
    ParserXBase::EnableDebugDump(a_pArg[0]->GetBool(), a_pArg[1]->GetBool());
    if (a_pArg[0]->GetBool())
      console() << _T("Bytecode output activated.\n");
    else
      console() << _T("Bytecode output deactivated.\n");

    if (a_pArg[1]->GetBool())
      console() << _T("Stack output activated.\n");
    else
      console() << _T("Stack output deactivated.\n");

      *ret = (float_type)0.0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("debug(bDumpRPN, bDumpStack) - Enable dumping of RPN and stack content.");
  }

  virtual IToken* Clone() const
  {
    return new FunEnableDebugDump(*this);
  }
}; // class FunEnableDebugDump

#if defined(_UNICODE)
//-------------------------------------------------------------------------------------------------
class FunLang : public ICallback
{
public:
  FunLang() : ICallback(cmFUNC, _T("lang"), 1)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)
  {
    string_type sID = a_pArg[0]->GetString();
    if (sID==_T("de"))
    {
      ParserX::ResetErrorMessageProvider(new mup::ParserMessageProviderGerman);
    }
    else if (sID==_T("en"))
    {
      ParserX::ResetErrorMessageProvider(new mup::ParserMessageProviderEnglish);
    }
    else
    {
      console() << _T("Invalid language ID\n");
    }

    *ret = (float_type)0.0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("lang(sLang) - Set the language of error messages (i.e. \"de\" or \"en\").");
  }

  virtual IToken* Clone() const
  {
    return new FunLang(*this);
  }
}; // class FunLang
#endif // #if defined(_UNICODE)

/*
//-------------------------------------------------------------------------------------------------
class FunGeneric : public ICallback
{
public:

  FunGeneric(string_type sIdent, string_type sFunction)
    :ICallback(cmFUNC, sIdent.c_str())
    ,m_parser()
    ,m_vars()
    ,m_val()
  {
    m_parser.SetExpr(sFunction);
    m_vars = m_parser.GetExprVar();
    SetArgc(m_vars.size());

    // Create values for the undefined variables and bind them
    // to the variables
    var_maptype::iterator item = m_vars.begin();
    for (; item!=m_vars.end(); ++item)
    {
      ptr_val_type val(new Value());
      m_val.push_back(val);

      // assign a parser variable
      m_parser.DefineVar(item->second->GetIdent(), Variable(val.Get()));
    }
  }

  virtual ~FunGeneric()
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    // Set the variables
    for (std::size_t i=0; i<(std::size_t)a_iArgc; ++i)
    {
      *m_val[i] = *a_pArg[i];
    }

    *ret = m_parser.Eval();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("xxx(...) - Dynamically defined function");
  }

  virtual IToken* Clone() const
  {
    return new FunGeneric(*this);
  }

private:

  ParserX m_parser;
  mup::var_maptype m_vars;
  val_vec_type m_val;
}; // class FunGeneric

//---------------------------------------------------------------------------
class FunDefine : public ICallback
{
public:
  FunDefine() : ICallback(cmFUNC, _T("define"), 2)
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    string_type sFun = a_pArg[0]->GetString();
    string_type sDef = a_pArg[1]->GetString();

    ParserXBase &parser = *GetParent();
    parser.DefineFun(new FunGeneric(sFun, sDef));

    *ret = 0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("define(Function, Definition) - Define a new parser function.");
  }

  virtual IToken* Clone() const
  {
    return new FunDefine(*this);
  }
}; // class FunDefine
*/

//---------------------------------------------------------------------------
void ListExprVar(ParserXBase &parser)
{
  console() << _T("\nVariables found in : \"") << parser.GetExpr() << _T("\"\n");
  console() << _T(  "-----------------------------\n");

  // Query the used variables (must be done after calc)
  var_maptype vmap = parser.GetExprVar();
  if (!vmap.size())
  {
    console() << _T("Expression does not contain variables\n");
  }
  else
  {
    var_maptype::iterator item = vmap.begin();
    for (; item!=vmap.end(); ++item)
      console() << _T("  ") << item->first << _T(" =  ") << (Variable&)(*(item->second)) << _T("\n");
  }
}

//---------------------------------------------------------------------------
/** \brief Check for external keywords.
*/
int CheckKeywords(const char_type *a_szLine, ParserXBase &a_Parser)
{
  string_type sLine(a_szLine);

  if (sLine==_T("quit"))
  {
    return -1;
  }
  else if (sLine==_T("exprvar"))
  {
    ListExprVar(a_Parser);
    return 1;
  }
  else if (sLine==_T("rpn"))
  {
    a_Parser.DumpRPN();
    return 1;
  }

  return 0;
}

//---------------------------------------------------------------------------
void Calc()
{
  ParserX  parser(pckALL_NON_COMPLEX);
//  ParserX  parser(pckALL_COMPLEX);

  // Create an array variable
  Value arr1(3, 0);
  arr1.At(0) = (float_type)1.0;
  arr1.At(1) = (float_type)2.0;
  arr1.At(2) = (float_type)3.0;

  Value arr2(3, 0);
  arr2.At(0) = (float_type)4.0;
  arr2.At(1) = (float_type)3.0;
  arr2.At(2) = (float_type)2.0;

  Value arr3(4, 0);
  arr3.At(0) = (float_type)1.0;
  arr3.At(1) = (float_type)2.0;
  arr3.At(2) = (float_type)3.0;
  arr3.At(3) = (float_type)4.0;

  Value arr4(3, 0);
  arr4.At(0) = (float_type)4.0;
  arr4.At(1) = false;
  arr4.At(2) = _T("hallo");

  // Create a 3x3 matrix with zero elements
  Value m1(3, 3, 0);
  m1.At(0, 0) = 1.0;
  m1.At(1, 1) = 1.0;
  m1.At(2, 2) = 1.0;

  Value m2(3, 3, 0);
  m2.At(0, 0) = 1.0;
  m2.At(0, 1) = 2.0;
  m2.At(0, 2) = 3.0;
  m2.At(1, 0) = 4.0;
  m2.At(1, 1) = 5.0;
  m2.At(1, 2) = 6.0;
  m2.At(2, 0) = 7.0;
  m2.At(2, 1) = 8.0;
  m2.At(2, 2) = 9.0;

  Value val[5];
  val[0] = (float_type)1.1;
  val[1] = 1.0;
  val[2] = false;
  val[3] = _T("Hello");
  val[4] = _T("World");

  Value fVal[3];
  fVal[0] = 1;
  fVal[1] = (float_type)2.22;
  fVal[2] = (float_type)3.33;

  Value sVal[3];
  sVal[0] = _T("hello");
  sVal[1] = _T("world");
  sVal[2] = _T("test");

  Value cVal[3];
  cVal[0] = mup::cmplx_type(1, 1);
  cVal[1] = mup::cmplx_type(2, 2);
  cVal[2] = mup::cmplx_type(3, 3);

  Value ans;
  parser.DefineVar(_T("ans"), Variable(&ans));

  // some tests for vectors
  parser.DefineVar(_T("va"), Variable(&arr1));
  parser.DefineVar(_T("vb"), Variable(&arr2));
  parser.DefineVar(_T("vc"), Variable(&arr3));
  parser.DefineVar(_T("vd"), Variable(&arr4));
  parser.DefineVar(_T("m1"), Variable(&m1));
  parser.DefineVar(_T("m2"), Variable(&m2));

  parser.DefineVar(_T("a"),  Variable(&fVal[0]));
  parser.DefineVar(_T("b"),  Variable(&fVal[1]));
  parser.DefineVar(_T("c"),  Variable(&fVal[2]));

  parser.DefineVar(_T("ca"), Variable(&cVal[0]));
  parser.DefineVar(_T("cb"), Variable(&cVal[1]));
  parser.DefineVar(_T("cc"), Variable(&cVal[2]));

  parser.DefineVar(_T("sa"), Variable(&sVal[0]));
  parser.DefineVar(_T("sb"), Variable(&sVal[1]));

  // Add functions for inspecting the parser properties
  parser.DefineFun(new FunListVar);
  parser.DefineFun(new FunListFunctions);
  parser.DefineFun(new FunListConst);
  parser.DefineFun(new FunBenchmark);
  parser.DefineFun(new FunEnableOptimizer);
  parser.DefineFun(new FunSelfTest);
  parser.DefineFun(new FunEnableDebugDump);
  parser.DefineFun(new FunTest0);
  parser.DefineFun(new FunPrint);

#if defined(_UNICODE)
  parser.DefineFun(new FunLang);
#endif

  parser.EnableAutoCreateVar(true);

#ifdef _DEBUG
//  ParserXBase::EnableDebugDump(1, 0);
#endif

  Value x = 1.0;
  Value y = std::complex<double>(0, 1);
  parser.DefineVar(_T("x"), Variable(&x));
  parser.DefineVar(_T("y"), Variable(&y));

  for(;;)
  {
    try
    {
      console() << sPrompt;

      string_type sLine;
      std::getline(mup::console_in(), sLine);

      if (sLine==_T("dbg"))
      {
        sLine   = _T("{?{{{{:44");
        mup::console() << sLine << endl;
      }

      switch(CheckKeywords(sLine.c_str(), parser))
      {
      case  0: break;
      case  1: continue;
      case -1: return;
      }

      parser.SetExpr(sLine);

      // The returned result is of type Value, value is a Variant like
      // type that can be either a boolean an integer or a floating point value
      ans = parser.Eval();
      {
        // Value supports C++ streaming like this:
        console() << _T("Result (type: '") << ans.GetType() <<  _T("'):\n");
        console() << _T("ans = ") << ans << _T("\n");
/*
        // Or if you need the specific type use this:
        switch (ans.GetType())
        {
        case 's': { std::string s = ans.GetString();               console() << s << " (string)"  << "\n"; } break;
        case 'i': { int i = ans.GetInteger();                      console() << i << " (int)"     << "\n"; } break;
        case 'f': { float_type f = ans.GetFloat();                 console() << f << " (float)"   << "\n"; } break;
        case 'c': { std::complex<float_type> c = ans.GetComplex(); console() << c << " (complex)" << "\n"; } break;
        case 'b': break;
        }
*/
      }
    }
    catch(ParserError &e)
    {
      if (e.GetPos()!=-1)
      {
        string_type sMarker;
        sMarker.insert(0, sPrompt.size() + e.GetPos(), ' ');
        sMarker += _T("^\n");
        console() << sMarker;
      }

      console() << e.GetMsg() << _T(" (Errc: ") << std::dec << e.GetCode() << _T(")") << _T("\n\n");

      //if (e.GetContext().Ident.length())
      //  console() << _T("Ident.: ") << e.GetContext().Ident << _T("\n");

      //if (e.GetToken().length())
      //  console() << _T("Token: \"") << e.GetToken() << _T("\"\n");
    } // try / catch
  } // for (;;)
}













//koniec miejsca na funkcje ******************************************************





















// MAIN ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc, char* argv[])
{

    ALLEGRO_DISPLAY *display = NULL, *input_display = NULL;
    ALLEGRO_BITMAP *graph_bitmap, *input_bitmap;
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    if (!al_init() || !al_install_keyboard()) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }
    al_init_primitives_addon();
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    display = al_create_display(width, hight);

display = al_create_display(w, h);
    graph_bitmap = al_get_backbuffer(display);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display,"wykres");







 // czesc gl�wna programu. Chce dowiedzie� si� kto gra i czego od �ycia chce

        cout<<"Witam w programie"<<endl<<"Zadaniem jest trafic w cel lub w innego zawodnika"<<endl<<"Za ka�de trafienie otrzymasz 1 punkt za trafienie w przeciwnika punkt�w 5"<<endl;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
event_queue = al_create_event_queue();


DODAWANIE();

//cout<<Player.id=1;

        //punkt celu podstawowego
        al_draw_circle(250,250,5,al_map_rgb(100,250,100),2);
            al_flip_display();

//wsp�lrz�dne srodka ukladu 200,200

string x;

for (int i=1; i<=3; i++){

    for (int j=1; j<=no_of_players-1; j++){
    cout<<"Runda gracza "<<j<<endl;
        wykres();

        cout<<"Pozostalo "<<4-i<<" prob"<<endl;
        RUNDA;
        cin>>x;

        Value (x);


        al_flip_display();

    };
};


    al_rest(5);
    al_destroy_display(display);



    return 0;
}
