#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "BestScores.hpp"
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

void BestScores::show() {
    // Odczytanie najlepszych wynik�w z pliku
    std::ifstream file("best_scores.txt");

    if (!file.is_open()) {
        // Obs�uguje b��d w przypadku, gdy plik nie istnieje
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

    // Wy�wietlanie najlepszych wynik�w
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        // Obs�uguje b��d �adowania czcionki
        return;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Najlepszy wynik: " + std::to_string(bestScore));
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(100.0f, 100.0f);  // Pozycja wy�wietlania tekstu

    m_window.draw(scoreText);
}
