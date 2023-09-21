//
//  Gamehelpers.cpp
//  testSFML
//
//  Created by 詹怡君 on 9/19/23.
//

#include "Gamehelpers.hpp"
#include <SFML/Graphics/Text.hpp>

//sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban abc");
char a[10][10] = {
    {"  ###   "},
    {"  #6#   "},
    {"  #0####"},
    {"### o06#"},
    {"#60  ###"},
    {"####0#  "},
    {"   #6#  "},
    {"   ###  "}
};
//sf::RenderWindow& window = NULL;

// 声明一个字体对象

// 定义地图元素的尺寸
const float tileSize = 63.0f;

void drawMap(sf::RenderWindow& window) {
    // 清除窗口
    window.clear();
    
    //wall
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("/Users/caleychen/Desktop/Final Project/Sokoban pack/PNG/Wall_Brown.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }

    sf::Sprite wallSprite;
    wallSprite.setTexture(wallTexture);
    
    //target
    sf::Texture targetTexture;
    if (!targetTexture.loadFromFile("/Users/caleychen/Desktop/Final Project/Sokoban pack/PNG/EndPoint_Beige.png")) {
        std::cout <<"fail to open target img" << std::endl;
    }
    sf::Sprite targetSprite;
    targetSprite.setTexture(targetTexture);
    
    //box
    sf::Texture boxTexture;
    if (!boxTexture.loadFromFile("/Users/caleychen/Desktop/Final Project/Sokoban pack/PNG/Crate_Yellow.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite boxSprite;
    boxSprite.setTexture(boxTexture);
    
    //player
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("/Users/caleychen/Desktop/Final Project/Sokoban pack/PNG/Character5.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    
    //empty
    sf::Texture emptyTexture;
    if (!emptyTexture.loadFromFile("/Users/caleychen/Desktop/Final Project/Sokoban pack/PNG/GroundGravel_Grass.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite emptySprite;
    emptySprite.setTexture(emptyTexture);
    // 遍历地图数组，绘制地图元素
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            char tile = a[y][x];
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

// 根据地图元素绘制不同的颜色
//            if (tile == '#') {
//                shape.setFillColor(sf::Color::Black); // 墙壁
//            } else if (tile == '0') {
//                shape.setFillColor(sf::Color::Yellow); // 目标
//            } else if (tile == '6') {
//                shape.setFillColor(sf::Color::Green); // 箱子
//            } else if (tile == 'o') {
//                shape.setFillColor(sf::Color::Red); // 玩家
//            } else {
//                shape.setFillColor(sf::Color::White); // 空地
//            }
//
//            window.draw(shape);


void move(sf::RenderWindow& window){
    int x,y;
    x=3;
    y=4;
    drawMap(window);
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    bool gameStarted = false;
                    window.clear();
                    welcome(window, gameStarted);
                }

                // Check the next position and the position after that
                if(dx != 0 || dy != 0) {
                    char nextPos = a[x+dx][y+dy];
                    char nextNextPos = a[x+2*dx][y+2*dy];
                    
                    if (nextPos != '#' && (nextPos != '0' || (nextNextPos != '#' && nextNextPos != '0'))) {
                        // If player is pushing a box
                        if (nextPos == '0') {
                            a[x+2*dx][y+2*dy] = '0';
                            a[x+dx][y+dy] = 'o';
                        } else {
                            a[x+dx][y+dy] = 'o';
                        }
                        a[x][y] = ' ';
                        x += dx;
                        y += dy;
                        drawMap(window);
                    }
                }
            }
      }

                if (a[1][3] == '0' && a[6][4] == '0' && a[4][1] == '0' && a[3][6] == '0') {
                // You win condition
                sf::Font font;
                    if (!font.loadFromFile("/Users/caleychen/Desktop/Final Project/fonts/Skranji-Bold.ttf")) {
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
    
    sf::Font font;
    if (!font.loadFromFile("/Users/caleychen/Desktop/Final Project/fonts/InclusiveSans-Regular.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    

    // 创建一个作为背景的矩形
    sf::RectangleShape background(sf::Vector2f(500, 300));
    background.setFillColor(sf::Color(100, 100, 100, 255));
    background.setPosition(150, 150);
    background.setOutlineThickness(5);
    background.setOutlineColor(sf::Color::White);
    
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(24);
    welcomeText.setPosition(200, 200);
    welcomeText.setString("Sokoban\n\n> Play\n  Game rules");
    welcomeText.setFillColor(sf::Color::Yellow);

    sf::Text rulesText;
    rulesText.setFont(font);
    rulesText.setCharacterSize(24);
    rulesText.setPosition(200, 250);
    rulesText.setString("Rules:\nPress 'W,S,A,D' to control movement\nPush green box to yellow destination\nPress 'q' to exit\nPress 'Up' or 'Down' to navigate\nPress 'Enter' to select");
    rulesText.setFillColor(sf::Color::White);

    while (choice == 0) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // 处理键盘输入
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down && currentMenu == 0) {
                    welcomeText.setString("Sokoban\n\n  Play\n> Game rules");
                    currentMenu = 1;
                } else if (event.key.code == sf::Keyboard::Up && currentMenu == 1) {
                    welcomeText.setString("Sokoban\n\n> Play\n  Game rules");
                    currentMenu = 0;
                } else if (event.key.code == sf::Keyboard::Return) {
                    choice = currentMenu + 1;
                }
            }
        }

        window.clear();
        window.draw(background);
        if (currentMenu == 0) {
            window.draw(welcomeText);
        } else if (currentMenu == 1) {
            window.draw(rulesText);
        }
        window.display();
    }

    if (choice == 1) {
        gameStarted = true;
        window.clear();
        move(window);
    }
}



