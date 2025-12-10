#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "paletka.h"


class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float _x, float _y, float _vx, float _vy, float _radius)
        : x(_x), y(_y), vx(_vx), vy(_vy), radius(_radius)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    inline void move() { x += vx; y += vy; shape.setPosition(x, y); }
    inline void bounceX() { vx = -vx; }
    inline void bounceY() { vy = -vy; }

    inline void collideWalls(float width, float height) {
        if (x - radius <= 0) { x = radius; bounceX(); }
        if (x + radius >= width) { x = width - radius; bounceX(); }
        if (y - radius <= 0) { y = radius; bounceY(); }
    }

    inline bool collidePaddle(const Paletka& p) {
        float palLeft = p.getX() - p.getSzerokosc() / 2;
        float palRight = p.getX() + p.getSzerokosc() / 2;
        float palTop = p.getY() - p.getWysokosc() / 2;

        if (x >= palLeft && x <= palRight &&
            y + radius >= palTop && y - radius < palTop)
        {
            vy = -std::abs(vy);
            y = palTop - radius;
            shape.setPosition(x, y);
            return true;
        }
        return false;
    }

    inline void draw(sf::RenderTarget& target) { target.draw(shape); }

    inline float getX() const { return x; }
    inline float getY() const { return y; }
    inline float getVx() const { return vx; }
    inline float getVy() const { return vy; }
    inline float getRadius() const { return radius; }
};
