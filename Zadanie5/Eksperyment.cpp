/**
 * @file Eksperyment.cpp
 * @brief Szuka maksymalnej wartości elementu i maksymalnej długości ciągu Collatza.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Problem Collatza: https://pl.wikipedia.org/wiki/Problem_Collatza
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Dla każdego c0 od 1 do N program liczy ciąg funkcją collatz i zapamiętuje:
 * - największy element, jaki pojawił się w którymkolwiek ciągu, i jego c0,
 * - najdłuższy ciąg (liczba elementów przed cyklem) i jego c0.
 * Przy remisie zapamiętywane jest najmniejsze c0.
 *
 * Wyniki (długość = liczba elementów przed wpadnięciem w cykl (4, 2, 1)):
 *
 * Dla wszystkich sprawdzonych c0 ciąg ostatecznie wpadł w cykl (4, 2, 1).
 *
 * Aby uruchomić eksperyment, trzeba wpisać:
 * g++ -O2 Eksperyment.cpp -o eksperyment
 * ./eksperyment
 */

#include <iostream>
#include <vector>
#include "Collatz.h"
using namespace std;

/**
 * @brief Przeprowadza eksperyment dla c0 od 1 do N i wypisuje wyniki.
 * @param N największe sprawdzane c0
 */
void eksperyment(long long N) {
    unsigned long long maksWartosc = 0;
    long long c0MaksWartosci = 0;
    size_t maksDlugosc = 0;
    long long c0MaksDlugosci = 0;

    for (long long c0 = 1; c0 <= N; c0++) {
        vector<unsigned long long> ciag = collatz(c0);
        for (unsigned long long c : ciag) {
            if (c > maksWartosc) {
                maksWartosc = c;
                c0MaksWartosci = c0;
            }
        }
        if (ciag.size() > maksDlugosc) {
            maksDlugosc = ciag.size();
            c0MaksDlugosci = c0;
        }
    }

    cout << "c0 od 1 do " << N << ":\n";
    cout << "  maksymalna wartosc elementu: " << maksWartosc << " (dla c0 = " << c0MaksWartosci << ")\n";
    cout << "  maksymalna dlugosc ciagu:    " << maksDlugosc << " (dla c0 = " << c0MaksDlugosci << ")\n";
}

/**
 * @brief Uruchamia eksperyment dla kilku zakresów c0.
 * @return 0
 */
int main() {
    eksperyment(10);
    eksperyment(100);
    eksperyment(1000);
    eksperyment(10000);
    eksperyment(100000);
    eksperyment(1000000);
    return 0;
}
