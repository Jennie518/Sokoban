//
//  Gamehelpers.cpp
//  testSFML
//
//  Created by 詹怡君 on 9/19/23.
//

#include "Gamehelpers.hpp"
#include <SFML/Graphics/Text.hpp>

//sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban abc");
//char a[10][10] = {
//    {"  ###   "},
//    {"  #6#   "},
//    {"  #0####"},
//    {"### o06#"},
//    {"#60  ###"},
//    {"####0#  "},
//    {"   #6#  "},
//    {"   ###  "}
//};
//
//char b[10][10] = {
//    {"########"},
//    {"#   0 6#"},
//    {"#   ####"},
//    {"### o  #"},
//    {"#60    #"},
//    {"### 0# #"},
//    {"#6     #"},
//    {"########"}
//};
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
//int currentLevel = 0;

//bool hasNextLevel() {
//    return currentLevel < (sizeof(levels) / sizeof(levels[0]) - 1);
//}
//

// 定义地图元素的尺寸
const float tileSize = 63.0f;

void drawMap(sf::RenderWindow& window, int currentLevel) {
    // 清除窗口
    window.clear();
    //wall
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("../Sokoban pack/PNG/Wall_Brown.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }

    sf::Sprite wallSprite;
    wallSprite.setTexture(wallTexture);
    
    //target
    sf::Texture targetTexture;
    if (!targetTexture.loadFromFile("../Sokoban pack/PNG/EndPoint_Beige.png")) {
        std::cout <<"fail to open target img" << std::endl;
    }
    sf::Sprite targetSprite;
    targetSprite.setTexture(targetTexture);
    
    //box
    sf::Texture boxTexture;
    if (!boxTexture.loadFromFile("../Sokoban pack/PNG/Crate_Yellow.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite boxSprite;
    boxSprite.setTexture(boxTexture);
    
    //player
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../Sokoban pack/PNG/Character5.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    
    //empty
    sf::Texture emptyTexture;
    if (!emptyTexture.loadFromFile("../Sokoban pack/PNG/GroundGravel_Grass.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite emptySprite;
    emptySprite.setTexture(emptyTexture);
    // 遍历地图数组，绘制地图元素
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
//            std::cout << "currrent level: " << currentLevel << "\n";
            char tile = levels[currentLevel][y][x];
            // 设置草皮精灵位置
            emptySprite.setPosition(x * tileSize, y * tileSize);

              // 绘制草皮背景
            window.draw(emptySprite);
//            sf::RectangleShape shape(sf::Vector2f(tileSize, tileSize));
//
            sf::Sprite spriteToDraw;
                    switch (tile) {
                        case '#':
                            // 绘制墙壁
                            spriteToDraw = wallSprite;
                            break;
                        case '6':
                            // 绘制目标
                            spriteToDraw = targetSprite;
                            break;
                        case '0':
                            // 绘制箱子
                            spriteToDraw = boxSprite;
                            break;
                        case 'o':
                            // 绘制玩家
                            spriteToDraw = playerSprite;
                            break;
                        default:
                            break;
                    }
            spriteToDraw.setPosition(x * tileSize, y * tileSize);
            window.draw(spriteToDraw);
        }
    }
    // 显示绘制的内容
    window.display();
}
void move(sf::RenderWindow& window, int currentLevel){
    int x,y;
    x=3;
    y=4;
    drawMap(window, currentLevel);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle keyboard events
            if (event.type == sf::Event::KeyPressed) {
                int dx = 0, dy = 0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    dx = 1;
                }
                if (event.key.code == sf::Keyboard::W) {
                    dx = -1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    dy = -1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    dy = 1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    bool gameStarted = false;
                    window.clear();
                    welcome(window, gameStarted);
                }

                // Check the next position and the position after that
                
                if(dx != 0 || dy != 0) {
                    char nextPos = levels[currentLevel][x+dx][y+dy];
                    char nextNextPos = levels[currentLevel][x+2*dx][y+2*dy];
                    if (nextPos != '#' && (nextPos != '0' || (nextNextPos != '#' && nextNextPos != '0'))) {
                        // If player is pushing a box
                        if (nextPos == '0') {
                            levels[currentLevel][x+2*dx][y+2*dy] = '0';
                           
                        }
                        if(levels[currentLevel][x][y] =='6'){
                            levels[currentLevel][x][y] = '6';
                        }
                        else{
                            levels[currentLevel][x][y] =' ';
                        }
                        
                        levels[currentLevel][x+dx][y+dy] = 'o';
                        x += dx;
                        y += dy;
                        drawMap(window, currentLevel);
                    }
                }
            }
      }
                
        if (levels[0][1][3] == '0' &&levels[0][6][4] == '0' && levels[0][4][1] == '0' && levels[0][3][6] == '0')
            {
//                currentLevel++;
                // enter next level
                if (currentLevel == 0) {
                    move(window, currentLevel + 1);
                }
            }
        if(levels[1][1][6] == '0' && levels[1][4][1] == '0' && levels[1][6][1] == '0'){
            sf::Font font;
            if(!font.loadFromFile("../fonts/InclusiveSans-Regular.ttf")) {
                std::cerr << "Failed to load font." << std::endl;
                    }
            window.clear();

                sf::Text winText;
                winText.setFont(font);
                winText.setCharacterSize(40);
                winText.setPosition(200, 200);
                winText.setString("You Win!");
                winText.setFillColor(sf::Color::Yellow);

                window.draw(winText);
                window.display();
                sf::sleep(sf::seconds(2));

                // Close the window
                window.close();
        }
                }
}

void welcome(sf::RenderWindow& window, bool& gameStarted){
    int choice = 0;
    int currentMenu = 0;
    window.clear();
    sf::Text welcomeText;
    sf::Font font;
    if (!font.loadFromFile("../fonts/InclusiveSans-Regular.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(24);
    welcomeText.setPosition(10, 10);
    welcomeText.setString("Sokoban\n\n1. Play\n2. Game rules");
    welcomeText.setFillColor(sf::Color::White);
    sf::Text rulesText;
    // rulesText.setFont(font);
    rulesText.setFont(font);
    rulesText.setCharacterSize(24);
    rulesText.setPosition(30, 30);
    rulesText.setString("Rules:\nPress 'W,S,A,D' to control movement\nPush green box to yellow destination\nPress 'q' to exit\nPress 1 to return");
    rulesText.setFillColor(sf::Color::White);
    while (choice == 0) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // deal with keyboard input
            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == 0) {
                    std::cout << "choid is 0 now\n";
                    if (event.key.code == sf::Keyboard::Num1) {
                        choice = 1; // choose 1 to start
                    } else if (event.key.code == sf::Keyboard::Num2) {
                        currentMenu = 1;
                        // choose 2 to swift to rules menue
                    }
                } else if (currentMenu == 1) {
                    if (event.key.code == sf::Keyboard::Num1) {
                        currentMenu = 0; // press 1 return welcome page
                    }
                }
            }
        }
        if (currentMenu == 0) {
            window.clear();
            window.draw(welcomeText);
            window.display();
        }
        else if (currentMenu == 1) {
            window.clear();
            window.draw(rulesText);
            window.display();
        }
            
    }
    if (choice == 1) {
        std::cout << "choice becomes 1!\n";
        gameStarted = true;
        window.clear();
        move(window, 0);
    }
}

