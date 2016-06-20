GraphWar
================
Łukasz Filipiuk, Maciej Naduk

Wstęp
=====

Graph-War jest grą, w której walka tyczy się w układzie kartezjańskim. Twoim celem jest ominięcie wszystkich przeszkód i zestrzelenie wszystkim "pionków" przeciwnika przy pomocy funkcji matematycznych.

Dostępna składnia:

-   Operatory:
    -   + -
    -   * / %
    -   ^
    -   !
-   Funkcje:
    -   Abs, Exp, Sign, Log, Log10, Sqrt
    -   Sin, Cos, Tan, ASin, ACos, ATan
    -   Factorial
-   Stałe:
    -   Pi
    -   e

Instalacja
==========

Przy użyciu instalatora
-----------------------
[![Instalacja](http://puu.sh/pyQNr/60d289cedc.jpg)](https://vimeo.com/171339077)

Można skorzystać z dołączonego instalatora, jednak okazuje się, że nie na wszystkich komputerach działa on poprawnie. Najbardziej pewną metodą będzie instalacia przy pomocy *CodeBlocks*. Ta wersja jest także mniej odporna na błędy.

<a href="https://1drv.ms/u/s!AoVZ4kCCppbc8iJe7g4u25rprlQd">Pobierz instalator (.exe)</a>

<a href="https://1drv.ms/u/s!AoVZ4kCCppbc8iH0U5gLIpyqc6UD">Pobierz instalator (.msi)</a>

Instalacja przy użyciu CodeBlocks
---------------------------------
[![Instalacja](http://puu.sh/pyPxl/ebe0d2342f.jpg)](https://vimeo.com/171338304)

<a href="https://1drv.ms/f/s!AoVZ4kCCppbc8iQjrPlmubDhJFMF">Pobierz pliki</a>

Do projektu, z poprawnie skonfigurowaną biblioteką *Allegro* należy dołączyć następujące pliki i foldery:

-   Foldery:
    -   Images
    -   Sounds
    -   Fonts
-   Pliki:
    -   constants.h
    -   error.cpp
    -   error.h
    -   functions.cpp
    -   functions.h
    -   parser.cpp
    -   parser.h
    -   variablelist.cpp
    -   variablelist.h
    -   Main.cpp

Foldery zawierają grafiki, dźwięki oraz fonty niezbędne do poprawnego działania programu.

Powyższe pliki pochodzą ze strony internetowej <http://www.speqmath.com/tutorials/expression_parser_cpp/> i zawierają kod, który pozwala na odczytywanie funkcji.

Dodatkowo, do pliku Main.cpp należy wkleić kod z dołączonego pliku Main.cpp.

Prawidłowy układ plików z folderze z projektem powinien wyglądać następująco: <img src="http://puu.sh/pyCN6/105e52792c.png">

Aby dodać pliki .cpp oraz pliki nagłówkowe do projektu, należy otworzyć projekt, a następnie każdy a plików. Po kliknięciu prawym przyciskiem myszy w zakładkę z danym plikiem należy wybrać *Add file to active project.* <img src="http://puu.sh/pyD72/c4cccb285a.png">

Prawidłowy projekt w CodeBlocks powinien wyglądać następująco: <img src="http://puu.sh/pyCSU/6b3a44d07a.png">

Menu główne
===========

Ekran menu głównego: <img src="http://puu.sh/pyDCH/0181170e3d.png">

W menu głównym, użytkownik może: \* Ustalić nick dla każdego z graczy (w przypadku braku, zostanie przydzielony domyślny) \* Wybrać liczbę pionków po każdej stronie pola bitwy (minimum 1, maksimum 4). \* START - rozpoczęcie gry \* WCZYTAJ - wczytanie zapisanego stanu gry (o ile istnieje) \* ZAMKNIJ - zamknięcie gry

Rozgrywka
=========

Przykładowa rozgrywka:
----------------
[![Instalacja](http://puu.sh/pyR8T/a314a0b91c.jpg)](https://vimeo.com/171339926)


Ekran rozgrywki:
----------------

<img src="http://puu.sh/pyEcm/3cb46cd73d.png">

Ekran rozgrywki składa się z losowo wygenerowanej mapy z przeszkodami oraz pionkami. Pionki gracza pierwszego mają kolor niebieski, a drugiego - kolor czerwony. Aktywny gracz jest podświetlony. Układ współrzędnych narysowany jest dla (25 ≤ x ≤ 25) oraz (15 ≤ y ≤ 15)

Menu ekranu rozgrywki składa się z: \* okna do wpisywania funkcji. Długość funkcji nie jest ograniczona przez wielkość pola tekstowego - gracz może wyjść poza nie. \* zegara - informuje on gracz, ile czasu pozostało mu do końca tury (przez ostatnie 5 włącza się dźwięk odliczania)

Przyciski:
----------

### Aktywny gracz

Czasem samo podświetlenie aktywnego pionka może nie wystarczyć - w związku z tym, po naciśnięciu klawisza **TAB** zostanie wywołana krótka animacja pokazująca aktywny pionek.

### Zapis gry

<img src="http://puu.sh/pyEe8/bc361edcf2.png">

Aby zapisać grę, należy nacisnąć klawisz **F4** - po zapisaniu gry, możliwa będzie dalsza rozgrywka.

### Wyjście z gry

Aby wyjść z gry, należy nacisnąć klawisz **ESC** - gracze zostaną przeniesieni do ekranu początkowego.

Przebieg rozgrywki
------------------

Gracze strzelają na przemian - zawsze z lewej strony układu współrzędnych.

<img src="http://puu.sh/pyFhd/fc8302744a.png">

W przypadku trafienia w przeszkodę wyświetlana jest animacja wybuchu.

<img src="http://puu.sh/pyFos/8a6b1ece38.png">

Podobnie w przypadku trafienia w gracza.

<img src="http://puu.sh/pyFtU/ab0d405bf9.png">

Gra kończy się, kiedy na planszy pozostają pionki tylko jednego gracza.

<img src="http://puu.sh/pyFw8/ec257863a6.png">

Ciekawe funkcje
===============

Wartość bezwzględna
-------------------

<img src="http://puu.sh/pyGmy/45c6c7e3de.png">

Podwójna wartość bezwzględna
----------------------------

<img src="http://puu.sh/pyGMx/4b57918a89.png">

Lorentzian function
-------------------

<img src="http://puu.sh/pyHiz/b8ae37ea24.png">

Funkcja sinc
------------

<img src="http://puu.sh/pyHZC/dd125d5ec6.png">

Funkcja skokowa Heavyside'a
---------------------------

<img src="http://puu.sh/pyIOg/f53ee72e48.png">

Kamehameha
----------

<img src="http://puu.sh/pyK1E/34061e1f7f.png">
