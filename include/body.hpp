#pragma once

#include <settings.hpp>
#include <utility>

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
      body(double _mass, int _radius, bool _inplace, std::pair<double, double> _position, std::pair<double, double> _velocity, std::pair<double, double> _acceleration)
      : mass{_mass}, radius{_radius}, inplace{_inplace}, position{_position}, velocity{_velocity}, acceleration{_acceleration}
      {}

    private:
      double mass{};
      int radius{};
      bool inplace{};
      std::pair<double, double> position{};
      std::pair<double, double> velocity{};
      std::pair<double, double> acceleration{};


  };
}
