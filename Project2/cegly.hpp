#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Brick : public sf::RectangleShape {
private:
    int punktyZycia;
    bool jestZniszczony;
    static const std::array<sf::Color, 5> colorLUT;

public:
    Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);

    void aktualizujKolor();
    void trafienie();
    void draw(sf::RenderTarget& window);

    bool czyZniszczony() const { return jestZniszczony; }
    sf::FloatRect getGlobalBounds() const { return sf::RectangleShape::getGlobalBounds(); }
    int GetHp() const { return punktyZycia; }
};



