/**
 * @file Zadanie2.cpp
 * @brief Program obliczający część wspólną dwóch multizbiorów.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Multizbiór i jego część wspólna: https://pl.wikipedia.org/wiki/Multizbi%C3%B3r
 * - Obsługa wyjątków try/catch: https://en.cppreference.com/w/cpp/language/try
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Program wczytuje dwa multizbiory zapisane jako wektory krotności
 * i wypisuje ich część wspólną.
 *
 * Aby uruchomić program, trzeba wpisać:
 * g++ Zadanie2.cpp -o program
 * ./program
 *
 * Aby uruchomić testy, trzeba wpisać:
 * g++ Test.cpp -o testy
 * ./testy
 */

#include <iostream>
#include <vector>
#include "Multizbior.h"
using namespace std;

/**
 * @brief Wczytuje multizbiór: najpierw liczbę krotności, potem same krotności.
 * @param nazwa nazwa multizbioru wyświetlana użytkownikowi
 * @param m wektor, do którego zostaną zapisane krotności
 * @return true, jeśli wczytano same liczby, false w przeciwnym razie
 */
bool wczytajMultizbior(const char* nazwa, vector<int>& m) {
    int n;
    cout << "Podaj liczbe krotnosci w " << nazwa << ": ";
    if (!(cin >> n) || n < 0) {
        return false;
    }
    m.resize(n);
    cout << "Podaj " << n << " krotnosci: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> m[i])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Wczytuje dwa multizbiory i wypisuje ich część wspólną.
 * @return 0, jeśli obliczono wynik, 1, jeśli dane były niepoprawne
 */
int main() {
    vector<int> x, y;
    if (!wczytajMultizbior("x", x) || !wczytajMultizbior("y", y)) {
        cout << "Trzeba podac liczby\n";
        return 1;
    }
    try {
        vector<int> w = wspolne(x, y);
        cout << "Czesc wspolna:";
        for (int k : w) {
            cout << ' ' << k;
        }
        cout << '\n';
    } catch (const invalid_argument& e) {
        cout << e.what() << '\n';
        return 1;
    }
    return 0;
}
