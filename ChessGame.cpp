#include "ChessBoardState.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess Game");

    ChessBoardState chessBoardState;
    chessBoardState.initialize();

    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            chessBoardState.handleInput(window, event);
        }

        window.clear();
        chessBoardState.draw(window);
        window.display();
    }

    return 0;
}