/**
 * @file Podzbiory.h
 * @brief Funkcja zwracająca wszystkie podzbiory zadanego zbioru.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Zbiór potęgowy: https://pl.wikipedia.org/wiki/Zbi%C3%B3r_pot%C4%99gowy
 * - Operatory bitowe: https://en.cppreference.com/w/cpp/language/operator_arithmetic
 * - Wyjątek invalid_argument: https://en.cppreference.com/w/cpp/error/invalid_argument
 * - Klasa vector: https://en.cppreference.com/w/cpp/container/vector
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 *
 * Zbiór zapisany jest jako wektor znaków, np. {a, b, c} to {'a', 'b', 'c'}.
 */

#include <vector>
#include <stdexcept>
using namespace std;

/**
 * @brief Największa dozwolona liczba elementów zbioru (2^20 to ok. milion podzbiorów).
 */
const size_t MAKS_ELEMENTOW = 20;

/**
 * @brief Zwraca listę wszystkich podzbiorów zbioru x.
 *
 * Zbiór n-elementowy ma 2^n podzbiorów. Każdemu podzbiorowi odpowiada
 * liczba od 0 do 2^n - 1: jeśli i-ty bit tej liczby jest równy 1,
 * to i-ty element zbioru należy do podzbioru.
 * Na przykład dla x = {a, b, c} liczba 5 = 101 (binarnie) oznacza {a, c}.
 *
 * @param x zbiór (elementy nie mogą się powtarzać)
 * @return lista wszystkich 2^n podzbiorów zbioru x (łącznie z pustym i całym x)
 * @throw invalid_argument jeśli elementy x się powtarzają
 *        albo x ma więcej niż MAKS_ELEMENTOW elementów
 */
vector<vector<char>> podzbiory(const vector<char>& x) {
    if (x.size() > MAKS_ELEMENTOW) {
        throw invalid_argument("Zbior ma za duzo elementow");
    }
    for (size_t i = 0; i < x.size(); i++) {
        for (size_t j = i + 1; j < x.size(); j++) {
            if (x[i] == x[j]) {
                throw invalid_argument("Elementy zbioru nie moga sie powtarzac");
            }
        }
    }

    size_t n = x.size();
    size_t liczbaPodzbiorow = (size_t)1 << n;
    vector<vector<char>> wynik;
    for (size_t maska = 0; maska < liczbaPodzbiorow; maska++) {
        vector<char> podzbior;
        for (size_t i = 0; i < n; i++) {
            if (maska & ((size_t)1 << i)) {
                podzbior.push_back(x[i]);
            }
        }
        wynik.push_back(podzbior);
    }
    return wynik;
}
