//
// Created by mateu on 20.06.2022.
//

#ifndef SNAKE_GAME_GUI_H
#define SNAKE_GAME_GUI_H

#include <string>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Snake.h"

using namespace std;

class GUI {
private:
    sf::RenderWindow *window;
    sf::Sprite orange, refresh, red, fondo;
    Snake snake = Snake();
    int good = true;
    int dir = 0, speed = 700;
    bool gameIsRunning = true;
    int randomX{}, randomY{};
    sf::Texture squareTexture, refreshTexture, backgroundTexture;

public:
    explicit GUI(sf::RenderWindow *window) { this->window = window; }

    void createTextures();
    void setSpritesParameters();
    void checkRefreshButton(sf::Event appEvent);
    void drawState();
    void setDirection(int dir){this->dir = dir;}
    void handleKeyboard(sf::Event appEvent, GUI gui);
    static tuple<int, int> getRandomCoords();
};


#endif //SNAKE_GAME_GUI_H
