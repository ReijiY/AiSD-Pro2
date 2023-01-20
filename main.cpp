#include <iostream>
#include <vector>
#include <math.h>

#include "projekt.h"

// funkcja wywołująca testy czasów na obu algorytmach
std::vector<std::vector<double>> testy(int ilosc_testow, int start_len, std::pair<int, int> range, int multiplier);

// algorytm sortowania gnoma
std::vector<int> gnome_sort(std::vector<int> array);
// algorytm sortowania kubełkowego
std::vector<int> bucket_sort(std::vector<int> array, std::pair<int, int> range);

// funkcja testująca poprawność wykonania algorytmów sortowania
void test_sort(const std::vector<int>& arr)
{
    // dla każdego elementu tablicy zaczynając od 1
    for (size_t i = 1; i < arr.size(); i++)
        // wyrzuć błąd, jeżeli poprzedni element jest większy
        if (arr[i - 1] > arr[i]) throw std::string("Przeprowadzono bledne sortowanie!");
}

int main()
{
    // inicjalizacja funkcji pomocniczych
    pro::init();

    // stworzenie wybranego zakresu początkowego dla wszystkich testów
    std::pair<int, int> range = { 0, 1 };

    // wykonanie trzech zestawów testów
    for (int i = 1; i <= 3; i++)
    {

        // przechwytywanie wszystkich błędów typu std::string
        try
        {
            // wpisanie wyników testów do tabeli
            auto wyniki = testy(8, 1000, range, 2);

            // zapisanie tabeli do pliku odpowiadającego zestawowi testów
            std::string filename = std::string("test/Testy ") + std::to_string(i) + ".txt";
            pro::zapisz_ciag_2d_do_pliku(filename.c_str(), wyniki);
            std::cout << "Wyniki zapisane w pliku " << filename << "\n";
        }
        catch (std::string& e)
        {
            // wypisanie przechwyconego błędu
            std::cout << "Error: " << e << "\n";
        }

        range.first *= 500;
        range.second *= 500;
    }



    return 0;
}

// funkcja wywołująca testy czasów na obu algorytmach
std::vector<std::vector<double>> testy(int ilosc_testow, int start_len, std::pair<int, int> range_, int multiplier)
{
    // inicjalizacja struktur czasu
    std::chrono::high_resolution_clock::time_point start, stop;
    std::chrono::duration<double> timediff;

    // definicja tabeli wyników czasów trwania i obliczeń
    std::vector<std::vector<double>> wyniki;
    std::vector<int> wynik_obliczen;

    int arr_len;

    // dla podanej ilości testów
    for (int nr_testu = 0; nr_testu < ilosc_testow; nr_testu++)
    {
        // obliczanie mnożnika dla aktualnego numeru testu
        int mp_pow = std::pow(multiplier, nr_testu);

        // obliczenie zakresu losowanych liczb
        std::pair<int, int> range = { range_.first * mp_pow, range_.second * mp_pow };

        // obliczanie długości generowanego ciągu
        arr_len = start_len * mp_pow;

        // definicja tablicy przechowującej wyniki pojedyńczego testu
        std::vector<double> zebrane_dane;

        // wpisanie ilości danych do wyników
        zebrane_dane.push_back(arr_len);

        std::cout << "Test nr: " << nr_testu + 1 << "\n";
        std::cout << "Generowanie tablicy o rozmiarze " << arr_len << " i zakresie danych " << range.first << " do " << range.second << "\n";

        // generowanie ciągu o zadanych parametrach
        auto data = pro::generuj_losowy_ciag(range.first, range.second, arr_len);

        std::cout << "Tablica wejsciowa: ";
        pro::opisz_ciag(data);

        // wykonanie testu dla pierwszego algorytmu z pomiarem czasu
        std::cout << "Start A:\n";
        start = std::chrono::high_resolution_clock::now();
        wynik_obliczen = gnome_sort(data);
        stop = std::chrono::high_resolution_clock::now();
        // sprawdzenie poprawności wyników
        test_sort(wynik_obliczen);

        // obliczenie czasu trwania algorytmu
        timediff = stop - start;

        // wpisanie czasu do wyników
        zebrane_dane.push_back(timediff.count());
        std::cout << "Czas wykonania algorytmu A: " << timediff.count() << "\n";
        std::cout << "Ilosc wynikow: " << wynik_obliczen.size() << "\n";

        // wykonanie testu dla drugiego algorytmu z pomiarem czasu
        std::cout << "Start B:\n";
        start = std::chrono::high_resolution_clock::now();
        wynik_obliczen = bucket_sort(data, range);
        stop = std::chrono::high_resolution_clock::now();
        // sprawdzenie poprawności wyników
        test_sort(wynik_obliczen);

        // obliczenie czasu trwania algorytmu
        timediff = stop - start;

        // wpisanie czasu do wyników
        zebrane_dane.push_back(timediff.count());
        std::cout << "Czas wykonania algorytmu B: " << timediff.count() << "\n";
        std::cout << "Ilosc wynikow: " << wynik_obliczen.size() << "\n";

        std::cout << "<int>";
        pro::opisz_ciag(wynik_obliczen);
        std::cout << "\n";

        // wpisanie wyników do zwracanej tabeli
        wyniki.push_back(zebrane_dane);

    }

    return wyniki;
}

// algorytm sortowania gnoma
std::vector<int> gnome_sort(std::vector<int> array)
{
    if (array.size() <= 1) return array;

    // iterator przechowujący aktualną pozycję w tablicy
    size_t i = 1;
    // iterator przechowujący następną nieposortowaną pozycję
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
        buckets[el - range.first]++;

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
