#include "Shape.h"

Shape::Shape()
{
    m_name = "Shape";
    m_color = sf::Color::Cyan;
    m_size = sf::Vector2f(50.f, 50.0f);
}
void Shape::draw(sf::RenderWindow &window)
{

}

b2Body* Shape::getBody()
{
    return m_body;
}

void Shape::setBody(b2Body* body)
{
    m_body = body;
}
