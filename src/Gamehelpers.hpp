//
//  Gamehelpers.hpp
//  testSFML
//
//  Created by 詹怡君 on 9/19/23.
//
#include <SFML/Graphics.hpp>
#ifndef Gamehelpers_hpp
#define Gamehelpers_hpp
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<stdio.h>

#import <Availability.h>


//#import <Foundation/Foundation.h>
void welcome(sf::RenderWindow& window, bool& gameStarted);
void move(sf::RenderWindow& window, int currentLevel);
void print();
void drawMap(sf::RenderWindow& window);
#endif /* Gamehelpers_hpp */
