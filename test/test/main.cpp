#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*#include <iostream>
#include <cstring>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>*/

#include <iostream>     // dla std::cout
#include <vector>       // dla std::vector 
#include <array>
#include <list> 
#include <deque> 
#include <algorithm>    // dla std::sort
#include <stdio.h>
#include <string>

void drukujN(const std::vector<std::string>& napisy) {
    for (const auto& slowo : napisy) {
        std::cout << slowo << " ";
    }
    std::cout << "\n";
}

void drukuj(const std::vector<int>& liczby) {
	for (int liczba : liczby) {
		std::cout << liczba << " ";
	}
	std::cout << "\n";
}

void szukajLiczby(const std::vector<int>& dt, int szukana) {
    bool znaleziono = false;
    for (size_t i = 0; i < dt.size(); ++i) {
        if (dt[i] == szukana) {
            std::cout << "Liczba " << szukana << " znaleziona na pozycji: " << i << "\n";
            znaleziono = true;
            break;
        }
    }
    if (!znaleziono) {
        std::cout << "Liczba " << szukana << " nie zostala znaleziona.\n";
    }
}

void usunE(std::vector<std::string>& napisy, int indeks) {
        napisy.erase(napisy.begin() + indeks);
        std::cout << "Usunieto element o indeksie " << indeks << ".\n";
 
}

void bubbleSort(std::vector<int>& liczby) {
    int n = liczby.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (liczby[j] > liczby[j + 1]) {
                std::swap(liczby[j], liczby[j + 1]);
            }
        }
    }
}       




int main() {
	std::vector<int> dt{ 2, 1, 3, 7};
    // Wyœwietlenie pocz¹tkowego kontenera
    std::cout << "Poczatkowa zawartosc wektora: ";
    drukuj(dt);
    std::cout << "Rozmiar: " << dt.size() << "\n";

    // Dodanie trzech liczb
    dt.push_back(0);
    dt.push_back(0);
    dt.push_back(7);

    std::cout << "\nPo dodaniu trzech liczb: ";
    drukuj(dt);
    std::cout << "Rozmiar: " << dt.size() << "\n";

    // Usuniêcie ostatniej liczby
    dt.pop_back();

    std::cout << "\nPo usunieciu ostatniej liczby: ";
    drukuj(dt);
    std::cout << "Rozmiar: " << dt.size() << "\n \n";

    std::cout << "***************************************************** \n";
    //szukanie liczby
    szukajLiczby(dt, 15);
    std::cout << "***************************************************** \n";


    std::vector<int> liczby = { 34, 7, 23, 32, 5, 62, 31, 1, 12, 8 };

    std::cout << "\n" << "Przed sortowaniem: ";
    drukuj(liczby);

    // Sortowanie b¹belkowe
    bubbleSort(liczby);
    std::cout << "Po sortowaniu b¹belowym: ";
    drukuj(liczby);

    // Sortowanie za pomoc¹ biblioteki algorithm
    std::sort(liczby.begin(), liczby.end());
    std::cout << "Po sortowaniu std::sort: ";
    drukuj(liczby);


    

    std::cout << "\n" << "***************************************************** \n";
    std::vector<std::string> napisy = { "Hermetyzacja", "to", "paradygmat", "programowania", "obiektowego" };
    // Wyœwietlenie pocz¹tkowej zawartoœci
    std::cout << "Poczatkowa zawartosc wektora:\n";
    drukujN(napisy);

    //Nowe  elementu
    napisy.push_back(",pierwszy");
    napisy.push_back(",drugi");

    std::cout << "\nPo dodaniu nowych elementow:\n";
    drukujN(napisy);

    
    // Usuniêcie trzeciego elementu 
    usunE(napisy, 2);
    std::cout << "\nPo usunieciu trzeciego:\n";
    drukujN(napisy);
    std::cout << "***************************************************** \n";

    return 0;
}

	/*std::cout << "Liczby: ";
	for (const auto& i : dt)
		std::cout << i << " ";
	std::cout << "\n" << "Ilosc liczb: " << dt.size() << "\n";
*/



/*
int main() {
	std::vector<int> dt {5, 10, 15};
	for (const auto& i : dt )
		std::cout << i << " ";
}
*/