/**
 * @file Test.cpp
 * @brief Testy funkcji komplement, transkrybuj i transluj z pliku Genetyka.h.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Testowanie programu: https://uwf-fang.github.io/teaching/cpp/testing/testing/#simple-test-run
 * - Przykład translacji (MAMAPRTEINSTRING): https://rosalind.info/problems/prot/
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
#include <string>
#include "Genetyka.h"
using namespace std;

/**
 * @brief Typ wskaźnika na testowaną funkcję (string -> string).
 */
typedef string (*FunkcjaSekwencji)(const string&);

/**
 * @brief Sprawdza, czy funkcja f rzuca wyjątek invalid_argument dla danej sekwencji.
 * @param f testowana funkcja
 * @param sekwencja argument
 * @return true, jeśli został rzucony wyjątek invalid_argument
 */
bool rzucaWyjatek(FunkcjaSekwencji f, const string& sekwencja) {
    try {
        f(sekwencja);
    } catch (const invalid_argument&) {
        return true;
    }
    return false;
}

/**
 * @brief Sprawdza, czy sekwencja zawiera tylko dozwolone znaki.
 * @param sekwencja sprawdzana sekwencja
 * @param dozwolone dozwolone znaki
 * @return true, jeśli wszystkie znaki są dozwolone
 */
bool tylkoZnaki(const string& sekwencja, const string& dozwolone) {
    for (char z : sekwencja) {
        if (dozwolone.find(z) == string::npos) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Testy funkcji komplement.
 *
 * Typowe: krótkie sekwencje, sekwencja z dokumentacji (ATGC -> GCAT).
 * Brzegowe: jedna zasada, małe litery, palindrom (sekwencja równa
 * swojemu odwróconemu komplementowi), dwukrotny komplement daje sekwencję
 * wyjściową, wynik zawiera tylko A, C, G, T.
 * Błędne dane: pusta sekwencja, litera U, znak spoza alfabetu, spacja.
 */
void testKomplement() {
    assert(komplement("ATGC") == "GCAT");
    assert(komplement("AAAACCCGGT") == "ACCGGGTTTT");
    assert(komplement("ATGGCCTGA") == "TCAGGCCAT");

    assert(komplement("A") == "T");
    assert(komplement("G") == "C");
    assert(komplement("atgc") == "GCAT");
    assert(komplement("GAATTC") == "GAATTC");
    assert(komplement(komplement("ATGGCCTGA")) == "ATGGCCTGA");
    assert(tylkoZnaki(komplement("ACGTTGCA"), "ACGT"));

    assert(rzucaWyjatek(komplement, ""));
    assert(rzucaWyjatek(komplement, "AUGC"));
    assert(rzucaWyjatek(komplement, "ATGX"));
    assert(rzucaWyjatek(komplement, "AT GC"));

    cout << "testKomplement: OK\n";
}

/**
 * @brief Testy funkcji transkrybuj.
 *
 * Typowe: matryca daje RNA o kolejności zasad nici kodującej (z U zamiast T).
 * Brzegowe: jedna zasada, małe litery, połączenie z funkcją komplement
 * (transkrybuj(komplement(x)) to x z U zamiast T), wynik zawiera tylko A, C, G, U.
 * Błędne dane: pusta sekwencja, litera U (to już RNA), znak spoza alfabetu.
 */
void testTranskrybuj() {
    assert(transkrybuj("GCAT") == "AUGC");
    assert(transkrybuj("TCAGGCCAT") == "AUGGCCUGA");

    assert(transkrybuj("A") == "U");
    assert(transkrybuj("C") == "G");
    assert(transkrybuj("gcat") == "AUGC");
    assert(transkrybuj(komplement("GATGGAACTTGACTACGTAAATT")) == "GAUGGAACUUGACUACGUAAAUU");
    assert(tylkoZnaki(transkrybuj("ACGTTGCA"), "ACGU"));

    assert(rzucaWyjatek(transkrybuj, ""));
    assert(rzucaWyjatek(transkrybuj, "GCAU"));
    assert(rzucaWyjatek(transkrybuj, "GC-T"));

    cout << "testTranskrybuj: OK\n";
}

/**
 * @brief Testy funkcji transluj.
 *
 * Typowe: przykład MAMAPRTEINSTRING (Rosalind), krótkie białko.
 * Brzegowe: sekwencja przed kodonem start, każdy z trzech kodonów Stop,
 * sam kodon start i Stop (białko "M"), nukleotydy za kodonem Stop,
 * kodon Stop poza ramką odczytu (nie kończy translacji), małe litery.
 * Błędne dane: pusta sekwencja, litera T (to DNA), brak kodonu start,
 * brak kodonu Stop.
 */
void testTransluj() {
    assert(transluj("AUGGCCAUGGCGCCCAGAACUGAGAUCAAUAGUACCCGUAUUAACGGGUGA") == "MAMAPRTEINSTRING");
    assert(transluj("AUGUUUGGCUAA") == "MFG");

    assert(transluj("CCGAUGUUUUAA") == "MF");
    assert(transluj("AUGAAAUAG") == "MK");
    assert(transluj("AUGAAAUGA") == "MK");
    assert(transluj("AUGUAA") == "M");
    assert(transluj("AUGCCCUAAGGGCCC") == "MP");
    assert(transluj("AUGCUAAAGUGA") == "MLK");
    assert(transluj("augccuuaa") == "MP");

    assert(rzucaWyjatek(transluj, ""));
    assert(rzucaWyjatek(transluj, "ATGTAA"));
    assert(rzucaWyjatek(transluj, "CCCGGGUUU"));
    assert(rzucaWyjatek(transluj, "AUGCCCGGG"));
    assert(rzucaWyjatek(transluj, "AUGCCCGG"));

    cout << "testTransluj: OK\n";
}

/**
 * @brief Test całego procesu: nić kodująca -> nić matrycowa -> RNA -> białko.
 */
void testCalyProces() {
    string kodujaca = "ATGGCCATGGCGCCCAGAACTGAGATCAATAGTACCCGTATTAACGGGTGA";
    string matrycowa = komplement(kodujaca);
    string rna = transkrybuj(matrycowa);
    assert(rna == "AUGGCCAUGGCGCCCAGAACUGAGAUCAAUAGUACCCGUAUUAACGGGUGA");
    assert(transluj(rna) == "MAMAPRTEINSTRING");

    cout << "testCalyProces: OK\n";
}

/**
 * @brief Uruchamia wszystkie testy.
 * @return 0, jeśli wszystkie testy przeszły
 */
int main() {
    testKomplement();
    testTranskrybuj();
    testTransluj();
    testCalyProces();
    cout << "Wszystkie testy przeszly\n";
    return 0;
}
