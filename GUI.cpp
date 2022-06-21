//
// Created by mateu on 20.06.2022.
//

#include "GUI.h"

void GUI::createTextures() {
    squareTexture.loadFromFile("square.jpg");
    refreshTexture.loadFromFile("refresh.png");
    backgroundTexture.loadFromFile("background.jpg");
}

void GUI::setSpritesParameters() {
    orange.setTexture(squareTexture);
    refresh.setTexture(refreshTexture);
    red.setTexture(squareTexture);
    fondo.setTexture(backgroundTexture);
    orange.setPosition(0, 0);
    orange.setColor(sf::Color(255, 120, 0));
    red.setPosition(1000, 0);
    red.setColor(sf::Color(255, 0, 36));
}

tuple<int, int> GUI::getRandomCoords() {
    return std::make_tuple(1 + rand()%450, 1 + rand()%450);
}

void GUI::checkRefreshButton(sf::Event appEvent) {
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    if(appEvent.type == sf::Event::MouseButtonReleased){
        if(refresh.getGlobalBounds().contains(pos.x, pos.y)){
            if(!gameIsRunning){
                gameIsRunning = true;
                refresh.setPosition(1000, 0);
                snake.setSnakeSize(1);
                snake.p[0].x = 0;
                snake.p[0].y = 0;
                dir = 0;
                speed = 700;
                good = true;

                while(good){
                    tie(randomX, randomY) = getRandomCoords();
                    for(int i = 0; i<9; i++){
                        if(randomX <= (i+1)*50 && randomX > i*50) randomX=(i+1)*50;
                        if(randomY <= (i+1)*50 && randomY > i*50) randomY=(i+1)*50;
                    }
                    for(int i = 0; i < snake.getSnakeSize(); i++){
                        if(randomX != snake.p[i].x ||randomY != snake.p[i].y ) good = false;
                    }
                }
            }
        }
    }
}

void GUI::drawState() {
    if(gameIsRunning){
        refresh.setPosition(1000,0);
        window->draw(fondo);

        for(int i = snake.getSnakeSize(); i > 0; i--){
            snake.p[i].x = snake.p[i-1].x;
            snake.p[i].y = snake.p[i-1].y;
        }

        if(dir == 0) snake.p[0].x += 50;
        if(dir == 1) snake.p[0].x -= 50;
        if(dir == 2) snake.p[0].y += 50;
        if(dir == 3) snake.p[0].y -= 50;
        if(snake.p[0].x == 500 || snake.p[0].x == -50 || snake.p[0].y == 500 || snake.p[0].y == -50) gameIsRunning = false;

        for(int i = 1; i < snake.getSnakeSize(); i++){
            if(snake.p[0].x == snake.p[i].x && snake.p[0].y == snake.p[i].y) gameIsRunning = false;
        }

        if(snake.p[0].x == red.getPosition().x && snake.p[0].y == red.getPosition().y){
            snake.setSnakeSize(snake.getSnakeSize() + 1);
            if(speed>100)speed-=20;
            good = true;
            while(good){
                tie(randomX, randomY) = getRandomCoords();

                for(int i = 0; i<9; i++){
                    if(randomX <= (i+1)*50 && randomX > i*50) randomX=(i+1)*50;
                    if(randomY <= (i+1)*50 && randomY > i*50) randomY=(i+1)*50;
                }
                for(int i = 0; i < 9; i++){
                    if(randomX == snake.p[i].x && randomY == snake.p[i].y){
                        break;
                    }else if((randomX != snake.p[i].x ||randomY != snake.p[i].y ) && i == snake.getSnakeSize()-1){
                        good = false;
                    }
                }
            }
        }

        red.setPosition(randomX, randomY);
        window->draw(red);

        for(int i = 0; i<snake.getSnakeSize();i++){
            orange.setPosition(snake.p[i].x,snake.p[i].y);
            window->draw(orange);
        }
        window->display();
        Sleep(speed);
    }else{
        window->draw(fondo);
        refresh.setPosition(100, 100);
        window->draw(refresh);
        window->display();
    }
}

void GUI::handleKeyboard(sf::Event appEvent, GUI gui) {
    if (appEvent.type == sf::Event::KeyPressed) {
        if (gameIsRunning) {
            if (appEvent.key.code == sf::Keyboard::Right && dir != 1) dir = 0;
            else if (appEvent.key.code == sf::Keyboard::Left && dir != 0) dir = 1;
            else if (appEvent.key.code == sf::Keyboard::Down && dir != 3) dir = 2;
            else if (appEvent.key.code == sf::Keyboard::Up && dir != 2) dir = 3;
            gui.setDirection(dir);
        }
    }
}
