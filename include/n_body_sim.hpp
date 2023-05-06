#pragma once

#include <settings.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include <utility>
#include <body.hpp>
#include <barnes_hut_tree.hpp>

namespace simulation
{
    class n_body_sim
    {
        private:
            std::vector<body*> bodies;
            sf::RenderWindow window;
            sf::Clock Clock;

        public:

            n_body_sim();
            
            ~n_body_sim();

            void init();
            

            void add_body(double _mass, int _radius, bool _inplace = false, std::pair<double, double> position = std::make_pair(0.0, 0.0), std::pair<double, double> velocity = std::make_pair(0.0, 0.0));
            
    };
}