#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "Paletka.hpp"
#include "pilka.hpp"
#include "cegly.hpp"

struct BlockData {
    float x, y;
    int hp;
};

class GameState1 {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameState1() = default;

    void capture(const Paletka& paddle, const Pilka& ball, const std::vector<Brick>& stones);
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition() const { return ballPosition; }
    const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }
};
