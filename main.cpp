#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Shape.h"
#include "Square.h"
#include "Circle.h"

#include <iostream>

#define TIMESTEP 1.0f/60.0f     //TIEMPO DE REFRESCO
#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION

#define PPM 64.0f               //PIXELS POR METRO
#define MPP (1.0f/PPM)          //METROS POR PIXEL

using namespace std;



int main()
{
    std::vector<Shape* > m_shapeVector;

    // Define world Box2D
    b2World world(b2Vec2(0.0f, 10.0f));

    // Define static ground
    b2BodyDef sueloBodyDef;
    sueloBodyDef.position.Set(400.0f*MPP, 550.0f*MPP);
    b2Body* sueloBody = world.CreateBody(&sueloBodyDef);
    b2PolygonShape sueloBox;
    sueloBox.SetAsBox(800.0f/2*MPP, 100.0f/2*MPP);
    sueloBody->CreateFixture(&sueloBox, 0.0f);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Shapes", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

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
                    Circle* circle = new Circle(position.x, position.y, world);
                    m_shapeVector.push_back(circle);
                }
            }
        }

        // Update window
        window.clear(sf::Color::Black);
        // Update word
        world.Step(TIMESTEP, VELITER, POSITER);

        // Draw vector shapes
        for (unsigned i = 0; i < m_shapeVector.size(); i++)
        {
            m_shapeVector.at(i)->draw(window);
        }

        // Draw ground
        sf::RectangleShape rectSuelo(sf::Vector2f(800, 100));
        rectSuelo.setOrigin(800/2, 100/2);
        rectSuelo.setPosition(sf::Vector2f(sueloBody->GetPosition().x*PPM, sueloBody->GetPosition().y*PPM));
        rectSuelo.setFillColor(sf::Color::Red);
        window.draw(rectSuelo);

        window.display();
    }

    return 0;
}
