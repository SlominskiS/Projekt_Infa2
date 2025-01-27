#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Game {
public:
    Game(sf::RenderWindow& window);
    void start();
    void setBackgroundTexture(const std::string& backgroundPath);
    void showHelp();

private:
    void handleInput();
    void update();
    void draw();
    void saveBestScore();
    void spawnEnemy(); // Nowa funkcja generuj¹ca przeciwników
    bool confirmExit();
    void showGameOverScreen();



    sf::RenderWindow& m_window;


    // Gracz
    sf::RectangleShape m_player;
    sf::Texture m_playerTexture;
    float m_playerSpeed;

    // Pociski
    std::vector<sf::RectangleShape> m_bullets;
    float m_bulletSpeed;

    // Przeciwnicy
    std::vector<sf::RectangleShape> m_enemies;
    sf::Texture m_enemyTexture; // Tekstura dla przeciwników

    // Celownik
    sf::RectangleShape m_crosshair;
    sf::Clock m_shootClock; // Zegar do mierzenia czasu od ostatniego strza³u
    sf::Texture m_crosshairTexture; // Tekstura celownika
    sf::Texture m_crosshairEnemyTexture; // Tekstura celownika, gdy przeciwnik jest przed nim

    // Stan gry
    bool m_isGameOver;
    int m_score;
};

#endif
