#include "Gamestate1.hpp"
#include <fstream>
void GameState1::capture(const Paletka& paddle, const Pilka& ball, const std::vector<Brick>& stones)
{
   
    paddlePosition = { paddle.getX(),paddle.getY() };
    ballPosition = { ball.getX(),ball.getY() };
    ballVelocity = { ball.getVx(),ball.getVy() };

    
    blocks.clear();
    blocks.reserve(stones.size());

    
    for (const auto& b : stones) {
        BlockData d;
        d.x = b.getPosition().x;
        d.y = b.getPosition().y;
        d.hp = b.GetHp();
        blocks.push_back(d);
    }
}
bool GameState1::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;
    file << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << ballPosition.x << " " << ballPosition.y << "\n";
    file << ballVelocity.x << " " << ballVelocity.y << "\n";
    file << blocks.size() << "\n";   
    for (const auto& b : blocks) {
        file << b.x << " " << b.y << " " << b.hp << "\n";
    }

    return true;
}
bool GameState1::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    file >> paddlePosition.x >> paddlePosition.y;
    file >> ballPosition.x >> ballPosition.y;
    file >> ballVelocity.x >> ballVelocity.y;

    size_t count;
    file >> count;

    blocks.clear();
    blocks.resize(count);

    for (size_t i = 0; i < count; i++) {
        file >> blocks[i].x >> blocks[i].y >> blocks[i].hp;
    }

    return true;
}
