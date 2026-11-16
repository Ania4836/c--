/**
 * @file Trojkat.h
 * @brief Funkcje do obliczania pola trójkąta i sprawdzania danych wejściowych.
 * @author Anna Maciążek, nr indeksu 276063
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Wzór Herona: https://pl.wikipedia.org/wiki/Wz%C3%B3r_Herona
 * - Warunek istnienia trójkąta (nierówność trójkąta):
 *   https://pl.wikipedia.org/wiki/Nier%C3%B3wno%C5%9B%C4%87_tr%C3%B3jk%C4%85ta
 * - Funkcja sqrt: https://cpp0x.pl/dokumentacja/standard-C/sqrt/33$0
 * - Sprawdzanie, czy cin wczytał liczbę:
 *   https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 * - Narzędzie AI: Claude Opus 5.5 (Anthropic, claude.ai), rozmowa z 16.11.2026 – pomoc przy
 *   wydzieleniu kodu do funkcji (poprawnyBok, wczytajBok, czyTrojkat).
 */

#include <cmath>
#include <iostream>
using namespace std;

/**
 * @brief Sprawdza, czy długość boku jest dodatnia.
 * @param x długość boku
 * @return true, jeśli x > 0, false w przeciwnym razie (też dla x = 0)
 */
bool poprawnyBok(double x) {
    return x > 0;
}
 
/**
 * @brief Wczytuje długość boku ze strumienia i sprawdza jej poprawność.
 *
 * Dzięki temu, że funkcja przyjmuje dowolny strumień, w programie można
 * przekazać cin (klawiatura), a w testach istringstream (gotowy tekst).
 *
 * @param wejscie strumień, z którego wczytywana jest liczba
 * @param bok zmienna, do której zostanie zapisana wczytana wartość
 * @return true, jeśli wczytano liczbę dodatnią, false, jeśli wpisano coś,
 *         co nie jest liczbą (np. literę), wejście było puste
 *         albo liczba nie jest dodatnia
 */
bool wczytajBok(istream& wejscie, double& bok) {
    return (wejscie >> bok) && poprawnyBok(bok);
}
 
/**
 * @brief Sprawdza, czy z boków a, b, c można zbudować trójkąt.
 *
 * Korzysta z nierówności trójkąta: suma każdych dwóch boków musi być
 * większa od trzeciego boku. Gdy suma jest równa trzeciemu bokowi,
 * trójkąt jest zdegenerowany (odcinek) i funkcja zwraca false.
 *
 * @param a długość boku a
 * @param b długość boku b
 * @param c długość boku c
 * @return true, jeśli boki tworzą trójkąt, false w przeciwnym razie
 */
bool czyTrojkat(double a, double b, double c) {
    return a + b > c && a + c > b && b + c > a;
}
 
/**
 * @brief Oblicza pole trójkąta ze wzoru Herona.
 *
 * Pole = sqrt(p * (p - a) * (p - b) * (p - c)), gdzie p = (a + b + c) / 2
 * to połowa obwodu.
 *
 * @pre Boki a, b, c są dodatnie i tworzą trójkąt (zobacz czyTrojkat).
 * @param a długość boku a
 * @param b długość boku b
 * @param c długość boku c
 * @return pole trójkąta
 */
double heron(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}