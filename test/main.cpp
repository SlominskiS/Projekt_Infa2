#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "BestScores.hpp"
#include "ChangeBackground.hpp"

#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Credits.hpp"
#include "Game.hpp"
#include "Bestscores.hpp"
#include "ChangeBackground.hpp"
#include "GameState.hpp"


int main() {

    //  okno gry
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Sebatian's Game", sf::Style::Fullscreen);

    //  obiekty menu, credits, gry i zmiany t�a
    Menu menu(window);
    Credits credits(window);
    Game game(window);
    BestScores bestScores(window);
    ChangeBackground changeBackground(window);

    // ladowanie dost�pne t�a
    changeBackground.loadBackgrounds({ "kosmos.jpg", "woda.jpg", "powietrze.jpg" });

    GameState gameState = GameState::Menu; // Domy�lny stan gry to Menu

    // P�tla gry
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Obs�uguje r�ne stany gry
        switch (gameState) {
        case GameState::Menu:
            menu.handleInput();
            if (menu.isGameSelected()) {
                gameState = GameState::Game; // zmieniamy stan na..
                menu.resetGameSelected(); // resetujemy flage
            }
            else if (menu.isChangeBackgroundSelected()) {
                gameState = GameState::ChangeBackground;
                menu.resetChangeBackgroundSelected();
            }
            else if (menu.isCreditsSelected()) {
                gameState = GameState::Credits;
                menu.resetCreditsSelected();
            }
            else if (menu.isBestScoresSelected()) {
                gameState = GameState::BestScores;
                menu.resetBestScoresSelected();
            }
            else if (menu.isExitSelected()) {
                gameState = GameState::Exit;
                menu.resetExitSelected();
            }
            menu.draw();
            break;


        case GameState::BestScores:  // Obs�uguje stan BestScores
            bestScores.show();  // Wy�wietlanie najlepszych wynik�w
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                gameState = GameState::Menu;  // Powr�t do menu
            }
            break;


        case GameState::ChangeBackground:
            changeBackground.changeBackground(); // Obs�uga zmiany t�a
            gameState = GameState::Menu; // Powr�t do menu po zako�czeniu zmiany t�a
            break;

        case GameState::Credits:
            credits.draw();
            credits.handleInput();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                gameState = GameState::Menu; // Powr�t do menu
            }
            break;



        case GameState::Game:
            // Ustaw wybrane t�o
            game.setBackgroundTexture(changeBackground.getGameBackground());
            game.start();
            gameState = GameState::Menu;
            break;


    

        case GameState::Exit:
            window.close(); // Zamkni�cie gry
            break;
        }

      
        window.display();
    }

    return 0;
}
