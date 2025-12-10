#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y, szerokosc, wysokosc, predkosc;
    sf::RectangleShape shape;
public:
    Paletka(float _x, float _y, float _szer, float _wys, float _predkosc)
        : x(_x), y(_y), szerokosc(_szer), wysokosc(_wys), predkosc(_predkosc)
    {
        shape.setSize({ szerokosc, wysokosc });
        shape.setOrigin(szerokosc / 2, wysokosc / 2);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
    }

    inline void moveLeft() { x -= predkosc; shape.setPosition(x, y); }
    inline void moveRight() { x += predkosc; shape.setPosition(x, y); }

    inline void clampToBounds(float width) {
        if (x - szerokosc / 2 < 0) x = szerokosc / 2;
        if (x + szerokosc / 2 > width) x = width - szerokosc / 2;
        shape.setPosition(x, y);
    }

    inline void draw(sf::RenderTarget& target) { target.draw(shape); }

    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline float getSzerokosc() const { return szerokosc; }
    inline float getWysokosc() const { return wysokosc; }
};
