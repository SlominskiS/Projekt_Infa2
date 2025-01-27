#include "Game.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Menu.hpp"
#include "GameState.hpp"
#include "ChangeBackground.hpp"

sf::Texture m_gameBackgroundTexture;
sf::Sprite m_gameBackgroundSprite;

void Game::showHelp() {
    sf::Text helpText;
    sf::Font font;
    font.loadFromFile("font.ttf");
    helpText.setFont(font);
    helpText.setString(
        "Pomoc:\n"
        "- Strzalki lewo/prawo: ruch gracza\n"
        "- Spacja: strzal\n"
        "- ESC: wyjscie z gry\n"
        "- F1: wyswietlenie pomocy\n"
    );
    helpText.setCharacterSize(24);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(50.f, 50.f);

    m_window.clear();
    m_window.draw(helpText);
    m_window.display();

    sf::Event event;
    while (m_window.waitEvent(event)) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            return; // Wyj�cie z ekranu pomocy
        }
    }
}

bool Game::confirmExit() {
    sf::Text confirmText;
    sf::Font font;
    font.loadFromFile("font.ttf");
    confirmText.setFont(font);
    confirmText.setString("Czy na pewno chcesz wyjsc (Y/N)");
    confirmText.setCharacterSize(30);
    confirmText.setFillColor(sf::Color::Red);
    confirmText.setPosition(m_window.getSize().x / 2 - confirmText.getLocalBounds().width / 2, m_window.getSize().y / 2);

    m_window.clear();
    m_window.draw(confirmText);
    m_window.display();

    while (true) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Y) {
                    return true; // Potwierdzenie wyj�cia
                }
                else if (event.key.code == sf::Keyboard::N) {
                    return false; // Anulowanie wyj�cia
                }
            }
        }
    }
}

void Game::showGameOverScreen() {
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text gameOverText("Game Over\nPress Enter to continue", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(m_window.getSize().x / 2 - gameOverText.getLocalBounds().width / 2,
        m_window.getSize().y / 2 - gameOverText.getLocalBounds().height / 2);

    m_window.clear();
    m_window.draw(gameOverText);
    m_window.display();

    while (true) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return; // Wyj�cie z ekranu Game Over
            }
        }
    }
}


void Game::setBackgroundTexture(const std::string& backgroundPath) {
    if (!m_gameBackgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Nie udalo sie za�adowa� tla gry: " << backgroundPath << std::endl;
    }
    else {
        m_gameBackgroundSprite.setTexture(m_gameBackgroundTexture);
    }
}


Game::Game(sf::RenderWindow& window)
    : m_window(window), m_playerSpeed(5.0f), m_bulletSpeed(10.0f), m_isGameOver(false), m_score(0) {
    // �adowanie tekstury statku gracza
    if (!m_playerTexture.loadFromFile("player.png")) {
        // Obs�uguje b��d �adowania tekstury
    }

    if (!m_enemyTexture.loadFromFile("wrog.png")) {
        // Obs�uguje b��d �adowania tekstury
    }

    // �adowanie tekstur celownika
    if (!m_crosshairTexture.loadFromFile("crosshair.png")) {
        // Obs�uguje b��d �adowania tekstury
    }
    if (!m_crosshairEnemyTexture.loadFromFile("crosshair_enemy.png")) {
        // Obs�uguje b��d �adowania tekstury
    }


    m_gameBackgroundSprite.setTexture(m_gameBackgroundTexture);

    // Ustawienie gracza
    m_player.setSize(sf::Vector2f(50.0f, 50.0f));
    m_player.setTexture(&m_playerTexture);
    m_player.setPosition(m_window.getSize().x / 2 - m_player.getSize().x / 2, m_window.getSize().y - 100.0f);

    // Ustawienie celownika
    m_crosshair.setSize(sf::Vector2f(30.0f, 30.0f)); // Rozmiar celownika
    m_crosshair.setTexture(&m_crosshairTexture);

    spawnEnemy(); // Generowanie pocz�tkowych przeciwnik�w
}


void Game::spawnEnemy() {
    // Losowe pozycje przeciwnik�w
    for (int i = 0; i < 2; ++i) { // Generuj 2 przeciwnik�w na raz
        sf::RectangleShape enemy(sf::Vector2f(50.0f, 50.0f));
        enemy.setTexture(&m_enemyTexture);
        enemy.setPosition(static_cast<float>(rand() % m_window.getSize().x), 0.0f); // Losowa pozycja na g�rze
        m_enemies.push_back(enemy);
    }
}


void Game::start() {
    sf::Clock enemySpawnTimer;

    while (!m_isGameOver) {
        handleInput();
        update();

        // Dodawanie przeciwnik�w co sekund�
        if (enemySpawnTimer.getElapsedTime().asSeconds() >= 1.0f) {
            spawnEnemy();
            enemySpawnTimer.restart();
        }

        draw();
    }
}

void Game::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_player.getPosition().x > 0) {
        m_player.move(-m_playerSpeed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_player.getPosition().x + m_player.getSize().x < m_window.getSize().x) {
        m_player.move(m_playerSpeed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
        showHelp(); // Wy�wietlenie pomocy
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (confirmExit()) {
            m_window.close();
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        // Sprawdzanie, czy min�o wystarczaj�co du�o czasu od ostatniego strza�u
        if (m_shootClock.getElapsedTime().asMilliseconds() > 200) { // 500 ms op�nienia
            // Tworzenie pocisku
            sf::RectangleShape bullet(sf::Vector2f(5.0f, 20.0f));
            bullet.setFillColor(sf::Color::Red);
            bullet.setPosition(m_player.getPosition().x + m_player.getSize().x / 2 - bullet.getSize().x / 2, m_player.getPosition().y);
            m_bullets.push_back(bullet);

            // Resetuj zegar
            m_shootClock.restart();
        }
    }
}


void Game::update() {
    // Ruch pocisk�w gracza
    for (auto& bullet : m_bullets) {
        bullet.move(0, -m_bulletSpeed);
    }

    // Sprawdzanie kolizji z obcymi
    for (size_t i = 0; i < m_bullets.size();) {
        bool bulletDestroyed = false;
        for (size_t j = 0; j < m_enemies.size();) {
            if (m_bullets[i].getGlobalBounds().intersects(m_enemies[j].getGlobalBounds())) {
                // Zniszczenie obcego i pocisku
                m_enemies.erase(m_enemies.begin() + j);
                bulletDestroyed = true;
                m_score += 10; // Zwi�kszenie punkt�w
                break;
            }
            else {
                ++j;
            }
        }
        if (bulletDestroyed) {
            m_bullets.erase(m_bullets.begin() + i);
        }
        else {
            ++i;
        }
    }

    // Ruch przeciwnik�w w kierunku gracza
    for (auto& enemy : m_enemies) {
        sf::Vector2f direction = m_player.getPosition() - enemy.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // Normalizacja wektora
        enemy.move(direction * 1.0f); // Ruch przeciwnika w kierunku gracza
    }

    // Synchronizacja celownika z graczem
    m_crosshair.setPosition(m_player.getPosition().x, m_player.getPosition().y - 100.0f);

    // Sprawdzanie kolizji przeciwnik�w z graczem
    for (const auto& enemy : m_enemies) {
        if (enemy.getGlobalBounds().intersects(m_player.getGlobalBounds())) {
            m_isGameOver = true; // Gra ko�czy si�
            break;
        }
    }

    // Je�li gra si� sko�czy�a, zapisujemy najlepszy wynik
    if (m_isGameOver) {
        saveBestScore();  // Zapisz najlepszy wynik tylko, gdy gra jest zako�czona
        showGameOverScreen(); // Wy�wietlenie ekranu Game Over
        m_isGameOver = false; // Resetowanie stanu gry
        return;
    }

    


    // Losowe generowanie nowych przeciwnik�w
    if (rand() % 100000 < 2) { // Szansa 0.002% na stworzenie nowych przeciwnik�w przy ka�dej aktualizacji
        spawnEnemy();
    }

    // Synchronizacja celownika z graczem - zmie� pozycj�
        m_crosshair.setPosition(
            m_player.getPosition().x + m_player.getSize().x / 2 - m_crosshair.getSize().x / 2,
            m_player.getPosition().y - 120.0f // Celownik przed graczem, zmie� warto�� Y, aby przesun�� go w pionie
        );

    // Sprawdzanie, czy przeciwnik znajduje si� przed celownikiem
    bool enemyDetected = false;
    for (const auto& enemy : m_enemies) {
        if (m_crosshair.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            enemyDetected = true;
            break;
        }
    }

    // Zmiana tekstury celownika w zale�no�ci od obecno�ci przeciwnika
    if (enemyDetected) {
        m_crosshair.setTexture(&m_crosshairEnemyTexture);
    }
    else {
        m_crosshair.setTexture(&m_crosshairTexture);
    }
}


void Game::saveBestScore() {
    // Odczytanie obecnego najlepszego wyniku z pliku
    std::ifstream file("best_scores.txt");
    int bestScore = 0;
    if (file.is_open()) {
        int score;
        while (file >> score) {
            if (score > bestScore) {
                bestScore = score;
            }
        }
    }

    // Je�li obecny wynik jest lepszy, zapisujemy go do pliku
    if (m_score > bestScore) {
        std::ofstream file("best_scores.txt", std::ios::app);
        if (file.is_open()) {
            file << m_score << std::endl;
        }
    }
}

void Game::draw() {
    m_window.clear();  // Wyczy�� ekran
    m_window.draw(m_gameBackgroundSprite);

    // T�o tylko w trakcie gry
  

    // Rysowanie gracza, obcych i pocisk�w
    m_window.draw(m_player);
    for (auto& enemy : m_enemies) {
        m_window.draw(enemy);
    }
    for (auto& bullet : m_bullets) {
        m_window.draw(bullet);
    }

    // Rysowanie celownika
    m_window.draw(m_crosshair);

    // Wy�wietlanie wyniku
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text scoreText("Score: " + std::to_string(m_score), font, 30);
    scoreText.setPosition(10.0f, 10.0f);
    m_window.draw(scoreText);

    // Sprawdzanie ko�ca gry
    if (m_isGameOver) {
        sf::Text gameOverText("Game Over", font, 50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(m_window.getSize().x / 2 - gameOverText.getLocalBounds().width / 2, m_window.getSize().y / 2 - gameOverText.getLocalBounds().height / 2);
        m_window.draw(gameOverText);
    }

    m_window.display();
}








