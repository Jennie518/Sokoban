#include <SFML/Graphics.hpp>
#include "Gamehelpers.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban 123");
    bool gameStarted = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!gameStarted) {
                welcome(window, gameStarted);
            }
            if (gameStarted) {
                move(window);
            }
        }
    }

    return 0;
}

   

   

