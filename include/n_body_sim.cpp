#include <n_body_sim.hpp>
#include <settings.hpp>
#include <iostream>
#include <barnes_hut_tree.hpp>
#include <cmath>

/**
 * @brief Constructs a n_body_sim object.
*/
simulation::n_body_sim::n_body_sim() : bodies{}, window(sf::VideoMode(settings::DIMENSIONS.first, settings::DIMENSIONS.second), "N body sim")
, Clock{}
{
    
}

/**
 * @brief Destructor for the n_body_sim object, cleans up dynamically allocated memory.
*/
simulation::n_body_sim::~n_body_sim()
{
    for(body* body_ptr : bodies)
    {
        delete body_ptr;
    }
}

/**
 * @brief Initializes a n body sim with an inputted number of bodies. The bodies have random mass, random radius, and
 *        random initial positions and initial velocities.
 * @param num_bodies The number of bodies in the n body sim.
 * @param b_h_flag True if a simulation using the Barnes Hut method is desired, false if a naive simulation is desired.
*/
void simulation::n_body_sim::random_sim_init(size_t num_bodies, bool b_h_flag)
{
    for(size_t i = 0; i < num_bodies; ++i)
    {
        add_body(rand() % 500 + 50, 
                    rand() % 9 + 1, 
                    false, 
                    std::make_pair(rand() % settings::DIMENSIONS.first, 
                    rand() % settings::DIMENSIONS.second), 
                    std::make_pair(rand() % 10 - 5, rand() % 10 - 5));
    }

    if(b_h_flag)
    {
        init_barnes_hut();
    }
    else
    {
        init();
    }
}

/**
 * @brief Initializes a n body sim with circular orbit.
 * @param b_h_flag True if a simulation using the Barnes Hut method is desired, false if a naive simulation is desired.
*/
void simulation::n_body_sim::circular_orbit(bool b_h_flag)
{
    double m1 = 50;
    double m2 = 100;

    int r1 = static_cast<int>(m1) / 10;
    int r2 = static_cast<int>(m2) / 10;

    int pos_diff = rand() % 50 + 50;
    
    add_body(m1, r1, false, std::make_pair<double, double>(settings::DIMENSIONS.first / 2.0 + pos_diff, settings::DIMENSIONS.second / 2.0), std::make_pair<double, double>(0, -sqrt((m2 * settings::G) / pos_diff)));
    add_body(m2, r2, true, std::make_pair<double, double>(settings::DIMENSIONS.first / 2.0, settings::DIMENSIONS.second / 2.0), std::make_pair<double, double>(0, 0));
    
    init();
}

/**
 * @brief Initializes a naive n body simulation.
*/
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

/**
 * @brief Initializes a simulation using the Barnes Hut method of approximation.
*/
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

/**
 * @brief Adds a body to the simulation. 
 * @param _mass The mass of the body being added.
 * @param _radius The radius of the body being added.
 * @param _inplace Whether the body being added is in place.
 * @param position The initial position of the body being added.
 * @param velocity The initial velocity of the body being added.
*/
void simulation::n_body_sim::add_body(double _mass, int _radius, bool _inplace, std::pair<double, double> position, std::pair<double, double> velocity)
{
    sf::Vector2<double> init_pos(position.first, position.second);
    sf::Vector2<double> init_vel(velocity.first, velocity.second);

    body* new_body = new body{_mass, _radius, _inplace, init_pos, init_vel};

    bodies.push_back(new_body);

}