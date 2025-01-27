#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Menu.hpp"
#include "Game.hpp"
#include "Credits.hpp"
#include "BestScores.hpp"
#include "ChangeBackground.hpp"

Menu::Menu(sf::RenderWindow& window)
    : m_window(window),
    m_selectedOption(0),
    m_isGameSelected(false),
    m_isCreditsSelected(false),
    m_isExitSelected(false),
    m_isChangeBackgroundSelected(false),
    m_isBestScoresSelected(false),
    m_keyDelay(0.2f),
    m_keyTimer(0.0f) {
    loadResources();

    // £adowanie sta³ego t³a menu
    if (!m_backgroundTexture.loadFromFile("obrazek.jpg")) {
        // Obs³uga b³êdu ³adowania t³a
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);
}


void Menu::loadResources() {
    if (!m_font.loadFromFile("font.ttf")) {
        // Obs³uga b³êdu ³adowania czcionki
    }
    if (!m_backgroundTexture.loadFromFile("obrazek.jpg")) {
        // Obs³uga b³êdu ³adowania t³a
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_title.setFont(m_font);
    m_title.setString("Sebastian's Game :)");
    m_title.setCharacterSize(60);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(static_cast<float>(m_window.getSize().x) / 2.0f - m_title.getLocalBounds().width / 2.0f, 50);


    std::vector<std::string> options = { "New Game", "Best Scores", "Change Background", "Credits", "Exit" };
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text option;
        option.setFont(m_font);
        option.setString(options[i]);
        option.setCharacterSize(40);
        option.setFillColor(sf::Color::White);
        option.setPosition(m_window.getSize().x / 2.0f - option.getLocalBounds().width / 2.0f, 150.0f + static_cast<float>(i) * 60.0f);

        m_options.push_back(option);
    }

}

void Menu::draw() {
    // T³o menu
    sf::Texture backgroundTexture;
    if (backgroundTexture.loadFromFile("obrazek.jpg")) {
        sf::Sprite backgroundSprite(backgroundTexture);
        m_window.draw(backgroundSprite);
    }
    m_window.draw(m_backgroundSprite);
    // Rysowanie tytu³u i opcji
    m_window.draw(m_title);
    for (size_t i = 0; i < m_options.size(); ++i) {
        if (i == m_selectedOption) {
            m_options[i].setFillColor(sf::Color::Yellow); // Zmiana koloru wybranej opcji
        }
        else {
            m_options[i].setFillColor(sf::Color::White);
        }
        m_window.draw(m_options[i]);
    }
}


void Menu::handleInput() {
    m_keyTimer += 1.0f / 60.0f;

    if (m_keyTimer >= m_keyDelay) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_selectedOption > 0) {
            --m_selectedOption;
            m_keyTimer = 0.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_selectedOption < m_options.size() - 1) {
            ++m_selectedOption;
            m_keyTimer = 0.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            m_isGameSelected = (m_selectedOption == 0);
            m_isBestScoresSelected = (m_selectedOption == 1);
            m_isChangeBackgroundSelected = (m_selectedOption == 2);
            m_isCreditsSelected = (m_selectedOption == 3);
            m_isExitSelected = (m_selectedOption == 4);
            m_keyTimer = 0.0f;
        }
        // Obs³uga naciœniêcia Escape
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close(); // Zamkniêcie gry
            m_keyTimer = 0.0f; // Resetujemy timer po naciœniêciu Escape
        }

    }

}




bool Menu::isGameSelected() const { return m_isGameSelected; }
bool Menu::isCreditsSelected() const { return m_isCreditsSelected; }
bool Menu::isExitSelected() const { return m_isExitSelected; }
bool Menu::isChangeBackgroundSelected() const { return m_isChangeBackgroundSelected; }
bool Menu::isBestScoresSelected() const { return m_isBestScoresSelected; }

void Menu::resetGameSelected() { m_isGameSelected = false; }
void Menu::resetCreditsSelected() { m_isCreditsSelected = false; }
void Menu::resetExitSelected() { m_isExitSelected = false; }
void Menu::resetChangeBackgroundSelected() { m_isChangeBackgroundSelected = false; }
void Menu::resetBestScoresSelected() { m_isBestScoresSelected = false; }
