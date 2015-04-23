#ifndef SQUARE_H
#define SQUARE_H

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

#include "Shape.h"

class Square : public Shape
{
    public:
        Square();
        Square(sf::Vector2f size);
        void draw(sf::RenderWindow &window);

    protected:

    private:
};

#endif // SQUARE_H
