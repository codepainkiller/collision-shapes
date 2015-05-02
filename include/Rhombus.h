#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Shape.h"

class Rhombus : public Shape
{
    public:

        Rhombus(b2World &world, sf::Vector2f center);

        void draw(sf::RenderWindow &window);

    protected:

        sf::ConvexShape m_shape;

    private:
};

#endif // RHOMBUS_H
