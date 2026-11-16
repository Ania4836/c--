/**
 * @file Zadanie3.cpp
 * @brief Program wypisujący wszystkie podzbiory zadanego zbioru.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Zbiór potęgowy: https://pl.wikipedia.org/wiki/Zbi%C3%B3r_pot%C4%99gowy
 * - Wczytywanie całej linii (getline): https://en.cppreference.com/w/cpp/string/basic_string/getline
 * - Obsługa wyjątków try/catch: https://en.cppreference.com/w/cpp/language/try
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Program wczytuje elementy zbioru (pojedyncze znaki, bez spacji)
 * i wypisuje wszystkie jego podzbiory.
 *
 * Aby uruchomić program, trzeba wpisać:
 * g++ Zadanie3.cpp -o program
 * ./program
 *
 * Aby uruchomić testy, trzeba wpisać:
 * g++ Test.cpp -o testy
 * ./testy
 */

#include <iostream>
#include <string>
#include <vector>
#include "Podzbiory.h"
using namespace std;

/**
 * @brief Wypisuje zbiór w postaci {a, b, c}.
 * @param z zbiór do wypisania
 */
void wypiszZbior(const vector<char>& z) {
    cout << '{';
    for (size_t i = 0; i < z.size(); i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << z[i];
    }
    cout << '}';
}

/**
 * @brief Wczytuje zbiór i wypisuje wszystkie jego podzbiory.
 * @return 0, jeśli wypisano podzbiory, 1, jeśli zbiór był niepoprawny
 */
int main() {
    string linia;
    cout << "Podaj elementy zbioru (np. abcd, pusta linia = zbior pusty): ";
    getline(cin, linia);
    vector<char> x(linia.begin(), linia.end());

    try {
        vector<vector<char>> wynik = podzbiory(x);
        cout << "Liczba podzbiorow: " << wynik.size() << '\n';
        for (const vector<char>& p : wynik) {
            wypiszZbior(p);
            cout << '\n';
        }
    } catch (const invalid_argument& e) {
        cout << e.what() << '\n';
        return 1;
    }
    return 0;
}
