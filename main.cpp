#include <SFML/Graphics.hpp>
#include "GUI.h"

using namespace sf;
using namespace std;

int main() {
    RenderWindow appWindow(VideoMode(500, 500), "Snake");
    GUI gui(&appWindow);
    Event appEvent;

    gui.createTextures();
    gui.setSpritesParameters();

    while(appWindow.isOpen()){
        while(appWindow.pollEvent(appEvent)){
            if(appEvent.type == Event::Closed){
                appWindow.close();
            }
            gui.checkRefreshButton(appEvent);
            gui.checkExitButton(appEvent);
            gui.handleKeyboard(appEvent, gui);
        }
        appWindow.clear(Color(26, 28, 36));
        gui.drawState();
    }
    return 0;
}
