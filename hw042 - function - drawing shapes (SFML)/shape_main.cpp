#include "shape.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Drawing Shapes");
    sf::View view(sf::FloatRect(0, SCREEN_HEIGHT, SCREEN_WIDTH, -SCREEN_HEIGHT));
    window.setView(view);

    bool isQuit = false;
    while(window.isOpen()&&!isQuit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        while (!isQuit) {
            std::string command;
            std::cin >> command;
            if (command == "RECT") {
                Point pos1, pos2;
                std::cin >> pos1.x >> pos1.y >> pos2.x >> pos2.y;
                create_rectangle(pos1, pos2);
            } else if (command == "CIRCLE") {
                Point center;
                int radius;
                std::cin >> center.x >> center.y >> radius;
                create_circle(center, radius);
            } else if (command == "MOVE") {
                int id, x, y;
                std::cin >> id >> x >> y;
                move_shape(id, x, y);
            }
            else if (command == "SORT") sort_shapes();
            else if (command == "MAX") find_furthest_shape();
            else if (command == "REMOVE") {
                int id;
                std::cin >> id;
                remove_shape_by_id(id);
            }
            else if (command == "ALIGN") align_shapes();
            else if (command == "PRINT") print_shapes();

            else if (command == "DRAW") {
                window.clear();
                draw_shapes(window);
                window.display();
            }
            else if (command == "QUIT") isQuit = true;
            else std::cout << "Invalid command." << std::endl;
        }
    }
    return 0;
}