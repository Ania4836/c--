/**
 * @file Genetyka.h
 * @brief Funkcje do transkrypcji i translacji: komplement, transkrybuj, transluj.
 * @author Anna Maciążek, nr indeksu 276063
 *
 * Oświadczam, że kod w tym pliku został napisany samodzielnie,
 * z wykorzystaniem źródeł:
 * - Transkrypcja: https://pl.wikipedia.org/wiki/Transkrypcja_(biologia)
 * - Kod genetyczny (tabela kodonów): https://pl.wikipedia.org/wiki/Kod_genetyczny
 * - Klasa map: https://en.cppreference.com/w/cpp/container/map
 * - Funkcja toupper: https://en.cppreference.com/w/cpp/string/byte/toupper
 * - Wyjątek invalid_argument: https://en.cppreference.com/w/cpp/error/invalid_argument
 * - Dokumentacja kodu: https://www.doxygen.nl/manual/docblocks.html
 * - Narzędzie ai: Claude Opus 5.5 (Anthropic, claude.ai) - pomoc w podjęciu kilku decyzji
 *
 * Wszystkie sekwencje zapisywane są od końca 5' do końca 3'.
 * Dlatego nić matrycowa to odwrócony komplement nici kodującej,
 * a RNA to odwrócony komplement nici matrycowej (z U zamiast T),
 * czyli ma taką samą kolejność zasad jak nić kodująca.
 *
 * Przykład:
 * nić kodująca 5'-ATGC-3' -> nić matrycowa 5'-GCAT-3' -> RNA 5'-AUGC-3'
 */

#include <string>
#include <map>
#include <cctype>
#include <stdexcept>
using namespace std;

/**
 * @brief Sprawdza sekwencję i zamienia małe litery na wielkie.
 * @param sekwencja sekwencja do sprawdzenia
 * @param dozwolone dozwolone znaki (wielkie litery), np. "ACGT" dla DNA
 * @return sekwencja zapisana wielkimi literami
 * @throw invalid_argument jeśli sekwencja jest pusta albo zawiera
 * niedozwolony znak
 */
string sprawdzSekwencje(const string& sekwencja, const string& dozwolone) {
    if (sekwencja.empty()) {
        throw invalid_argument("Sekwencja nie moze byc pusta");
    }
    string wynik = sekwencja;
    for (char& z : wynik) {
        z = toupper(z);
        if (dozwolone.find(z) == string::npos) {
            throw invalid_argument("Niedozwolony znak w sekwencji");
        }
    }
    return wynik;
}

/**
 * @brief Zwraca zasadę komplementarną do zasady DNA (A-T, C-G).
 * @param z zasada DNA (A, C, G albo T)
 * @return zasada komplementarna
 */
char komplementarnaDNA(char z) {
    if (z == 'A') return 'T';
    if (z == 'T') return 'A';
    if (z == 'C') return 'G';
    return 'C';
}

/**
 * @brief Zwraca sekwencję nici matrycowej dla nici kodującej DNA.
 *
 * Nić matrycowa jest komplementarna do kodującej i biegnie w przeciwnym
 * kierunku, więc po zapisaniu od 5' do 3' jest odwróconym komplementem.
 *
 * @param kodujaca nić kodująca DNA (5'->3'), znaki A, C, G, T
 * (małe litery są zamieniane na wielkie)
 * @return nić matrycowa DNA (5'->3')
 * @throw invalid_argument jeśli sekwencja jest pusta albo zawiera znak inny niż A, C, G, T
 */
string komplement(const string& kodujaca) {
    string dna = sprawdzSekwencje(kodujaca, "ACGT");
    string wynik = "";
    for (int i = dna.size() - 1; i >= 0; i--) {
        wynik += komplementarnaDNA(dna[i]);
    }
    return wynik;
}

/**
 * @brief Zwraca sekwencję RNA powstałą na podstawie nici matrycowej DNA.
 *
 * Polimeraza RNA czyta matrycę od 3' do 5' i dobudowuje zasady
 * komplementarne (A-U, T-A, C-G, G-C), więc RNA (5'->3') to odwrócony
 * komplement matrycy z U zamiast T.
 *
 * @param matrycowa nić matrycowa DNA (5'->3'), znaki A, C, G, T
 * (małe litery są zamieniane na wielkie)
 * @return sekwencja RNA (5'->3'), znaki A, C, G, U
 * @throw invalid_argument jeśli sekwencja jest pusta albo zawiera znak inny niż A, C, G, T
 */
string transkrybuj(const string& matrycowa) {
    string dna = sprawdzSekwencje(matrycowa, "ACGT");
    string wynik = "";
    for (int i = dna.size() - 1; i >= 0; i--) {
        char z = komplementarnaDNA(dna[i]);
        if (z == 'T') {
            z = 'U';
        }
        wynik += z;
    }
    return wynik;
}

/**
 * @brief Tabela kodu genetycznego: kodon RNA -> aminokwas (kod 1-literowy).
 *
 * Kodony Stop (UAA, UAG, UGA) oznaczone są znakiem '*'.
 */
const map<string, char> KOD_GENETYCZNY = {
    {"UUU", 'F'}, {"UUC", 'F'}, {"UUA", 'L'}, {"UUG", 'L'},
    {"CUU", 'L'}, {"CUC", 'L'}, {"CUA", 'L'}, {"CUG", 'L'},
    {"AUU", 'I'}, {"AUC", 'I'}, {"AUA", 'I'}, {"AUG", 'M'},
    {"GUU", 'V'}, {"GUC", 'V'}, {"GUA", 'V'}, {"GUG", 'V'},
    {"UCU", 'S'}, {"UCC", 'S'}, {"UCA", 'S'}, {"UCG", 'S'},
    {"CCU", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'},
    {"ACU", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'},
    {"GCU", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'},
    {"UAU", 'Y'}, {"UAC", 'Y'}, {"UAA", '*'}, {"UAG", '*'},
    {"CAU", 'H'}, {"CAC", 'H'}, {"CAA", 'Q'}, {"CAG", 'Q'},
    {"AAU", 'N'}, {"AAC", 'N'}, {"AAA", 'K'}, {"AAG", 'K'},
    {"GAU", 'D'}, {"GAC", 'D'}, {"GAA", 'E'}, {"GAG", 'E'},
    {"UGU", 'C'}, {"UGC", 'C'}, {"UGA", '*'}, {"UGG", 'W'},
    {"CGU", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'},
    {"AGU", 'S'}, {"AGC", 'S'}, {"AGA", 'R'}, {"AGG", 'R'},
    {"GGU", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'}
};

/**
 * @brief Zwraca sekwencję białka kodowanego przez mRNA (kody 1-literowe).
 *
 * Translacja zaczyna się od pierwszego kodonu start AUG (metionina, M)
 * i trwa do pierwszego kodonu Stop (UAA, UAG, UGA) w tej samej ramce
 * odczytu. Kodon Stop nie jest dopisywany do białka.
 *
 * @param mrna sekwencja mRNA (5'->3'), znaki A, C, G, U
 * (małe litery są zamieniane na wielkie)
 * @return sekwencja białka w kodzie 1-literowym, zaczynająca się od M
 * @throw invalid_argument jeśli sekwencja jest pusta, zawiera znak inny
 * niż A, C, G, U, nie zawiera kodonu start AUG albo po kodonie start
 * nie ma kodonu Stop
 */
string transluj(const string& mrna) {
    string rna = sprawdzSekwencje(mrna, "ACGU");
    size_t start = rna.find("AUG");
    if (start == string::npos) {
        throw invalid_argument("Brak kodonu start AUG");
    }
    string bialko = "";
    for (size_t i = start; i + 3 <= rna.size(); i += 3) {
        char aminokwas = KOD_GENETYCZNY.at(rna.substr(i, 3));
        if (aminokwas == '*') {
            return bialko;
        }
        bialko += aminokwas;
    }
    throw invalid_argument("Brak kodonu Stop");
}
