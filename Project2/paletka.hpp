#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Paletka {
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float x_, float y_, float szerokosc_, float wysokosc_, float predkosc_)
        : x(x_), y(y_), szerokosc(szerokosc_), wysokosc(wysokosc_), predkosc(predkosc_) {
        shape.setSize({ szerokosc, wysokosc });
        shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(150, 200, 250));
    }

    void moveLeft() {
        x -= predkosc;
        shape.setPosition(x, y);
    }

    void moveRight() {
        x += predkosc;
        shape.setPosition(x, y);
    }

    void clampToBounds(float width) {
        float half = szerokosc / 2.f;
        if (x - half < 0.f) {
            x = half;
            shape.setPosition(x, y);
        }
        if (x + half > width) {
            x = width - half;
            shape.setPosition(x, y);
        }
    }

    void draw(sf::RenderTarget& target) { target.draw(shape); }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }

    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
        shape.setPosition(x, y);
    }
};
