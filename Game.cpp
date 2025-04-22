#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Hopper.h"
#include "Jumper.h"
#include "Crawler.h"

int main() {
    const int gridSize = 10;
    const int tileSize = 60;

    sf::RenderWindow window(sf::VideoMode(gridSize * tileSize, gridSize * tileSize + 100), "A Bug's Life - SFML");

    Board board(gridSize, gridSize);
    board.loadBugsFromFile("bugs.txt");

    sf::Texture superBugTexture, hopperTexture, jumperTexture, crawlerTexture;
    if (!superBugTexture.loadFromFile("superbug.png") ||
        !hopperTexture.loadFromFile("hopper.png") ||
        !jumperTexture.loadFromFile("jumper.png") ||
        !crawlerTexture.loadFromFile("crawler.png")) {
        std::cerr << "Failed to load one or more bug textures" << std::endl;
        return 1;
    }

    sf::Sprite superBugSprite;
    superBugSprite.setTexture(superBugTexture);
    superBugSprite.setScale(
        static_cast<float>(tileSize) / superBugTexture.getSize().x,
        static_cast<float>(tileSize) / superBugTexture.getSize().y
    );

    int superX = 0, superY = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && superY > 0) superY--;
                if (event.key.code == sf::Keyboard::Down && superY < gridSize - 1) superY++;
                if (event.key.code == sf::Keyboard::Left && superX > 0) superX--;
                if (event.key.code == sf::Keyboard::Right && superX < gridSize - 1) superX++;
                if (event.key.code == sf::Keyboard::Space) {
                    board.moveAll();
                    board.tapBoard();
                }
            }
        }

        board.superBugFight(superX, superY);

        window.clear(sf::Color::White);

        for (int y = 0; y < gridSize; ++y) {
            for (int x = 0; x < gridSize; ++x) {
                sf::RectangleShape cell(sf::Vector2f(tileSize, tileSize));
                cell.setPosition(x * tileSize, y * tileSize);
                cell.setFillColor(sf::Color(220, 220, 220));
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);
                window.draw(cell);
            }
        }

        for (Bug* bug : board.getBugs()) {
            if (!bug->isAlive()) continue;

            Position pos = bug->getPosition();
            sf::Sprite bugSprite;

            if (dynamic_cast<Hopper*>(bug)) {
                bugSprite.setTexture(hopperTexture);
            } else if (dynamic_cast<Jumper*>(bug)) {
                bugSprite.setTexture(jumperTexture);
            } else if (dynamic_cast<Crawler*>(bug)) {
                bugSprite.setTexture(crawlerTexture);
            } else {
                continue; // Unknown type
            }

            bugSprite.setScale(
                static_cast<float>(tileSize) / bugSprite.getTexture()->getSize().x,
                static_cast<float>(tileSize) / bugSprite.getTexture()->getSize().y
            );
            bugSprite.setPosition(pos.x * tileSize, pos.y * tileSize);
            window.draw(bugSprite);
        }

        superBugSprite.setPosition(superX * tileSize, superY * tileSize);
        window.draw(superBugSprite);

        window.display();
    }

    return 0;
}