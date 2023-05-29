#pragma once

#include <settings.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <utility>
#include <body.hpp>
#include <barnes_hut_tree.hpp>


namespace simulation
{
    /**
     * @brief The n_body_sim class represents an n body simulation. It provides the functionality for initializing
     *        an n body simulation in an encapsulated way.
    */
    class n_body_sim
    {
        private:
            std::vector<body*> bodies;
            sf::RenderWindow window;
            sf::Clock Clock;

            void init();
            
            void init_barnes_hut();

            void add_body(double _mass, int _radius, bool _inplace = false, std::pair<double, double> position = std::make_pair(0.0, 0.0), std::pair<double, double> velocity = std::make_pair(0.0, 0.0));

        public:

            n_body_sim();
            
            ~n_body_sim();

            void random_sim_init(size_t num_bodies, bool b_h_flag);

           
    };
}