#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;

int game = 1, dir = 0, speed = 500, size = 1;
struct Point{
    int x = 0;
    int y = 0;
}p[100];

int main() {
    RenderWindow appWindow(VideoMode(500, 500), "Snake");
    Event appEvent;

    Texture squaret, refresht, backgroundt;
    squaret.loadFromFile("square.png");
    refresht.loadFromFile("refresh.png");
    backgroundt.loadFromFile("background.png");

    Sprite orange(squaret), refresh(refresht), red(squaret), fondo(backgroundt);
    orange.setPosition(0,0);
    orange.setColor(Color(255, 120, 0));
    red.setPosition(1000, 0);
    red.setColor(Color(255,0,36));

    while(appWindow.isOpen()){
        while(appWindow.pollEvent(appEvent)){
            if(appEvent.type == Event::Closed){
                appWindow.close();
            }
            if(appEvent.type == Event::KeyPressed){
                if(game == 1){
                    if(appEvent.key.code == Keyboard::Right && dir != 1) dir = 0;
                    else if(appEvent.key.code == Keyboard::Left && dir != 0) dir = 1;
                    else if(appEvent.key.code == Keyboard::Down && dir != 3) dir = 2;
                    else if(appEvent.key.code == Keyboard::Up && dir != 2) dir = 3;

                }
            }
        }
        appWindow.clear(Color(26, 28, 36));

        if(game == 1){
            refresh.setPosition(1000,0);
            appWindow.draw(fondo);
            if(dir == 0) p[0].x += 50;
            if(dir == 1) p[0].x -= 50;
            if(dir == 2) p[0].y += 50;
            if(dir == 3) p[0].y -= 50;

            for(int i = 0; i<size;i++){
                orange.setPosition(p[i].x,p[i].y);
                appWindow.draw(orange);
            }
        }
        appWindow.display();
        Sleep(speed);

    }

    return 0;
}