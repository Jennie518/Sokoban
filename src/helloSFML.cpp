#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gamehelpers.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban 123");
    
    bool gameStarted = false;
    int currentLevel = 0;
    
    sf::Music backgroundMusic; // Initialize the background music object
    
    // Load the background music once, outside the loop
    if (!backgroundMusic.openFromFile("../Sokoban pack/main.ogg")) {
        std::cerr << "Failed to open background music file." << std::endl;
    }
    backgroundMusic.setVolume(20);
    backgroundMusic.setLoop(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        if (!gameStarted) {
            welcome(window, gameStarted);
        }
        else {
            // Play the background music if it's not already playing
            if (backgroundMusic.getStatus() != sf::Music::Playing) {
                backgroundMusic.play();
            }

            move(window, currentLevel, backgroundMusic);  // Pass the backgroundMusic reference to the move function
            
            window.display();
        }
    }
    return 0;
}
