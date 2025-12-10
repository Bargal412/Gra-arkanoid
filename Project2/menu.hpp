#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#define MAX_LICZBA_POZIOMOW 3

class Menu
{
private:
    sf::Font font;
    sf::Text menu[MAX_LICZBA_POZIOMOW];
    int selectedItem = 0;

public:
    Menu(float width, float height);
    ~Menu() {}

    const sf::Font& getFont() const { return font; }

    void przesunG();
    void przesunD();
    int getSelectedItem() const { return selectedItem; }
    void draw(sf::RenderWindow& window);
};

void myDelay(int opoznienie); 

#endif

