#pragma once

#include <settings.hpp>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace planets
{
  /**
   * @brief  The Body object represents a body that is influenced by gravitational forces.
   *         This class handles all the calculations necessary to simulate gravitational attraction
   *         on a body, keeping track of and updating a body's position, velocity, and acceleration.
   *
   */
  class body
  {
    
    private:

       /**
       * @brief Increments the position of the body given some 
       *        time segment and velocity.
       * 
       * @param dt Time segment from last frame in seconds.
      */
      void increment_position(double dt)
      {
        sf::Vector2<double> delta_x = velocity * dt;
        position = position + delta_x;
      }

      /**
       * @brief Increments the velocity of the body given some 
       *        time segment and acceleration.
       * 
       * @param dt Time segment (time since last frame update) in seconds.
      */
      void increment_velocity(double dt)
      {
        sf::Vector2<double> delta_v = acceleration * dt;
        velocity = velocity + delta_v;
      }
      
      /**
       * @brief Function to call to initiate updating of velocity given 
       *        a vector of other bodies exerting a force on this body and
       *        a small time segment.
       * 
       * @param bodies Vector containing other bodies exerting a force on this body.
       * @param dt Time segment (time since last frame update) in seconds.
      */
      void update_velocity(const std::vector<body*>& bodies, double dt)
      {

        update_acceleration(bodies);
        increment_velocity(dt);

      }

      /**
       * @brief Function to call to initiate updating of acceleration given 
       *        a vector of other bodies exerting a force on this body and
       *        a small time segment.
       * 
       * @param bodies Vector containing other bodies exerting a force on this body.
       * @param dt Time segment (time since last frame update) in seconds.
      */
      void update_acceleration(const std::vector<body*>& bodies)
      {
        sf::Vector2<double> new_acceleration{0, 0};
        for(const body* element : bodies)
        {

          if(element != this)
          {
            sf::Vector2<double> a_vector = calc_accel_bruteforce(element);
            new_acceleration = new_acceleration + a_vector;
          }

        }

        acceleration = new_acceleration;
      }

      /**
       * @brief Calculates the acceleration induced on this body by another body.
       * 
       * @param bodyptr Pointer to the body object inducing an acceleration on this body.
       * @return sf::Vector2<double> The acceleration vector induced on this body.
      */
      sf::Vector2<double> calc_accel_bruteforce(const body* bodyptr)
      {
        double x_dist = bodyptr -> position.x - this -> position.x;
        double y_dist = bodyptr -> position.y - this -> position.y;

        double theta = atan2(y_dist, x_dist);

        double dist_mag = sqrt(pow(x_dist, 2) + pow(y_dist, 2));

        double accel_mult = 1;
        if(dist_mag <= this -> radius + bodyptr -> radius)
        {

          dist_mag = this -> radius + bodyptr -> radius;
          accel_mult = -1;
        }

        double accel_mag = (settings::G * bodyptr -> mass) / (pow(dist_mag, 2));

        accel_mag *= accel_mult;

        sf::Vector2<double> new_acceleration{accel_mag * cos(theta), accel_mag * sin(theta)};

        return new_acceleration;
      }



    public:

      /**
       * @brief Construct a new body object.
       *
       * @param _mass Mass of the body.
       * @param _radius Radius of the body.
       * @param _inplace Whether the body can move.
       * @param _position The starting position of the body.
       * @param _velocity The initial velocity of the body
       */
      body(double _mass, int _radius, bool _inplace, sf::Vector2<double> _position, sf::Vector2<double> _velocity)
      : mass{_mass}, radius{_radius}, inplace{_inplace}, position{_position}, velocity{_velocity}, acceleration{0, 0}
      {}

      /**
       * @brief Gets the radius (pixels) of the body.
       * @return int The radius (pixel count) of the body.
      */
      int get_radius()
      {
        return radius;
      }

      /**
       * @brief Gets the position of the body.
       * @return double The 2D coordinates of the body.
      */
      sf::Vector2<double> get_position()
      {
        return position;
      }


      /**
       * @brief Function to call to initiate updating of position given 
       *        a vector of other bodies exerting a force on this body and
       *        a small time segment.
       * 
       * @param bodies Vector containing other bodies exerting a force on this body.
       * @param dt Time segment (time since last frame update) in seconds.
      */
      void update_position(const std::vector<body*>& bodies, double dt)
      {
        if(!inplace)
        {
          increment_position(dt);
          update_velocity(bodies, dt);
        }


      }


      
    private:

      double mass{};
      int radius{};
      bool inplace{};
      sf::Vector2<double> position{};
      sf::Vector2<double> velocity{};
      sf::Vector2<double> acceleration{};


  };
}
