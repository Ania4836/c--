/**
 * @file Multizbior.h
 * @brief Funkcja obliczająca część wspólną dwóch multizbiorów.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Multizbiór i jego część wspólna: https://pl.wikipedia.org/wiki/Multizbi%C3%B3r
 * - Wyjątek invalid_argument: https://en.cppreference.com/w/cpp/error/invalid_argument
 * - Klasa vector: https://en.cppreference.com/w/cpp/container/vector
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Multizbiór zapisany jest jako wektor krotności:
 * x[i] mówi, ile razy element i występuje w multizbiorze.
 * Na przykład {0, 0, 2} zapisujemy jako [2, 0, 1]
 * (element 0 dwa razy, element 1 zero razy, element 2 raz).
 */

#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

/**
 * @brief Zwraca część wspólną dwóch multizbiorów.
 *
 * Element występuje w części wspólnej tyle razy, ile wynosi mniejsza
 * z jego krotności w x i w y.
 * Jeśli wektory mają różne długości, brakujące krotności traktowane są
 * jako 0, więc wynik ma długość krótszego wektora.
 *
 * @param x pierwszy multizbiór (wektor krotności)
 * @param y drugi multizbiór (wektor krotności)
 * @return wektor krotności części wspólnej x i y
 * @throw invalid_argument jeśli któraś krotność jest ujemna
 */
vector<int> wspolne(const vector<int>& x, const vector<int>& y) {
    for (int k : x) {
        if (k < 0) {
            throw invalid_argument("Krotnosc nie moze byc ujemna");
        }
    }
    for (int k : y) {
        if (k < 0) {
            throw invalid_argument("Krotnosc nie moze byc ujemna");
        }
    }

    size_t n = min(x.size(), y.size());
    vector<int> wynik(n);
    for (size_t i = 0; i < n; i++) {
        wynik[i] = min(x[i], y[i]);
    }
    return wynik;
}
