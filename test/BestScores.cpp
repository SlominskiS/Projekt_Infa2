#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "BestScores.hpp"
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

void BestScores::show() {
    // Odczytanie najlepszych wyników z pliku
    std::ifstream file("best_scores.txt");

    if (!file.is_open()) {
        // Obs³uguje b³¹d w przypadku, gdy plik nie istnieje
        return;
    }

    int bestScore = 0;
    int score;
    while (file >> score) {
        if (score > bestScore) {
            bestScore = score;
        }
    }

    file.close();

    // Wyœwietlanie najlepszych wyników
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        // Obs³uguje b³¹d ³adowania czcionki
        return;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Najlepszy wynik: " + std::to_string(bestScore));
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(100.0f, 100.0f);  // Pozycja wyœwietlania tekstu

    m_window.draw(scoreText);
}
