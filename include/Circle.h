#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
    public:
        Circle(float x, float y, b2World &world);

        void draw(sf::RenderWindow &window);

    protected:
        float           m_radius;
        sf::CircleShape m_shape;
    private:
};

#endif // CIRCLE_H
