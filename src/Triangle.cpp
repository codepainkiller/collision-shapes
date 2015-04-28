#include "Triangle.h"

Triangle::Triangle()
{
    m_name = "Triangle";

}

Triangle::Triangle(b2World &world, sf::Vector2f center)
{
    m_name = "Triangle";
    m_radius = m_size.x/2;

    /*
    m_shape = sf::CircleShape(m_radius, 3);
    m_shape.setOrigin(m_size.x / 2, m_size.y /2);
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
    m_shape.setPosition(center);
    */
    m_shape.setPosition(center);
    m_shape.setOrigin(m_size.x /2, m_size.y /2);
    m_shape.setPointCount(3);
    m_shape.setPoint( 0, sf::Vector2f(m_size.x/2, 0) );
    m_shape.setPoint( 1, sf::Vector2f(0, m_size.x) );
    m_shape.setPoint( 2, sf::Vector2f(m_size.x, m_size.x) );


    // Create body Box2D
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    b2BodyDef bodyDef;
    int32 counts = 3;
    b2Vec2 vertex[3];

    float size = m_radius * MPP;
    vertex[0].Set(0, -size);
    vertex[1].Set(-size, size);
    vertex[2].Set(size, size);

    polygonShape.Set(vertex, 3);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(center.x * MPP, center.y * MPP);
    m_body = world.CreateBody(&bodyDef);

    fixtureDef.shape = &polygonShape;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution	= 0.3f;
    fixtureDef.density	= 0.7f;

    m_body->CreateFixture(&fixtureDef);

}

void Triangle::draw(sf::RenderWindow& window)
{
    if (m_body != NULL)
    {
        float angle = m_body->GetAngle();
        b2Vec2 position =  m_body->GetPosition();

        m_shape.setOrigin(m_size.x/2, m_size.y/2);
        m_shape.setPosition(position.x * PPM, position.y * PPM);
        m_shape.setRotation((angle * 180) / M_PI);

        m_shape.setFillColor(m_color);
        window.draw(m_shape);
    }
}
