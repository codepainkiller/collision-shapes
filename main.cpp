#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "SFMLDebugDraw.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rhombus.h"

#include <iostream>
#include <ctime>

#define TIMESTEP 1.0f/60.0f     // Refresh time
#define VELITER 10              // Number of iterations per tick to calculate speed
#define POSITER 10              // Number tick iterations to calculate the position

#define WIDTH 800
#define HEIGHT 600

using namespace std;

int randomNumber(int min, int max)
{
    return min + rand()% (max - min + 1);
}

void createShape(vector<Shape* > &vectorShapes, b2World &world, int numberShape)
{
    if (numberShape < 1 || numberShape > 4)
        return;

    Shape*          shape;
    b2Body*         body;
    sf::Vector2f    position;

    position.x = randomNumber(50, WIDTH - 50);
    position.y = randomNumber(50, HEIGHT - 50);

    switch( numberShape )
    {
        case 1:
            shape = static_cast<Square*>( new Square(world, position) );
            break;

        case 2:
            shape = static_cast<Circle*>( new Circle(world, position) );
            break;

        case 3:
            shape = static_cast<Triangle*>( new Triangle(world, position) );
            break;

        case 4:
            shape = static_cast<Rhombus*>( new Rhombus(world, position) );
            break;
    }

    // Add shape
    vectorShapes.push_back(shape);

    // Initial move
    b2Vec2 force;
    force.x = randomNumber(-100, 100);
    force.y = randomNumber(-100, 100);

    body = vectorShapes.back()->getBody();
    body->ApplyForce(force, body->GetWorldCenter(), true);
}

void showInstructions()
{
    cout << endl << endl;

    cout << " INSTRUCTIONS             "            << endl << endl;

    cout << " Draw square       : Key 1"            << endl;
    cout << " Draw circle       : Key 2"            << endl;
    cout << " Draw triangle     : Key 3"            << endl;
    cout << " Draw rhombus      : Key 4"            << endl;
    cout << " Random movement   : Key 5"            << endl << endl;

    cout << " Debug draw        : Keys F1, F2, F3";
}

int main()
{
    srand(time(0));

    // Instructions
    showInstructions();

    // Define world Box2D - Zero gravity
    b2World m_world(b2Vec2(0.f, 0.f));

    std::vector<Shape* > m_vectorShapes;

    // Create walls - static bodies
    m_vectorShapes.push_back(new Rectangle(400.f, 0.f, sf::Vector2f(800.f, 1.f), m_world));
    m_vectorShapes.push_back(new Rectangle(400.f, 600.f, sf::Vector2f(800.f, 1.f), m_world));
    m_vectorShapes.push_back(new Rectangle(0.f, 300.f, sf::Vector2f(1.f, 800.f), m_world));
    m_vectorShapes.push_back(new Rectangle(800.f, 300.f, sf::Vector2f(1.f, 800.f), m_world));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow m_window(sf::VideoMode(800, 600), "Collision Shapes", sf::Style::Default, settings);
    m_window.setFramerateLimit(60);

    // Initialize Debug draw
    SFMLDebugDraw debugDraw(m_window);
    m_world.SetDebugDraw(&debugDraw);

    // Set initial flags for what to draw
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if ( event.type == sf::Event::KeyReleased )
            {
                // Create shapes
                if (event.key.code == sf::Keyboard::Num1)
                    createShape(m_vectorShapes, m_world, 1);

                if (event.key.code == sf::Keyboard::Num2)
                    createShape(m_vectorShapes, m_world, 2);

                if (event.key.code == sf::Keyboard::Num3)
                    createShape(m_vectorShapes, m_world, 3);

                if (event.key.code == sf::Keyboard::Num4)
                    createShape(m_vectorShapes, m_world, 4);

                // Move shape
                if (event.key.code == sf::Keyboard::Space)
                {
                    int nShapes = m_vectorShapes.size();

                    if (nShapes > 4)
                    {
                        int randShape = randomNumber(5, nShapes);
                        b2Vec2 force(randomNumber(-100, 100), randomNumber(-100, 100));

                        b2Body* body = m_vectorShapes.at(randShape - 1)->getBody();
                        body->ApplyForce( force, body->GetWorldCenter(), true );
                    }
                }

                // Close application
                if (event.key.code == sf::Keyboard::Escape)
                    m_window.close();

                // Debug draw shapes
                if(event.key.code == sf::Keyboard::F1)
                {
                    if(debugDraw.GetFlags() & b2Draw::e_shapeBit) debugDraw.ClearFlags(b2Draw::e_shapeBit);
                    else debugDraw.AppendFlags(b2Draw::e_shapeBit);
                }
                if(event.key.code == sf::Keyboard::F2)
                {
                    if(debugDraw.GetFlags() & b2Draw::e_aabbBit) debugDraw.ClearFlags(b2Draw::e_aabbBit);
                    else debugDraw.AppendFlags(b2Draw::e_aabbBit);
                }
                if(event.key.code == sf::Keyboard::F3)
                {
                    if(debugDraw.GetFlags() & b2Draw::e_centerOfMassBit) debugDraw.ClearFlags(b2Draw::e_centerOfMassBit);
                    else debugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
                }
            }
        }

        // Update window
        m_window.clear(sf::Color::Transparent);

        // Update world Box2D
        m_world.Step(TIMESTEP, VELITER, POSITER);

        // Draw vector shapes
        for (unsigned i = 0; i < m_vectorShapes.size(); i++)
            m_vectorShapes.at(i)->draw(m_window);

        // Debug draw display
        m_world.DrawDebugData();

        // Render window
        m_window.display();
    }

    return 0;
}
