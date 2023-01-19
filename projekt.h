/**
 * \file   projekt1.h
 * \brief
 *
 * \author Dariusz Strojny
 * \date   November 2022
*/

#ifndef __PROJEKT_1_AISD__
#define __PROJEKT_1_AISD__

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <algorithm>

#include <time.h>

#include <vector>
#include <chrono>

#include <deque>

#define PRO_FILE_VALUE_DELIMITER ' '
#define PRO_FILE_ARRAY_DELIMITER '\n'

namespace pro
{
	/* ---===---   FUNCTION DECLARATIONS   ---===--- */

	/**
	 * @brief Inicjalizuje bibliotekę pomocniczą.
	 */
	void init();

	/**
	 * @brief Generuje losową liczbę z przedziału [min, max].
	 * 
	 * @param min Minimalna wartość liczby
	 * @param max Maksymalna wartosć liczby
	 * 
	 * @return wygenerowana liczba
	 */
	inline int losowa_liczba(int min, int max);

	// 
	/**
	 * @brief Generuje losowy ciąg o podanej długości z wartościami z podanego przedziału.
	 * 
	 * @param min Minimalna wartość elementu w ciągu
	 * @param max Maksymalna wartosć elementu w ciągu
	 * @param width Ilość elementów w ciągu
	 * 
	 * @return wygenerowany ciąg
	 */
	std::vector<int> generuj_losowy_ciag(int min, int max, int width);

	/**
	 * @brief Generuje losowy dwuwymiarowy ciąg o podanych wymiarach z wartościami z podanego przedziału.
	 * 
	 * @param min Minimalna wartość elementu w ciągu
	 * @param max Maksymalna wartosć elementu w ciągu
	 * @param width Ilość kolumn w ciągu
	 * @param height Ilość wierszy ciągu
	 * 
	 * @return wygenerowany ciąg
	 */
	std::vector<std::vector<int>> generuj_losowy_ciag_2d(int min, int max, int width, int height);

	/**
	 * @brief Zwraca ciąg z zakresu start do end z krokiem step.
	 * 
	 * @code
	 * np. f(2, 6, 2) -> [2, 4, 6]
	 * @endcode
	 * 
	 * @param start Początkowa wartość iteratora
	 * @param end Maksymalna wartość iteratora (włącznie)
	 * @param step Krok o jaki zwiększany jest iterator
	 */
	std::vector<int> generuj_ciag_z_zakresu(int start, int end, int step = 1);

	/**
	 * @brief Funkcja pomocnicza sortowania quicksort.
	 * 
	 * Dzieli ciąg danych na dwie części przenosząc elementy mniejsze lub równe pierwszej wartości na jej lewą stronę a pozostałe na jej prawą stronę.
	 * 
	 * @param begin 
	 * @param end 
	 * 
	 * @return Iterator wskazujący na wartość oddzielającą oba ciągi
	*/
	std::vector<int>::iterator quicksort_iterator_partition(std::vector<int>::iterator begin, std::vector<int>::iterator end);

	/**
	 * @brief Sortowanie metodą quicksort na podanym przedziale.
	 * 
	 * @param begin Iterator wskazujący na początek przedziału
	 * @param end Iterator wskazujący na koniec przedziału
	*/
	void quicksort_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end);

	/**
	 * @brief Funkcja pomocnicza sortowania quicksort wykorzystująca usprawnienie dla ciągów z często powtarzającymi się wartościami.
	 *
	 * Dzieli ciąg danych na trzy części przenosząc elementy mniejsze pierwszej wartości na jej lewą stronę, większe od niej na jej prawą stronę a równe jej na środek.
	 *
	 * @param begin
	 * @param end
	 *
	 * @return Para iteratorów wskazujących odpowiednio na koniec i początek przedziałów oddzielonych ciągiem złożonym z wartości równych wybranej wartości pivot.
	*/
	std::pair<std::vector<int>::iterator, std::vector<int>::iterator> quicksort_iterator_three_way_partition(std::vector<int>::iterator start, std::vector<int>::iterator end);

	/**
		* @brief Sortowanie metodą quicksort na podanym przedziale.
		*
		* @param begin Iterator wskazujący na początek przedziału
		* @param end Iterator wskazujący na koniec przedziału
	*/
	void quicksort_three_way_iterator(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	/**
	 * @brief Przeprowadza wyszukiwanie liniowe w wartościach tablicy.
	 * 
	 * @param arr Tablica, na której wykonywane jest wyszukiwanie
	 * @param val Wartość szukana w tablicy
	 * 
	 * @return Iterator wskazujący na znaleziony element lub na koniec przedziału
	*/
	std::vector<int>::iterator linear_search_iterator(std::vector<int>& arr, int val);

	// wyszukuje wspólne elementy tablic arr1 i arr2 poprzez intersekcje oraz przepisuje je do tablicy res
	// zwraca iterator tablicy res wskazujący na ostatni przypisany element
	
	/**
	 * @brief Wyszukuje wspólne elementy dwóch tablic.
	 * 
	 * Funkcja wykonuje wyszukiwanie wspólnych elementów poprzez skrzyżowanie ze sobą dwóch tablic.
	 * Tablice wejściowe muszą być posortowane rosnąco.
	 * 
	 * @param arr1 Pierwsza tablica
	 * @param arr2 Druga tablica
	 * @param res Iterator wskazujący na pierwszy element tablicy o rozmiarze przynajmniej min(rozmiar arr1, rozmiar arr2)
	 * 
	 * @return Iterator wskazujący na element za ostatnim wpisanym elementem
	*/
	std::vector<int>::iterator set_intersection(const std::vector<int>& arr1, const std::vector<int>& arr2, std::vector<int>::iterator res);

	/**
	 * @brief Wypisuje w konsoli wymiary tablicy.
	 * 
	 * @param arr opisywana tablica
	*/
	void opisz_ciag(const std::vector<int>& arr);

	/**
	 * @brief Wypisuje w konsoli wymiary tablicy.
	 * 
	 * @param arr opisywana tablica
	*/
	void opisz_ciag(const std::vector<std::vector<int>>& arr);

	/**
	 * @brief Odczytuje ciąg z pliku wejściowego.
	 * 
	 * @param nazwa_pliku ścieżka do pliku
	 * @param delimiter Znak oddzielający wartości w pliku
	 * 
	 * @return Ciąg odczytany z pliku
	*/
	std::vector<int> odczytaj_ciag_z_pliku(const char* nazwa_pliku, char delimiter = PRO_FILE_VALUE_DELIMITER);

	/**
	 * @brief Odczytuje dwuwymiarową tablicę z pliku wejściowego.
	 * 
	 * @param nazwa_pliku ścieżka do pliku
	 * @param delimiter_val Znak oddzielający wartości wiersza w pliku
	 * @param delimiter_array Znak oddzielający wiersze w pliku
	 * 
	 * @return Dwuwymiarowa tablica odczytana z pliku
	*/
	std::vector<std::vector<int>> odczytaj_ciag_2d_z_pliku(const char* nazwa_pliku, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);

	/**
	 * @brief Oblicza zakres danych, na których mają być wykonane operacje dla podanego wątku.
	 * 
	 * @param data Dane do podzielenia
	 * @param thread_count £ączna ilość wątków
	 * @param thread_id Numer wątku, dla którego obliczany jest zakres
	 * 
	 * @return Para iteratorów wskazujących na początek i koniec wyznaczonego zakresu danych
	*/
	std::pair<std::vector<std::vector<int>>::const_iterator, std::vector<std::vector<int>>::const_iterator> 
		thread_bounds(const std::vector<std::vector<int>>& data, int thread_count, int thread_id);


	/* ---===---   TEMPLATE FUNCTION DECLARATIONS   ---===--- */

	/**
	 * @brief Wypisuje zawartość tablicy na ekranie.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param arr Tablica do wyświetlenia
	 * @param spacing Dopełnienie każdej komórki danych znakami białymi do podanej ilości znaków
	*/
	template<class T>
	void wypisz_ciag(const std::vector<T>& arr, unsigned spacing = 0);

	/**
	 * @brief Wypisuje zawartość tablicy dwuwymiarowej na ekranie.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param data Tablica do wyświetlenia
	 * @param spacing Dopełnienie każdej komórki danych znakami białymi do podanej ilości znaków
	*/
	template<class T>
	void wypisz_ciag(const std::vector<std::vector<T>>& data, unsigned spacing = 0);

	/**
	 * @brief Zapisuje ciąg do pliku wyjściowego.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w ciągu
	 * @param nazwa_pliku ścieżka do pliku
	 * @param data Ciąg do zapisania
	 * @param delimiter Znak oddzielający wartości w pliku
	*/
	template<class T>
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<T>& data, char delimiter = PRO_FILE_VALUE_DELIMITER);

	/**
	 * @brief Zapisuje tablicę dwuwymiarową do pliku wyjściowego.
	 * 
	 * @tparam T Rodzaj danych przechowywanych w tablicy
	 * @param nazwa_pliku ścieżka do pliku
	 * @param data Tablica do zapisania
	 * @param delimiter_val Znak oddzielający wartości wiersza w pliku
	 * @param delimiter_array Znak oddzielający wiersze w pliku
	*/
	template<class T>
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<T>>& data, char delimiter_val = PRO_FILE_VALUE_DELIMITER, char delimiter_array = PRO_FILE_ARRAY_DELIMITER);


	/* ---===---   TEMPLATE FUNCTION DEFINITIONS   ---===--- */

	// wypisuje tablice na ekranie
	template<class T>
	void wypisz_ciag(const std::vector<T>& arr, unsigned spacing)
	{
		std::cout << "[";

		// jeżeli przekazana została domyślna długość dopełnienia
		if (spacing == 0)
		{
			// dla każdego elementu tablicy
			for (auto el = arr.begin(); el != arr.end(); el++)
			{
				// wypisanie wartości elementu
				std::cout << *el;
				// dla wartości innych niż ostatnia wypisz znak ','
				if (el != arr.end() - 1) std::cout << ",";
			}
		}
		// w przeciwnym wypadku
		else
		{
			// zabezpieczenie przed przypadkowym przepełnieniem w dół (unsigned -1 = 4294967295)
			if (spacing > 50) spacing = 50;


			// utworzenie tablicy znaków dla formatu dopełnienia wartości
			char* mod = new char[12];
			// wpisanie formatu do tablicy znaków (np. "%3d, ")
			sprintf_s(mod, 12, "%%%dd", spacing);

			// dla każdego elementu tablicy
			for (auto el = arr.begin(); el != arr.end(); el++)
			{
				// wypisanie wartości elementu przy użyciu utworzonego wcześniej formatu
				printf(mod, *el);
				if (el != arr.end() - 1) std::cout << ",";
			}

			// zwolnienie pamięci tablicy formatu
			delete[] mod;
		}

		std::cout << "]\n";
	}

	template<class T>
	void wypisz_ciag(const std::vector<std::vector<T>>& data, unsigned spacing)
	{
		// dla każdego elementu tablicy 2-wymiarowej
		for (auto const& arr : data)
		{
			// wypisz wartości ciągu 1-wymiarowego wykorzystując istniającą funkcję wypisz_ciąg
			pro::wypisz_ciag(arr, spacing);
		}
	}

	// zapisuje tablice do pliku wyjsciowego z opcjonalną specyfikacją znaku oddzielającego warości
	template<class T>
	void zapisz_ciag_do_pliku(const char* nazwa_pliku, const std::vector<T>& data, char delimiter)
	{
		// otwarcie pliku do zapisu
		std::fstream ofs(nazwa_pliku, std::ios::out);

		// weryfikacja otwarcia pliku
		if (!ofs.good())
			// błąd przy próbie otwarcia pliku
			throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu!";

		// dla każdego elementu tablicy
		for (const auto& el : data)
			// wpisane wartości do pliku razem ze znakiem końca wartości
			ofs << el << delimiter;
	}

	// zapisuje tablice dwuwymiarową do pliku wyjsciowego z opcjonalną specyfikacją znaku oddzielającego warości i tablice
	template<class T>
	void zapisz_ciag_2d_do_pliku(const char* nazwa_pliku, const std::vector<std::vector<T>>& data, char delimiter_val, char delimiter_array)
	{
		// otwarcie pliku do zapisu
		std::fstream ofs(nazwa_pliku, std::ios::out);

		// weryfikacja otwarcia pliku
		if (!ofs.good())
		{
			// jeżeli wartość błędu jest równa 2, to ścieżka do pliku jest niepoprawna lub nie istnieje
			// tworzenie folderu wskazanego przez ścieżkę
			if (errno == 2)
			{
				std::string fn = std::string(nazwa_pliku);
				size_t pos = fn.rfind("/");
				if (pos == std::string::npos)
					pos = fn.rfind("\\");
				
				std::string cmd = std::string("mkdir ");
				if (pos == std::string::npos) cmd += std::string(nazwa_pliku);
				else cmd += std::string(nazwa_pliku).substr(0, pos);

				std::cout << "Executing \"" << cmd << "\"\n";
				system(cmd.c_str());

				ofs.open(nazwa_pliku, std::ios::out);
			}
			
			if(!ofs.good())
				// błąd przy próbie otwarcia pliku
				throw std::string("Nie udalo sie otworzyc pliku ") + nazwa_pliku + " do zapisu! Kod bledu: " + std::to_string(errno);
		}
			
		// dla każdego podciągu
		for (const auto& arr : data)
		{
			//dla każdego elementu tablicy
			for (const auto& el : arr)
			{
				// wpisane wartości do pliku razem ze znakiem końca wartości
				ofs << el << delimiter_val;
			}

			// wpisane znaku końca tabeli
			ofs << delimiter_array;
		}

	}
}

#endif