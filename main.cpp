#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "SFMLDebugDraw.h"
#include "Shape.h"
#include "Square.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <iostream>
#include <ctime>

#define TIMESTEP 1.0f/60.0f     //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION

#define WIDTH 800
#define HEIGHT 600

using namespace std;

int randomNumber(int min, int max)
{
    srand(time(0));
    return min + rand()% (max - min);
}

int main()
{
    // Define world Box2D
    b2World world(b2Vec2(0, 9.8f));

    std::vector<Shape* > m_shapeVector;

    // Create body's static
    m_shapeVector.push_back(new Rectangle(400.f, 0.f, sf::Vector2f(800.f, 1.f), world));
    m_shapeVector.push_back(new Rectangle(400.f, 600.f, sf::Vector2f(800.f, 1.f), world));
    m_shapeVector.push_back(new Rectangle(0.f, 300.f, sf::Vector2f(1.f, 800.f), world));
    m_shapeVector.push_back(new Rectangle(800.f, 300.f, sf::Vector2f(1.f, 800.f), world));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Shapes", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    // Initialize Debug draw
    SFMLDebugDraw debugDraw(window);
    world.SetDebugDraw(&debugDraw);

    // Set initial flags for what to draw
    debugDraw.SetFlags(b2Draw::e_shapeBit);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Q) )
            {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
			{
				if(debugDraw.GetFlags() & b2Draw::e_shapeBit) debugDraw.ClearFlags(b2Draw::e_shapeBit);
				else debugDraw.AppendFlags(b2Draw::e_shapeBit);
			}
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
			{
				if(debugDraw.GetFlags() & b2Draw::e_aabbBit) debugDraw.ClearFlags(b2Draw::e_aabbBit);
				else debugDraw.AppendFlags(b2Draw::e_aabbBit);
			}
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
			{
				if(debugDraw.GetFlags() & b2Draw::e_centerOfMassBit) debugDraw.ClearFlags(b2Draw::e_centerOfMassBit);
				else debugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
			}

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    Square* square = new Square(position.x, position.y, world);
                    m_shapeVector.push_back(square);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //Circle* circle = new Circle(position.x, position.y, world);
                    //m_shapeVector.push_back(circle);
                    //Rectangle* rectangle = new Rectangle(position.x, position.y, sf::Vector2f(100.0f, 50.0f), world);
                    //m_shapeVector.push_back(rectangle);

                    Triangle* triangle = new Triangle(world, position);
                    m_shapeVector.push_back(triangle);
                }
            }
        }

        // Update window
        window.clear(sf::Color::White);

        // Update word
        world.Step(TIMESTEP, VELITER, POSITER);

        // Draw vector shapes

        for (unsigned i = 0; i < m_shapeVector.size(); i++)
        {
            m_shapeVector.at(i)->draw(window);
        }

        world.DrawDebugData();

        window.display();
    }

    return 0;
}
