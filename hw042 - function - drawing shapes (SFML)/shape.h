#include <memory>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

enum class ShapeType {
    RECT,
    CIRCLE
};

struct Point {
    int x;
    int y;
};

struct Shape {
    int id;
    ShapeType type;
    Point pos1;
    Point pos2;
    Point center;
    int radius;
    double area;
    std::shared_ptr<sf::RectangleShape> rect = std::make_shared<sf::RectangleShape>();
    std::shared_ptr<sf::CircleShape> circle = std::make_shared<sf::CircleShape>();
};

void create_rectangle(Point& pos1, Point& pos2);
void create_circle(Point& center, int radius);
void move_shape(int id, int x, int y);
void sort_shapes();
int find_furthest_shape();
void remove_shape_by_id(int id);
void align_shapes();
void print_shapes();
void draw_shapes(sf::RenderWindow& window);