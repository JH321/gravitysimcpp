#include <n_body_sim.hpp>
#include <settings.hpp>
#include <iostream>
#include <barnes_hut_tree.hpp>

simulation::n_body_sim::n_body_sim() : bodies{}, window(sf::VideoMode(settings::DIMENSIONS.first, settings::DIMENSIONS.second), "N body sim")
, Clock{}
{
    
}

simulation::n_body_sim::~n_body_sim()
{
    for(body* body_ptr : bodies)
    {
        delete body_ptr;
    }
}

void simulation::n_body_sim::init()
{

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

        sf::Vector2u size = window.getSize();

        settings::DIMENSIONS.first = size.x;
        settings::DIMENSIONS.second = size.y;

        float Time = Clock.getElapsedTime().asSeconds();
        
        
        Clock.restart();
        for(body* ptr : bodies)
        {
            ptr -> update_position(bodies, Time);

            sf::CircleShape body_shape(ptr -> get_radius());

            body_shape.setPosition(ptr -> get_position().x - ptr -> get_radius(), ptr -> get_position().y - ptr -> get_radius());
            body_shape.setFillColor(sf::Color::Magenta);
            window.draw(body_shape);

        }
        
        
        std::cout << settings::DIMENSIONS.first << std::endl;
        std::cout << settings::DIMENSIONS.second << std::endl;
        std::cout << Time << std::endl;
        window.display();

        
    }
}

void simulation::n_body_sim::init_barnes_hut()
{


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

        sf::Vector2u size = window.getSize();

        settings::DIMENSIONS.first = size.x;
        settings::DIMENSIONS.second = size.y;

        float Time = Clock.getElapsedTime().asSeconds();
        
        Clock.restart();


        
        b_h_tree body_tree{bodies};

        for(body* ptr : bodies)
        {
            ptr -> update_position_barnes_hut(body_tree, Time);

            sf::CircleShape body_shape(ptr -> get_radius());

            body_shape.setPosition(ptr -> get_position().x - ptr -> get_radius(), ptr -> get_position().y - ptr -> get_radius());
            body_shape.setFillColor(sf::Color::Magenta);
            window.draw(body_shape);
        }
    
        
        std::cout << settings::DIMENSIONS.first << std::endl;
        std::cout << settings::DIMENSIONS.second << std::endl;
        std::cout << Time << std::endl;
        window.display();

        
    }
}

void simulation::n_body_sim::add_body(double _mass, int _radius, bool _inplace, std::pair<double, double> position, std::pair<double, double> velocity)
{
    sf::Vector2<double> init_pos(position.first, position.second);
    sf::Vector2<double> init_vel(velocity.first, velocity.second);

    body* new_body = new body{_mass, _radius, _inplace, init_pos, init_vel};

    bodies.push_back(new_body);

}