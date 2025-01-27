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

    // Wczytaj dostêpne t³a
    void loadBackgrounds(const std::vector<std::string>& backgrounds);

    // Wyœwietl ekran zmiany t³a
    void changeBackground();

    // Pobierz aktualne t³o
    const std::string& getGameBackground() const;

    // Rysowanie wybranego t³a
    void drawBackground();
};
