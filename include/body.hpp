#pragma once

#include <settings.hpp>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <barnes_hut_tree.hpp>

  class b_h_tree;

  /**
   * @brief  The Body object represents a body that is influenced by gravitational forces.
   *         This class handles all the calculations necessary to simulate gravitational attraction
   *         on a body, keeping track of and updating a body's position, velocity, and acceleration.
   *
   */
  class body
  {
    private:

      double mass{};
      int radius{};
      bool inplace{};
      sf::Vector2<double> position{};
      sf::Vector2<double> velocity{};
      sf::Vector2<double> acceleration{};


    public:

      
      body(double _mass, int _radius, bool _inplace, sf::Vector2<double> _position, sf::Vector2<double> _velocity = sf::Vector2<double>(0, 0));

      
      int get_radius();

      
      double get_mass();

     
      sf::Vector2<double> get_position();
     
      
      void update_position(const std::vector<body*>& bodies, double dt);

      void update_position_barnes_hut(const b_h_tree& body_tree, double dt);
      
      sf::Vector2<double> calc_accel(const body* bodyptr);
      
     private:

      
      void increment_position(double dt);
      

      
      void increment_velocity(double dt);
      
      
     
      void update_velocity(const std::vector<body*>& bodies, double dt);
      
      void update_velocity_barnes_hut(const b_h_tree& body_tree, double dt);
      
      void update_acceleration(const std::vector<body*>& bodies);
      
      void update_acceleration_barnes_hut(const b_h_tree& body_tree);

      void update_acceleration_brute_force(const std::vector<body*>& bodies);
      

      void update_acceleration_b_h(const std::vector<body*>& bodies);
      



      

  };

