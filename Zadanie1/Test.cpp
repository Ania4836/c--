/**
 * @file Test.cpp
 * @brief Testy funkcji z pliku Trojkat.h.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 * - Testowanie programu: https://uwf-fang.github.io/teaching/cpp/testing/testing/#simple-test-run
 * - Narzędzie ai: Claude Opus 5.5 (Anthropic, claude.ai), 
 * rozmowa z 16.11.2026 - pomoc przy pisaniu testów (załączona w sprawozdaniu)
 * 
 * Każdy test to jedno wywołanie assert. Jeśli warunek nie jest spełniony,
 * program zatrzymuje się i wypisuje numer linii z błędnym testem.
 *
 * Aby uruchomić program, trzeba wpisać:
 * g++ Zadanie1.cpp -o program
 * ./program
 *
 * g++ Test.cpp -o testy
 * ./testy
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include "Trojkat.h"
using namespace std;

const double EPS = 1e-9;
 
/**
 * @brief Testy funkcji heron.
 *
 * Typowe: trójkąt prostokątny, równoramienny, równoboczny, kolejność boków.
 * Brzegowe: bardzo małe i bardzo duże boki, trójkąt zdegenerowany (pole 0).
 */
void testHeron() {
    assert(fabs(heron(3, 4, 5) - 6) < EPS);
    assert(fabs(heron(5, 4, 3) - 6) < EPS);
    assert(fabs(heron(5, 5, 6) - 12) < EPS);
    assert(fabs(heron(2, 2, 2) - sqrt(3)) < EPS);
 
    assert(fabs(heron(0.001, 0.001, 0.001) - sqrt(3) / 4 * 0.000001) < EPS);
    assert(fabs(heron(1000, 1000, 1000) - sqrt(3) / 4 * 1000000) < 1e-6);
    assert(fabs(heron(1, 2, 3)) < EPS);
 
    cout << "testHeron: OK\n";
}
 
/**
 * @brief Testy funkcji czyTrojkat.
 *
 * Typowe: poprawne trójkąty i boki, z których trójkąta nie da się zbudować.
 * Brzegowe: suma dwóch boków równa trzeciemu (zdegenerowany),
 * suma tylko trochę większa od trzeciego boku.
 */
void testCzyTrojkat() {
    assert(czyTrojkat(3, 4, 5) == true);
    assert(czyTrojkat(1, 1, 1) == true);
    assert(czyTrojkat(1, 2, 10) == false);
    assert(czyTrojkat(10, 1, 2) == false);
    assert(czyTrojkat(1, 10, 2) == false);
 
    assert(czyTrojkat(1, 2, 3) == false);
    assert(czyTrojkat(3, 1, 2) == false);
    assert(czyTrojkat(1, 1, 1.999) == true);
 
    cout << "testCzyTrojkat: OK\n";
}
 
/**
 * @brief Testy funkcji poprawnyBok.
 *
 * Typowe: liczba dodatnia i ujemna.
 * Brzegowe: zero i bardzo mała liczba dodatnia.
 */
void testPoprawnyBok() {
    assert(poprawnyBok(5) == true);
    assert(poprawnyBok(-3) == false);
 
    assert(poprawnyBok(0) == false);
    assert(poprawnyBok(0.0001) == true);
 
    cout << "testPoprawnyBok: OK\n";
}
 
/**
 * @brief Testy funkcji wczytajBok.
 *
 * istringstream udaje wpisywanie z klawiatury.
 * Typowe: liczba całkowita, liczba z kropką, litery.
 * Brzegowe: zero, liczba ujemna, puste wejście.
 */
void testWczytajBok() {
    double x;
 
    istringstream calkowita("5");
    assert(wczytajBok(calkowita, x) == true);
    assert(x == 5);
 
    istringstream ulamek("2.5");
    assert(wczytajBok(ulamek, x) == true);
    assert(x == 2.5);
 
    istringstream litery("abc");
    assert(wczytajBok(litery, x) == false);
 
    istringstream zero("0");
    assert(wczytajBok(zero, x) == false);
 
    istringstream ujemna("-2");
    assert(wczytajBok(ujemna, x) == false);
 
    istringstream pusto("");
    assert(wczytajBok(pusto, x) == false);
 
    cout << "testWczytajBok: OK\n";
}
 
/**
 * @brief Uruchamia wszystkie testy.
 * @return 0, jeśli wszystkie testy przeszły
 */
int main() {
    testHeron();
    testCzyTrojkat();
    testPoprawnyBok();
    testWczytajBok();
    cout << "Wszystkie testy przeszly\n";
    return 0;
}