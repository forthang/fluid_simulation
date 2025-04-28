#pragma once
#include <vector>
#include "Particle.h"
#include "Kernel.h"

class SPHManager {
public:
    static constexpr float GAS_CONSTANT = 20000.0f;
    static constexpr float VISCOSITY = 20000.0f;
    static constexpr float REST_DENSITY = 10000.0f;
    
    static void computeDensityPressure(std::vector<Particle>& particles);
    static void computeForces(std::vector<Particle>& particles);
    static void findNeighbors(std::vector<Particle>& particles);
};