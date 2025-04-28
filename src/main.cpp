#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Particle.h"
#include "SPHManager.h"
#include <cmath>
#include <random>

const int NUM_PARTICLES = 500;
const float PARTICLE_RADIUS = 5.0f;
const float WALL_LEFT = 50;
const float WALL_RIGHT = 1000;
const float WALL_BOTTOM = 50;
const float WALL_TOP = 1000;
const float ENERGY_LOSS = 0.5f;

std::vector<Particle> particles;

void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)segments;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void initParticles() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-50, 50);
    
    for(int i = 0; i < NUM_PARTICLES; i++) {
        particles.emplace_back(400 + dis(gen), 500 + dis(gen), PARTICLE_RADIUS);
    }
}

void checkWallCollisions() {
    for(auto& p : particles) {
        if(p.position.x - p.radius < WALL_LEFT) {
            p.position.x = WALL_LEFT + p.radius;
            p.velocity.x *= -ENERGY_LOSS;
        }
        if(p.position.x + p.radius > WALL_RIGHT) {
            p.position.x = WALL_RIGHT - p.radius;
            p.velocity.x *= -ENERGY_LOSS;
        }
        if(p.position.y - p.radius < WALL_BOTTOM) {
            p.position.y = WALL_BOTTOM + p.radius;
            p.velocity.y *= -ENERGY_LOSS;
        }
        if(p.position.y + p.radius > WALL_TOP) {
            p.position.y = WALL_TOP - p.radius;
            p.velocity.y *= -ENERGY_LOSS;
        }
    }
}

int main() {
    if(!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "SPH Fluid", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();
    initParticles();

    glOrtho(0, 800, 0, 600, -1, 1);

    float lastTime = glfwGetTime();
    
    while(!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT);
        
        // SPH simulation steps
        SPHManager::findNeighbors(particles);
        SPHManager::computeDensityPressure(particles);
        SPHManager::computeForces(particles);
        
        for(auto& p : particles) {
            p.update(dt);
        }
        checkWallCollisions();

        // Color based on density
        glColor3f(0.2f, 0.6f, 1.0f);
        for(auto& p : particles) {
            float colorIntensity = fmin(p.density / 2000.0f, 1.0f);
            glColor3f(0.2f * colorIntensity, 0.6f * colorIntensity, 1.0f * colorIntensity);
            drawCircle(p.position.x, p.position.y, p.radius, 16);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}