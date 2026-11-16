/**
 * @file Zadanie6.cpp
 * @brief Program wykonujący transkrypcję i translację dla podanej nici kodującej DNA.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Transkrypcja: https://pl.wikipedia.org/wiki/Transkrypcja_(biologia)
 * - Kod genetyczny: https://pl.wikipedia.org/wiki/Kod_genetyczny
 * - Obsługa wyjątków try/catch: https://en.cppreference.com/w/cpp/language/try
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Program wczytuje nić kodującą DNA i wypisuje nić matrycową,
 * sekwencję RNA i sekwencję białka.
 *
 * Aby uruchomić program, trzeba wpisać:
 * g++ Zadanie6.cpp -o program
 * ./program
 *
 * Aby uruchomić testy, trzeba wpisać:
 * g++ Test.cpp -o testy
 * ./testy
 */

#include <iostream>
#include <string>
#include "Genetyka.h"
using namespace std;

/**
 * @brief Wczytuje nić kodującą i wypisuje wyniki kolejnych etapów.
 * @return 0, jeśli wszystkie etapy się udały, 1 w przeciwnym razie
 */
int main() {
    string kodujaca;
    cout << "Podaj nic kodujaca DNA (5'->3'): ";
    cin >> kodujaca;
    try {
        string matrycowa = komplement(kodujaca);
        cout << "Nic matrycowa (5'->3'): " << matrycowa << '\n';
        string rna = transkrybuj(matrycowa);
        cout << "RNA (5'->3'):           " << rna << '\n';
        string bialko = transluj(rna);
        cout << "Bialko:                 " << bialko << '\n';
    } catch (const invalid_argument& e) {
        cout << e.what() << '\n';
        return 1;
    }
    return 0;
}
