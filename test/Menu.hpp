#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    explicit Menu(sf::RenderWindow& window);

    void handleInput(); // Obs³uga wejœcia
    void draw();        // Rysowanie menu

    bool isGameSelected() const;
    bool isCreditsSelected() const;
    bool isExitSelected() const;
    bool isChangeBackgroundSelected() const;
    bool isBestScoresSelected() const;

    void resetGameSelected();
    void resetCreditsSelected();
    void resetExitSelected();
    void resetChangeBackgroundSelected();
    void resetBestScoresSelected();

private:
    void loadResources();

    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_bestScoresText;
    std::vector<sf::Text> m_options;

    size_t m_selectedOption;

    bool m_isGameSelected;
    bool m_isCreditsSelected;
    bool m_isExitSelected;
    bool m_isChangeBackgroundSelected;
    bool m_isBestScoresSelected;

    sf::Texture m_backgroundTexture; // Tekstura dla t³a menu
    sf::Sprite m_backgroundSprite;  // Sprite dla t³a menu

    float m_keyDelay;
    float m_keyTimer;
};

#endif // MENU_HPP
