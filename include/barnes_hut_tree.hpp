#pragma once

#include <body.hpp>
#include <vector>
#include <utility>

class b_h_tree
{
    private:

        struct b_h_node
        {
            body* node_body{};

            std::vector<b_h_node*> children{};

            std::vector<body*> body_children{};

            sf::Vector2<double> top_left{};

            int width{};

            int height{};

            int depth{};

            double total_mass{};

            sf::Vector2<double> center_of_mass{};


            bool is_internal()
            {
                return node_body == nullptr && children.size() != 0;
            }

            bool is_external()
            {
                return node_body != nullptr && children.size() == 0;
            }

            bool is_empty()
            {
                return node_body == nullptr && children.size() == 0;
            }

            void update_total_mass()
            {
                double new_total_mass{};
                for(body* body_ptr : body_children)
                {
                    new_total_mass += body_ptr -> get_mass();
                }

                total_mass = new_total_mass;
            }

            void update_center_of_mass()
            {
                sf::Vector2<double> new_center_of_mass{};

                for(body* body_ptr : body_children)
                {
                    new_center_of_mass += ((body_ptr -> get_position()) * body_ptr -> get_mass());
                }

                new_center_of_mass /= total_mass;

                center_of_mass = new_center_of_mass;

            }

            





        };
    };