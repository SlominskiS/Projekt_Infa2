#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "ChangeBackground.hpp"
#include <iostream>

ChangeBackground::ChangeBackground(sf::RenderWindow& window)
    : m_window(window), m_selectedBackground(0), m_gameBackground("") {
    // Wczytaj domy�ln� czcionk�
    if (!m_font.loadFromFile("font.ttf")) {
        std::cerr << "Nie udalo sie zaladowa� czcionki!" << std::endl;
    }
}

void ChangeBackground::loadBackgrounds(const std::vector<std::string>& backgrounds) {
    m_backgrounds = backgrounds;
    if (!m_backgrounds.empty()) {
        m_gameBackground = m_backgrounds[0]; // Ustaw pierwsze t�o jako domy�lne
    }
    if (backgrounds.empty()) {
        std::cerr << "Lista dost�pnych tel nie moze by� pusta!" << std::endl;
        return;
    }

}

void ChangeBackground::changeBackground() {
    while (m_window.isOpen()) {
        m_window.clear();
        sf::Texture bgTexture;
        if (!bgTexture.loadFromFile(m_backgrounds[m_selectedBackground])) {
            std::cerr << "Nie udalo sie zaladowac tla: " << m_backgrounds[m_selectedBackground] << std::endl;
            return;
        }
        sf::Sprite bgSprite(bgTexture);
        m_window.draw(bgSprite);
        // Wy�wietlanie instrukcji
        sf::Text prompt("Press Left/Right to change, Enter to select, Esc to cancel", m_font, 20);
        prompt.setFillColor(sf::Color::White);
        prompt.setPosition(100.f, m_window.getSize().y - 100.f);
        m_window.draw(prompt);
        m_window.display();

        // Obs�uga zdarze�
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    m_selectedBackground = (m_selectedBackground + m_backgrounds.size() - 1) % m_backgrounds.size();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    m_selectedBackground = (m_selectedBackground + 1) % m_backgrounds.size();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    std::cout << "Wybrane background: " << m_backgrounds[m_selectedBackground] << std::endl;
                    m_gameBackground = m_backgrounds[m_selectedBackground];
                    return; // Zatwierd� i wyjd�
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    return; // Wyjd� bez zmian
                }
            }
        }
    }
}


const std::string& ChangeBackground::getGameBackground() const {
    return m_gameBackground;
}

void ChangeBackground::drawBackground() {
    if (m_gameBackground.empty()) {
        std::cerr << "Brak ustawionego t�a." << std::endl;
        return;
    }
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile(m_gameBackground)) {
        std::cerr << "Nie udalo sie za�adowa� tla: " << m_gameBackground << std::endl;
        return;
    }
    sf::Sprite bgSprite(bgTexture);
    m_window.draw(bgSprite);
}
