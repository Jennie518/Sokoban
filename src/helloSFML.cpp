#include <SFML/Graphics.hpp>
#include "Gamehelpers.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban 123");
    bool gameStarted = false;
    int currentLevel = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!gameStarted) {
            welcome(window, gameStarted);
        } else {
            move(window, currentLevel);
        }

        window.display();
    }

    return 0;
}
