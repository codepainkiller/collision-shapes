#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
    public:
        Rectangle(float x, float y, sf::Vector2f size, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:

        sf::RectangleShape m_shape;
    private:
};

#endif // RECTANGLE_H
