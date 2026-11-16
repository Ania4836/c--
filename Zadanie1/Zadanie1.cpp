/**
 *
 * @file Zadanie1.cpp
 * @brief Program obliczający pole trójkąta na podstawie długości jego boków.
 * @author Anna Maciążek, nr indeksu 276063
 * 
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Wzór Herona: https://pl.wikipedia.org/wiki/Wz%C3%B3r_Herona
 * - Funkcja sqrt: https://cpp0x.pl/dokumentacja/standard-C/sqrt/33$0
 * - Podstawy C++: https://www.galaxy.agh.edu.pl/~pamalino/programowanie/cpp/index.php
 * - Sprawdzanie, czy cin wczytał liczbę:
 * https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html

 * Program ten oblicza pole trójkąta na podstawie długości jego boków,
 * korzystając ze wzoru Herona.
 * Sprawdza również, czy podane długości boków mogą utworzyć trójkąt,
 * oraz czy wprowadzone wartości są dodatnimi liczbami.
 * 
 * Aby uruchomić program, trzeba wpisać:
 * g++ Zadanie1.cpp -o program
 * ./program
 *
 * g++ Test.cpp -o testy
 * ./testy
 */



#include <iostream>
#include "Trojkat.h"
using namespace std;


/**
 * @brief Wczytuje trzy boki, sprawdza je i wypisuje pole trójkąta.
 * @return 0, jeśli obliczono pole; 1, jeśli dane były niepoprawne
 * (nie liczba, liczba niedodatnia albo boki nie tworzą trójkąta)
 */

int main() {
    double a, b, c;
    cout << "Podaj bok a: ";
    if (!wczytajBok(cin, a)) {
        cout << "Bok musi byc liczba i byc dodatni\n";
        return 1;
    }
    cout << "Podaj bok b: ";
    if (!wczytajBok(cin, b)) {
        cout << "Bok musi byc liczba i byc dodatni\n";
        return 1;
    }
    cout << "Podaj bok c: ";
    if (!wczytajBok(cin, c)) {
        cout << "Bok musi byc liczba i byc dodatni\n";
        return 1;
    }
    if (!czyTrojkat(a, b, c)) {
        cout << "To nie jest trojkat\n";
        return 1;
    }
    cout << "Pole trojkata: " << heron(a, b, c) << '\n';
    return 0;
}