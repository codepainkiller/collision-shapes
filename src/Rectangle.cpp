#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, sf::Vector2f size, b2World& world)
{
    m_name = "Rectangle";
    m_size = size;
    m_color = sf::Color::Green;

    // Create body static box2D
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x * MPP, y * MPP);
    m_body = world.CreateBody(&bodyDef);

    polygonShape.SetAsBox( m_size.x/2 * MPP, m_size.y/2 * MPP);
    fixtureDef.shape = &polygonShape;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution	= 0.3f;
    fixtureDef.density	= 0.7f;

    m_body->CreateFixture(&fixtureDef);

    // Create shape SFML
    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size.x/2, m_size.y/2);
    m_shape.setFillColor(m_color);
}

void Rectangle::draw(sf::RenderWindow &window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();

        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        window.draw(m_shape);
    }
}
