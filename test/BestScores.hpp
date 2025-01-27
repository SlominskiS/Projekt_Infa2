#ifndef BESTSCORES_HPP
#define BESTSCORES_HPP

#include <SFML/Graphics.hpp>

class BestScores {
public:
    BestScores(sf::RenderWindow& window) : m_window(window) {}

    void show();  // Funkcja wyświetlająca najlepszy wynik

private:
    sf::RenderWindow& m_window;
};

#endif // BESTSCORES_HPP
