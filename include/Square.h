#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

class Square : public Shape
{
    public:
        Square(float x, float y, b2World &world);

        Square(sf::Vector2f size);

        void draw(sf::RenderWindow &window);

    protected:
        sf::RectangleShape m_shape;

    private:
};

#endif // SQUARE_H
