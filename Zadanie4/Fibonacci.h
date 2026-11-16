/**
 * @file Fibonacci.h
 * @brief Funkcje zwracające n pierwszych elementów ciągu Fibonacciego
 * (wersja iteracyjna i rekurencyjna).
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Ciąg Fibonacciego: https://pl.wikipedia.org/wiki/Ci%C4%85g_Fibonacciego
 * - Rekurencja: https://pl.wikipedia.org/wiki/Rekurencja
 * - Wyjątki invalid_argument i out_of_range:
 *   https://en.cppreference.com/w/cpp/error/invalid_argument
 *   https://en.cppreference.com/w/cpp/error/out_of_range
 * - Typ unsigned long long: https://en.cppreference.com/w/cpp/language/types
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 * - Narzędzie ai: Claude Opus 5.5 (Anthropic, claude.ai) - 
 * pomoc przy wybraniu najwiekszego dozwolonego n (załączona w sprawozdaniu)
 *
 * Ciąg Fibonacciego zaczyna się od 0 i 1, a każdy kolejny element
 * jest sumą dwóch poprzednich: 0, 1, 1, 2, 3, 5, 8, 13, ...
 */

#include <vector>
#include <stdexcept>
using namespace std;

/**
 * @brief Największe dozwolone n.
 *
 * Element o numerze 93 (licząc od 0) to 12200160415121876738 i jest
 * największym elementem ciągu, który mieści się w typie unsigned long long.
 * Dla większego n wynik byłby błędny (przepełnienie).
 */
const int MAKS_N = 94;

/**
 * @brief Sprawdza warunki początkowe dla n.
 * @param n liczba elementów ciągu
 * @throw invalid_argument jeśli n jest ujemne
 * @throw out_of_range jeśli n > MAKS_N (elementy nie zmieściłyby się w typie)
 */
void sprawdzN(int n) {
    if (n < 0) {
        throw invalid_argument("n nie moze byc ujemne");
    }
    if (n > MAKS_N) {
        throw out_of_range("n jest za duze, wynik nie zmiescilby sie w typie");
    }
}

/**
 * @brief Zwraca n pierwszych elementów ciągu Fibonacciego (wersja z pętlą).
 * @param n liczba elementów (0 <= n <= MAKS_N)
 * @return wektor n pierwszych elementów ciągu; dla n = 0 wektor pusty
 * @throw invalid_argument jeśli n jest ujemne
 * @throw out_of_range jeśli n > MAKS_N
 */
vector<unsigned long long> fibonacciIteracyjnie(int n) {
    sprawdzN(n);
    vector<unsigned long long> wynik;
    for (int i = 0; i < n; i++) {
        if (i < 2) {
            wynik.push_back(i);
        } else {
            wynik.push_back(wynik[i - 1] + wynik[i - 2]);
        }
    }
    return wynik;
}

/**
 * @brief Zwraca n pierwszych elementów ciągu Fibonacciego (wersja rekurencyjna).
 *
 * Funkcja wywołuje samą siebie dla n - 1, a potem dopisuje na końcu
 * jeden element: sumę dwóch ostatnich. Przypadki bazowe to n = 0, 1, 2.
 *
 * @param n liczba elementów (0 <= n <= MAKS_N)
 * @return wektor n pierwszych elementów ciągu; dla n = 0 wektor pusty
 * @throw invalid_argument jeśli n jest ujemne
 * @throw out_of_range jeśli n > MAKS_N
 */
vector<unsigned long long> fibonacciRekurencyjnie(int n) {
    sprawdzN(n);
    if (n == 0) {
        return {};
    }
    if (n == 1) {
        return {0};
    }
    if (n == 2) {
        return {0, 1};
    }
    vector<unsigned long long> wynik = fibonacciRekurencyjnie(n - 1);
    wynik.push_back(wynik[n - 2] + wynik[n - 3]);
    return wynik;
}
