#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "paletka.hpp"
#include "pilka.hpp"
#include "cegly.hpp"

class GameState1;

class Game {
private:
    static constexpr float WIDTH = 640.f;
    static constexpr float HEIGHT = 480.f;
    Paletka m_paletka;
    Pilka m_pilka;
    bool m_isGameOver = false;
    std::vector<Brick> m_bloki;
    sf::Clock m_deltaClock;
    int m_score = 0;

public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    bool isGameOver() const { return m_isGameOver; }
    void reset();
    void applyState(const GameState1& state);
    int getScore() const { return m_score; }
};