/**
 * @file Test.cpp
 * @brief Testy funkcji fibonacciIteracyjnie i fibonacciRekurencyjnie z pliku Fibonacci.h.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Testowanie programu: https://uwf-fang.github.io/teaching/cpp/testing/testing/#simple-test-run
 * - Ciąg Fibonacciego: https://pl.wikipedia.org/wiki/Ci%C4%85g_Fibonacciego
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
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
#include "Fibonacci.h"
using namespace std;

/**
 * @brief Typ wskaźnika na funkcję liczącą ciąg, żeby te same testy
 *        uruchomić dla obu wariantów.
 */
typedef vector<unsigned long long> (*FunkcjaFibonacci)(int);

/**
 * @brief Sprawdza, czy funkcja f(n) rzuca wyjątek invalid_argument.
 * @param f testowana funkcja
 * @param n argument
 * @return true, jeśli został rzucony wyjątek invalid_argument
 */
bool rzucaInvalidArgument(FunkcjaFibonacci f, int n) {
    try {
        f(n);
    } catch (const invalid_argument&) {
        return true;
    }
    return false;
}

/**
 * @brief Sprawdza, czy funkcja f(n) rzuca wyjątek out_of_range.
 * @param f testowana funkcja
 * @param n argument
 * @return true, jeśli został rzucony wyjątek out_of_range
 */
bool rzucaOutOfRange(FunkcjaFibonacci f, int n) {
    try {
        f(n);
    } catch (const out_of_range&) {
        return true;
    }
    return false;
}

/**
 * @brief Testy jednego wariantu funkcji dla poprawnych argumentów.
 *
 * Typowe: n = 5 i n = 10.
 * Brzegowe: n = 0 (pusty wektor), n = 1, n = 2 (przypadki bazowe rekursji),
 * n = MAKS_N (ostatni element mieszczący się w typie).
 *
 * @param f testowana funkcja (wariant iteracyjny albo rekurencyjny)
 */
void testPoprawneN(FunkcjaFibonacci f) {
    assert(f(5) == vector<unsigned long long>({0, 1, 1, 2, 3}));
    assert(f(10) == vector<unsigned long long>({0, 1, 1, 2, 3, 5, 8, 13, 21, 34}));

    assert(f(0) == vector<unsigned long long>({}));
    assert(f(1) == vector<unsigned long long>({0}));
    assert(f(2) == vector<unsigned long long>({0, 1}));
    assert(f(3) == vector<unsigned long long>({0, 1, 1}));
    assert(f(MAKS_N).size() == MAKS_N);
    assert(f(MAKS_N).back() == 12200160415121876738ULL);
}

/**
 * @brief Testy sprawdzania warunków początkowych jednego wariantu funkcji.
 *
 * Typowe: n ujemne, n dużo za duże.
 * Brzegowe: n = -1, n = MAKS_N + 1, a n = 0 i n = MAKS_N nie rzucają wyjątku.
 *
 * @param f testowana funkcja (wariant iteracyjny albo rekurencyjny)
 */
void testWyjatki(FunkcjaFibonacci f) {
    assert(rzucaInvalidArgument(f, -5) == true);
    assert(rzucaOutOfRange(f, 1000) == true);

    assert(rzucaInvalidArgument(f, -1) == true);
    assert(rzucaOutOfRange(f, MAKS_N + 1) == true);
    assert(rzucaInvalidArgument(f, 0) == false);
    assert(rzucaOutOfRange(f, MAKS_N) == false);
}

/**
 * @brief Sprawdza, czy oba warianty dają ten sam wynik dla każdego n od 0 do MAKS_N.
 */
void testZgodnosc() {
    for (int n = 0; n <= MAKS_N; n++) {
        assert(fibonacciIteracyjnie(n) == fibonacciRekurencyjnie(n));
    }
    cout << "testZgodnosc: OK\n";
}

/**
 * @brief Uruchamia wszystkie testy dla obu wariantów.
 * @return 0, jeśli wszystkie testy przeszły
 */
int main() {
    testPoprawneN(fibonacciIteracyjnie);
    testWyjatki(fibonacciIteracyjnie);
    cout << "fibonacciIteracyjnie: OK\n";

    testPoprawneN(fibonacciRekurencyjnie);
    testWyjatki(fibonacciRekurencyjnie);
    cout << "fibonacciRekurencyjnie: OK\n";

    testZgodnosc();
    cout << "Wszystkie testy przeszly\n";
    return 0;
}
