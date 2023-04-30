#include <settings.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <utility>

namespace simulation
{
    class n_body_sim
    {
        private:
            std::vector<body*> bodies;
            sf::RenderWindow window;
            sf::Clock Clock;

        public:

            n_body_sim() : bodies{}, window(sf::VideoMode(settings::DIMENSIONS.first, settings::DIMENSIONS.second), "N body sim")
            , Clock{}
            {
                
            }

            void init()
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


                    float Time = Clock.getElapsedTime().asSeconds();

                    for(body* ptr : bodies)
                    {
                        ptr -> update_position(bodies, Time);

                        sf::CircleShape body_shape(ptr -> get_radius());

                        body_shape.setPosition(ptr -> get_position().x - ptr -> get_radius(), ptr -> get_position().y - ptr -> get_radius());
                        body_shape.setFillColor(sf::Color::Magenta);
                        window.draw(body_shape);

                    }
                    window.display();

                    Clock.restart();
                }
            }

            void add_body(double _mass, int _radius, bool _inplace = false, std::pair<double, double> position = std::make_pair(0.0, 0.0), std::pair<double, double> velocity = std::make_pair(0.0, 0.0))
            {
                sf::Vector2<double> init_pos(position.first, position.second);
                sf::Vector2<double> init_vel(velocity.first, velocity.second);

                body* new_body = new body{_mass, _radius, _inplace, init_pos, init_vel};

                bodies.push_back(new_body);

            }
    };
}