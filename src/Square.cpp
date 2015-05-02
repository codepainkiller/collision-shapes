#include "Square.h"

Square::Square(b2World &world, sf::Vector2f center)
{
    m_name = "Square";

    // Create body Box2D
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x * MPP, center.y * MPP);
    m_body = world.CreateBody(&bodyDef);

    polygonShape.SetAsBox( m_size.x/2 * MPP, m_size.y/2 * MPP);
    fixtureDef.shape = &polygonShape;
    fixtureDef.friction = 1;
    fixtureDef.restitution	= 1.f;
    fixtureDef.density	= 0.7f;

    m_body->CreateFixture(&fixtureDef);

    // Create shape SFML
    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size.x/2, m_size.y/2);
    m_shape.setFillColor(m_color);
}

void Square::draw(sf::RenderWindow &window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();
        //std::cout << position.x << ", " << position.y << std::endl;
        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        window.draw(m_shape);
    }
}
