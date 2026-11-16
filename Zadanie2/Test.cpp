/**
 * @file Test.cpp
 * @brief Testy funkcji wspolne z pliku Multizbior.h.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Testowanie programu: https://uwf-fang.github.io/teaching/cpp/testing/testing/#simple-test-run
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 * - Narzędzie ai: Claude Opus 5.5 (Anthropic, claude.ai) - pomoc przy
 *   pisaniu testów.
 *
 * Każdy test to jedno wywołanie assert. Jeśli warunek nie jest spełniony,
 * program zatrzymuje się i wypisuje numer linii z błędnym testem.
 *
 * Aby uruchomić testy, trzeba wpisać:
 * g++ Test.cpp -o testy
 * ./testy
 */

#include <iostream>
#include <cassert>
#include <vector>
#include "Multizbior.h"
using namespace std;

/**
 * @brief Sprawdza, czy wspolne(x, y) rzuca wyjątek invalid_argument.
 * @param x pierwszy multizbiór
 * @param y drugi multizbiór
 * @return true, jeśli został rzucony wyjątek
 */
bool rzucaWyjatek(const vector<int>& x, const vector<int>& y) {
    try {
        wspolne(x, y);
    } catch (const invalid_argument&) {
        return true;
    }
    return false;
}

/**
 * @brief Testy funkcji wspolne dla poprawnych argumentów.
 *
 * Typowe: różne krotności, kolejność argumentów.
 * Brzegowe: puste multizbiory, brak wspólnych elementów,
 * identyczne multizbiory, różne długości wektorów.
 */
void testWspolne() {
    assert(wspolne({2, 0, 1}, {1, 3, 1}) == vector<int>({1, 0, 1}));
    assert(wspolne({1, 3, 1}, {2, 0, 1}) == vector<int>({1, 0, 1}));
    assert(wspolne({5, 2, 7}, {3, 4, 7}) == vector<int>({3, 2, 7}));

    assert(wspolne({}, {}) == vector<int>({}));
    assert(wspolne({}, {1, 2}) == vector<int>({}));
    assert(wspolne({2, 0}, {0, 3}) == vector<int>({0, 0}));
    assert(wspolne({1, 2, 3}, {1, 2, 3}) == vector<int>({1, 2, 3}));
    assert(wspolne({4, 1, 2, 5}, {2, 3}) == vector<int>({2, 1}));

    cout << "testWspolne: OK\n";
}

/**
 * @brief Testy sprawdzania poprawności argumentów funkcji wspolne.
 *
 * Typowe: ujemna krotność w x albo w y.
 * Brzegowe: ujemna krotność na końcu dłuższego wektora (poza częścią
 * wspólną długości), poprawne argumenty nie rzucają wyjątku.
 */
void testPoprawnoscArgumentow() {
    assert(rzucaWyjatek({-1, 2}, {1, 1}) == true);
    assert(rzucaWyjatek({1, 1}, {1, -2}) == true);

    assert(rzucaWyjatek({1, 1, -1}, {1}) == true);
    assert(rzucaWyjatek({0, 0}, {0, 0}) == false);
    assert(rzucaWyjatek({}, {}) == false);

    cout << "testPoprawnoscArgumentow: OK\n";
}

/**
 * @brief Uruchamia wszystkie testy.
 * @return 0, jeśli wszystkie testy przeszły
 */
int main() {
    testWspolne();
    testPoprawnoscArgumentow();
    cout << "Wszystkie testy przeszly\n";
    return 0;
}
