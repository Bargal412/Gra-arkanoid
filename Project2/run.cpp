#include "run.hpp"
#include "Menu.hpp"
#include "Game1.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Score.hpp"

enum class GameState { MenuState, Playing, Scores, Exiting };

void Run::run() {
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "GRA");
    window.setFramerateLimit(60);

    Menu menu(WIDTH, HEIGHT);
    Game game;
    GameState currentState = GameState::MenuState;
    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                currentState = GameState::Exiting;

            if (event.type == sf::Event::KeyPressed) {
                if (currentState == GameState::MenuState) {
                    if (event.key.code == sf::Keyboard::Up) menu.przesunG();
                    else if (event.key.code == sf::Keyboard::Down) menu.przesunD();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedItem();
                        if (selected == 0) { currentState = GameState::Playing; game.reset(); }
                        else if (selected == 1) currentState = GameState::Scores;
                        else if (selected == 2) currentState = GameState::Exiting;
                    }
                }
                else if (currentState == GameState::Playing && event.key.code == sf::Keyboard::Escape)
                    currentState = GameState::MenuState;
                else if (currentState == GameState::Scores &&
                    (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter))
                    currentState = GameState::MenuState;
            }
        }

        if (currentState == GameState::Exiting)
            window.close();

        
        if (currentState == GameState::Playing) {
            game.update(dt);

            if (game.isGameOver()) {
                saveScoreToFile(game.getScore());  
                currentState = GameState::MenuState;
            }
        }


        
        window.clear(sf::Color(20, 20, 30));
        if (currentState == GameState::MenuState) menu.draw(window);
        else if (currentState == GameState::Playing) game.render(window);
        else if (currentState == GameState::Scores) {
            auto scores = loadScoresFromFile();

            sf::Text header("OSTATNIE WYNIKI:", menu.getFont(), 28);
            header.setFillColor(sf::Color::Yellow);
            header.setPosition(50, 50);
            window.draw(header);

            float y = 120;

            for (int i = 0; i < std::min(10, (int)scores.size()); i++)
            {
                sf::Text line(std::to_string(i + 1) + ". " + std::to_string(scores[i]),
                    menu.getFont(), 24);
                line.setFillColor(sf::Color::White);
                line.setPosition(50, y);
                y += 30;
                window.draw(line);
            }

            sf::Text back("ESC lub ENTER aby powrocic", menu.getFont(), 20);
            back.setFillColor(sf::Color::Cyan);
            back.setPosition(50, y + 20);
            window.draw(back);

        }
        window.display();
    }
}
