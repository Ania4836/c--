/**
 * @file Collatz.h
 * @brief Funkcja zwracająca elementy ciągu Collatza przed wpadnięciem w cykl (4, 2, 1).
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Problem Collatza: https://pl.wikipedia.org/wiki/Problem_Collatza
 * - Wyjątki invalid_argument i overflow_error:
 *   https://en.cppreference.com/w/cpp/error/invalid_argument
 *   https://en.cppreference.com/w/cpp/error/overflow_error
 * - Typ unsigned long long i jego zakres: https://en.cppreference.com/w/cpp/types/climits
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 * - Narzędzie AI: Claude Opus 5.5 (Anthropic, claude.ai) - pomoc w pisaniu kodu
 *
 * Ciąg Collatza: c(n+1) = c(n) / 2, gdy c(n) jest parzyste,
 *                c(n+1) = 3 * c(n) + 1, gdy c(n) jest nieparzyste.
 */

#include <vector>
#include <stdexcept>
#include <climits>
using namespace std;

/**
 * @brief Sprawdza, czy liczba należy do cyklu (4, 2, 1).
 * @param c liczba do sprawdzenia
 * @return true, jeśli c jest równe 4, 2 albo 1
 */
bool wCyklu(unsigned long long c) {
    return c == 4 || c == 2 || c == 1;
}

/**
 * @brief Zwraca elementy ciągu Collatza przed wpadnięciem w cykl (4, 2, 1).
 *
 * Funkcja zaczyna od c0 i liczy kolejne elementy, dopóki nie trafi na
 * element cyklu (4, 2 albo 1). Elementy cyklu nie są dopisywane do wyniku.
 * Na przykład dla c0 = 6 ciąg to 6, 3, 10, 5, 16, 8, 4, 2, 1, ...
 * więc funkcja zwraca {6, 3, 10, 5, 16, 8}.
 * Dla c0 = 1, 2 albo 4 ciąg od razu jest w cyklu, więc wynik jest pusty.
 *
 * @param c0 pierwszy element ciągu (liczba naturalna, c0 >= 1)
 * @return wektor elementów ciągu przed wpadnięciem w cykl
 * @throw invalid_argument jeśli c0 < 1
 * @throw overflow_error jeśli kolejny element nie zmieściłby się
 * w typie unsigned long long
 */
vector<unsigned long long> collatz(long long c0) {
    if (c0 < 1) {
        throw invalid_argument("c0 musi byc liczba naturalna (c0 >= 1)");
    }
    vector<unsigned long long> wynik;
    unsigned long long c = c0;
    while (!wCyklu(c)) {
        wynik.push_back(c);
        if (c % 2 == 0) {
            c = c / 2;
        } else {
            if (c > (ULLONG_MAX - 1) / 3) {
                throw overflow_error("Element ciagu nie miesci sie w typie");
            }
            c = 3 * c + 1;
        }
    }
    return wynik;
}
