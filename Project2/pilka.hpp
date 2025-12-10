#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "paletka.hpp"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float x_, float y_, float vx_, float vy_, float radius_)
        : x(x_), y(y_), vx(vx_), vy(vy_), radius(radius_) {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);  
    }
    sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }

    void move() {
        x += vx;
        y += vy;
        shape.setPosition(x, y);
    }

    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    void collideWalls(float width, float height) {
        if (x - radius <= 0.f) {
            x = radius;
            bounceX();
            shape.setPosition(x, y);
        }
        if (x + radius >= width) {
            x = width - radius;
            bounceX();
            shape.setPosition(x, y);
        }
        if (y - radius <= 0.f) {
            y = radius;
            bounceY();
            shape.setPosition(x, y);
        }
    }

    bool collidePaddle(const Paletka& p) {
        float palX = p.getX();
        float palY = p.getY();
        float palW = p.getSzerokosc();
        float palH = p.getWysokosc();

        float palLeft = palX - palW / 2.f;
        float palRight = palX + palW / 2.f;
        float palTop = palY - palH / 2.f;

        if (x >= palLeft && x <= palRight) {
            if ((y + radius) >= palTop && (y - radius) < palTop) {
                vy = -std::abs(vy);
                y = palTop - radius;
                shape.setPosition(x, y);
                return true;
            }
        }
        return false;
    }

    void draw(sf::RenderTarget& target) { target.draw(shape); }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
    void setVx(float newVx) { vx = newVx; }
    void setVy(float newVy) { vy = newVy; }

    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
        shape.setPosition(x, y);
    }
};