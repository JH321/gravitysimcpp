#include <settings.hpp>
#include <utility>

namespace planets
{
  class body
  {

    public:

    private:
      double mass{};
      int radius{};
      std::pair<double, double> position{};
      std::pair<double, double> velocity{};
      std::pair<double, double> acceleration{};


  };
}
