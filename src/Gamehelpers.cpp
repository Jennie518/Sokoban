//
//  Gamehelpers.cpp
//  testSFML

//

#include "Gamehelpers.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

// Define a array to represent levels
char levels[2][10][10] = {
    {
        {"  ###   "},
        {"  #6#   "},
        {"  #0####"},
        {"### o06#"},
        {"#60  ###"},
        {"####0#  "},
        {"   #6#  "},
        {"   ###  "}
    },
    {
        {"########"},
        {"#   0 6#"},
        {"#   ####"},
        {"### o  #"},
        {"#60    #"},
        {"### 0# #"},
        {"#6     #"},
        {"########"}
    }
};

// Define sound variables for a box being pushed
sf::SoundBuffer boxPushedSoundBuffer;
sf::Sound boxPushedSound;
sf::SoundBuffer winnerSoundBuffer;
sf::Sound winnerSound;
// Set the size of each game tile
const float tileSize = 63.0f;

// Function to draw the game map on the screen
void drawMap(sf::RenderWindow& window, int currentLevel) {
    // Start by clearing the previous contents of the window
    window.clear();
    
    // Load the wall texture and handle any loading errors
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("../Sokoban pack/PNG/Wall_Brown.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }

    // Create a sprite for the wall and assign the loaded texture to it
    sf::Sprite wallSprite;
    wallSprite.setTexture(wallTexture);
    
    // Load the target texture (same steps as above)
    sf::Texture targetTexture;
    if (!targetTexture.loadFromFile("../Sokoban pack/PNG/EndPoint_Beige.png")) {
        std::cout <<"fail to open target img" << std::endl;
    }
    sf::Sprite targetSprite;
    targetSprite.setTexture(targetTexture);
    
    // Load the box texture (same steps as above)
    sf::Texture boxTexture;
    if (!boxTexture.loadFromFile("../Sokoban pack/PNG/Crate_Yellow.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite boxSprite;
    boxSprite.setTexture(boxTexture);
    
    // Load the player texture (same steps as above)
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../Sokoban pack/PNG/Character5.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    
    // Load the texture for empty ground tiles (same steps as above)
    sf::Texture emptyTexture;
    if (!emptyTexture.loadFromFile("../Sokoban pack/PNG/GroundGravel_Grass.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite emptySprite;
    emptySprite.setTexture(emptyTexture);

    // Go through each tile in the current level
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {

            char tile = levels[currentLevel][y][x];

            // Set the background of every tile to be the empty ground sprite
            emptySprite.setPosition(x * tileSize, y * tileSize);
            window.draw(emptySprite);

            // Decide which sprite to draw based on the character from the levels array
            sf::Sprite spriteToDraw;
                    switch (tile) {
                        case '#':
                            // Wall
                            spriteToDraw = wallSprite;
                            break;
                        case '6':
                            // Target
                            spriteToDraw = targetSprite;
                            break;
                        case '0':
                            // Box
                            spriteToDraw = boxSprite;
                            break;
                        case 'o':
                            // Player
                            spriteToDraw = playerSprite;
                            break;
                        default: // For other characters, no additional sprite is drawn
                            break;
                    }
            // Set the position for the sprite based on the tile's x, y coordinates and draw it
            spriteToDraw.setPosition(x * tileSize, y * tileSize);
            window.draw(spriteToDraw);
        }
    }
    window.display();
}

// This function handles player movement within the game
void move(sf::RenderWindow& window, int currentLevel, sf::Music& backgroundMusic)
{
    // Initialize player's starting position on the map
    int x,y;
    x=3;
    y=4;
    
    if (!winnerSoundBuffer.loadFromFile("../Sokoban pack/winneris.ogg")) {
        std::cout << "Failed to load winner sound." << std::endl;
    }
    winnerSound.setBuffer(winnerSoundBuffer);

    // Load the sound effect for when a box is pushed
    if (!boxPushedSoundBuffer.loadFromFile("../Sokoban pack/icon.ogg")) {
        std::cout << "Failed to load box pushed sound." << std::endl;
    }
    boxPushedSound.setBuffer(boxPushedSoundBuffer);
    
    sf::Font font;
        if (!font.loadFromFile("../fonts/Anton-Regular.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
        }

        
        sf::Text levelText;
        levelText.setFont(font);
        levelText.setCharacterSize(80);
        std::string levelStr = "Level " + std::to_string(currentLevel + 1);  // 关卡计数从1开始
        levelText.setString(levelStr);
        levelText.setFillColor(sf::Color::White);
        levelText.setOutlineThickness(3);
        levelText.setOutlineColor(sf::Color(0, 56, 168));

        sf::FloatRect textRect = levelText.getLocalBounds();
        levelText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        levelText.setPosition(sf::Vector2f(window.getSize().x/2.0f, window.getSize().y/2.0f));

        window.clear(sf::Color(255, 223, 186));
        window.draw(levelText);
        window.display();

        sf::sleep(sf::seconds(1));  // 为提示停留2秒
    
    // Display the initial game map
    drawMap(window, currentLevel);
    
    // Main loop to keep checking for events as long as the window is open
    while (window.isOpen()) {
        sf::Event event;
        
        // Event loop
        while (window.pollEvent(event)) {
            // If the window is closed, exit the game
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Check for key presses
            if (event.type == sf::Event::KeyPressed) {
                int dx = 0, dy = 0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    dx = 1;
                }
                
                // Determine direction of player movement based on key pressed
                if (event.key.code == sf::Keyboard::W) {
                    dx = -1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    dy = -1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    dy = 1;
                }
                // Check for 'Q' key press to quit to the welcome screen
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    bool gameStarted = false;
                    window.clear();
                    welcome(window, gameStarted);
                }
                
                // If a movement key is pressed
                if(dx != 0 || dy != 0) {
                    // Check the character at the next position
                    char nextPos = levels[currentLevel][x+dx][y+dy];
                    // Check the character two positions ahead (useful for determining box movement)
                    char nextNextPos = levels[currentLevel][x+2*dx][y+2*dy];
                    // Conditions for valid movements
                    if (nextPos != '#' && (nextPos != '0' || (nextNextPos != '#' && nextNextPos != '0'))) {
                        // If player is trying to push a box
                        if (nextPos == '0') {
                            levels[currentLevel][x+2*dx][y+2*dy] = '0';
                            
                            // Play sound if the box is being pushed onto a target
                            if (nextNextPos == '6') {
                                boxPushedSound.play();
                            }
                        }
                        
                        // Check if the current position was a target; if so, keep it as a target
                        if(levels[currentLevel][x][y] =='6'){
                            levels[currentLevel][x][y] = '6';
                        }
                        else{
                            levels[currentLevel][x][y] =' ';
                        }
                        // Update the player's position
                        levels[currentLevel][x+dx][y+dy] = 'o';
                        x += dx;
                        y += dy;
                        // Redraw the map to show updated positions
                        drawMap(window, currentLevel);
                    }
                }
            }
        }
        
        // Checking if all boxes in level 0 are placed on their respective targets.
        if (levels[0][1][3] == '0' && levels[0][6][4] == '0' && levels[0][4][1] == '0' && levels[0][3][6] == '0') {
            
            // If the current level is 0, we move to the next level.
            if (currentLevel == 0) {
                move(window, currentLevel + 1, backgroundMusic);  // Calls the move function to start the next level.
 // Calls the move function to start the next level.
            }
        }
        
        if (levels[1][1][6] == '0' && levels[1][4][1] == '0' && levels[1][6][1] == '0') {
            backgroundMusic.stop(); 
            winnerSound.play();
         
            sf::Font font;
            if (!font.loadFromFile("../fonts/Anton-Regular.ttf")) {
                std::cerr << "Failed to load font." << std::endl;
            }
            
            sf::Text winnerText;
            winnerText.setFont(font);
            winnerText.setCharacterSize(80);
            winnerText.setString("Winner!");
            winnerText.setFillColor(sf::Color(0, 56, 168));
            winnerText.setOutlineThickness(3);
            winnerText.setOutlineColor(sf::Color::Black);

            
            sf::FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            winnerText.setPosition(sf::Vector2f(window.getSize().x/2.0f, window.getSize().y/2.0f));
            
            sf::Clock scaleClock;
            bool scaleUp = true;
            
            while (window.isOpen()) {
                sf::Event e;
                while (window.pollEvent(e)) {
                    if (e.type == sf::Event::Closed) {
                        window.close();
                    }
                }
                
                float time = scaleClock.getElapsedTime().asSeconds();
                if (time >= 0.02) { // 每0.02秒更新一次
                    if (scaleUp) {
                        winnerText.scale(1.01f, 1.01f); // 放大1%
                        if (winnerText.getScale().x > 1.5f) scaleUp = false;
                    } else {
                        winnerText.scale(0.99f, 0.99f); // 缩小1%
                        if (winnerText.getScale().x < 1.0f) scaleUp = true;
                    }
                    scaleClock.restart();
                }
                
                sf::Color Gold(255, 223, 186);
                window.clear(Gold);
                window.draw(winnerText);
                window.display();
                
            }
        }
    }
}


// This function is responsible for displaying the welcome menu of the game.
void welcome(sf::RenderWindow& window, bool& gameStarted) {
    int currentMenu = 0;         // Used to track the currently highlighted menu item.
    bool showRules = false;      // Flag to determine if the game rules should be displayed.
    
    // Set up the background music for the welcome screen.
    sf::Music menu;
    if (!menu.openFromFile("../Sokoban pack/puzzlemenu.ogg")) {
        std::cerr << "Failed to open background music file." << std::endl;  // Display error message if music file fails to load.
    }
    // Set the music to loop
    menu.setLoop(true);
    // Play the background music.
    menu.play();
    
    // Load the font used for displaying text on the welcome screen.
    sf::Font font;
    if (!font.loadFromFile("../fonts/Skranji-Bold.ttf")) {
        std::cerr << "Failed to load font." << std::endl;  // Display error message if font file fails to load.
    }
    
    // Set up the game title text displayed at the top of the welcome screen.
    sf::Text gameTitle;
    gameTitle.setFont(font);    // Set the font.
    gameTitle.setString("Sokoban Game"); // Set the text content.
    gameTitle.setCharacterSize(60);  // Set the font size.
    gameTitle.setFillColor(sf::Color::White);  // Set the color of the text.
    gameTitle.setPosition(
                          window.getSize().x / 2 - gameTitle.getLocalBounds().width / 2,  // Position the text in the center of the window.
                          100   // Position the text at a fixed vertical location.
                          );
    
    // Load the textures for the play and rules icons that will be displayed beside their respective menu options.
    sf::Texture playTexture;
    if (!playTexture.loadFromFile("../Sokoban pack/green_sliderRight.png")) {
        std::cerr << "Failed to load play icon texture." << std::endl;  // Display error message if play icon fails to load.
    }
    
    sf::Texture rulesTexture;
    if (!rulesTexture.loadFromFile("../Sokoban pack/green_sliderLeft.png")) {
        std::cerr << "Failed to load rules icon texture." << std::endl;  // Display error message if rules icon fails to load.
    }
    
    // Set up the sprites for the play and rules icons.
    sf::Sprite playSprite;
    playSprite.setTexture(playTexture);   // Set the texture.
    playSprite.setPosition(300, 250);     // Set the position on the window.
    
    sf::Sprite rulesSprite;
    rulesSprite.setTexture(rulesTexture); // Set the texture.
    rulesSprite.setPosition(300, 290);    // Set the position on the window.
    
    // Set up the text for the "Play" and "Game rules" menu options.
    sf::Text playText;
    playText.setFont(font);  // Set the font.
    playText.setCharacterSize(30);  // Set the font size.
    playText.setString("Play");  // Set the text content.
    playText.setPosition(
                         playSprite.getPosition().x + playSprite.getLocalBounds().width + 10,  // Position the text just to the right of the play icon.
                         playSprite.getPosition().y  // Set the vertical position same as the play icon.
                         );
    
    sf::Text rulesText;
    rulesText.setFont(font);  // Set the font.
    rulesText.setCharacterSize(30); // Set the font size.
    rulesText.setString("Game rules"); // Set the text content.
    rulesText.setPosition(
                          rulesSprite.getPosition().x + rulesSprite.getLocalBounds().width + 10, // Position the text just to the right of the rules icon.
                          rulesSprite.getPosition().y   // Set the vertical position same as the rules icon.
                          );
    
    // Load and set up the background image for the welcome menu.
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../Sokoban pack/castle_backround.png")) {
        std::cerr << "Failed to load background image." << std::endl;  // Error message if the background image fails to load.
    }
    
    sf::Sprite backgroundSprite;  // Sprite to display the background image.
    backgroundSprite.setTexture(backgroundTexture);  // Set the loaded texture to the sprite.
    
    // Get the size of the window.
    sf::Vector2u windowSize = window.getSize();
    
    // Get the size of the texture (background image).
    sf::Vector2u textureSize = backgroundTexture.getSize();
    
    // Calculate the necessary scaling factors to fit the background image to the window size.
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    
    // Set the sprite's scale according to the calculated scaling factors.
    backgroundSprite.setScale(scaleX, scaleY);
    
    // Text to display the game rules.
    sf::Text rulesDetailsText;
    rulesDetailsText.setFont(font);   // Set the font.
    rulesDetailsText.setCharacterSize(20);  // Set the font size.
    rulesDetailsText.setPosition(200, 320); // Set the position on the window.
    rulesDetailsText.setString("Rules:\nPress 'W,S,A,D' to control movement\nPush the box to the destination\nPress 'q' to exit");  // Set the text content.
    rulesDetailsText.setFillColor(sf::Color::White);  // Set the text color.
    
    // Main game loop for the welcome menu.
    while (window.isOpen()) {
        
        sf::Event event;
        // Event handling loop.
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close the window if the close button is pressed.
            }
            
            // Handle keyboard inputs.
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {
                    currentMenu = 1;  // Highlight the next menu option.
                } else if (event.key.code == sf::Keyboard::Up) {
                    currentMenu = 0;  // Highlight the previous menu option.
                } else if (event.key.code == sf::Keyboard::Return) {
                    if (currentMenu == 0) {
                        gameStarted = true;  // Set flag to start the game.
                        return;  // Exit the welcome function and start the game.
                    } else {
                        showRules = true;  // Set flag to show game rules.
                    }
                } else if (event.key.code == sf::Keyboard::Escape) {
                    showRules = false;  // If user presses the "Escape" key, hide the game rules.
                }
            }
        }
        
        // Drawing logic.
        // Change the color of the text based on the highlighted menu option.
        playText.setFillColor(currentMenu == 0 ? sf::Color::Yellow : sf::Color::White);
        rulesText.setFillColor(currentMenu == 1 ? sf::Color::Yellow : sf::Color::White);
        
        window.clear();  // Clear the window.
        window.draw(backgroundSprite);  // Draw the background image.
        window.draw(gameTitle);  // Draw the game title.
        window.draw(playSprite);  // Draw the play icon.
        window.draw(rulesSprite); // Draw the rules icon.
        window.draw(playText);  // Draw the play text.
        window.draw(rulesText); // Draw the rules text.
        
        if (showRules) {
            window.draw(rulesDetailsText);  // Draw the detailed game rules if the flag is set.
        }
        
        window.display();  // Display everything drawn to the window.
        
    }
}
