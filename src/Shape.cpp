#include "Shape.h"

Shape::Shape()
{
    m_name = "Shape";
    m_color = sf::Color::White;
    std::cout << m_name << ": constructor" << std::endl;
}
void Shape::draw(sf::RenderWindow &window){

}

b2Body* Shape::getBody()
{
    return m_body;
}

void Shape::setBody(b2Body* body)
{
    m_body = body;
}
