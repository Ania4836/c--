/**
 * @file Test.cpp
 * @brief Testy funkcji collatz z pliku Collatz.h.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Testowanie programu: https://uwf-fang.github.io/teaching/cpp/testing/testing/#simple-test-run
 * - Problem Collatza (przykład c0 = 27): https://pl.wikipedia.org/wiki/Problem_Collatza
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
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
#include <climits>
#include <algorithm>
#include "Collatz.h"
using namespace std;

/**
 * @brief Sprawdza, czy collatz(c0) rzuca wyjątek invalid_argument.
 * @param c0 argument
 * @return true, jeśli został rzucony wyjątek invalid_argument
 */
bool rzucaInvalidArgument(long long c0) {
    try {
        collatz(c0);
    } catch (const invalid_argument&) {
        return true;
    }
    return false;
}

/**
 * @brief Sprawdza, czy collatz(c0) rzuca wyjątek overflow_error.
 * @param c0 argument
 * @return true, jeśli został rzucony wyjątek overflow_error
 */
bool rzucaOverflowError(long long c0) {
    try {
        collatz(c0);
    } catch (const overflow_error&) {
        return true;
    }
    return false;
}

/**
 * @brief Testy funkcji collatz dla poprawnych argumentów.
 *
 * Typowe: c0 = 6, c0 = 3, c0 = 7, c0 = 27 (znany długi ciąg, maksimum 9232).
 * Brzegowe: c0 = 1, 2, 4 (od razu w cyklu, wynik pusty),
 * c0 = 8 i 16 (jeden i dwa kroki przed cyklem), c0 = 5 (wchodzi w cykl przez 16, 8).
 */
void testCollatz() {
    assert(collatz(6) == vector<unsigned long long>({6, 3, 10, 5, 16, 8}));
    assert(collatz(3) == vector<unsigned long long>({3, 10, 5, 16, 8}));
    assert(collatz(7) == vector<unsigned long long>({7, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8}));
    vector<unsigned long long> c27 = collatz(27);
    assert(c27.size() == 109);
    assert(*max_element(c27.begin(), c27.end()) == 9232);

    assert(collatz(1) == vector<unsigned long long>({}));
    assert(collatz(2) == vector<unsigned long long>({}));
    assert(collatz(4) == vector<unsigned long long>({}));
    assert(collatz(8) == vector<unsigned long long>({8}));
    assert(collatz(16) == vector<unsigned long long>({16, 8}));
    assert(collatz(5) == vector<unsigned long long>({5, 16, 8}));

    cout << "testCollatz: OK\n";
}

/**
 * @brief Testy sprawdzania poprawności argumentu funkcji collatz.
 *
 * Typowe: c0 ujemne.
 * Brzegowe: c0 = 0 (nie jest liczbą naturalną w sensie zadania),
 * c0 = 1 (najmniejsze poprawne, bez wyjątku),
 * c0 = LLONG_MAX (nieparzyste, 3 * c0 + 1 nie mieści się w typie).
 */
void testPoprawnoscArgumentu() {
    assert(rzucaInvalidArgument(-5) == true);

    assert(rzucaInvalidArgument(0) == true);
    assert(rzucaInvalidArgument(1) == false);
    assert(rzucaOverflowError(LLONG_MAX) == true);

    cout << "testPoprawnoscArgumentu: OK\n";
}

/**
 * @brief Uruchamia wszystkie testy.
 * @return 0, jeśli wszystkie testy przeszły
 */
int main() {
    testCollatz();
    testPoprawnoscArgumentu();
    cout << "Wszystkie testy przeszly\n";
    return 0;
}
