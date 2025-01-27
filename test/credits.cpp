#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Menu.hpp"
#include "GameState.hpp"
#include "ChangeBackground.hpp"

#include "Credits.hpp"

Credits::Credits(sf::RenderWindow& window) : m_window(window) {
    if (!m_font.loadFromFile("font.ttf")) {
        // Obs³uga b³êdu
    }

    m_creditsText.setFont(m_font);
    m_creditsText.setString(
        "Gra to klasyczna gra 2D stworzona w C++ z wykorzystaniem biblioteki SFML.\n"
        "Gracz porusza sie w dynamicznym swiecie, gdzie celem jest zdobywanie punktow\n"
        "i unikanie przeszkod. Gra oferuje rozne funkcje, takie jak:\n"
        "- Menu glowne\n"
        "- Zmiana tla\n"
        "- Najlepsze wyniki\n"
        "- Ekran Game Over\n"
        "- Instrukcja pod klawiszem F1\n"
        "- Wyjscie z potwierdzeniem pod ESC\n"
    );
    m_creditsText.setCharacterSize(25);
    m_creditsText.setFillColor(sf::Color::White);
    m_creditsText.setPosition(50, 50);

    m_signature.setFont(m_font);
    m_signature.setString("Prace wykonal Sebastian Slominski");
    m_signature.setCharacterSize(20);
    m_signature.setFillColor(sf::Color::White);
    m_signature.setPosition(
        m_window.getSize().x / 2 - m_signature.getLocalBounds().width / 2,
        m_window.getSize().y - 50
    );

}

void Credits::handleInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::Closed) {
            return; // Wyjœcie z ekranu credits
        }
    }
}

void Credits::draw() {
    m_window.clear();
    m_window.draw(m_creditsText);
    m_window.draw(m_signature);
    m_window.display();
}
