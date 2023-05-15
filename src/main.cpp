#include <SFML/Graphics.hpp>
#include <settings.hpp>
#include <vector>
#include <iostream>
#include <n_body_sim.hpp>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    simulation::n_body_sim sim{};
    
    for(size_t i = 0; i < 500; ++i)
    {
        sim.add_body(rand() % 500 + 50, 
                    rand() % 10, 
                    false, 
                    std::make_pair(rand() % settings::DIMENSIONS.first, 
                    rand() % settings::DIMENSIONS.second), 
                    std::make_pair(rand() % 10 - 5, rand() % 10 - 5));
    }
    
    sim.init();
    return 0;
}
