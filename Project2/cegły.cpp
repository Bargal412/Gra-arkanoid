#include "cegly.hpp"
#include <algorithm>

const std::array<sf::Color, 5> Brick::colorLUT = {
    sf::Color(50, 50, 50),
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Green,
    sf::Color(100, 100, 255)
};

Brick::Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L)
    : punktyZycia(L), jestZniszczony(L <= 0)
{
    setSize(rozmiar);
    setPosition(startPo);
    setOutlineThickness(1.f);
    setOutlineColor(sf::Color::White);
    aktualizujKolor();
}

void Brick::aktualizujKolor() {
    int index = std::max(0, std::min(4, punktyZycia));
    setFillColor(colorLUT[index]);
}

void Brick::trafienie() {
    if (jestZniszczony)
        return;

    punktyZycia--;
    aktualizujKolor();

    if (punktyZycia <= 0)
        jestZniszczony = true;
}

void Brick::draw(sf::RenderTarget& window) {
    if (!jestZniszczony) {
        window.draw(*this);
    }
}
