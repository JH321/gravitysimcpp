#include <SFML/Graphics.hpp>
#include <settings.hpp>
#include <body.hpp>
#include <vector>
#include <iostream>

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(settings::DIMENSIONS.first, settings::DIMENSIONS.second), "Hello From SFML");

    sf::Clock Clock;
    planets::body p1{50, 5, false, sf::Vector2<double>(60, 60), sf::Vector2<double>(0, 0)};
    planets::body p2{100, 10, false, sf::Vector2<double>(100, 60), sf::Vector2<double>(0, 40)};

    std::vector<planets::body*> bodies{};
    bodies.push_back(&p2);
    bodies.push_back(&p1);

    sf::CircleShape shape1(p1.get_radius());
    window.draw(shape1);
    shape1.setPosition(p1.get_position().x - p1.get_radius(), p1.get_position().y - p1.get_radius());

    sf::CircleShape shape2(p2.get_radius());
    window.draw(shape2);
    shape2.setPosition(p2.get_position().x - p2.get_radius(), p2.get_position().y - p2.get_radius());
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();


        float Time = Clock.getElapsedTime().asSeconds();
        p1.update_position(bodies, Time);
        window.draw(shape1);
        shape1.setPosition(p1.get_position().x - p1.get_radius(), p1.get_position().y - p1.get_radius());
        shape1.setFillColor(sf::Color::Magenta);

        p2.update_position(bodies, Time);
        window.draw(shape2);
        shape2.setPosition(p2.get_position().x - p2.get_radius(), p2.get_position().y - p2.get_radius());

        shape2.setFillColor(sf::Color::Blue);


        window.display();

        Clock.restart();
    }

    return 0;
}
