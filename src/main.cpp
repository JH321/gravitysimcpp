#include <settings.hpp>
#include <vector>
#include <iostream>
#include <n_body_sim.hpp>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    simulation::n_body_sim sim{};
    
    //sim.random_sim_init(25, true);

    sim.circular_orbit(true);
    return 0;
}
