#include "Square.h"

Square::Square()
{
    m_name = "Square";
    //m_size = sf::Vector2f(50.f, 50.f);
    std::cout << m_name << ": constructor" << std::endl;
}
Square::Square(sf::Vector2f size)
{
    m_name = "Square";
    m_size = size;
    std::cout << m_name << ": constructor" << std::endl;
}

void Square::draw(sf::RenderWindow &window) {

    sf::RectangleShape rectCaja(m_size);
    rectCaja.setOrigin(m_size.x/2, m_size.y/2);
    rectCaja.setFillColor(m_color);

    float angle = m_body->GetAngle();
    b2Vec2 pos =  m_body->GetPosition();

    rectCaja.setPosition(pos.x * PPM, pos.y * PPM);
    rectCaja.setRotation((angle * 180) / M_PI);

    window.draw(rectCaja);

}
