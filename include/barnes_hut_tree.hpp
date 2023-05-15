#pragma once

#include <vector>
#include <utility>
#include <cmath>
#include <settings.hpp>
#include <SFML/Graphics.hpp>
#include <body.hpp>
#include <memory>

class body;

class b_h_tree
{
    public:

        struct b_h_node
        {
            body* node_body{};

            std::vector<std::shared_ptr<b_h_node>> children{};

            sf::Vector2<int> top_left{};

            int width{};

            int height{};

            int depth{};

            double total_mass{};

            sf::Vector2<double> center_of_mass{};
            
            b_h_node();
    

            b_h_node(sf::Vector2<int> _top_left, int _width, int _height);
            

            bool is_internal();
            

            bool is_external();
            

            bool is_empty();
            

            void update_total_mass();
            

            void update_center_of_mass();
            

            void add_body(body* new_body);
            

            bool in_quadrant(body* b);
            

            void create_children();
            
        };
        
        std::shared_ptr<b_h_node> root;

    public:

        b_h_tree(std::vector<body*> bodies);
        
        sf::Vector2<double> get_accel(body* b) const;

        void insert_node(std::shared_ptr<b_h_node> root, body* new_body);
        

        sf::Vector2<double> calc_accel(std::shared_ptr<b_h_node> root, body* b) const;
         
    };


