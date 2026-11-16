/**
 * @file Zadanie4.cpp
 * @brief Program wypisujący n pierwszych elementów ciągu Fibonacciego.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Ciąg Fibonacciego: https://pl.wikipedia.org/wiki/Ci%C4%85g_Fibonacciego
 * - Sprawdzanie, czy cin wczytał liczbę:
 *   https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers
 * - Obsługa wyjątków try/catch: https://en.cppreference.com/w/cpp/language/try
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Program wczytuje n i wypisuje n pierwszych elementów ciągu Fibonacciego
 * obliczonych iteracyjnie i rekurencyjnie.
 *
 * Aby uruchomić program, trzeba wpisać:
 * g++ Zadanie4.cpp -o program
 * ./program
 *
 * Aby uruchomić testy, trzeba wpisać:
 * g++ Test.cpp -o testy
 * ./testy
 */

#include <iostream>
#include <vector>
#include "Fibonacci.h"
using namespace std;

/**
 * @brief Wypisuje elementy ciągu oddzielone spacjami.
 * @param ciag elementy do wypisania
 */
void wypiszCiag(const vector<unsigned long long>& ciag) {
    for (unsigned long long element : ciag) {
        cout << element << ' ';
    }
    cout << '\n';
}

/**
 * @brief Wczytuje n i wypisuje ciąg Fibonacciego obiema metodami.
 * @return 0, jeśli wypisano ciąg, 1, jeśli n było niepoprawne
 */
int main() {
    int n;
    cout << "Podaj n: ";
    if (!(cin >> n)) {
        cout << "n musi byc liczba\n";
        return 1;
    }
    try {
        cout << "Iteracyjnie:    ";
        wypiszCiag(fibonacciIteracyjnie(n));
        cout << "Rekurencyjnie:  ";
        wypiszCiag(fibonacciRekurencyjnie(n));
    } catch (const exception& e) {
        cout << '\n' << e.what() << '\n';
        return 1;
    }
    return 0;
}
