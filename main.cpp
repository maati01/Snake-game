#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;

int dir = 0, speed = 500, size = 1;
int randomX = 0, randomY = 0;
bool good = true, gameIsRunning = true;


struct Point{
    int x = 0;
    int y = 0;
}p[100];

int main() {
    RenderWindow appWindow(VideoMode(500, 500), "Snake");
    Event appEvent;

    Texture squaret, refresht, backgroundt;
    squaret.loadFromFile("square.jpg");
    refresht.loadFromFile("refresh.png");
    backgroundt.loadFromFile("background.jpg");

    Sprite orange(squaret), refresh(refresht), red(squaret), fondo(backgroundt);
    orange.setPosition(0,0);
    orange.setColor(Color(255, 120, 0));
    red.setPosition(1000, 0);
    red.setColor(Color(255,0,36));

    srand(time(NULL));
    randomX = 1 + rand()%450;
    randomY = 1 + rand()%450;

    for(int i = 0; i<9; i++){
        if(randomX <= (i+1)*50 && randomX > i*50) randomX=(i+1)*50;
        if(randomY <= (i+1)*50 && randomY > i*50) randomY=(i+1)*50;

    }

    while(appWindow.isOpen()){
        Vector2i pos = Mouse::getPosition(appWindow);

        while(appWindow.pollEvent(appEvent)){
            if(appEvent.type == Event::Closed){
                appWindow.close();
            }

            if(appEvent.type == Event::MouseButtonReleased){
                if(refresh.getGlobalBounds().contains(pos.x, pos.y)){
                    if(!gameIsRunning){
                        gameIsRunning = true;
                        refresh.setPosition(1000, 0);
                        size = 1;
                        p[0].x = 0;
                        p[0].y = 0;
                        dir = 0;
                        speed = 700;
                        good = true;

                        while(good){
                            randomX = 1 + rand()%450;
                            randomY = 1 + rand()%450;

                            for(int i = 0; i<9; i++){
                                if(randomX <= (i+1)*50 && randomX > i*50) randomX=(i+1)*50;
                                if(randomY <= (i+1)*50 && randomY > i*50) randomY=(i+1)*50;

                            }
                            for(int i = 0; i < size; i++){
                                if(randomX != p[i].x ||randomY != p[i].y ) good = false;

                            }
                        }
                    }
                }
            }

            if(appEvent.type == Event::KeyPressed){
                if(gameIsRunning){
                    if(appEvent.key.code == Keyboard::Right && dir != 1) dir = 0;
                    else if(appEvent.key.code == Keyboard::Left && dir != 0) dir = 1;
                    else if(appEvent.key.code == Keyboard::Down && dir != 3) dir = 2;
                    else if(appEvent.key.code == Keyboard::Up && dir != 2) dir = 3;

                }
            }
        }
        appWindow.clear(Color(26, 28, 36));

        if(gameIsRunning){
            refresh.setPosition(1000,0);
            appWindow.draw(fondo);

            for(int i = size; i > 0; i--){
                p[i].x = p[i-1].x;
                p[i].y = p[i-1].y;
            }

            if(dir == 0) p[0].x += 50;
            if(dir == 1) p[0].x -= 50;
            if(dir == 2) p[0].y += 50;
            if(dir == 3) p[0].y -= 50;
            if(p[0].x == 500 || p[0].x == -50 || p[0].y == 500 || p[0].y == -50) gameIsRunning = false;

            for(int i = 1; i < size; i++){
                if(p[0].x == p[i].x && p[0].y == p[i].y) gameIsRunning = false;
            }

            if(p[0].x == red.getPosition().x && p[0].y == red.getPosition().y){
                size += 1;
                if(speed>100)speed-=20;
                good = true;
                while(good){
                    randomX = 1 + rand()%450;
                    randomY = 1 + rand()%450;

                    for(int i = 0; i<9; i++){
                        if(randomX <= (i+1)*50 && randomX > i*50) randomX=(i+1)*50;
                        if(randomY <= (i+1)*50 && randomY > i*50) randomY=(i+1)*50;

                    }
                    for(int i = 0; i < 9; i++){
                        if(randomX == p[i].x && randomY == p[i].y){
                            break;
                        }else if((randomX != p[i].x ||randomY != p[i].y ) && i == size-1){
                            good = false;
                        }
                    }
                }
            }

            red.setPosition(randomX, randomY);
            appWindow.draw(red);

            for(int i = 0; i<size;i++){
                orange.setPosition(p[i].x,p[i].y);
                appWindow.draw(orange);
            }
            appWindow.display();
            Sleep(speed);
        }else if(!gameIsRunning){
            appWindow.draw(fondo);
            refresh.setPosition(100,100);
            appWindow.draw(refresh);
            appWindow.display();
        }

    }
    return 0;
}