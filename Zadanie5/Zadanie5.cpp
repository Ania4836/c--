/**
 * @file Zadanie5.cpp
 * @brief Program wypisujący elementy ciągu Collatza przed wpadnięciem w cykl.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Problem Collatza: https://pl.wikipedia.org/wiki/Problem_Collatza
 * - Sprawdzanie, czy cin wczytał liczbę:
 *   https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers
 * - Obsługa wyjątków try/catch: https://en.cppreference.com/w/cpp/language/try
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Aby uruchomić program, trzeba wpisać:
 * g++ Zadanie5.cpp -o program
 * ./program
 *
 * Aby uruchomić testy, trzeba wpisać:
 * g++ Test.cpp -o testy
 * ./testy
 *
 * Aby uruchomić eksperyment (maksymalna wartość i długość ciągu), trzeba wpisać:
 * g++ -O2 Eksperyment.cpp -o eksperyment
 * ./eksperyment
 */

#include <iostream>
#include <vector>
#include "Collatz.h"
using namespace std;

/**
 * @brief Wczytuje c0 i wypisuje elementy ciągu przed wpadnięciem w cykl.
 * @return 0, jeśli wypisano ciąg,1, jeśli c0 było niepoprawne
 */
int main() {
    long long c0;
    cout << "Podaj c0: ";
    if (!(cin >> c0)) {
        cout << "c0 musi byc liczba\n";
        return 1;
    }
    try {
        vector<unsigned long long> ciag = collatz(c0);
        cout << "Elementy przed cyklem (4, 2, 1):";
        for (unsigned long long c : ciag) {
            cout << ' ' << c;
        }
        cout << "\nLiczba elementow: " << ciag.size() << '\n';
    } catch (const exception& e) {
        cout << e.what() << '\n';
        return 1;
    }
    return 0;
}
