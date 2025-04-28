#include "SPHManager.h"
#include <algorithm>

void SPHManager::findNeighbors(std::vector<Particle>& particles) {
    for(auto& p : particles) {
        p.neighbors.clear();
        for(auto& other : particles) {
            if(&p == &other) continue;
            glm::vec2 r = p.position - other.position;
            if(glm::dot(r, r) < SPH::KERNEL_RADIUS * SPH::KERNEL_RADIUS) {
                p.neighbors.push_back(&other);
            }
        }
    }
}

void SPHManager::computeDensityPressure(std::vector<Particle>& particles) {
    for(auto& p : particles) {
        p.density = 0.0f;
        for(auto& neighbor : p.neighbors) {
            glm::vec2 r = p.position - neighbor->position;
            p.density += neighbor->mass * SPH::poly6Kernel(r, SPH::KERNEL_RADIUS);
        }
        p.density = fmax(p.density, REST_DENSITY);
        p.pressure = GAS_CONSTANT * (p.density - REST_DENSITY);
    }
}

void SPHManager::computeForces(std::vector<Particle>& particles) {
    for(auto& p : particles) {
        glm::vec2 pressureForce(0.0f);
        glm::vec2 viscosityForce(0.0f);
        
        for(auto& neighbor : p.neighbors) {
            // Pressure force
            glm::vec2 r = p.position - neighbor->position;
            pressureForce += -neighbor->mass * (p.pressure + neighbor->pressure) / 
                            (2.0f * neighbor->density) * SPH::spikyGradKernel(r, SPH::KERNEL_RADIUS);
            
            // Viscosity force
            viscosityForce += VISCOSITY * neighbor->mass * (neighbor->velocity - p.velocity) / 
                             neighbor->density * SPH::viscLaplacianKernel(r, SPH::KERNEL_RADIUS);
        }
        
        // Gravity force
        glm::vec2 gravityForce = glm::vec2(0, -9.81f) * p.density;
        
        p.force = pressureForce + viscosityForce + gravityForce;
    }
}