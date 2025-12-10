#include "Game1.hpp" 
#include "Gamestate1.hpp" 
#include <iostream>

Game::Game()
    : m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
    m_pilka(320.f, 200.f, 4.f, 3.f, 8.f)
{
    m_score = 0;
    const int ILOSC_KOLUMN = 12;
    const int ILOSC_WIERSZY = 2;
    const int POCZATKOWE_ZYCIE_CEGLI = 3;

    float MARGINES = 2.f;
    float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN + 1) * MARGINES) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 20.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = MARGINES + x * (ROZMIAR_BLOKU_X + MARGINES);
            float posY = y * (ROZMIAR_BLOKU_Y + MARGINES) + 60.f;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                POCZATKOWE_ZYCIE_CEGLI
            );
        }
    }
}


void Game::applyState(const GameState1& state)
{
 
    m_paletka.setPosition(
        state.getPaddlePosition().x,
        state.getPaddlePosition().y
    );

    
    m_pilka.setPosition(
        state.getBallPosition().x,
        state.getBallPosition().y
    );


    m_pilka.setVx(state.getBallVelocity().x);
    m_pilka.setVy(state.getBallVelocity().y);


    m_bloki.clear();
    for (const auto& b : state.getBlocks()) {
        m_bloki.emplace_back(
            sf::Vector2f(b.x, b.y),
            sf::Vector2f((WIDTH - 13 * 2.f) / 12.f, 20.f),
            b.hp
        );
    }
}

void Game::update(sf::Time dt)
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        GameState1 snapshot;
        snapshot.capture(m_paletka, m_pilka, m_bloki);
        snapshot.saveToFile("save.txt");
        std::cout << "Zapisano stan gry (F5)\n";
    }

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
    {
        GameState1 snapshot;
        if (snapshot.loadFromFile("save.txt")) {
            applyState(snapshot);
            std::cout << "Wczytano stan gry (F9)\n";
        }
        else {
            std::cout << "Brak pliku save.txt — nie mo¿na wczytaæ!\n";
        }
    }

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(WIDTH);

   
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);
    m_pilka.collidePaddle(m_paletka);

    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
        std::cout << "MISS! KONIEC GRY\n";
        m_isGameOver = true;
    }

    
    for (int i = static_cast<int>(m_bloki.size()) - 1; i >= 0; i--) {
        if (m_pilka.getGlobalBounds().intersects(m_bloki[i].getGlobalBounds())) {
            m_bloki[i].trafienie();
            m_pilka.bounceY();

            if (m_bloki[i].czyZniszczony())
                m_bloki.erase(m_bloki.begin() + i);
                m_score += 5;

            return;
        }
    }
}


void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (auto& blk : m_bloki)
        blk.draw(target);
}


void Game::reset()
{
    m_isGameOver = false;
    m_score = 0;
    m_pilka.setPosition(WIDTH / 2.f, HEIGHT / 3.f);
    m_paletka.setPosition(WIDTH / 2.f - m_paletka.getSzerokosc() / 2.f, 440.f);

    m_bloki.clear();

    const int ILOSC_KOLUMN = 12;
    const int ILOSC_WIERSZY = 2;
    const int POCZATKOWE_ZYCIE_CEGLI = 3;

    float MARGINES = 2.f;
    float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN + 1) * MARGINES) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 20.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = MARGINES + x * (ROZMIAR_BLOKU_X + MARGINES);
            float posY = y * (ROZMIAR_BLOKU_Y + MARGINES) + 60.f;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                POCZATKOWE_ZYCIE_CEGLI
            );
        }
    }
}