#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
    public:
        Circle(b2World &world, sf::Vector2f center);

        void draw(sf::RenderWindow &window);

    protected:
        float           m_radius;
        sf::CircleShape m_shape;
    private:
};

#endif // CIRCLE_H
