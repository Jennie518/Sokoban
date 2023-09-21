//
//  Gamehelpers.cpp
//  testSFML
//
//  Created by 詹怡君 on 9/19/23.
//

#include "Gamehelpers.hpp"
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
    if (!wallTexture.loadFromFile("/Users/zhanyijun/Desktop/MSD/CS6010/Final Project/Sokoban pack/PNG/Wall_Brown.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }

    sf::Sprite wallSprite;
    wallSprite.setTexture(wallTexture);
    
    //target
    sf::Texture targetTexture;
    if (!targetTexture.loadFromFile("/Users/zhanyijun/Desktop/MSD/CS6010/Final Project/Sokoban pack/PNG/EndPoint_Beige.png")) {
        std::cout <<"fail to open target img" << std::endl;
    }
    sf::Sprite targetSprite;
    targetSprite.setTexture(targetTexture);
    
    //box
    sf::Texture boxTexture;
    if (!boxTexture.loadFromFile("/Users/zhanyijun/Desktop/MSD/CS6010/Final Project/Sokoban pack/PNG/Crate_Yellow.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite boxSprite;
    boxSprite.setTexture(boxTexture);
    
    //player
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("/Users/zhanyijun/Desktop/MSD/CS6010/Final Project/Sokoban pack/PNG/Character5.png")) {
        std::cout <<"fail to open wall img" << std::endl;
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    
    //empty
    sf::Texture emptyTexture;
    if (!emptyTexture.loadFromFile("/Users/zhanyijun/Desktop/MSD/CS6010/Final Project/Sokoban pack/PNG/GroundGravel_Grass.png")) {
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
    int x,y,p,q;
    x=3;
    y=4;
    p=5;
    q=10;
    drawMap(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // 处理键盘事件
            if (event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    // S键被按下
                    if(a[x+1][y]!='#' && a[x+1][y]=='0')
                    {
                        a[x+2][y]='0';
                        a[x][y]=' ';
                        a[x+1][y]='o';
                    }
                    if(a[x+1][y]!='#') {
                        a[x][y]=' ';
                        x++;
                        a[x][y]='o';
                        drawMap(window);
                    }
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    // 处理 W 键被按下的情况
                    if(a[x-1][y]!='#'&&a[x-1][y]=='0')
                    {
                        a[x-2][y]='0';
                        a[x][y]=' ';
                        a[x-1][y]='o';
                    }
                    if(a[x-1][y]!='#') {
                        a[x][y]=' ';
                        x--;
                        a[x][y]='o';
                        drawMap(window);
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    // 处理 A 键被按下的情况
                    if(a[x][y-1]!='#'&&a[x][y-1]=='0')
                    {
                        a[x][y-2]='0';
                        a[x][y]=' ';
                        a[x][y-1]='o';
                    }
                    if(a[x][y-1]!='#')
                    {
                        a[x][y]=' ';
                        y--;
                        a[x][y]='o';
                        drawMap(window);
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    if(a[x][y+1]!='#'&&a[x][y+1]=='0')
                    {
                        a[x][y+2]='0';
                        a[x][y]=' ';
                        a[x][y+1]='o';
                    }
                    if(a[x][y+1]!='#')
                    {
                        a[x][y]=' ';
                        y++;
                        a[x][y]='o';
                        window.clear();
                        drawMap(window);
                    }
                }
                if(a[1][3]=='0' && a[6][4]=='0' && a[4][1]=='0' && a[3][6]=='0')
                {
                    std::cout<<"You're Win";
                    window.close();
                    break;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    bool gameStarted = false;
                    window.clear();
                    welcome(window, gameStarted);
                }
            }
        }
    }
}
void welcome(sf::RenderWindow& window, bool& gameStarted){
    int choice = 0;
    int currentMenu = 0;
    window.clear();
    sf::Text welcomeText;
    sf::Font font;
    if (!font.loadFromFile("/Users/zhanyijun/Desktop/MSD/CS6010/Final Project/fonts/InclusiveSans-Regular.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
    }
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(24);
    welcomeText.setPosition(10, 10);
    welcomeText.setString("Sokoban\n\n1. Play\n2. Game rules");
    welcomeText.setFillColor(sf::Color::Red);
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
                     if (event.key.code == sf::Keyboard::Num1) {
                         choice = 1; // choose 1 to start
                     } else if (event.key.code == sf::Keyboard::Num2) {
                         currentMenu = 1; // choose 2 to swift to rules menue
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
         } else if (currentMenu == 1) {
             window.clear();
             window.draw(rulesText);
             window.display();
         }
         
     }
     if (choice == 1) {
         gameStarted = true;
         window.clear();
         move(window);
     }
 }



//
//     while (window.isOpen() && choice == 0) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//             // 处理用户的键盘输入
//             if (event.type == sf::Event::KeyPressed) {
//                 if (event.key.code == sf::Keyboard::Num1) {
//                     choice = 1; // 用户选择了1，开始游戏
//                 } else if (event.key.code == sf::Keyboard::Num2) {
//                     choice = 2; // 用户选择了2，查看游戏规则
//                 }
//             }
//         }
//
//         window.clear();
//         window.draw(welcomeText);
//         window.display();
//     }
//
//     if (choice == 1) {
//         gameStarted = true;
//         window.clear();
//         move();
//     }
//    else if(choice==2){
//        system("clear");
//        std::cout<<"Rules:"<<std::endl;
//        std::cout<<"Press 'W,S,A,D' to control movement  push green box to yellow destination "<<std::endl;
//        std::cout<<"Press 'q' to exit";
//        std::cout<<"Press 1 to return";
//        std::cin>>choice;
//    }
//           if(choice==1)
//           {
//               welcome(window, gameStarted);
//           }
//       }
//   }
//       window.clear();
//       window.draw(welcomeText);
//       window.display();
//}

   
