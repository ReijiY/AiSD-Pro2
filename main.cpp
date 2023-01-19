﻿#include <iostream>
#include <vector>

#include "projekt.h"

// algorytm sortowania gnoma
std::vector<int> gnome_sort(std::vector<int> array);
// algorytm sortowania kubełkowego
std::vector<int> bucket_sort(std::vector<int> array, std::pair<int, int> range);

// funkcja wywołująca testy czasów na obu algorytmach
std::vector<std::vector<double>> testy(int ilosc_testow, int start_w, int start_h, int multiplier, int ilosc_watkow);

int main()
{
    pro::init();

    std::pair<int, int> range{ -1, 1 };

    auto tab = pro::generuj_losowy_ciag(range.first, range.second, 10);
    auto sorted_gnome = gnome_sort(tab);
    auto sorted_bucket = bucket_sort(tab, range);

    std::cout << "\n\n";

    pro::wypisz_ciag(tab);
    pro::wypisz_ciag(sorted_gnome);
    pro::wypisz_ciag(sorted_bucket);

    return 0;
}

// algorytm sortowania gnoma
std::vector<int> gnome_sort(std::vector<int> array)
{
    if (array.size() <= 1) return array;

    // iterator przechowujący aktualną pozycję w tablicy
    size_t i = 1;
    // iterator przechowujący następną nie posortowaną pozycję
    size_t j = 2;

    // dopóki iterator "i" ma mniejszą wartość niż jest liczb w tablicy
    while (i < array.size())
    {
        // jeżeli i jest równe 0 lub 
        // liczba na lewo od liczby wskazywanej przez iterator jest niewiększa niż liczba, którą wskazuje ten iterator
        if (i == 0 || array[i - 1] <= array[i])
        {
            // przypisz do iteratora "i" element następnej 
            i = j;
            // zwiększ wartość następnej pozycji do sprawdzenia
            j++;
        }
        // jeżeli liczba na lewo od sprawdzanej jest od niej mniejsza
        else
        {
            // zamień te dwie liczby miejscami
            std::swap(array[i - 1], array[i]);;
            // zmniejsz wartość iteratora
            i--;
        }

    }

    // zwróć wartość posortowanego ciągu
    return array;
}

// algorytm sortowania kubełkowego
std::vector<int> bucket_sort(std::vector<int> array, std::pair<int, int> range)
{
    // zwrócenie ciągu jako posortowany, jeżeli jego rozmiar jest niewiększy niż 1
    if (array.size() <= 1) return array;
    // wyrzucenie błędu, jeżeli zakres danych jest niepoprawny
    if (range.second - range.first < 0) throw "Podany zakres danych jest niepoprawny!\n";

    // obliczenie rozmiaru tablicy liczników
    int range_size = range.second - range.first + 1;

    // definicja tablicy liczników
    std::vector<int> buckets;
    // zanicjowanie tablicy liczników wartościami zerowymi
    buckets.resize(range_size);

    // dla każdego elementu w tablicy
    for (const int& el : array)
        // zwiększenie wartość licznika o indeksie tego elementu
        if (buckets[el - range.first]++);

    // definicja iteratora "i" przechodzącego przez tablice liczników
    int i = 0;

    // definicja iteratora "j" wskazującego następne nienadpisane pole w tabeli wejściowej
    int j = 0;

    // dla każdego i w zakresie tablicy liczników
    while (i < range_size)
    {
        // dopóki licznik wskazywany przez indeks "i" jest większy od zera
        while (buckets[i] > 0)
        {
            // wpisanie do tablicy wejściowej na pierwszym nienadpisanym indeksie sumy wartości iteratora "i" oraz początku zakresu danych
            array[j] = i + range.first;
            // inkrementacja wskaźnika na nienadpisaną pozycję
            ++j;
            // dekrementacja licznika
            --buckets[i];
        }
        i++;
    }

    // zwracanie tablicy wejściowej nadpisanej posortowanymi wartościami
    return array;
}