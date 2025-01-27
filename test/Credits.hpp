
#pragma once
#include <SFML/Graphics.hpp>

class Credits {
private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_creditsText;
    sf::Text m_signature;

public:
    Credits(sf::RenderWindow& window); // Konstruktor
    void handleInput();                // Obs³uga wejœcia
    void draw();                       // Rysowanie ekranu
};
