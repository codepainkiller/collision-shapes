#include "Circle.h"

Circle::Circle(float x, float y, b2World &world)
{
    m_name = "Circle";
    m_color = sf::Color::White;
    m_radius = m_size.x / 2;

    // Create body Box2D

    b2CircleShape circleShape;
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;

    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius * MPP;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x * MPP, y * MPP);
    m_body = world.CreateBody(&bodyDef);

    fixtureDef.shape = &circleShape;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution	= 0.3f;
    fixtureDef.density	= 0.7f;
    m_body->CreateFixture(&fixtureDef);

    // Create shape SFML
    m_shape.setOrigin(m_size.x / 2, m_size.y /2);
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
}

void Circle::draw(sf::RenderWindow& window)
{
    if (m_body != NULL)
    {
        b2Vec2 position = m_body->GetPosition();
        float  angle = m_body->GetAngle();

        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        window.draw(m_shape);
    }
}
