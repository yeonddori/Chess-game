#include "shape.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>

std::vector<Shape> shape_list;
int next_id = 0;

void create_rectangle(Point& pos1, Point& pos2){
    std::unique_ptr<Shape> rectangle = std::make_unique<Shape>();
    rectangle->id = next_id++;
    rectangle->type = ShapeType::RECT;
    rectangle->pos1 = pos1;
    rectangle->pos2 = pos2;
    rectangle->center.x = (pos2.x-pos1.x)/2;
    rectangle->center.y = (pos2.y-pos1.y)/2;
    rectangle->area = (pos2.x-pos1.x) * (pos2.y-pos1.y);
    shape_list.push_back(*rectangle);
}

void create_circle(Point& center, int radius){
    std::unique_ptr<Shape> circle = std::make_unique<Shape>();
    circle->id = next_id++;
    circle->type = ShapeType::CIRCLE;
    circle->center = center;
    circle->radius = radius;
    circle->area = 3.14159 * radius * radius;
    shape_list.push_back(*circle);
}

void move_shape(int id, int x, int y){
    auto move = std::find_if(shape_list.begin(), shape_list.end(), [id](auto t){return t.id == id;});
    if(move->type == ShapeType::RECT){
        move->center.x += x;
        move->center.y += y;
    }
    else{
        move->center.x += x;
        move->center.y += y;
    }
}

void sort_shapes(){
    std::sort(shape_list.begin(), shape_list.end(), [](auto a, auto b){return a.area < b.area;});
}

int find_furthest_shape(){
    auto length = std::max_element(shape_list.begin(), shape_list.end(), [](auto a, auto b){
        return a.center.x * a.center.x + a.center.y * a.center.y < b.center.x * b.center.x + b.center.y * b.center.y;});
    if(length->type == ShapeType::RECT)
        std::cout << "ID: " << length->id << ", Type: RECT, Position: (" << length->center.x << ", " << length->center.y << "), Width: " <<
                length->pos2.x - length->pos1.x << ", Height: " << length->pos2.y - length->pos1.y << ", Area: " << length->area << std::endl;
    else std::cout << "ID: " << length->id << ", Type: CIRCLE, Center: (" << length->center.x << ", " << length->center.y << "), Radius: " <<
                length->radius << ", Area: " << length->area << std::endl;
}

void remove_shape_by_id(int id){
    shape_list.erase(std::remove_if(shape_list.begin(), shape_list.end(), [id](auto t){return t.id == id;}), shape_list.end());

}

void align_shapes(){
    std::sort(shape_list.begin(), shape_list.end(), [](auto a, auto b){return a.area < b.area;});
    int current_x=0, max_width=0, half_width;
    for(auto &i: shape_list){
        i.center.x = 0;
        i.center.y = 0;
        if(i.type == ShapeType::RECT){
            half_width = (i.pos2.x - i.pos1.x) / 2;
            if(current_x + half_width > current_x + max_width) {
                current_x += half_width;
            }
            else{
                current_x += max_width;
                max_width = half_width;
            }
        }
        else{
            half_width = i.radius;
            if(current_x + i.radius > current_x + max_width) {
                current_x += half_width;
                max_width = half_width;
            }
            else{
                current_x += max_width;
                max_width = half_width;
            }
        }
        move_shape(i.id, current_x, current_x);
        current_x += half_width;
    }
}

void print_shapes(){
    for(const auto &i: shape_list){
        if(i.type == ShapeType::RECT)
            std::cout << "ID: " << i.id << ", Type: RECT, Position: (" << i.center.x << ", " << i.center.y << "), Width: " <<
                      i.pos2.x - i.pos1.x << ", Height: " << i.pos2.y - i.pos1.y << ", Area: " << std::fixed << std::setprecision(2) <<i.area << std::endl;
        else std::cout << "ID: " << i.id << ", Type: CIRCLE, Center: (" << i.center.x << ", " << i.center.y << "), Radius: " <<
                       i.radius << ", Area: " << std::fixed << std::setprecision(2) << i.area << std::endl;
    }
}

void draw_shapes(sf::RenderWindow& window) {
    for (auto& shape : shape_list) {
        if (shape.type == ShapeType::RECT) {
            shape.rect->setSize(sf::Vector2f(shape.pos2.x - shape.pos1.x, shape.pos2.y - shape.pos1.y));
            shape.rect->setPosition(shape.center.x - (shape.pos2.x - shape.pos1.x)/2, shape.center.y - (shape.pos2.y - shape.pos1.y)/2);
            shape.rect->setFillColor(sf::Color::White);
            window.draw(*shape.rect);
        } else {
            shape.circle->setRadius(shape.radius);
            shape.circle->setPosition(shape.center.x - shape.radius, shape.center.y - shape.radius);
            shape.circle->setFillColor(sf::Color::White);
            window.draw(*shape.circle);
        }
        std::shared_ptr<sf::CircleShape> point = std::make_shared<sf::CircleShape>();
        point->setRadius(5);
        point->setPosition(shape.center.x-5, shape.center.y-5);
        point->setFillColor(sf::Color::Black);
        window.draw(*point);
    }
}