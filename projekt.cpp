#include "projekt.h"


void pro::init()
{
	// podanie wartości czasu do generatora liczb losowych
	srand(time(NULL));
}

inline int pro::losowa_liczba(int min, int max)
{
	// zwrócenie losowej liczby z przedziału [min, max]
	return rand() % ((max + 1) - min) + min;
}

std::vector<int> pro::generuj_losowy_ciag(int min, int max, int width)
{
	// weryfikacja kolejności argumentów w podanym zakresie
	if (min > max) std::swap(min, max);

	// utworzenie n-elementowego kontenera na losowy ciag
	std::vector<int> res(width);

	// generator losujący wartości z przedziału [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// wypełnienie losowego ciągu wartościami losowanymi przez generator
	std::generate(res.begin(), res.end(), gen);

	//zwrócenie utworzonej tablicy
	return res;
}

std::vector<std::vector<int>> pro::generuj_losowy_ciag_2d(int min, int max, int width, int height)
{
	// utworzenie kontenera na losowe ciągi
	std::vector<std::vector<int>> res;
	
	// zmiana rozmiaru kontenera na h-elementowy
	res.resize(height);

	// generator losujący wartości z przedziału [min, max]
	auto gen = [&min, &max]() {
		return losowa_liczba(min, max);
	};

	// dla każdego elementu kontenera
	for (auto &el : res)
	{
		// wpisanie pustego ciągu o rozmiarze w
		el = std::vector<int>(width);
		
		// wypełnienie losowego ciągu wartościami losowanymi przez generator
		std::generate(el.begin(), el.end(), gen);
	}

	//zwrócenie utworzonej tablicy
	return res;
}

std::vector<int> pro::generuj_ciag_z_zakresu(int start, int end, int step)
{
	// weryfikacja kolejności argumentów w podanym zakresie
	if (start > end) std::swap(start, end);

	// krok nie może być równy 0
	if (step == 0) step = 1;

	// utworzenie kontenera na ciag
	std::vector<int> res;

	// przewidziany rozmiar koncowy kontenera
	int rozmiar_kontenera = (end - start) / step + 1;

	// zmiana rozmiaru kontenera na końcową ilość elementów
	res.resize(rozmiar_kontenera);

	// indeks następnego elementu tablicy
	int i = 0;

	// dla iteratora opisanego argumentami funkcji
	for (int iterator = start; iterator <= end; iterator += step)
	{
		// wpisanie wartości iteratora do tablicy
		res[i++] = iterator;
	}


	// zwracanie utworzonej tablicy
	return res;
}

std::vector<int>::iterator pro::quicksort_iterator_partition(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
	// zabezpieczenie przed wywołaniem na niewłaściwym zakresie
	if (std::distance(start, end) <= 0) return end;

	// wybranie wartości pierwszego elementu zakresu jako elementu środkowego
	int pivot = *start;

	// wyznaczenie pozycji elementu dzielącego poprzez policzenie elementów o mniejszej lub tej samej wartości
	int count = 0;
	// dla iteratora przechodzącego od drugiego elementu do końca przedziału
	for (std::vector<int>::iterator it = start + 1; it != end; it++) {
		// jeżeli wartość wskazywana przez iterator jest mniejsza lub równa wartości pivot
		if (*it <= pivot)
		{
			// zwiększ licznik
			count++;
		}
	}

	// stworzenie iteratora na wyliczonej pozycji
	std::vector<int>::iterator pivot_index = start + count;
	// zamienienie wartości pierwszego elementu i elementu na wyznaczonym iteratorze
	std::swap(*pivot_index, *start);

	// stworzenie iteratorów wskazujących na pierwszy i ostatni element ciągu
	std::vector<int>::iterator it_1 = start, it_2 = end - 1;

	// dopóki oba iteratory nie przekroczyły indeksu wartości pivot
	while (it_1 < pivot_index && it_2 > pivot_index) {

		// dopóki wartość pierwszego iteratora jest mniejsza lub równa wartości pivot
		while (*it_1 <= pivot) {
			// zwiększ pierwszy iterator
			++it_1;
		}

		// dopóki wartość drugiego iteratora jest większa od wartości pivot
		while (*it_2 > pivot) {
			// zmniejsz drugi iterator
			--it_2;
		}

		// jeżeli pierwszy iterator jest mniejszy od indeksu pivota i drugi iterator jest od niego większy
		if (it_1 < pivot_index && it_2 > pivot_index) {
			// zamień ze sobą wartości wskazywane przez iteratory
			std::swap(*it_1++, *it_2--);
		}
	}

	// zwróć iterator wskazujący na wartość pivota
	return pivot_index;
}

void pro::quicksort_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	// zabezpieczenie przed wywołaniem na niewłaściwym zakresie oraz warunek kończący pracę funckji rekurencyjnej
	if (std::distance(begin, end) <= 0) return;

	// podział ciągu na dwie części z wartościami odpowiednio mniejszymi i większymi od pierwszego elementu
	std::vector<int>::iterator p = pro::quicksort_iterator_partition(begin, end);

	// wykonanie sortowania na pierwszej połowie podzielonego ciągu
	pro::quicksort_iterator(begin, p);

	// wykonanie sortowania na drugiej połowie podzielonego ciągu
	pro::quicksort_iterator(p + 1, end);
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> pro::quicksort_iterator_three_way_partition(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
	// iterator wskazujący pierwszy element w zakresie
	std::vector<int>::iterator mid = start;
	// wartość, względem której wykonujemy porównania wybrana jako ostani element z zakresu
	int pivot = *(end - 1);

	// dopóki iterator mid i end są inne (operujemy na iteratorze przekazanym jako argument)
	while (mid != end)
	{
		// jeżeli wartość ekementu wskazywanego przez iterator mid jest mniejsza niż wartość pivot
		if (*mid < pivot)
		{
			// zamień miejscami element wskazywany przez mid z pierwszym elementem w ciągu
			std::swap(*start, *mid);
			// przesuń początek ciągu i iterator mid do przodu o 1 element
			++start;
			++mid;
		}
		// jeżeli wartość ekementu wskazywanego przez iterator mid jest większa niż wartość pivot
		else if (*mid > pivot)
		{
			// zamień miejscami element wskazywany przez mid z ostatnim elementem w ciągu
			std::swap(*mid, *(end - 1));
			// zmniejsz długość ciągu o 1
			--end;
		}
		// w przeciwnym wypadku
		else
		{
			// przesuń iterator do przodu
			++mid;
		}
	}

	// ciąg [start ... mid] zawiera wszystkie wystąpienia wartości równych zmiennej pivot
	// zwróć iteratory start i mid
	return { start, mid };
}

void pro::quicksort_three_way_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	// jeżeli ciąg jest długości niewiększej od 1 to jest już posortowany
	if (std::distance(begin, end) <= 1)
	{
		return;
	}

	// jeżeli ciąg ma 2 elementy
	if (std::distance(begin, end) == 2)
	{
		// jeżeli pierwszy element jest większy od drugiego
		if (*begin > *(begin + 1))
		{
			// zamień je miejscami
			std::swap(*begin, *(begin + 1));
		}
		return;
	}

	// oblicz zakresy następnych obszarów do posortowania
	auto pivot = pro::quicksort_iterator_three_way_partition(begin, end);

	// posortuj lewą część tablicy
	pro::quicksort_three_way_iterator(begin, pivot.first);

	// posortuj prawą część tablicy
	pro::quicksort_three_way_iterator(pivot.second, end);
}

std::vector<int>::iterator pro::linear_search_iterator(std::vector<int>& arr, int val)
{
	// stworzenie iteratora początku z tablicy wejściowej
	auto it = arr.begin();
	// dopóki iterator nie dotarł do końca tablicy
	while (it != arr.end())
	{
		// jeżeli wartość wskazywana przez iterator jest równa wartości szukanej zwróć ten iterator
		if (*it == val) return it;
		// zwiększ wartość iteratora
		it++;
	}
	// zwróć iterator równy końcowi tablicy (brak wyników)
	return it;
}

std::vector<int>::iterator pro::set_intersection(const std::vector<int>& arr1, const std::vector<int>& arr2, std::vector<int>::iterator res)
{
	// swtorzenie iteratorów z danych wejściowych
	std::vector<int>::const_iterator first1 = arr1.begin(), last1 = arr1.end(), first2 = arr2.begin(), last2 = arr2.end();

	// dopóki iterator żadnej z tablicy nie dotarł do jej końca
	while (first1 != last1 && first2 != last2) 
	{
		// jeżeli wartość wskazywana przez pierwszy iterator jest mniejsza niż wartość wskazywana przez drugi iterator
		if (*first1 < *first2) 
		{
			// zwiększ pierwszy iterator
			++first1;
		}
		// w przeciwnym wypadku, jeżeli wartość wskazywana przez drugi iterator jest mniejsza od wartości wskazywanej przez pierwszy iterator
		else if (*first2 < *first1)
		{
			// zwiększ drugi operator
			++first2;
		}
		// w przeciwnych wypadkach
		else 
		{
			// w tym momencie wiemy, że pierwszy i drugi iterator wskazują na taką samą wartość
			// wpisz wartość wskazywaną przez pierwszy iterator do pamięci wskazywanej przez iterator tablicy z wynikami
			*res = *first1;
			
			// zwiększ iterator tablicy z wynikami oraz pierwszej i drugiej tablicy
			++res;
			++first1;
			++first2;
		}
	}
	// zwróć iterator tablicy z wynikami
	return res;
}

void pro::opisz_ciag(const std::vector<int>& arr)
{
	// wypisanie rozmiaru ciągu
	std::cout << "[" << arr.size() << "]\n";
}

void pro::opisz_ciag(const std::vector<std::vector<int>>& arr)
{
	// jeżeli tablica posiada wiersze
	if (arr.size() > 0)
	{
		// sprawdzenie czy wiersze są tej samej długości

		int i, j, size = 0;

		// dla każdego wiersza
		for (i = 0; i < arr.size(); i++)
		{
			// przypisanie wartości tego wiersza do zmiennej
			size = arr[i].size();

			// dla każdego następnego wiersza
			for (j = i + 1; j < arr.size(); j++)
			{
				// jeżeli długość wiersza jest inna niż wartość zapisanej zmiennej
				if (arr[j].size() != size)
				{
					// przerwij pętlę
					break;
				}
			}

			// jeżeli pętla została przerwana
			if (j < arr.size())
			{
				// przerwij szukanie różnych wierszy
				break;
			}
		}

		// jeżeli pętla została przerwana
		if (i < arr.size())
		{
			// wypisz nieznaną szerokość
			std::cout << "[?x" << arr.size() << "]\n";

			// zakończ wykonywanie funkcji
			return;
		}

		// jeżeli nie znaleziono różnych długości wierszy
		// wypisz wymiary ostatniego sprawdzonego wiersza na ilość wierszy
		std::cout << "[" << size << "x" << arr.size() << "]\n";
	}

	// wypisz brak elementów
	std::cout << "[0x" << 0 << "]\n";
}

std::vector<int> pro::odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter)
{
	// otwarcie pliku do odczytu
	std::fstream ifs(nazwa_pliku, std::ios::in);

	// weryfikacja otwarcia pliku
	if (!ifs.good())
		// błąd przy próbie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do odczytu!";

	// utworzenie tablicy na wartości odczytane z pliku
	std::vector<int> arr;

	// dla każdego łańcucha znaków, oddzielonego znakiem końca wartości, odczytanego z pliku
	for (std::string el; std::getline(ifs, el, delimiter); )
		// wpisanie do tablicy wartości przekonwertowanej na liczbę
		arr.push_back(atoi(el.c_str()));

	// zwrócenie tablicy z wartościami
	return arr;
}

std::vector<std::vector<int>> pro::odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val, char delimiter_array)
{
	// otwarcie pliku do odczytu
	std::fstream ifs(nazwa_pliku, std::ios::in);

	// weryfikacja otwarcia pliku
	if (!ifs.good())
		// błąd przy próbie otwarcia pliku
		throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do odczytu!";

	// utworzenie tablic na wartości odczytane z pliku
	std::vector<std::vector<int>> data;
	std::vector<int> arr;

	// dla każdego łańcucha znaków, oddzielonego znakiem końca tablicy, odczytanego z pliku
	for (std::string line_str; std::getline(ifs, line_str, delimiter_array); )
	{
		// wyczyszczenie tablicy wartości
		arr.clear();

		// przypisanie odczytanego łańcucha znaków do strumienia tekstowego
		std::stringstream line(line_str);

		// dla każdego łańcucha znaków, oddzielonego znakiem końca wartości, ze strumienia tekstowego
		for (std::string el; std::getline(line, el, delimiter_val); )
		{
			// wpisanie do tablicy wartości przekonwertowanej na liczbę
			arr.push_back(atoi(el.c_str()));
		}
		
		// wpisanie do tablicy dwuwymiarowej odczytanych wartości w postaci tablicy
		data.push_back(arr);
	}
		

	// zwrócenie dwuwymiarowej tablicy z wartościami
	return data;
}


std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator> pro::thread_bounds(const std::vector<std::vector<int>>& data, int thread_count, int thread_id)
{
	// odczytanie ilości wierszy w tablicy dla operacji
	int data_size = data.size();

	// zmienna przechowująca indeks wątku, który jako pierwszy posiada mniej elementów od wątku o indeksie o jeden mniejszym
	int break_point = data_size % thread_count;

	// obliczenie ilości wierszy, za których przetworzenie ma być odpowiedzialny wątek o podanym numerze
	int weight_sum = thread_id < break_point ? data_size / thread_count + 1 : data_size / thread_count;

	// oblicznenie indeksu początku danych przydzielonych dla wątku o podanym numerze
	int data_before = break_point - 1 < thread_id ? weight_sum * thread_id + break_point : weight_sum * thread_id;

	// utworzenie iteratorów początku i końca danych
	auto first = data.begin() + data_before;
	auto last = first + weight_sum;

	
	if (std::distance(first, last) < 0) {
		std::cout << "\n first > last !!! \n";
	}

	if (std::distance(data.begin(), first) < 0) {
		std::cout << "\n first < data.begin() !!! \n";
	}

	if (std::distance(last, data.end()) < 0) {
		std::cout << "\n last > data.end() !!! \n";
	}

	// zwrócenie pary iteratorów jako wyniku obliczeń
	return std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator>(first, last);
}