#pragma once
#include <glm/glm.hpp>
#include <vector> 

class Particle {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force;
    float density;
    float pressure;
    float radius;
    float mass;
    std::vector<Particle*> neighbors;
    
    Particle(float x, float y, float r);
    void update(float dt);
};