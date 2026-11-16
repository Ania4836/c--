/**
 * @file Test.cpp
 * @brief Testy funkcji podzbiory z pliku Podzbiory.h.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Testowanie programu: https://uwf-fang.github.io/teaching/cpp/testing/testing/#simple-test-run
 * - Funkcja sort: https://en.cppreference.com/w/cpp/algorithm/sort
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
#include <algorithm>
#include "Podzbiory.h"
using namespace std;

/**
 * @brief Porządkuje listę podzbiorów, żeby można ją było porównać z oczekiwaną.
 *
 * Funkcja podzbiory może zwrócić podzbiory w dowolnej kolejności,
 * więc przed porównaniem sortujemy elementy w każdym podzbiorze
 * i całą listę podzbiorów.
 *
 * @param lista lista podzbiorów
 * @return posortowana lista podzbiorów
 */
vector<vector<char>> uporzadkuj(vector<vector<char>> lista) {
    for (vector<char>& p : lista) {
        sort(p.begin(), p.end());
    }
    sort(lista.begin(), lista.end());
    return lista;
}

/**
 * @brief Sprawdza, czy podzbiory(x) rzuca wyjątek invalid_argument.
 * @param x zbiór
 * @return true, jeśli został rzucony wyjątek
 */
bool rzucaWyjatek(const vector<char>& x) {
    try {
        podzbiory(x);
    } catch (const invalid_argument&) {
        return true;
    }
    return false;
}

/**
 * @brief Testy funkcji podzbiory dla poprawnych argumentów.
 *
 * Typowe: przykład z treści zadania {a, b, c, d}, zbiór {a, b, c}.
 * Brzegowe: zbiór pusty (jeden podzbiór: pusty), zbiór jednoelementowy,
 * zbiór o maksymalnej dozwolonej liczbie elementów.
 */
void testPodzbiory() {
    vector<vector<char>> oczekiwane = {
        {'a', 'b', 'c', 'd'},
        {'a', 'b', 'c'}, {'a', 'b', 'd'}, {'a', 'c', 'd'}, {'b', 'c', 'd'},
        {'a', 'b'}, {'a', 'c'}, {'a', 'd'}, {'b', 'c'}, {'b', 'd'}, {'c', 'd'},
        {'a'}, {'b'}, {'c'}, {'d'},
        {}
    };
    assert(uporzadkuj(podzbiory({'a', 'b', 'c', 'd'})) == uporzadkuj(oczekiwane));

    assert(uporzadkuj(podzbiory({'a', 'b', 'c'})) == uporzadkuj({
        {'a', 'b', 'c'}, {'a', 'b'}, {'a', 'c'}, {'b', 'c'}, {'a'}, {'b'}, {'c'}, {}
    }));

    assert(podzbiory({}) == vector<vector<char>>({{}}));
    assert(uporzadkuj(podzbiory({'x'})) == uporzadkuj({{'x'}, {}}));

    vector<char> duzy;
    for (size_t i = 0; i < MAKS_ELEMENTOW; i++) {
        duzy.push_back('A' + i);
    }
    assert(podzbiory(duzy).size() == ((size_t)1 << MAKS_ELEMENTOW));

    cout << "testPodzbiory: OK\n";
}

/**
 * @brief Testy sprawdzania poprawności argumentu funkcji podzbiory.
 *
 * Typowe: powtarzający się element.
 * Brzegowe: powtórzenie na końcu zbioru, zbiór o jeden element za duży,
 * poprawne zbiory nie rzucają wyjątku.
 */
void testPoprawnoscArgumentu() {
    assert(rzucaWyjatek({'a', 'a'}) == true);
    assert(rzucaWyjatek({'a', 'b', 'a'}) == true);

    assert(rzucaWyjatek({'a', 'b', 'c', 'c'}) == true);
    vector<char> zaDuzy;
    for (size_t i = 0; i < MAKS_ELEMENTOW + 1; i++) {
        zaDuzy.push_back('A' + i);
    }
    assert(rzucaWyjatek(zaDuzy) == true);
    assert(rzucaWyjatek({}) == false);
    assert(rzucaWyjatek({'a', 'b'}) == false);

    cout << "testPoprawnoscArgumentu: OK\n";
}

/**
 * @brief Uruchamia wszystkie testy.
 * @return 0, jeśli wszystkie testy przeszły
 */
int main() {
    testPodzbiory();
    testPoprawnoscArgumentu();
    cout << "Wszystkie testy przeszly\n";
    return 0;
}
