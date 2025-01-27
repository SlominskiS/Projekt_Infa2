#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ChangeBackground {
private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    std::vector<std::string> m_backgrounds;
    size_t m_selectedBackground;
    std::string m_gameBackground;

public:
    ChangeBackground(sf::RenderWindow& window);

    // Wczytaj dost�pne t�a
    void loadBackgrounds(const std::vector<std::string>& backgrounds);

    // Wy�wietl ekran zmiany t�a
    void changeBackground();

    // Pobierz aktualne t�o
    const std::string& getGameBackground() const;

    // Rysowanie wybranego t�a
    void drawBackground();
};
