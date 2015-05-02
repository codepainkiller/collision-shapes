#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

class Square : public Shape
{
    public:
        Square(b2World &world, sf::Vector2f center);

        Square(sf::Vector2f size);

        void draw(sf::RenderWindow &window);

    protected:
        sf::RectangleShape m_shape;

    private:
};

#endif // SQUARE_H
