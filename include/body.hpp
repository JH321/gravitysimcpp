#pragma once

#include <settings.hpp>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>

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
      body(double _mass, int _radius, bool _inplace, std::pair<double, double> _position, std::pair<double, double> _velocity)
      : mass{_mass}, radius{_radius}, inplace{_inplace}, position{_position}, velocity{_velocity}, acceleration{std::make_pair(0, 0)}
      {}

      int get_radius()
      {
        return radius;
      }

      std::pair<double, double> get_position()
      {
        return position;
      }

      void increment_position(double dt)
      {
        double delta_x = velocity.first * dt;
        double delta_y = velocity.second * dt;

        position = std::make_pair(position.first + delta_x, position.second + delta_y);
      }

      void increment_velocity(double dt)
      {
        double delta_v_x = acceleration.first * dt;
        double delta_v_y = acceleration.second * dt;

        velocity = std::make_pair(velocity.first + delta_v_x, velocity.second + delta_v_y);
      }

      void update_position(const std::vector<body*>& bodies, double dt)
      {
        if(!inplace)
        {
          increment_position(dt);
          update_velocity(bodies, dt);
        }


      }


      void update_velocity(const std::vector<body*>& bodies, double dt)
      {

        update_acceleration(bodies);
        increment_velocity(dt);

      }

      void update_acceleration(const std::vector<body*>& bodies)
      {
        std::pair<double, double> new_acceleration{0, 0};
        for(const body* element : bodies)
        {

          if(element != this)
          {
            std::pair<double, double> a_vector = calc_accel_bruteforce(element);
            new_acceleration = std::make_pair(new_acceleration.first + a_vector.first, new_acceleration.second + a_vector.second);
          }

        }

        acceleration = new_acceleration;
      }

      std::pair<double, double> calc_accel_bruteforce(const body* bodyptr)
      {
        double x_dist = bodyptr -> position.first - this -> position.first;
        double y_dist = bodyptr -> position.second - this -> position.second;

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

        std::pair<double, double> new_acceleration = std::make_pair(accel_mag * cos(theta), accel_mag * sin(theta));

        return new_acceleration;
      }



    private:
      double mass{};
      int radius{};
      bool inplace{};
      std::pair<double, double> position{};
      std::pair<double, double> velocity{};
      std::pair<double, double> acceleration{};


  };
}
