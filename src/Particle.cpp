#include "Particle.h"

Particle::Particle(float x, float y, float r) 
    : position(x, y), velocity(0, 0), force(0), 
      density(0), pressure(0), radius(r), mass(r * r * 10.0f) {}

void Particle::update(float dt) {
    velocity += force / density * dt;
    position += velocity * dt;
    force = glm::vec2(0);
}