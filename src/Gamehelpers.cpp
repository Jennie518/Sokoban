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
        if (levels[1][1][6] == '0' && levels[1][4][1] == '0' && levels[1][6][1] == '0') {
            sf::Font font;
            if (!font.loadFromFile("../fonts/Anton-Regular.ttf")) {
                std::cerr << "Failed to load font." << std::endl;
            }

            window.clear();
            
            // Step 1: Load the victory image
            sf::Texture victoryTexture;
            if (!victoryTexture.loadFromFile("../Sokoban pack/pizza.png")) {
                std::cerr << "Failed to load victory image." << std::endl;
            }

            sf::Sprite victorySprite;
            victorySprite.setTexture(victoryTexture);

            sf::Clock clock;  // 用于跟踪已过去的时间
            float durationPerText = 2.0f;  // 每句话的渐入时间，单位为秒

            float totalDuration = 2 * durationPerText;  // 两句话的总时间
            bool shouldClose = false;

            while (window.isOpen() && !shouldClose) {
                float elapsed = clock.getElapsedTime().asSeconds();

                // 第一句话的透明度计算
                int alpha1 = std::min(static_cast<int>(255 * (elapsed / durationPerText)), 255);
                
                // 第二句话的透明度计算
                int alpha2 = std::max(0, static_cast<int>(255 * ((elapsed - durationPerText) / durationPerText)));
                
                sf::Text text1;
                text1.setFont(font);
                text1.setCharacterSize(40);
                text1.setPosition(150, 50);
                text1.setString("Congratulations!");
                text1.setFillColor(sf::Color::Red);

                sf::Text text2;
                text2.setFont(font);
                text2.setCharacterSize(40);
                text2.setPosition(150, 100);
                text2.setString("Enjoy your pizza now!");
                text2.setFillColor(sf::Color::Red);

                window.clear(sf::Color::White);
                window.draw(victorySprite);  // Draw the victory image

                window.draw(text1);
                window.draw(text2);
                window.display();

                if (elapsed > totalDuration) {
                    shouldClose = true;
                }
            }

            sf::sleep(sf::seconds(3));
            window.close();
        }

    }
}

void welcome(sf::RenderWindow& window, bool& gameStarted) {
    int currentMenu = 0;
    bool showRules = false;

    sf::Font font;
    if (!font.loadFromFile("../fonts/Skranji-Bold.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    // 创建并设置游戏名字的文本
    sf::Text gameTitle;
    gameTitle.setFont(font);
    gameTitle.setString("Sokoban Game");
    gameTitle.setCharacterSize(60);
    gameTitle.setFillColor(sf::Color::White);
    gameTitle.setPosition(window.getSize().x / 2 - gameTitle.getLocalBounds().width / 2, 100);

    // 加载选项图标的纹理
    sf::Texture playTexture;
    if (!playTexture.loadFromFile("../Sokoban pack/green_sliderRight.png")) {
        std::cerr << "Failed to load play icon texture." << std::endl;
    }

    sf::Texture rulesTexture;
    if (!rulesTexture.loadFromFile("../Sokoban pack/green_sliderLeft.png")) {
        std::cerr << "Failed to load rules icon texture." << std::endl;
    }

    // 创建并设置选项图标的精灵
    sf::Sprite playSprite;
    playSprite.setTexture(playTexture);
    playSprite.setPosition(300, 250);

    sf::Sprite rulesSprite;
    rulesSprite.setTexture(rulesTexture);
    rulesSprite.setPosition(300, 290);

    // 创建菜单项文本
    sf::Text playText;
    playText.setFont(font);
    playText.setCharacterSize(30);
    playText.setString("Play");
    playText.setPosition(playSprite.getPosition().x + playSprite.getLocalBounds().width + 10, playSprite.getPosition().y);

    sf::Text rulesText;
    rulesText.setFont(font);
    rulesText.setCharacterSize(30);
    rulesText.setString("Game rules");
    rulesText.setPosition(rulesSprite.getPosition().x + rulesSprite.getLocalBounds().width + 10, rulesSprite.getPosition().y);

    // 加载和设置背景图像
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../Sokoban pack/castle_backround.png")) {
        std::cerr << "Failed to load background image." << std::endl;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // 获取窗口的大小
    sf::Vector2u windowSize = window.getSize();

    // 获取纹理的大小
    sf::Vector2u textureSize = backgroundTexture.getSize();

    // 计算需要的缩放比例
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // 设置精灵的缩放比例
    backgroundSprite.setScale(scaleX, scaleY);
    
    sf::Text rulesDetailsText;
        rulesDetailsText.setFont(font);
        rulesDetailsText.setCharacterSize(20);
        rulesDetailsText.setPosition(200, 320);
        rulesDetailsText.setString("Rules:\nPress 'W,S,A,D' to control movement\nPush green box to yellow destination\nPress 'q' to exit");
        rulesDetailsText.setFillColor(sf::Color::White);

    while (window.isOpen()) { // 主循环开始

            sf::Event event;
        while (window.pollEvent(event)) { // 事件处理开始
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {
                    currentMenu = 1;
                } else if (event.key.code == sf::Keyboard::Up) {
                    currentMenu = 0;
                } else if (event.key.code == sf::Keyboard::Return) {
                    if (currentMenu == 0) {
                        gameStarted = true;
                        return; // 退出 welcome 函数，开始游戏
                    } else {
                        showRules = true; // 设置标志，显示游戏规则
                    }
                } else if (event.key.code == sf::Keyboard::Escape) {
                    showRules = false; // 如果用户按下 "Escape" 键，不显示规则
                }
            }
        }

            // 绘图逻辑开始
            playText.setFillColor(currentMenu == 0 ? sf::Color::Yellow : sf::Color::White);
            rulesText.setFillColor(currentMenu == 1 ? sf::Color::Yellow : sf::Color::White);

            window.clear();
            window.draw(backgroundSprite);
            window.draw(gameTitle);
            window.draw(playSprite);
            window.draw(rulesSprite);
            window.draw(playText);
            window.draw(rulesText);
            
            if (showRules) {
                window.draw(rulesDetailsText);
            }

            window.display();
            // 绘图逻辑结束
            
        } // 主循环结束
    }
